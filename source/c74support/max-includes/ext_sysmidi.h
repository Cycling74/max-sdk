// sysmidi.h
#ifndef _EXT_SYSMIDI_H_
#define _EXT_SYSMIDI_H_

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

enum {
	SYSMIDI_ENABLED = 1,
	SYSMIDI_DYNAMIC = 2,
	SYSMIDI_PERMANENT = 4
};

typedef struct midistate
{
	long midicmd;   /* top nibble of the most recent status byte */
	long chan;      /* midi channel (if not sysex) */
	long sysex;     /* true if we are getting a sysex message */
	long argc;      /* # of bytes received in msg excluding status byte */
	t_uint8 *data;
} t_midistate;


typedef struct _midiportinfo {
	t_symbol *p_name;
	struct _sysmididriver *p_driver;
	long p_refnum;
	long p_id;
	short p_abbrev;
	short p_chanoffset;
	char p_enabled;
	char p_dynamic;		// is (was) a dynamically created port
	char p_permanent;	// should be saved in prefs
	char p_delete;
	void *p_data1;
	long p_data2;
	void *p_wait;
	t_midistate p_state;
} t_midiportinfo;

typedef struct _sysmididriver {
	t_object d_ob;
	t_symbol *d_name;
	char d_available;	// positive response on informational instantiation
	char d_hastimer;
	method d_sendmethod;
	method d_bytesreceivedmethod;
	// driver-specific info follows
} t_sysmididriver;


void sysmidi_enqbigpacket(t_midiportinfo *port, t_uint8 *data, double ts, long len, long contFlags);
long sysmidi_numinports(void);
long sysmidi_numoutports(void);
t_symbol *sysmidi_indextoname(long index, long io);
void sysmidi_iterate(method meth, void *arg, long io);
t_midiportinfo *sysmidi_createport(long id, long refnum, t_symbol *name, t_sysmididriver *dx, long io, long flags);
void sysmidi_deletemarked(long io);
t_midiportinfo *sysmidi_idtoport(long id, long io);
long sysmidi_uniqueid(void);
t_midiportinfo *sysmidi_data1toport(void *data, long io);
t_midiportinfo *sysmidi_nametoport(t_symbol *name, long io);

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

END_USING_C_LINKAGE

#endif // _EXT_SYSMIDI_H_
