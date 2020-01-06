/**
	@page chapter_jit_networking Jitter Networking Specification

This appendix describes the format of the data sent by a jit.net.send object.
The object attempts to form a TCP connection with a host at the IP and port specified by the object's attributes.
Any program wishing to receive data will therefore have to set itself up as a host and listen for incoming TCP connections.

Once a connection is formed, data can be sent.
Data is sent as a stream of chunks.
The first thing received will be a chunk header.
It consists of a 32-bit chunk ID and a 32-bit int representing the size of the next chunk to come.
The chunk ID can be one of the following 4-char symbols, depending on what kind of packet it is:

@code
#define JIT_MATRIX_PACKET_ID  'JMTX'
#define JIT_MATRIX_LATENCY_PACKET_ID  'JMLP'
#define JIT_MESSAGE_PACKET_ID  'JMMP'
@endcode

This chunk header could be represented in C by the following struct:
@code
typedef struct _jit_net_packet_header
{
   t_int32 id;
   t_int32 size; //size of packet to come
} t_jit_net_packet_header;
@endcode

If the chunk is a matrix packet, the next data received will be a header of 288 bytes with the following contents:

<table>
	<tr><td>id	 			</td><td>'JMTX'                                                             </td></tr>
	<tr><td>Size	 		</td><td>288 (32-bit int, size of this header)                           	</td></tr>
	<tr><td>Planecount		</td><td>32-bit int                                                   		</td></tr>
	<tr><td>Type	 		</td><td>32-bit int, 0 for char, 1 for long, 2 for float32, 3 for float64	</td></tr>
	<tr><td>Dimcount		</td><td>32-bit int                                                   		</td></tr>
	<tr><td>Dim	 			</td><td>Array of 32 32-bit ints                                            </td></tr>
	<tr><td>Dimstride		</td><td>Array of 32 32-bit ints                                      		</td></tr>
	<tr><td>Datasize		</td><td>32-bit int, size of the data buffer to come                  		</td></tr>
	<tr><td>Time	 		</td><td>64-bit double precision float                                    	</td></tr>
</table>

This chunk could be represented with the following C struct:

@code
typedef struct _jit_net_packet_matrix
{
	t_int32	id;
	t_int32	size;
	t_int32	planecount;
	t_int32	type;			//0=char,1=long,2=float32,3=float64
	t_int32	dimcount;
	t_int32	dim[JIT_MATRIX_MAX_DIMCOUNT];
	t_int32	dimstride[JIT_MATRIX_MAX_DIMCOUNT];
	t_int32	datasize;
	double	time;
} t_jit_net_packet_matrix;
@endcode

Following this header the next data received will be the matrix data, the size of which was passed in the above header. When using the data, please note the dimstrides transmitted in the header.

The time field in the above header will be set to the time of transmission from the sending computer. jit.net.send expects the server to respond by sending back timing data of its own – it uses this data to estimate the transmission latency. The exact data in the latency chunk that jit.net.send expects to receive is the following:

<table>
	<tr><td>id	 						</td><td>'JMLP'   																					</td></tr>
	<tr><td>client_time_original	 	</td><td>64-bit double, the time value received in the matrix header packet                     	</td></tr>
	<tr><td>server_time_before_data	 	</td><td>64-bit double, the time on the server when the packet header is received               	</td></tr>
	<tr><td>server_time_after_data	 	</td><td>64-bit double, the time on the server after the packet has been processed and is in use	</td></tr>
	<tr><td>
</table>

This chunk can be represnted by the following C struct:

@code
typedef struct _jit_net_packet_latency
{
   t_int32 id;
   double client_time_original;
   double server_time_before_data;
   double server_time_after_data;
} t_jit_net_packet_latency;
@endcode

The difference between the server time before and server time after processing the data represents the time it takes the server to mobilize the data after it has been received. jit.net.send will send and expects to receive time in milliseconds. When this timing information is received by the transmitting computer, it notes its current time, calculates the round trip time and then estimates the latency as half the round trip time plus half of the server processing time. This estimate is accurate if the time of flight from A to B is the same as the time of flight from B to A, but network topology can be very complicated, and often the route from A to B is not the reverse of the route from B to A. In simple situations, such as a direct connection between two computers or a small LAN, the estimate should be reasonably accurate.

Finally, the last type of packet that can be sent is the message packet.
The size of the message packet is sent in the initial header packet.
Standard #A_GIMME messages (t_symbol *s, long ac, t_atom *av) are serialized starting with a 32-bit integer that contains the size of the serialized message in bytes.
Following that another 32-bit integer gives the argument count for the atoms.
Following that comes the message atoms themselves, starting with the leading symbol if it exists.
Each atom is represented in memory first with a char that indicates what type of atom it is: 's' for symbol, 'l' for long, and 'f' for float.
For long and float atoms, the next 4 bytes contain the value of the atom; for symbol atoms a null terminated character string follows.

All data is represented with little endian byte ordering.

Below is a C function that will deserialize a message passed in as a data pointer.

@code
void gimme_deserialize(char *data, t_symbol **s, long *ac, t_atom **av)
{
   char *curr = data;
   float *currf;
   long *currl,i;
   long datasize = BE_I32(*((long *)curr));
   curr += sizeof(long);
   *ac = BE_I32(*(long *)(curr));
   curr += sizeof(long);
   *av = (t_atom *)sysmem_newptr(sizeof(t_atom)*(*ac));

   if (*curr == ATOM_SERIALIZATION_SYMBOL_CODE)
   {
      curr++;
      *s = gensym(curr);
      while (*(++curr) != '\0') ;
      curr++;
   }
   else
      *s = 0L;
   for (i=0;i<*ac;i++)
      switch (*curr++)
      {
         case ATOM_SERIALIZATION_SYMBOL_CODE:
            (*av)[i].a_type = A_SYM;
            (*av)[i].a_w.w_sym = gensym(curr);
            while (*(++curr) != '\0') ;
            curr++;
            break;
         case ATOM_SERIALIZATION_FLOAT_CODE:
            (*av)[i].a_type = A_FLOAT;
            (*av)[i].a_w.w_float = BE_F32(*((float *)curr));
            curr += sizeof(float);
            break;
         case ATOM_SERIALIZATION_LONG_CODE:
            (*av)[i].a_type = A_LONG;
            (*av)[i].a_w.w_long = BE_I32(*((long *)curr));
            curr += sizeof(long);
            break;
      }
}
@endcode

*/
