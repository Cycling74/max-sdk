/**
	@page chapter_jit_jxf JXF File Specification

The Jitter File Format (JXF) stores matrix data in a binary (not human-readable) form. When using Jitter you can create JXF files by sending the write message to a jit.matrix object. Conversely you can read JXF files from disk using the read message. This section will cover first the API functions that one can use from C to read and write JXF files. Then it will break down the file format at the bit level.


@section chapter_jit_jxf_api The Binary JXF API

Most Jitter users do not need or want to know about the internal binary format of a JXF-file. Even users who want to read and write JXF-files from C do not need to know the internal details if they use the functions of the Jitter API for the binary interface. Not only is the API more convenient, but using the functions provided by Cycling '74 may protect your code from having to be altered in the future in the event of a specification change.

There are two primary functions one should use to read data from a JXF file. jit_bin_read_header() reads the version number and the size of the file from the header, and has the following signature:

@code
t_jit_err jit_bin_read_header(t_filehandle fh, ulong *version, long *filesize)
@endcode

jit_bin_read_matrix() imports matrix data from a file to a matrix, resizing the matrix if necessary, and has the following signature:

@code
t_jit_err jit_bin_read_matrix(t_filehandle fh, void *matrix)
@endcode

Here’s a chunk of code that shows how to read a matrix from disk:

@code
if (!(err=path_opensysfile(filename, path, &fh, READ_PERM))) {
   //all is well
} else {
   error("jit.matrix: can't open file %s",name->s_name);
   goto out;
}
if (jit_bin_read_header(fh,&version,&filesize)) {
   error("jit.matrix: improper file format %s",name->s_name);
   sysfile_close(fh);
   goto out;
}
if (jit_bin_read_matrix(fh,matrix)) {
   error("jit.matrix: improper file format %s",name->s_name);
   sysfile_close(fh);
   goto out;
}
sysfile_close(fh);
@endcode

Similarly there are two functions one should use when writing data to a JXF file. jit_bin_write_header() writes a header to a file, and has the following signature:

@code
t_jit_err jit_bin_write_header(t_filehandle fh, long filesize)
@endcode

jit_bin_write_matrix() writes a matrix to a file, and has the following signature:

@code
t_jit_err jit_bin_write_matrix(t_filehandle fh, void *matrix)
@endcode

Here’s a section of code that shows how you might write a file with one matrix. Note that the initial filesize argument to jit_bin_write_header() is bogus, but that the header is written again at the end of the operation when the filesize can be determined from the file position after writing the matrix.

@code
if (err=path_createsysfile(filename, path, type, &fh)) {
   error("jit.matrix: could not create file %s",name->s_name);
   goto out;
}
if (jit_bin_write_header(fh,0)) {
   error("jit.matrix: could not write header %s", matrixName->s_name);
   sysfile_close(fh);
   goto out;
}
if (jit_bin_write_matrix(fh,pointerToMatrix)) {
   error("jit.matrix: could not write matrix %s", matrixName->s_name);
   sysfile_close(fh);
   goto out;
}
sysfile_getpos(fh, &position);
sysfile_seteof(fh, position);
if (jit_bin_write_header(fh,position)) {
   error("jit.matrix: could not write header %s",
matrixName->s_name);
   sysfile_close(fh);
   goto out;
}
sysfile_close(fh);
@endcode


@section chapter_jit_jxf_spec Specification of the JXF Format

The internal format of JXF-files is based on the Interchange File Format (IFF) (http://en.wikipedia.org/wiki/Interchange_File_Format). An IFF file is built up from chunks. All data in IFF files is big-endian. Several convenience macros defined in jit.byteorder.h are available to help convert numbers to the proper format before and after they're written to and read from a JXF file: BE_I32() can be called on 32-bit integers, BE_F32() on 32-bit floats, and BE_F64() on 64-bit doubles.

Each chunk in an IFF file begins with a four character Type ID. This is followed by a 32-bit unsigned integer specifying the size of the chunk content in bytes. In a JXF file, the 32-bit integer part of the first chunk tells us the size of the file, and all the subsequent chunks, which begin immediately after the first chunk, contain matrices. In the future chunks may also be used to store other kinds of data.

Here is a tabular overview of an example minimal JXF file.

Container Chunk

<table>
	<tr><td>groupID</td>	 	<td>JIT_BIN_CHUNK_CONTAINER ('FORM')					</td></tr>
	<tr><td>File size</td>	 	<td>32-bit int                              			</td></tr>
	<tr><td>IFF Type</td>	 	<td>JIT_BIN_FORMAT ('JIT!')                 			</td></tr>
	<tr><td>Format Chunk		<tr><td>                                   				</td></tr>
	<tr><td>chunkID</td>	 	<td>JIT_BIN_CHUNK_FORMAT_VERSION ('FVER')       		</td></tr>
	<tr><td>Chunk size</td>	 	<td>12 bytes                                			</td></tr>
	<tr><td>Version</td>	 	<td>JIT_BIN_VERSION_1 (0x3C93DC80)              		</td></tr>
	<tr><td>Matrix Chunk</td>	<td>                                    				</td></tr>
	<tr><td>chunk ID</td>	 	<td>JIT_BIN_CHUNK_MATRIX ('MTRX')           			</td></tr>
	<tr><td>chunk size</td>	 	<td>32-bit int                              			</td></tr>
	<tr><td>offset</td>	 		<td>32-bit int                                  		</td></tr>
	<tr><td>type</td>	 		<td>4-char                                      		</td></tr>
	<tr><td>planecount</td>	 	<td>32-bit int                              			</td></tr>
	<tr><td>dimcount</td>	 	<td>32-bit int                              			</td></tr>
	<tr><td>dim</td>	 		<td>Array of 32-bit ints that contain the dimensions	</td></tr>
	<tr><td>data</td>	 		<td>                                            		</td></tr>
</table>

The data offset of the matrix chunk represents the offset, in bytes, from the beginning of the chunk to the beginning of the data portion of the chunk. The type is one of CHAR, LONG, FL32 and FL64. The dim array contains dimcount elements, each of which is a 32-bit int. The data portion consists of the cells of the matrix written out one at a time in row-major order. Planar data is multiplexed in each cell. For example, a 3-plane 2 by 2 matrix would be written out in the following order:

<table>
	<tr><td>Plane	</td><td>Dim 0	</td><td>Dim 1	</td></tr>
	<tr><td>0	 	</td><td>0	 	</td><td>0    	</td></tr>
	<tr><td>1	 	</td><td>0	 	</td><td>0    	</td></tr>
	<tr><td>2	 	</td><td>0	 	</td><td>0    	</td></tr>
	<tr><td>0	 	</td><td>1	 	</td><td>0    	</td></tr>
	<tr><td>1	 	</td><td>1	 	</td><td>0    	</td></tr>
	<tr><td>2	 	</td><td>1	 	</td><td>0    	</td></tr>
	<tr><td>0	 	</td><td>0	 	</td><td>1    	</td></tr>
	<tr><td>1	 	</td><td>0	 	</td><td>1    	</td></tr>
	<tr><td>2	 	</td><td>0	 	</td><td>1    	</td></tr>
	<tr><td>0	 	</td><td>1	 	</td><td>1    	</td></tr>
	<tr><td>1	 	</td><td>1	 	</td><td>1    	</td></tr>
	<tr><td>2	 	</td><td>1	 	</td><td>1    	</td></tr>
</table>

The various chunks discussed above can be represented by the C structs listed below:

@code
typedef struct _jit_bin_chunk_container
{
   ulong   ckid;       //'FORM'
   long   cksize;      //filesize
   ulong   formtype;   //'JIT!'
} t_jit_bin_chunk_container;

typedef struct _jit_bin_chunk_format_version
{
   ulong   ckid;       //'FVER'
   long   cksize;      //12
   ulong   vers;      //timestamp
} t_jit_bin_chunk_format_version;

typedef struct _jit_bin_chunk_matrix
{
   ulong   ckid;       //'MTRX'
   long   cksize;      //varies(should be equal to
               //24+(4*dimcount)+(typesize*planecount*totalpoints))
   long    offset;      //data offset(should be equal to 24+(4*dimcount))
   ulong   type;      //'CHAR','LONG','FL32','FL64'
   long   planecount;
   long   dimcount;
   long   dim[1];
} t_jit_bin_chunk_matrix;
@endcode
*/
