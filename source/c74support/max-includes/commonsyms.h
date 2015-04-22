/* 
	commonsyms.h
		
*/

#ifndef __COMMON_SYMBOLS_H__
#define __COMMON_SYMBOLS_H__

BEGIN_USING_C_LINKAGE

#define COMMON_SYMBOLS_VERSION_5_0_0	500 // Max 5
#define COMMON_SYMBOLS_VERSION			COMMON_SYMBOLS_VERSION_5_0_0

typedef struct _common_symbols_table
{
	long	version;
	t_symbol *s__preset;
	t_symbol *s_abbrev;
	t_symbol *s_abbrev_rowcomponent;
	t_symbol *s_abbrev_setvalue;
	t_symbol *s_acceptsdrag;
	t_symbol *s_acceptsdrag_locked;
	t_symbol *s_acceptsdrag_unlocked;
	t_symbol *s_action;
	t_symbol *s_action_rowcomponent;
	t_symbol *s_action_setvalue;
	t_symbol *s_activate;
	t_symbol *s_active;
	t_symbol *s_activetab;
	t_symbol *s_activetabname;
	t_symbol *s_activewindow;
	t_symbol *s_adapt;
	t_symbol *s_add;
	t_symbol *s_addattr;
	t_symbol *s_addattr_enable;
	t_symbol *s_addclient;
	t_symbol *s_addfolder;
	t_symbol *s_addfolderandsave;
	t_symbol *s_addquerydict;
	t_symbol *s_addquerydictfromfile;
	t_symbol *s_addslot;
	t_symbol *s_addtopresentation;
	t_symbol *s_addwiretap;
	t_symbol *s_adornments;
	t_symbol *s_alias;
	t_symbol *s_alignboxes;
	t_symbol *s_alignconnections;
	t_symbol *s_alignlines;
	t_symbol *s_all;
	t_symbol *s_allkinds;
	t_symbol *s_allowmod;
	t_symbol *s_alpha;
	t_symbol *s_annotation;
	t_symbol *s_annotation_name;
	t_symbol *s_anydate;
	t_symbol *s_anykind;
	t_symbol *s_anything;
	t_symbol *s_append;
	t_symbol *s_append_sql;
	t_symbol *s_appendatoms;
	t_symbol *s_appendtodictionary;
	t_symbol *s_apply;
	t_symbol *s_applyboxprototype;
	t_symbol *s_applydeep;
	t_symbol *s_applydeepif;
	t_symbol *s_applyif;
	t_symbol *s_args;
	t_symbol *s_argument;
	t_symbol *s_arguments;
	t_symbol *s_argv;
	t_symbol *s_ascending;
	t_symbol *s_aspect;
	t_symbol *s_assist;
	t_symbol *s_assoc;
	t_symbol *s_atbclick;
	t_symbol *s_atom;
	t_symbol *s_atomarray;
	t_symbol *s_attach;
	t_symbol *s_attr_filter_clip;
	t_symbol *s_attr_get;
	t_symbol *s_attr_getnames;
	t_symbol *s_attr_gettarget;
	t_symbol *s_attr_modified;
	t_symbol *s_attr_offset_array;
	t_symbol *s_attr_renamed;
	t_symbol *s_attr_setdisabled;
	t_symbol *s_attr_setinvisible;
	t_symbol *s_attribute;
	t_symbol *s_attributes;
	t_symbol *s_attrname;
	t_symbol *s_audiofile;
	t_symbol *s_audioplugin;
	t_symbol *s_author;
	t_symbol *s_autocompletion;
	t_symbol *s_autocompletion_query;
	t_symbol *s_autofixwidth;
	t_symbol *s_autoheightchanged;
	t_symbol *s_autoscroll;
	t_symbol *s_back;
	t_symbol *s_background;
	t_symbol *s_bang;
	t_symbol *s_bbu;
	t_symbol *s_bclear;
	t_symbol *s_bcopy;
	t_symbol *s_bcut;
	t_symbol *s_begineditbox;
	t_symbol *s_beginswith;
	t_symbol *s_beginswithorcontains;
	t_symbol *s_bfixwidth;
	t_symbol *s_bfont;
	t_symbol *s_bgcolor;
	t_symbol *s_bgcount;
	t_symbol *s_bghidden;
	t_symbol *s_bglocked;
	t_symbol *s_bgmode;
	t_symbol *s_blue;
	t_symbol *s_bogus;
	t_symbol *s_bold;
	t_symbol *s_border;
	t_symbol *s_borderchanged;
	t_symbol *s_bottom_inset;
	t_symbol *s_boundingbox;
	t_symbol *s_bounds;
	t_symbol *s_box;
	t_symbol *s_box1;
	t_symbol *s_box2;
	t_symbol *s_boxalpha;
	t_symbol *s_boxanimatetime;
	t_symbol *s_boxcomponent;
	t_symbol *s_boxcontextitems;
	t_symbol *s_boxcontextmenu;
	t_symbol *s_boxes;
	t_symbol *s_boxlayer;
	t_symbol *s_boxnotify;
	t_symbol *s_boxscreenrectchanged;
	t_symbol *s_bpaste;
	t_symbol *s_bpastepic;
	t_symbol *s_bpatcher;
	t_symbol *s_bpatcher_holder;
	t_symbol *s_bpm;
	t_symbol *s_bracket_default;
	t_symbol *s_bracket_none;
	t_symbol *s_break;
	t_symbol *s_bredo;
	t_symbol *s_brgba;
	t_symbol *s_bringforward;
	t_symbol *s_bringtofront;
	t_symbol *s_bubblesize;
	t_symbol *s_build;
	t_symbol *s_buildcolumns;
	t_symbol *s_bundo;
	t_symbol *s_button;
	t_symbol *s_c74object;
	t_symbol *s_canback;
	t_symbol *s_cancopychanged;
	t_symbol *s_candropfiles;
	t_symbol *s_canforward;
	t_symbol *s_canhilite;
	t_symbol *s_canmovebackward;
	t_symbol *s_canmoveforward;
	t_symbol *s_canpastechanged;
	t_symbol *s_canremove;
	t_symbol *s_cansave;
	t_symbol *s_canschedule;
	t_symbol *s_canselectchanged;
	t_symbol *s_canvastoscreen;
	t_symbol *s_caption;
	t_symbol *s_catcolors;
	t_symbol *s_category;
	t_symbol *s_category_first;
	t_symbol *s_cell;
	t_symbol *s_cell_clue;
	t_symbol *s_cellclue;
	t_symbol *s_cellenabled;
	t_symbol *s_cellschanged;
	t_symbol *s_char;
	t_symbol *s_char_comma;
	t_symbol *s_char_minus;
	t_symbol *s_char_semi;
	t_symbol *s_char_space;
	t_symbol *s_charset_converter;
	t_symbol *s_checkbox;
	t_symbol *s_choose;
	t_symbol *s_chord;
	t_symbol *s_chuck;
	t_symbol *s_chuckindex;
	t_symbol *s_class;
	t_symbol *s_class_jit_attribute;
	t_symbol *s_class_jit_matrix;
	t_symbol *s_class_jit_namespace;
	t_symbol *s_classname;
	t_symbol *s_classsym;
	t_symbol *s_clear;
	t_symbol *s_clearactions;
	t_symbol *s_clearcolumns;
	t_symbol *s_clearitem;
	t_symbol *s_clearslots;
	t_symbol *s_click;
	t_symbol *s_clickaction;
	t_symbol *s_clientcontext;
	t_symbol *s_clipboard;
	t_symbol *s_clipping;
	t_symbol *s_clock;
	t_symbol *s_close;
	t_symbol *s_closebang;
	t_symbol *s_clue_cell;
	t_symbol *s_clue_header;
	t_symbol *s_clueclass;
	t_symbol *s_cluelookupattr;
	t_symbol *s_cluename;
	t_symbol *s_clues;
	t_symbol *s_colhead;
	t_symbol *s_coll;
	t_symbol *s_collectfiles;
	t_symbol *s_collective;
	t_symbol *s_color;
	t_symbol *s_colorvalue;
	t_symbol *s_columnadded;
	t_symbol *s_columnclue;
	t_symbol *s_columndeleted;
	t_symbol *s_columnheaderclue;
	t_symbol *s_columnminmaxchanged;
	t_symbol *s_columnnamechanged;
	t_symbol *s_columns;
	t_symbol *s_columnwidthchanged;
	t_symbol *s_com;
	t_symbol *s_command;
	t_symbol *s_command_enable;
	t_symbol *s_commandgroup;
	t_symbol *s_commands;
	t_symbol *s_comment;
	t_symbol *s_comparison;
	t_symbol *s_comparisons;
	t_symbol *s_completeconnection;
	t_symbol *s_connect;
	t_symbol *s_connectcolor;
	t_symbol *s_containersizechange;
	t_symbol *s_contains;
	t_symbol *s_contextmenu;
	t_symbol *s_contextualpaste;
	t_symbol *s_controller;
	t_symbol *s_convert;
	t_symbol *s_copy;
	t_symbol *s_copyatoms;
	t_symbol *s_copyjundo;
	t_symbol *s_coremidi;
	t_symbol *s_count;
	t_symbol *s_create_backup;
	t_symbol *s_createbpatcher;
	t_symbol *s_createsubpatcher;
	t_symbol *s_current;
	t_symbol *s_cut;
	t_symbol *s_data;
	t_symbol *s_date_created;
	t_symbol *s_date_lastaccessed;
	t_symbol *s_date_modified;
	t_symbol *s_days;
	t_symbol *s_dblclick;
	t_symbol *s_debugwindow_show;
	t_symbol *s_decorator;
	t_symbol *s_default;
	t_symbol *s_default_fontface;
	t_symbol *s_default_fontname;
	t_symbol *s_default_fontsize;
	t_symbol *s_default_matrixplcolor;
	t_symbol *s_default_plcolor;
	t_symbol *s_default_query;
	t_symbol *s_default_sigplcolor;
	t_symbol *s_defaultcommand;
	t_symbol *s_defaultfocusbox;
	t_symbol *s_defaultname;
	t_symbol *s_defaultquery;
	t_symbol *s_defaults;
	t_symbol *s_defaultvaluechanged;
	t_symbol *s_definearg;
	t_symbol *s_defineargument;
	t_symbol *s_definecomparison;
	t_symbol *s_definefield;
	t_symbol *s_definefolder;
	t_symbol *s_definequantifier;
	t_symbol *s_definequery;
	t_symbol *s_defineslot;
	t_symbol *s_definesort;
	t_symbol *s_defrect;
	t_symbol *s_delete;
	t_symbol *s_deleteindex;
	t_symbol *s_deletemetadata;
	t_symbol *s_deletequery;
	t_symbol *s_depthbuffer;
	t_symbol *s_descending;
	t_symbol *s_description;
	t_symbol *s_dest_closing;
	t_symbol *s_destination;
	t_symbol *s_destrect;
	t_symbol *s_destroy;
	t_symbol *s_detach;
	t_symbol *s_devicerects;
	t_symbol *s_dictionary;
	t_symbol *s_digest;
	t_symbol *s_dim;
	t_symbol *s_dimlink;
	t_symbol *s_dirty;
	t_symbol *s_disabled;
	t_symbol *s_disablewiretap;
	t_symbol *s_disconnect;
	t_symbol *s_do_get_shared_context;
	t_symbol *s_document;
	t_symbol *s_docwindow_docrect;
	t_symbol *s_docwindow_refrect;
	t_symbol *s_docwindow_searchrect;
	t_symbol *s_docwindow_tocrect;
	t_symbol *s_docwindow_tutrect;
	t_symbol *s_domain;
	t_symbol *s_done;
	t_symbol *s_donewobj;
	t_symbol *s_dontsave;
	t_symbol *s_doublebuffer;
	t_symbol *s_doubleclick;
	t_symbol *s_doubleclickaction;
	t_symbol *s_doubleclicked;
	t_symbol *s_down;
	t_symbol *s_downcaption;
	t_symbol *s_downicon;
	t_symbol *s_drag;
	t_symbol *s_dragactive;
	t_symbol *s_dragdrop;
	t_symbol *s_dragenter;
	t_symbol *s_dragexit;
	t_symbol *s_draggablechanged;
	t_symbol *s_dragmove;
	t_symbol *s_dragrole;
	t_symbol *s_dragtarget;
	t_symbol *s_drawfirstin;
	t_symbol *s_drawinlast;
	t_symbol *s_drawsresizer;
	t_symbol *s_dropaction;
	t_symbol *s_dropaction_addapplyprototype;
	t_symbol *s_dropaction_addconnectedmessage;
	t_symbol *s_dropaction_addcustom;
	t_symbol *s_dropaction_addcustom_extended;
	t_symbol *s_dropaction_addobjectcreation;
	t_symbol *s_dropaction_addopeninnewwindow;
	t_symbol *s_dropaction_addprototypeobjectcreation;
	t_symbol *s_dropfiles;
	t_symbol *s_droprole;
	t_symbol *s_droprole_locked;
	t_symbol *s_droprole_unlocked;
	t_symbol *s_dsp;
	t_symbol *s_dump;
	t_symbol *s_dumpboxes;
	t_symbol *s_dumpout;
	t_symbol *s_duplicate;
	t_symbol *s_edit;
	t_symbol *s_edit_framecolor;
	t_symbol *s_editactive;
	t_symbol *s_editbox;
	t_symbol *s_editcell;
	t_symbol *s_editing_bgcolor;
	t_symbol *s_editmetadata;
	t_symbol *s_editonclick;
	t_symbol *s_editor;
	t_symbol *s_elements;
	t_symbol *s_embed;
	t_symbol *s_emptytext;
	t_symbol *s_enable;
	t_symbol *s_enable_rowcomponent;
	t_symbol *s_enable_setvalue;
	t_symbol *s_enablehscroll;
	t_symbol *s_enabler;
	t_symbol *s_enablevscroll;
	t_symbol *s_enddrag;
	t_symbol *s_endmoveboxes;
	t_symbol *s_endpoint;
	t_symbol *s_endprobe;
	t_symbol *s_endswith;
	t_symbol *s_endtransaction;
	t_symbol *s_enter;
	t_symbol *s_entertext;
	t_symbol *s_enum;
	t_symbol *s_enumindex;
	t_symbol *s_enummsg;
	t_symbol *s_enumtarget;
	t_symbol *s_enumvals;
	t_symbol *s_equalto;
	t_symbol *s_error;
	t_symbol *s_eventinterval;
	t_symbol *s_everything;
	t_symbol *s_excludebg;
	t_symbol *s_exec;
	t_symbol *s_execstring;
	t_symbol *s_execstring_safe;
	t_symbol *s_execute;
	t_symbol *s_executefind;
	t_symbol *s_extension;
	t_symbol *s_extra;
	t_symbol *s_ezquery;
	t_symbol *s_fadetinge;
	t_symbol *s_fgcolor;
	t_symbol *s_fghidden;
	t_symbol *s_field;
	t_symbol *s_fieldnamebyindex;
	t_symbol *s_fields;
	t_symbol *s_file;
	t_symbol *s_filefolder;
	t_symbol *s_fileformat;
	t_symbol *s_filename;
	t_symbol *s_filepath;
	t_symbol *s_filetypemessage;
	t_symbol *s_fileusage;
	t_symbol *s_filter;
	t_symbol *s_filterget;
	t_symbol *s_filterset;
	t_symbol *s_find;
	t_symbol *s_find_enableselectall;
	t_symbol *s_findall;
	t_symbol *s_finddoneclicked;
	t_symbol *s_findfirst;
	t_symbol *s_findmaster;
	t_symbol *s_findnextclicked;
	t_symbol *s_findprevclicked;
	t_symbol *s_findreturnkeypressed;
	t_symbol *s_findselectallclicked;
	t_symbol *s_findsize;
	t_symbol *s_findtextchanged;
	t_symbol *s_first;
	t_symbol *s_firstline;
	t_symbol *s_firstobject;
	t_symbol *s_firstview;
	t_symbol *s_five;
	t_symbol *s_fixed;
	t_symbol *s_fixwidth;
	t_symbol *s_flags;
	t_symbol *s_flat;
	t_symbol *s_float;
	t_symbol *s_float32;
	t_symbol *s_float64;
	t_symbol *s_floating;
	t_symbol *s_flonum;
	t_symbol *s_flush;
	t_symbol *s_focusgained;
	t_symbol *s_focuslost;
	t_symbol *s_focusonvis;
	t_symbol *s_fold;
	t_symbol *s_folder;
	t_symbol *s_folderdropped;
	t_symbol *s_folderpath;
	t_symbol *s_font;
	t_symbol *s_fontchanged;
	t_symbol *s_fontface;
	t_symbol *s_fontfixwidth;
	t_symbol *s_fontinfochanged;
	t_symbol *s_fontname;
	t_symbol *s_fontnamechanged;
	t_symbol *s_fontpanel_isclientwindow;
	t_symbol *s_fontpanelfontcolor;
	t_symbol *s_fontpanelfontface;
	t_symbol *s_fontpanelfontname;
	t_symbol *s_fontpanelfontsize;
	t_symbol *s_fontsize;
	t_symbol *s_fontsizechanged;
	t_symbol *s_fonttarget;
	t_symbol *s_forbidclose;
	t_symbol *s_forward;
	t_symbol *s_four;
	t_symbol *s_fpic;
	t_symbol *s_free;
	t_symbol *s_freebang;
	t_symbol *s_freekeys;
	t_symbol *s_freepatcherview;
	t_symbol *s_frgb;
	t_symbol *s_frgba;
	t_symbol *s_fromdictionary;
	t_symbol *s_fromgworld;
	t_symbol *s_frommatrix;
	t_symbol *s_frommatrix_trunc;
	t_symbol *s_front;
	t_symbol *s_frozen;
	t_symbol *s_frozen_box_attributes;
	t_symbol *s_frozen_object_attributes;
	t_symbol *s_frozen_pendingattrs;
	t_symbol *s_frozen_text;
	t_symbol *s_fsaa;
	t_symbol *s_fullname;
	t_symbol *s_fullscreen;
	t_symbol *s_funall;
	t_symbol *s_function;
	t_symbol *s_g_inout_binlet;
	t_symbol *s_g_max_newest;
	t_symbol *s_g_max_newest_box;
	t_symbol *s_gb;
	t_symbol *s_genframe;
	t_symbol *s_get;
	t_symbol *s_get_jit_ob;
	t_symbol *s_getargumentlabel;
	t_symbol *s_getassoc;
	t_symbol *s_getatoms;
	t_symbol *s_getattrtext;
	t_symbol *s_getbounds;
	t_symbol *s_getboxlayer;
	t_symbol *s_getcaptioninfo;
	t_symbol *s_getcellcolor;
	t_symbol *s_getcelldescription;
	t_symbol *s_getcelleditable;
	t_symbol *s_getcellfiletypes;
	t_symbol *s_getcellicon;
	t_symbol *s_getcellindentlevel;
	t_symbol *s_getcellmenu;
	t_symbol *s_getcelltext;
	t_symbol *s_getcelltextlength;
	t_symbol *s_getcellunits;
	t_symbol *s_getcellunitsyms;
	t_symbol *s_getcellvalue;
	t_symbol *s_getcolumnnames;
	t_symbol *s_getcomparisonlabel;
	t_symbol *s_getcomponent;
	t_symbol *s_getcontainedcomponent;
	t_symbol *s_getdata;
	t_symbol *s_getdefaultfocuscomponent;
	t_symbol *s_getdefext;
	t_symbol *s_getdeftype;
	t_symbol *s_getdrawparams;
	t_symbol *s_getdst;
	t_symbol *s_getfieldlabel;
	t_symbol *s_getfindtext;
	t_symbol *s_getflags;
	t_symbol *s_getfolderpath;
	t_symbol *s_getfonttarget;
	t_symbol *s_getfontview;
	t_symbol *s_getformat;
	t_symbol *s_gethintdelay;
	t_symbol *s_getholder;
	t_symbol *s_getimage;
	t_symbol *s_getindex;
	t_symbol *s_getinfo;
	t_symbol *s_getinports;
	t_symbol *s_getinput;
	t_symbol *s_getinputlist;
	t_symbol *s_getioproc;
	t_symbol *s_getkeys;
	t_symbol *s_getlastinsertid;
	t_symbol *s_getlayoutinfo;
	t_symbol *s_getlogical;
	t_symbol *s_getmatrix;
	t_symbol *s_getmethod;
	t_symbol *s_getname;
	t_symbol *s_getnamed;
	t_symbol *s_getnamedbox;
	t_symbol *s_getnextrecord;
	t_symbol *s_getnthview;
	t_symbol *s_getobject;
	t_symbol *s_getoffset;
	t_symbol *s_getoutports;
	t_symbol *s_getoutput;
	t_symbol *s_getoutputlist;
	t_symbol *s_getprobevalue;
	t_symbol *s_getptr;
	t_symbol *s_getptr_forview;
	t_symbol *s_getquantifierlabel;
	t_symbol *s_getquery;
	t_symbol *s_getquerydict;
	t_symbol *s_getquerynames;
	t_symbol *s_getquerytype;
	t_symbol *s_getrect;
	t_symbol *s_getrowcolor;
	t_symbol *s_getrowobject;
	t_symbol *s_getselected;
	t_symbol *s_getsize;
	t_symbol *s_getsort;
	t_symbol *s_getspecial;
	t_symbol *s_getsrc;
	t_symbol *s_getstackbase;
	t_symbol *s_getsyswind;
	t_symbol *s_gettextptr;
	t_symbol *s_gettitle;
	t_symbol *s_gettype;
	t_symbol *s_gettypelist;
	t_symbol *s_getunitstext;
	t_symbol *s_getunitsyms;
	t_symbol *s_getvalueof;
	t_symbol *s_getvisiblecanvasrect;
	t_symbol *s_getwind;
	t_symbol *s_getwindowrect;
	t_symbol *s_gl_line_loop;
	t_symbol *s_gl_line_strip;
	t_symbol *s_gl_lines;
	t_symbol *s_gl_points;
	t_symbol *s_gl_polygon;
	t_symbol *s_gl_quad_grid;
	t_symbol *s_gl_quad_strip;
	t_symbol *s_gl_quads;
	t_symbol *s_gl_tri_fan;
	t_symbol *s_gl_tri_grid;
	t_symbol *s_gl_tri_strip;
	t_symbol *s_gl_triangles;
	t_symbol *s_global;
	t_symbol *s_globalpatchername;
	t_symbol *s_go;
	t_symbol *s_grabfocus;
	t_symbol *s_greaterthan;
	t_symbol *s_green;
	t_symbol *s_grid;
	t_symbol *s_gridonopen;
	t_symbol *s_gridsize;
	t_symbol *s_gridsnap;
	t_symbol *s_gridsnaponopen;
	t_symbol *s_group;
	t_symbol *s_grow;
	t_symbol *s_growboth;
	t_symbol *s_growy;
	t_symbol *s_hasclose;
	t_symbol *s_hasdatatype;
	t_symbol *s_hasgrow;
	t_symbol *s_hashorizscroll;
	t_symbol *s_hashtab_entry_free;
	t_symbol *s_hashtab_entry_new;
	t_symbol *s_hashtab_free;
	t_symbol *s_hasmenu;
	t_symbol *s_hasminimize;
	t_symbol *s_hastitlebar;
	t_symbol *s_hasvertscroll;
	t_symbol *s_haszoom;
	t_symbol *s_head;
	t_symbol *s_height;
	t_symbol *s_help;
	t_symbol *s_helpfile;
	t_symbol *s_helpmenu;
	t_symbol *s_helpname;
	t_symbol *s_hidden;
	t_symbol *s_hiddenconnect;
	t_symbol *s_hide;
	t_symbol *s_hideablechanged;
	t_symbol *s_hidecaption;
	t_symbol *s_hidewindow;
	t_symbol *s_hint;
	t_symbol *s_hint_disabled;
	t_symbol *s_hinttrack;
	t_symbol *s_history;
	t_symbol *s_history_entry;
	t_symbol *s_hittest;
	t_symbol *s_holderoptions;
	t_symbol *s_hz;
	t_symbol *s_icon;
	t_symbol *s_id;
	t_symbol *s_identifier;
	t_symbol *s_ignoreclick;
	t_symbol *s_image;
	t_symbol *s_imagefile;
	t_symbol *s_imbed;
	t_symbol *s_imprint;
	t_symbol *s_includebg;
	t_symbol *s_index;
	t_symbol *s_info;
	t_symbol *s_init;
	t_symbol *s_inlet;
	t_symbol *s_inletinfo;
	t_symbol *s_inletnum;
	t_symbol *s_inletoutlet;
	t_symbol *s_inletscaleratio;
	t_symbol *s_inputcount;
	t_symbol *s_insert;
	t_symbol *s_insertboxtext;
	t_symbol *s_insertindex;
	t_symbol *s_insertpatcher;
	t_symbol *s_insertsegment;
	t_symbol *s_insetchanged;
	t_symbol *s_insp;
	t_symbol *s_inspectee;
	t_symbol *s_inspectees;
	t_symbol *s_inspector;
	t_symbol *s_inspector_clueclass;
	t_symbol *s_inspector_color;
	t_symbol *s_inspector_customize;
	t_symbol *s_inspector_editor;
	t_symbol *s_inspector_fontattr;
	t_symbol *s_inspector_rect;
	t_symbol *s_inspector_tab;
	t_symbol *s_inspector_tabheight;
	t_symbol *s_inspector_title;
	t_symbol *s_inspector_toolbarid;
	t_symbol *s_inspectorchange;
	t_symbol *s_instance_attributes;
	t_symbol *s_instanceattr;
	t_symbol *s_int;
	t_symbol *s_int16;
	t_symbol *s_int24;
	t_symbol *s_int32;
	t_symbol *s_int8;
	t_symbol *s_interface;
	t_symbol *s_interp;
	t_symbol *s_interp_arg;
	t_symbol *s_interval;
	t_symbol *s_invalidate;
	t_symbol *s_invalidateallboxlayers;
	t_symbol *s_invalidateboxlayer;
	t_symbol *s_invalidatetoolbar;
	t_symbol *s_invis;
	t_symbol *s_invisaction;
	t_symbol *s_invisible;
	t_symbol *s_invlabel;
	t_symbol *s_invmsg;
	t_symbol *s_ioname;
	t_symbol *s_ioproc;
	t_symbol *s_is;
	t_symbol *s_iscolumnvisible;
	t_symbol *s_isfile;
	t_symbol *s_isfirstin;
	t_symbol *s_isfolder;
	t_symbol *s_iso_8859_1;
	t_symbol *s_isproto;
	t_symbol *s_isselectedqueryremovable;
	t_symbol *s_isselectionvalid;
	t_symbol *s_issystemquery;
	t_symbol *s_italic;
	t_symbol *s_items;
	t_symbol *s_iterate;
	t_symbol *s_javascript;
	t_symbol *s_jbogus;
	t_symbol *s_jbox;
	t_symbol *s_jbox_bytecount;
	t_symbol *s_jbox_instances;
	t_symbol *s_jboxattr;
	t_symbol *s_jdrag;
	t_symbol *s_jed;
	t_symbol *s_jgraphics;
	t_symbol *s_jit_attr_offset;
	t_symbol *s_jit_attr_offset_array;
	t_symbol *s_jit_attribute;
	t_symbol *s_jit_gl_texture;
	t_symbol *s_jit_linklist;
	t_symbol *s_jit_matrix;
	t_symbol *s_jit_mop;
	t_symbol *s_jit_namespace;
	t_symbol *s_jpatcher;
	t_symbol *s_jpatcher_bytecount;
	t_symbol *s_jpatcher_instances;
	t_symbol *s_jpatchercontroller;
	t_symbol *s_jpatcherholder;
	t_symbol *s_jpatchline;
	t_symbol *s_jpg;
	t_symbol *s_jsave;
	t_symbol *s_JSON;
	t_symbol *s_jsonreader;
	t_symbol *s_jsonwriter;
	t_symbol *s_juibogus;
	t_symbol *s_juiobject;
	t_symbol *s_jundo_command;
	t_symbol *s_jundo_commandgroup;
	t_symbol *s_jweb_history;
	t_symbol *s_jwind;
	t_symbol *s_kb;
	t_symbol *s_key;
	t_symbol *s_key_backslash;
	t_symbol *s_key_backspace;
	t_symbol *s_key_clear;
	t_symbol *s_key_delete;
	t_symbol *s_key_downarrow;
	t_symbol *s_key_end;
	t_symbol *s_key_enter;
	t_symbol *s_key_esc;
	t_symbol *s_key_grave;
	t_symbol *s_key_helpkey;
	t_symbol *s_key_home;
	t_symbol *s_key_insert;
	t_symbol *s_key_leftarrow;
	t_symbol *s_key_optionspace;
	t_symbol *s_key_pagedown;
	t_symbol *s_key_pageup;
	t_symbol *s_key_return;
	t_symbol *s_key_rightarrow;
	t_symbol *s_key_spacebar;
	t_symbol *s_key_tab;
	t_symbol *s_key_tilde;
	t_symbol *s_key_uparrow;
	t_symbol *s_key_vertbar;
	t_symbol *s_keyaction;
	t_symbol *s_keyfilter;
	t_symbol *s_keyfocuschanged;
	t_symbol *s_keymessage;
	t_symbol *s_kind;
	t_symbol *s_kindenum;
	t_symbol *s_kindis;
	t_symbol *s_kindmenu;
	t_symbol *s_label;
	t_symbol *s_labels;
	t_symbol *s_last;
	t_symbol *s_last_access;
	t_symbol *s_lastmessage;
	t_symbol *s_lastmodified;
	t_symbol *s_lastobject;
	t_symbol *s_latency;
	t_symbol *s_lessthan;
	t_symbol *s_linear;
	t_symbol *s_linechanged;
	t_symbol *s_linecontextmenu;
	t_symbol *s_linecount;
	t_symbol *s_linenotify;
	t_symbol *s_lines;
	t_symbol *s_lineup;
	t_symbol *s_list;
	t_symbol *s_list_rowcomponent;
	t_symbol *s_list_setvalue;
	t_symbol *s_listboxprototype;
	t_symbol *s_listfiles;
	t_symbol *s_listwindow;
	t_symbol *s_loadbang;
	t_symbol *s_local;
	t_symbol *s_lock;
	t_symbol *s_locked;
	t_symbol *s_locked_iocolor;
	t_symbol *s_lockeddragscroll;
	t_symbol *s_lockedpatchercontextmenu;
	t_symbol *s_log;
	t_symbol *s_long;
	t_symbol *s_lookup;
	t_symbol *s_lookupcommand;
	t_symbol *s_loop;
	t_symbol *s_macroman;
	t_symbol *s_mainsearchentry;
	t_symbol *s_makearray;
	t_symbol *s_makeview;
	t_symbol *s_margin;
	t_symbol *s_matchdragrole;
	t_symbol *s_matchinspectees;
	t_symbol *s_matrix;
	t_symbol *s_matrix_calc;
	t_symbol *s_matrixctrl;
	t_symbol *s_matrixname;
	t_symbol *s_max;
	t_symbol *s_max_jit_classex;
	t_symbol *s_maxapplication;
	t_symbol *s_maxclass;
	t_symbol *s_maxdebug;
	t_symbol *s_maxdim;
	t_symbol *s_maximize;
	t_symbol *s_maxmessage;
	t_symbol *s_maxplanecount;
	t_symbol *s_maxwindow;
	t_symbol *s_mb;
	t_symbol *s_measuretext;
	t_symbol *s_menu;
	t_symbol *s_menubar;
	t_symbol *s_menus;
	t_symbol *s_menus_runtime;
	t_symbol *s_message;
	t_symbol *s_messages;
	t_symbol *s_metadata;
	t_symbol *s_metadatalist;
	t_symbol *s_metadatawindow;
	t_symbol *s_methodall;
	t_symbol *s_methodindex;
	t_symbol *s_methods;
	t_symbol *s_midpoints;
	t_symbol *s_min;
	t_symbol *s_mindim;
	t_symbol *s_minimize;
	t_symbol *s_minplanecount;
	t_symbol *s_minus;
	t_symbol *s_mode;
	t_symbol *s_modified;
	t_symbol *s_monitor;
	t_symbol *s_months;
	t_symbol *s_mousedoubleclick;
	t_symbol *s_mousedown;
	t_symbol *s_mousedownonchar;
	t_symbol *s_mousedrag;
	t_symbol *s_mousedragdelta;
	t_symbol *s_mouseenter;
	t_symbol *s_mouseleave;
	t_symbol *s_mousemove;
	t_symbol *s_mousescale;
	t_symbol *s_mouseup;
	t_symbol *s_mousewheel;
	t_symbol *s_move;
	t_symbol *s_moveboxes;
	t_symbol *s_moved;
	t_symbol *s_moveifoffdisplay;
	t_symbol *s_movelines;
	t_symbol *s_movesegment;
	t_symbol *s_moviedim;
	t_symbol *s_moviefile;
	t_symbol *s_ms;
	t_symbol *s_ms_ansi;
	t_symbol *s_mulaw;
	t_symbol *s_mult;
	t_symbol *s_multiboxcontextmenu;
	t_symbol *s_multilinecontextmenu;
	t_symbol *s_mute;
	t_symbol *s_name;
	t_symbol *s_name_changed;
	t_symbol *s_name_rowcomponent;
	t_symbol *s_name_setvalue;
	t_symbol *s_name_textcolor;
	t_symbol *s_name_textstyle;
	t_symbol *s_name_width;
	t_symbol *s_nameinspector;
	t_symbol *s_nativewindow;
	t_symbol *s_navkey;
	t_symbol *s_new;
	t_symbol *s_newcopy;
	t_symbol *s_newdefault;
	t_symbol *s_newex;
	t_symbol *s_newfilebrowser;
	t_symbol *s_newfolder;
	t_symbol *s_newlines;
	t_symbol *s_newobj;
	t_symbol *s_newobject;
	t_symbol *s_newobjects;
	t_symbol *s_newpatcherview;
	t_symbol *s_newpatchline;
	t_symbol *s_newquery;
	t_symbol *s_next;
	t_symbol *s_nextline;
	t_symbol *s_nextobject;
	t_symbol *s_nextrecord;
	t_symbol *s_nextview;
	t_symbol *s_nfilters;
	t_symbol *s_No;
	t_symbol *s_noactivate;
	t_symbol *s_nobox;
	t_symbol *s_noclipse;
	t_symbol *s_noclose;
	t_symbol *s_noedit;
	t_symbol *s_noeval;
	t_symbol *s_nofloat;
	t_symbol *s_nofontpanel;
	t_symbol *s_nogrow;
	t_symbol *s_nomad;
	t_symbol *s_nomenu;
	t_symbol *s_nominimize;
	t_symbol *s_none;
	t_symbol *s_nonomad;
	t_symbol *s_normalheight;
	t_symbol *s_normalwidth;
	t_symbol *s_noscroll;
	t_symbol *s_not;
	t_symbol *s_notevalues;
	t_symbol *s_nothing;
	t_symbol *s_notify;
	t_symbol *s_notifyall;
	t_symbol *s_notifyall_delete;
	t_symbol *s_notifyall_new;
	t_symbol *s_notitle;
	t_symbol *s_nozoom;
	t_symbol *s_nth;
	t_symbol *s_number;
	t_symbol *s_number_paint;
	t_symbol *s_number_rowcomponent;
	t_symbol *s_number_setvalue;
	t_symbol *s_numfields;
	t_symbol *s_nummidpoints;
	t_symbol *s_numrecords;
	t_symbol *s_numresults;
	t_symbol *s_numrowschanged;
	t_symbol *s_numtabs;
	t_symbol *s_numviews;
	t_symbol *s_numwindowviews;
	t_symbol *s_ob_sym;
	t_symbol *s_obex_container;
	t_symbol *s_objargs;
	t_symbol *s_object;
	t_symbol *s_object_id;
	t_symbol *s_objectcount;
	t_symbol *s_objectfilename;
	t_symbol *s_objectlist;
	t_symbol *s_objectpalette;
	t_symbol *s_objectview_doubleclick;
	t_symbol *s_objectview_selected;
	t_symbol *s_objptr2index;
	t_symbol *s_objtype;
	t_symbol *s_obtrusiveerror;
	t_symbol *s_offset;
	t_symbol *s_offset_rowcomponent;
	t_symbol *s_offset_setvalue;
	t_symbol *s_offsetfrom;
	t_symbol *s_offsetmidpoints;
	t_symbol *s_okclose;
	t_symbol *s_oksize;
	t_symbol *s_one;
	t_symbol *s_onoff;
	t_symbol *s_opaque;
	t_symbol *s_open;
	t_symbol *s_openassoc;
	t_symbol *s_openfile;
	t_symbol *s_openinpresentation;
	t_symbol *s_openquery;
	t_symbol *s_openrect;
	t_symbol *s_openweb;
	t_symbol *s_optional;
	t_symbol *s_optionsdirty;
	t_symbol *s_order;
	t_symbol *s_order_by;
	t_symbol *s_orderbefore;
	t_symbol *s_orderfront;
	t_symbol *s_orientation;
	t_symbol *s_outlet;
	t_symbol *s_outletnum;
	t_symbol *s_outline;
	t_symbol *s_outmode;
	t_symbol *s_output;
	t_symbol *s_outputcount;
	t_symbol *s_outputmatrix;
	t_symbol *s_outputmode;
	t_symbol *s_overdrive;
	t_symbol *s_owner;
	t_symbol *s_ownervis;
	t_symbol *s_p;
	t_symbol *s_paint;
	t_symbol *s_paintsbackground;
	t_symbol *s_palette_action;
	t_symbol *s_palette_caption;
	t_symbol *s_palette_category;
	t_symbol *s_palette_numerical_order;
	t_symbol *s_palette_order;
	t_symbol *s_palette_protocount;
	t_symbol *s_palette_tab_action;
	t_symbol *s_parameter_enable;
	t_symbol *s_parent;
	t_symbol *s_parentclass;
	t_symbol *s_parentpatcher;
	t_symbol *s_parse;
	t_symbol *s_parsefile;
	t_symbol *s_paste;
	t_symbol *s_pastefileintoobject;
	t_symbol *s_pastefrom;
	t_symbol *s_pastereplace;
	t_symbol *s_patcher;
	t_symbol *s_patchercomponent;
	t_symbol *s_patchercontextmenu;
	t_symbol *s_patchereditor;
	t_symbol *s_patchername;
	t_symbol *s_patchernotify;
	t_symbol *s_patcherview;
	t_symbol *s_patcherview_instances;
	t_symbol *s_patcherview_invis;
	t_symbol *s_patcherview_notify_locked;
	t_symbol *s_patcherview_notify_presentation;
	t_symbol *s_patcherview_vis;
	t_symbol *s_patching_position;
	t_symbol *s_patching_rect;
	t_symbol *s_patching_size;
	t_symbol *s_patchline;
	t_symbol *s_path;
	t_symbol *s_pattrstorage;
	t_symbol *s_pclose;
	t_symbol *s_pending;
	t_symbol *s_pic;
	t_symbol *s_pictctrl;
	t_symbol *s_plane;
	t_symbol *s_planecount;
	t_symbol *s_planelink;
	t_symbol *s_plugconfig;
	t_symbol *s_plus;
	t_symbol *s_png;
	t_symbol *s_pointer;
	t_symbol *s_popupmenu;
	t_symbol *s_portenable;
	t_symbol *s_position;
	t_symbol *s_postname;
	t_symbol *s_pound_B;
	t_symbol *s_pound_D;
	t_symbol *s_pound_N;
	t_symbol *s_pound_P;
	t_symbol *s_pound_X;
	t_symbol *s_preferences;
	t_symbol *s_preload;
	t_symbol *s_presentation;
	t_symbol *s_presentation_linecount;
	t_symbol *s_presentation_position;
	t_symbol *s_presentation_rect;
	t_symbol *s_presentation_size;
	t_symbol *s_preset;
	t_symbol *s_preset_data;
	t_symbol *s_preview;
	t_symbol *s_preview_image;
	t_symbol *s_previewheight;
	t_symbol *s_previewimagedata;
	t_symbol *s_prevobject;
	t_symbol *s_print;
	t_symbol *s_priority;
	t_symbol *s_prototype;
	t_symbol *s_prototype_binbuf;
	t_symbol *s_prototypename;
	t_symbol *s_psave;
	t_symbol *s_pulsate;
	t_symbol *s_pupdate;
	t_symbol *s_quantifier;
	t_symbol *s_quantifier_exists;
	t_symbol *s_quantifiers;
	t_symbol *s_quantize;
	t_symbol *s_queries;
	t_symbol *s_query;
	t_symbol *s_query_selected;
	t_symbol *s_querycontroller;
	t_symbol *s_queryid;
	t_symbol *s_querylist;
	t_symbol *s_queryname;
	t_symbol *s_querypreview;
	t_symbol *s_querysearch;
	t_symbol *s_quickmap;
	t_symbol *s_quit;
	t_symbol *s_quitting;
	t_symbol *s_radial;
	t_symbol *s_range;
	t_symbol *s_rawfind;
	t_symbol *s_rawwindsave;
	t_symbol *s_rawwindsaveas;
	t_symbol *s_read;
	t_symbol *s_readonly;
	t_symbol *s_realclass;
	t_symbol *s_rebuilding;
	t_symbol *s_recordbyindex;
	t_symbol *s_recreate_invis;
	t_symbol *s_recreate_vis;
	t_symbol *s_rect;
	t_symbol *s_rectangle;
	t_symbol *s_rectangular;
	t_symbol *s_red;
	t_symbol *s_redostack;
	t_symbol *s_redraw;
	t_symbol *s_redrawcontents;
	t_symbol *s_reference;
	t_symbol *s_reffile;
	t_symbol *s_refinequery;
	t_symbol *s_refresh;
	t_symbol *s_register;
	t_symbol *s_remove;
	t_symbol *s_removeattr;
	t_symbol *s_removeattr_enable;
	t_symbol *s_removeboxlayer;
	t_symbol *s_removeclient;
	t_symbol *s_removefrompresentation;
	t_symbol *s_removelines;
	t_symbol *s_removeobjects;
	t_symbol *s_removesegment;
	t_symbol *s_removeslot;
	t_symbol *s_removewiretap;
	t_symbol *s_rename;
	t_symbol *s_renumberslot;
	t_symbol *s_replace;
	t_symbol *s_replaced_args;
	t_symbol *s_reschedule;
	t_symbol *s_reset;
	t_symbol *s_resize;
	t_symbol *s_resizeaction;
	t_symbol *s_resized;
	t_symbol *s_resizelimits;
	t_symbol *s_resizenotify;
	t_symbol *s_resolve_name;
	t_symbol *s_resolve_raw;
	t_symbol *s_resort;
	t_symbol *s_resource;
	t_symbol *s_respondtoclick;
	t_symbol *s_restore;
	t_symbol *s_restrict_dim;
	t_symbol *s_restrict_planecount;
	t_symbol *s_restrict_type;
	t_symbol *s_result;
	t_symbol *s_retain;
	t_symbol *s_revealinfinder;
	t_symbol *s_reverse;
	t_symbol *s_rgb;
	t_symbol *s_rgba;
	t_symbol *s_rolename;
	t_symbol *s_rotate;
	t_symbol *s_rounded;
	t_symbol *s_rowcolorchanged;
	t_symbol *s_rowcomponent;
	t_symbol *s_rowenabled;
	t_symbol *s_rowhead;
	t_symbol *s_rowheightchanged;
	t_symbol *s_safebang;
	t_symbol *s_safeclear;
	t_symbol *s_samples;
	t_symbol *s_save;
	t_symbol *s_save2;
	t_symbol *s_saveas;
	t_symbol *s_saveboxprototype;
	t_symbol *s_saved_object_attributes;
	t_symbol *s_savefilepath;
	t_symbol *s_savelasttab;
	t_symbol *s_savequery;
	t_symbol *s_saveto;
	t_symbol *s_savewindow;
	t_symbol *s_savingdefault;
	t_symbol *s_scale;
	t_symbol *s_script;
	t_symbol *s_scrollanimatetime;
	t_symbol *s_scrolloffset;
	t_symbol *s_scrollorigin;
	t_symbol *s_scrollposition;
	t_symbol *s_scrollselectedobjectsintoview;
	t_symbol *s_scrollto;
	t_symbol *s_scrollviewtoshow;
	t_symbol *s_search;
	t_symbol *s_searchterm;
	t_symbol *s_searchtext;
	t_symbol *s_select;
	t_symbol *s_selectallonedit;
	t_symbol *s_selectbox;
	t_symbol *s_selectcategory;
	t_symbol *s_selectcell;
	t_symbol *s_selectdropped;
	t_symbol *s_selected;
	t_symbol *s_selectedboxes;
	t_symbol *s_selectedlines;
	t_symbol *s_selectedrow;
	t_symbol *s_selectedrow_contextual;
	t_symbol *s_selfsave;
	t_symbol *s_selmode;
	t_symbol *s_send;
	t_symbol *s_sendbackward;
	t_symbol *s_sendbox;
	t_symbol *s_sendboxmsg;
	t_symbol *s_senderclasssym;
	t_symbol *s_sendtoback;
	t_symbol *s_session_usage_count;
	t_symbol *s_set;
	t_symbol *s_setall;
	t_symbol *s_setassoc;
	t_symbol *s_setatoms;
	t_symbol *s_setattr;
	t_symbol *s_setboxrect;
	t_symbol *s_setcellunits;
	t_symbol *s_setcellvalue;
	t_symbol *s_setcontainedcomponent;
	t_symbol *s_setdata;
	t_symbol *s_setdefaults;
	t_symbol *s_setdirty;
	t_symbol *s_seteditboxcaretposition;
	t_symbol *s_seteditboxhighlightedregion;
	t_symbol *s_seteditview;
	t_symbol *s_setfilter;
	t_symbol *s_setflags;
	t_symbol *s_setfont;
	t_symbol *s_setglobalcoords;
	t_symbol *s_setinfo;
	t_symbol *s_setinfo_ex;
	t_symbol *s_setmethod;
	t_symbol *s_setmidpoint;
	t_symbol *s_setpatcherattr;
	t_symbol *s_setptr;
	t_symbol *s_setrect;
	t_symbol *s_setspecialrow;
	t_symbol *s_settext;
	t_symbol *s_setunitsym;
	t_symbol *s_setvalue;
	t_symbol *s_setvalueof;
	t_symbol *s_setvaluetext;
	t_symbol *s_setwindowrect;
	t_symbol *s_setwindowsize;
	t_symbol *s_setzorder;
	t_symbol *s_shortcut;
	t_symbol *s_show;
	t_symbol *s_showcaption;
	t_symbol *s_showdoc;
	t_symbol *s_showfind;
	t_symbol *s_showpreview;
	t_symbol *s_showrecent;
	t_symbol *s_showrow;
	t_symbol *s_showsaveable;
	t_symbol *s_showtarget;
	t_symbol *s_shuffle;
	t_symbol *s_signal;
	t_symbol *s_sinceyesterday;
	t_symbol *s_singleinspector;
	t_symbol *s_size;
	t_symbol *s_sizeboxes;
	t_symbol *s_slot_definition;
	t_symbol *s_slot_modified;
	t_symbol *s_slots;
	t_symbol *s_smpte;
	t_symbol *s_snaptogrid;
	t_symbol *s_sort;
	t_symbol *s_sortablechanged;
	t_symbol *s_sortcolumn;
	t_symbol *s_sortdata;
	t_symbol *s_sorted;
	t_symbol *s_sorted_by_column;
	t_symbol *s_source;
	t_symbol *s_spacing;
	t_symbol *s_special;
	t_symbol *s_specialclick;
	t_symbol *s_specialcount;
	t_symbol *s_sql;
	t_symbol *s_sql2;
	t_symbol *s_sqlite;
	t_symbol *s_sqlite_result;
	t_symbol *s_sqlstring;
	t_symbol *s_sr;
	t_symbol *s_start;
	t_symbol *s_startdrag;
	t_symbol *s_startmoveboxes;
	t_symbol *s_startpoint;
	t_symbol *s_startprobe;
	t_symbol *s_starttransaction;
	t_symbol *s_startwindow;
	t_symbol *s_state;
	t_symbol *s_sticky_attr;
	t_symbol *s_sticky_method;
	t_symbol *s_stop;
	t_symbol *s_store;
	t_symbol *s_straighten;
	t_symbol *s_straightend;
	t_symbol *s_straightstart;
	t_symbol *s_straightthresh;
	t_symbol *s_string;
	t_symbol *s_style;
	t_symbol *s_sub;
	t_symbol *s_subpatcher;
	t_symbol *s_surfacebuffer;
	t_symbol *s_svg;
	t_symbol *s_swap;
	t_symbol *s_swatches;
	t_symbol *s_symbol;
	t_symbol *s_sysqelem;
	t_symbol *s_t;
	t_symbol *s_tab_bgcolor;
	t_symbol *s_table;
	t_symbol *s_tabledata;
	t_symbol *s_tag;
	t_symbol *s_tags;
	t_symbol *s_tapcontroller_show;
	t_symbol *s_tapwindow;
	t_symbol *s_target;
	t_symbol *s_template;
	t_symbol *s_tempo;
	t_symbol *s_text;
	t_symbol *s_text_commaseparated;
	t_symbol *s_text_large;
	t_symbol *s_text_onesymbol;
	t_symbol *s_textchanged;
	t_symbol *s_textcolor;
	t_symbol *s_textfield;
	t_symbol *s_textfile;
	t_symbol *s_textmargins;
	t_symbol *s_textstyle;
	t_symbol *s_thismonth;
	t_symbol *s_thisweek;
	t_symbol *s_threadpriority;
	t_symbol *s_threadsafe;
	t_symbol *s_three;
	t_symbol *s_ticks;
	t_symbol *s_time;
	t_symbol *s_timeobj;
	t_symbol *s_timesigchanged;
	t_symbol *s_timeupdate;
	t_symbol *s_tinge;
	t_symbol *s_title;
	t_symbol *s_titleassoc;
	t_symbol *s_tobinbuf;
	t_symbol *s_toc;
	t_symbol *s_today;
	t_symbol *s_todictionary;
	t_symbol *s_togworld;
	t_symbol *s_tool;
	t_symbol *s_tool_paint;
	t_symbol *s_tool_rowcomponent;
	t_symbol *s_tool_setvalue;
	t_symbol *s_tool_sort;
	t_symbol *s_toolbarheight;
	t_symbol *s_toolbarid;
	t_symbol *s_toolbars;
	t_symbol *s_toolbarvisible;
	t_symbol *s_top_inset;
	t_symbol *s_topmost;
	t_symbol *s_toppatcher;
	t_symbol *s_topredoname;
	t_symbol *s_topundoname;
	t_symbol *s_trackaction;
	t_symbol *s_transparent;
	t_symbol *s_transport;
	t_symbol *s_traverse;
	t_symbol *s_triangle;
	t_symbol *s_tutorial;
	t_symbol *s_two;
	t_symbol *s_twobytecomment;
	t_symbol *s_type;
	t_symbol *s_typed_usage_count;
	t_symbol *s_typedwrapper;
	t_symbol *s_typelink;
	t_symbol *s_types;
	t_symbol *s_underline;
	t_symbol *s_understands;
	t_symbol *s_undo;
	t_symbol *s_undostack;
	t_symbol *s_unimbed;
	t_symbol *s_uninitialized;
	t_symbol *s_unique;
	t_symbol *s_unit;
	t_symbol *s_units;
	t_symbol *s_unlocked_iocolor;
	t_symbol *s_unlockedinteraction;
	t_symbol *s_unset;
	t_symbol *s_up;
	t_symbol *s_update;
	t_symbol *s_update_metadata;
	t_symbol *s_updatecommand;
	t_symbol *s_updatecontent;
	t_symbol *s_updatefind;
	t_symbol *s_updatelookandfeel;
	t_symbol *s_updatemenu;
	t_symbol *s_updateprototypes;
	t_symbol *s_updatequery;
	t_symbol *s_updatequerydict;
	t_symbol *s_updaterect;
	t_symbol *s_url;
	t_symbol *s_us_ascii;
	t_symbol *s_usage_count;
	t_symbol *s_usedslotlist;
	t_symbol *s_useellipsis;
	t_symbol *s_useimagebuffer;
	t_symbol *s_usemax;
	t_symbol *s_usemin;
	t_symbol *s_user;
	t_symbol *s_usercanget;
	t_symbol *s_usercanset;
	t_symbol *s_utf_16;
	t_symbol *s_utf_16be;
	t_symbol *s_utf_16le;
	t_symbol *s_utf_8;
	t_symbol *s_val;
	t_symbol *s_value;
	t_symbol *s_value_endchange;
	t_symbol *s_value_rowcomponent;
	t_symbol *s_valuebyindex;
	t_symbol *s_varname;
	t_symbol *s_varname_set;
	t_symbol *s_varname_unset;
	t_symbol *s_version;
	t_symbol *s_videofile;
	t_symbol *s_views;
	t_symbol *s_viewspan;
	t_symbol *s_vignette;
	t_symbol *s_vis;
	t_symbol *s_visibilitychanged;
	t_symbol *s_visible;
	t_symbol *s_visiblecanvasrect;
	t_symbol *s_vol;
	t_symbol *s_vpicture;
	t_symbol *s_vpreset;
	t_symbol *s_wantfree;
	t_symbol *s_wantsreturn;
	t_symbol *s_wantstab;
	t_symbol *s_watch;
	t_symbol *s_watchpoint_flags;
	t_symbol *s_watchpoint_id;
	t_symbol *s_wclose;
	t_symbol *s_webpage;
	t_symbol *s_weeks;
	t_symbol *s_wind;
	t_symbol *s_window;
	t_symbol *s_windowbounds;
	t_symbol *s_windowrect;
	t_symbol *s_windsave;
	t_symbol *s_wiretap;
	t_symbol *s_withinlast;
	t_symbol *s_wobjectname;
	t_symbol *s_wordwrap;
	t_symbol *s_workspace;
	t_symbol *s_write;
	t_symbol *s_writedictionary;
	t_symbol *s_xmlfile;
	t_symbol *s_years;
	t_symbol *s_zero;
	t_symbol *s_zoom;
	t_symbol *s_zoombox;
	t_symbol *s_zoomfactor;
	t_symbol *s_zorder;
	t_symbol *s_zzz;
	t_symbol *s_Sans_Serif;

} t_common_symbols_table;

#define _sym__preset (_common_symbols->s__preset)
#define _sym_abbrev (_common_symbols->s_abbrev)
#define _sym_abbrev_rowcomponent (_common_symbols->s_abbrev_rowcomponent)
#define _sym_abbrev_setvalue (_common_symbols->s_abbrev_setvalue)
#define _sym_acceptsdrag (_common_symbols->s_acceptsdrag)
#define _sym_acceptsdrag_locked (_common_symbols->s_acceptsdrag_locked)
#define _sym_acceptsdrag_unlocked (_common_symbols->s_acceptsdrag_unlocked)
#define _sym_action (_common_symbols->s_action)
#define _sym_action_rowcomponent (_common_symbols->s_action_rowcomponent)
#define _sym_action_setvalue (_common_symbols->s_action_setvalue)
#define _sym_activate (_common_symbols->s_activate)
#define _sym_active (_common_symbols->s_active)
#define _sym_activetab (_common_symbols->s_activetab)
#define _sym_activetabname (_common_symbols->s_activetabname)
#define _sym_activewindow (_common_symbols->s_activewindow)
#define _sym_adapt (_common_symbols->s_adapt)
#define _sym_add (_common_symbols->s_add)
#define _sym_addattr (_common_symbols->s_addattr)
#define _sym_addattr_enable (_common_symbols->s_addattr_enable)
#define _sym_addclient (_common_symbols->s_addclient)
#define _sym_addfolder (_common_symbols->s_addfolder)
#define _sym_addfolderandsave (_common_symbols->s_addfolderandsave)
#define _sym_addquerydict (_common_symbols->s_addquerydict)
#define _sym_addquerydictfromfile (_common_symbols->s_addquerydictfromfile)
#define _sym_addslot (_common_symbols->s_addslot)
#define _sym_addtopresentation (_common_symbols->s_addtopresentation)
#define _sym_addwiretap (_common_symbols->s_addwiretap)
#define _sym_adornments (_common_symbols->s_adornments)
#define _sym_alias (_common_symbols->s_alias)
#define _sym_alignboxes (_common_symbols->s_alignboxes)
#define _sym_alignconnections (_common_symbols->s_alignconnections)
#define _sym_alignlines (_common_symbols->s_alignlines)
#define _sym_all (_common_symbols->s_all)
#define _sym_allkinds (_common_symbols->s_allkinds)
#define _sym_allowmod (_common_symbols->s_allowmod)
#define _sym_alpha (_common_symbols->s_alpha)
#define _sym_annotation (_common_symbols->s_annotation)
#define _sym_annotation_name (_common_symbols->s_annotation_name)
#define _sym_anydate (_common_symbols->s_anydate)
#define _sym_anykind (_common_symbols->s_anykind)
#define _sym_anything (_common_symbols->s_anything)
#define _sym_append (_common_symbols->s_append)
#define _sym_append_sql (_common_symbols->s_append_sql)
#define _sym_appendatoms (_common_symbols->s_appendatoms)
#define _sym_appendtodictionary (_common_symbols->s_appendtodictionary)
#define _sym_apply (_common_symbols->s_apply)
#define _sym_applyboxprototype (_common_symbols->s_applyboxprototype)
#define _sym_applydeep (_common_symbols->s_applydeep)
#define _sym_applydeepif (_common_symbols->s_applydeepif)
#define _sym_applyif (_common_symbols->s_applyif)
#define _sym_args (_common_symbols->s_args)
#define _sym_argument (_common_symbols->s_argument)
#define _sym_arguments (_common_symbols->s_arguments)
#define _sym_argv (_common_symbols->s_argv)
#define _sym_ascending (_common_symbols->s_ascending)
#define _sym_aspect (_common_symbols->s_aspect)
#define _sym_assist (_common_symbols->s_assist)
#define _sym_assoc (_common_symbols->s_assoc)
#define _sym_atbclick (_common_symbols->s_atbclick)
#define _sym_atom (_common_symbols->s_atom)
#define _sym_atomarray (_common_symbols->s_atomarray)
#define _sym_attach (_common_symbols->s_attach)
#define _sym_attr_filter_clip (_common_symbols->s_attr_filter_clip)
#define _sym_attr_get (_common_symbols->s_attr_get)
#define _sym_attr_getnames (_common_symbols->s_attr_getnames)
#define _sym_attr_gettarget (_common_symbols->s_attr_gettarget)
#define _sym_attr_modified (_common_symbols->s_attr_modified)
#define _sym_attr_offset_array (_common_symbols->s_attr_offset_array)
#define _sym_attr_renamed (_common_symbols->s_attr_renamed)
#define _sym_attr_setdisabled (_common_symbols->s_attr_setdisabled)
#define _sym_attr_setinvisible (_common_symbols->s_attr_setinvisible)
#define _sym_attribute (_common_symbols->s_attribute)
#define _sym_attributes (_common_symbols->s_attributes)
#define _sym_attrname (_common_symbols->s_attrname)
#define _sym_audiofile (_common_symbols->s_audiofile)
#define _sym_audioplugin (_common_symbols->s_audioplugin)
#define _sym_author (_common_symbols->s_author)
#define _sym_autocompletion (_common_symbols->s_autocompletion)
#define _sym_autocompletion_query (_common_symbols->s_autocompletion_query)
#define _sym_autofixwidth (_common_symbols->s_autofixwidth)
#define _sym_autoheightchanged (_common_symbols->s_autoheightchanged)
#define _sym_autoscroll (_common_symbols->s_autoscroll)
#define _sym_back (_common_symbols->s_back)
#define _sym_background (_common_symbols->s_background)
#define _sym_bang (_common_symbols->s_bang)
#define _sym_bbu (_common_symbols->s_bbu)
#define _sym_bclear (_common_symbols->s_bclear)
#define _sym_bcopy (_common_symbols->s_bcopy)
#define _sym_bcut (_common_symbols->s_bcut)
#define _sym_begineditbox (_common_symbols->s_begineditbox)
#define _sym_beginswith (_common_symbols->s_beginswith)
#define _sym_beginswithorcontains (_common_symbols->s_beginswithorcontains)
#define _sym_bfixwidth (_common_symbols->s_bfixwidth)
#define _sym_bfont (_common_symbols->s_bfont)
#define _sym_bgcolor (_common_symbols->s_bgcolor)
#define _sym_bgcount (_common_symbols->s_bgcount)
#define _sym_bghidden (_common_symbols->s_bghidden)
#define _sym_bglocked (_common_symbols->s_bglocked)
#define _sym_bgmode (_common_symbols->s_bgmode)
#define _sym_blue (_common_symbols->s_blue)
#define _sym_bogus (_common_symbols->s_bogus)
#define _sym_bold (_common_symbols->s_bold)
#define _sym_border (_common_symbols->s_border)
#define _sym_borderchanged (_common_symbols->s_borderchanged)
#define _sym_bottom_inset (_common_symbols->s_bottom_inset)
#define _sym_boundingbox (_common_symbols->s_boundingbox)
#define _sym_bounds (_common_symbols->s_bounds)
#define _sym_box (_common_symbols->s_box)
#define _sym_box1 (_common_symbols->s_box1)
#define _sym_box2 (_common_symbols->s_box2)
#define _sym_boxalpha (_common_symbols->s_boxalpha)
#define _sym_boxanimatetime (_common_symbols->s_boxanimatetime)
#define _sym_boxcomponent (_common_symbols->s_boxcomponent)
#define _sym_boxcontextitems (_common_symbols->s_boxcontextitems)
#define _sym_boxcontextmenu (_common_symbols->s_boxcontextmenu)
#define _sym_boxes (_common_symbols->s_boxes)
#define _sym_boxlayer (_common_symbols->s_boxlayer)
#define _sym_boxnotify (_common_symbols->s_boxnotify)
#define _sym_boxscreenrectchanged (_common_symbols->s_boxscreenrectchanged)
#define _sym_bpaste (_common_symbols->s_bpaste)
#define _sym_bpastepic (_common_symbols->s_bpastepic)
#define _sym_bpatcher (_common_symbols->s_bpatcher)
#define _sym_bpatcher_holder (_common_symbols->s_bpatcher_holder)
#define _sym_bpm (_common_symbols->s_bpm)
#define _sym_bracket_default (_common_symbols->s_bracket_default)
#define _sym_bracket_none (_common_symbols->s_bracket_none)
#define _sym_break (_common_symbols->s_break)
#define _sym_bredo (_common_symbols->s_bredo)
#define _sym_brgba (_common_symbols->s_brgba)
#define _sym_bringforward (_common_symbols->s_bringforward)
#define _sym_bringtofront (_common_symbols->s_bringtofront)
#define _sym_bubblesize (_common_symbols->s_bubblesize)
#define _sym_build (_common_symbols->s_build)
#define _sym_buildcolumns (_common_symbols->s_buildcolumns)
#define _sym_bundo (_common_symbols->s_bundo)
#define _sym_button (_common_symbols->s_button)
#define _sym_c74object (_common_symbols->s_c74object)
#define _sym_canback (_common_symbols->s_canback)
#define _sym_cancopychanged (_common_symbols->s_cancopychanged)
#define _sym_candropfiles (_common_symbols->s_candropfiles)
#define _sym_canforward (_common_symbols->s_canforward)
#define _sym_canhilite (_common_symbols->s_canhilite)
#define _sym_canmovebackward (_common_symbols->s_canmovebackward)
#define _sym_canmoveforward (_common_symbols->s_canmoveforward)
#define _sym_canpastechanged (_common_symbols->s_canpastechanged)
#define _sym_canremove (_common_symbols->s_canremove)
#define _sym_cansave (_common_symbols->s_cansave)
#define _sym_canschedule (_common_symbols->s_canschedule)
#define _sym_canselectchanged (_common_symbols->s_canselectchanged)
#define _sym_canvastoscreen (_common_symbols->s_canvastoscreen)
#define _sym_caption (_common_symbols->s_caption)
#define _sym_catcolors (_common_symbols->s_catcolors)
#define _sym_category (_common_symbols->s_category)
#define _sym_category_first (_common_symbols->s_category_first)
#define _sym_cell (_common_symbols->s_cell)
#define _sym_cell_clue (_common_symbols->s_cell_clue)
#define _sym_cellclue (_common_symbols->s_cellclue)
#define _sym_cellenabled (_common_symbols->s_cellenabled)
#define _sym_cellschanged (_common_symbols->s_cellschanged)
#define _sym_char (_common_symbols->s_char)
#define _sym_char_comma (_common_symbols->s_char_comma)
#define _sym_char_minus (_common_symbols->s_char_minus)
#define _sym_char_semi (_common_symbols->s_char_semi)
#define _sym_char_space (_common_symbols->s_char_space)
#define _sym_charset_converter (_common_symbols->s_charset_converter)
#define _sym_checkbox (_common_symbols->s_checkbox)
#define _sym_choose (_common_symbols->s_choose)
#define _sym_chord (_common_symbols->s_chord)
#define _sym_chuck (_common_symbols->s_chuck)
#define _sym_chuckindex (_common_symbols->s_chuckindex)
#define _sym_class (_common_symbols->s_class)
#define _sym_class_jit_attribute (_common_symbols->s_class_jit_attribute)
#define _sym_class_jit_matrix (_common_symbols->s_class_jit_matrix)
#define _sym_class_jit_namespace (_common_symbols->s_class_jit_namespace)
#define _sym_classname (_common_symbols->s_classname)
#define _sym_classsym (_common_symbols->s_classsym)
#define _sym_clear (_common_symbols->s_clear)
#define _sym_clearactions (_common_symbols->s_clearactions)
#define _sym_clearcolumns (_common_symbols->s_clearcolumns)
#define _sym_clearitem (_common_symbols->s_clearitem)
#define _sym_clearslots (_common_symbols->s_clearslots)
#define _sym_click (_common_symbols->s_click)
#define _sym_clickaction (_common_symbols->s_clickaction)
#define _sym_clientcontext (_common_symbols->s_clientcontext)
#define _sym_clipboard (_common_symbols->s_clipboard)
#define _sym_clipping (_common_symbols->s_clipping)
#define _sym_clock (_common_symbols->s_clock)
#define _sym_close (_common_symbols->s_close)
#define _sym_closebang (_common_symbols->s_closebang)
#define _sym_clue_cell (_common_symbols->s_clue_cell)
#define _sym_clue_header (_common_symbols->s_clue_header)
#define _sym_clueclass (_common_symbols->s_clueclass)
#define _sym_cluelookupattr (_common_symbols->s_cluelookupattr)
#define _sym_cluename (_common_symbols->s_cluename)
#define _sym_clues (_common_symbols->s_clues)
#define _sym_colhead (_common_symbols->s_colhead)
#define _sym_coll (_common_symbols->s_coll)
#define _sym_collectfiles (_common_symbols->s_collectfiles)
#define _sym_collective (_common_symbols->s_collective)
#define _sym_color (_common_symbols->s_color)
#define _sym_colorvalue (_common_symbols->s_colorvalue)
#define _sym_columnadded (_common_symbols->s_columnadded)
#define _sym_columnclue (_common_symbols->s_columnclue)
#define _sym_columndeleted (_common_symbols->s_columndeleted)
#define _sym_columnheaderclue (_common_symbols->s_columnheaderclue)
#define _sym_columnminmaxchanged (_common_symbols->s_columnminmaxchanged)
#define _sym_columnnamechanged (_common_symbols->s_columnnamechanged)
#define _sym_columns (_common_symbols->s_columns)
#define _sym_columnwidthchanged (_common_symbols->s_columnwidthchanged)
#define _sym_com (_common_symbols->s_com)
#define _sym_command (_common_symbols->s_command)
#define _sym_command_enable (_common_symbols->s_command_enable)
#define _sym_commandgroup (_common_symbols->s_commandgroup)
#define _sym_commands (_common_symbols->s_commands)
#define _sym_comment (_common_symbols->s_comment)
#define _sym_comparison (_common_symbols->s_comparison)
#define _sym_comparisons (_common_symbols->s_comparisons)
#define _sym_completeconnection (_common_symbols->s_completeconnection)
#define _sym_connect (_common_symbols->s_connect)
#define _sym_connectcolor (_common_symbols->s_connectcolor)
#define _sym_containersizechange (_common_symbols->s_containersizechange)
#define _sym_contains (_common_symbols->s_contains)
#define _sym_contextmenu (_common_symbols->s_contextmenu)
#define _sym_contextualpaste (_common_symbols->s_contextualpaste)
#define _sym_controller (_common_symbols->s_controller)
#define _sym_convert (_common_symbols->s_convert)
#define _sym_copy (_common_symbols->s_copy)
#define _sym_copyatoms (_common_symbols->s_copyatoms)
#define _sym_copyjundo (_common_symbols->s_copyjundo)
#define _sym_coremidi (_common_symbols->s_coremidi)
#define _sym_count (_common_symbols->s_count)
#define _sym_create_backup (_common_symbols->s_create_backup)
#define _sym_createbpatcher (_common_symbols->s_createbpatcher)
#define _sym_createsubpatcher (_common_symbols->s_createsubpatcher)
#define _sym_current (_common_symbols->s_current)
#define _sym_cut (_common_symbols->s_cut)
#define _sym_data (_common_symbols->s_data)
#define _sym_date_created (_common_symbols->s_date_created)
#define _sym_date_lastaccessed (_common_symbols->s_date_lastaccessed)
#define _sym_date_modified (_common_symbols->s_date_modified)
#define _sym_days (_common_symbols->s_days)
#define _sym_dblclick (_common_symbols->s_dblclick)
#define _sym_debugwindow_show (_common_symbols->s_debugwindow_show)
#define _sym_decorator (_common_symbols->s_decorator)
#define _sym_default (_common_symbols->s_default)
#define _sym_default_fontface (_common_symbols->s_default_fontface)
#define _sym_default_fontname (_common_symbols->s_default_fontname)
#define _sym_default_fontsize (_common_symbols->s_default_fontsize)
#define _sym_default_matrixplcolor (_common_symbols->s_default_matrixplcolor)
#define _sym_default_plcolor (_common_symbols->s_default_plcolor)
#define _sym_default_query (_common_symbols->s_default_query)
#define _sym_default_sigplcolor (_common_symbols->s_default_sigplcolor)
#define _sym_defaultcommand (_common_symbols->s_defaultcommand)
#define _sym_defaultfocusbox (_common_symbols->s_defaultfocusbox)
#define _sym_defaultname (_common_symbols->s_defaultname)
#define _sym_defaultquery (_common_symbols->s_defaultquery)
#define _sym_defaults (_common_symbols->s_defaults)
#define _sym_defaultvaluechanged (_common_symbols->s_defaultvaluechanged)
#define _sym_definearg (_common_symbols->s_definearg)
#define _sym_defineargument (_common_symbols->s_defineargument)
#define _sym_definecomparison (_common_symbols->s_definecomparison)
#define _sym_definefield (_common_symbols->s_definefield)
#define _sym_definefolder (_common_symbols->s_definefolder)
#define _sym_definequantifier (_common_symbols->s_definequantifier)
#define _sym_definequery (_common_symbols->s_definequery)
#define _sym_defineslot (_common_symbols->s_defineslot)
#define _sym_definesort (_common_symbols->s_definesort)
#define _sym_defrect (_common_symbols->s_defrect)
#define _sym_delete (_common_symbols->s_delete)
#define _sym_deleteindex (_common_symbols->s_deleteindex)
#define _sym_deletemetadata (_common_symbols->s_deletemetadata)
#define _sym_deletequery (_common_symbols->s_deletequery)
#define _sym_depthbuffer (_common_symbols->s_depthbuffer)
#define _sym_descending (_common_symbols->s_descending)
#define _sym_description (_common_symbols->s_description)
#define _sym_dest_closing (_common_symbols->s_dest_closing)
#define _sym_destination (_common_symbols->s_destination)
#define _sym_destrect (_common_symbols->s_destrect)
#define _sym_destroy (_common_symbols->s_destroy)
#define _sym_detach (_common_symbols->s_detach)
#define _sym_devicerects (_common_symbols->s_devicerects)
#define _sym_dictionary (_common_symbols->s_dictionary)
#define _sym_digest (_common_symbols->s_digest)
#define _sym_dim (_common_symbols->s_dim)
#define _sym_dimlink (_common_symbols->s_dimlink)
#define _sym_dirty (_common_symbols->s_dirty)
#define _sym_disabled (_common_symbols->s_disabled)
#define _sym_disablewiretap (_common_symbols->s_disablewiretap)
#define _sym_disconnect (_common_symbols->s_disconnect)
#define _sym_do_get_shared_context (_common_symbols->s_do_get_shared_context)
#define _sym_document (_common_symbols->s_document)
#define _sym_docwindow_docrect (_common_symbols->s_docwindow_docrect)
#define _sym_docwindow_refrect (_common_symbols->s_docwindow_refrect)
#define _sym_docwindow_searchrect (_common_symbols->s_docwindow_searchrect)
#define _sym_docwindow_tocrect (_common_symbols->s_docwindow_tocrect)
#define _sym_docwindow_tutrect (_common_symbols->s_docwindow_tutrect)
#define _sym_domain (_common_symbols->s_domain)
#define _sym_done (_common_symbols->s_done)
#define _sym_donewobj (_common_symbols->s_donewobj)
#define _sym_dontsave (_common_symbols->s_dontsave)
#define _sym_doublebuffer (_common_symbols->s_doublebuffer)
#define _sym_doubleclick (_common_symbols->s_doubleclick)
#define _sym_doubleclickaction (_common_symbols->s_doubleclickaction)
#define _sym_doubleclicked (_common_symbols->s_doubleclicked)
#define _sym_down (_common_symbols->s_down)
#define _sym_downcaption (_common_symbols->s_downcaption)
#define _sym_downicon (_common_symbols->s_downicon)
#define _sym_drag (_common_symbols->s_drag)
#define _sym_dragactive (_common_symbols->s_dragactive)
#define _sym_dragdrop (_common_symbols->s_dragdrop)
#define _sym_dragenter (_common_symbols->s_dragenter)
#define _sym_dragexit (_common_symbols->s_dragexit)
#define _sym_draggablechanged (_common_symbols->s_draggablechanged)
#define _sym_dragmove (_common_symbols->s_dragmove)
#define _sym_dragrole (_common_symbols->s_dragrole)
#define _sym_dragtarget (_common_symbols->s_dragtarget)
#define _sym_drawfirstin (_common_symbols->s_drawfirstin)
#define _sym_drawinlast (_common_symbols->s_drawinlast)
#define _sym_drawsresizer (_common_symbols->s_drawsresizer)
#define _sym_dropaction (_common_symbols->s_dropaction)
#define _sym_dropaction_addapplyprototype (_common_symbols->s_dropaction_addapplyprototype)
#define _sym_dropaction_addconnectedmessage (_common_symbols->s_dropaction_addconnectedmessage)
#define _sym_dropaction_addcustom (_common_symbols->s_dropaction_addcustom)
#define _sym_dropaction_addcustom_extended (_common_symbols->s_dropaction_addcustom_extended)
#define _sym_dropaction_addobjectcreation (_common_symbols->s_dropaction_addobjectcreation)
#define _sym_dropaction_addopeninnewwindow (_common_symbols->s_dropaction_addopeninnewwindow)
#define _sym_dropaction_addprototypeobjectcreation (_common_symbols->s_dropaction_addprototypeobjectcreation)
#define _sym_dropfiles (_common_symbols->s_dropfiles)
#define _sym_droprole (_common_symbols->s_droprole)
#define _sym_droprole_locked (_common_symbols->s_droprole_locked)
#define _sym_droprole_unlocked (_common_symbols->s_droprole_unlocked)
#define _sym_dsp (_common_symbols->s_dsp)
#define _sym_dump (_common_symbols->s_dump)
#define _sym_dumpboxes (_common_symbols->s_dumpboxes)
#define _sym_dumpout (_common_symbols->s_dumpout)
#define _sym_duplicate (_common_symbols->s_duplicate)
#define _sym_edit (_common_symbols->s_edit)
#define _sym_edit_framecolor (_common_symbols->s_edit_framecolor)
#define _sym_editactive (_common_symbols->s_editactive)
#define _sym_editbox (_common_symbols->s_editbox)
#define _sym_editcell (_common_symbols->s_editcell)
#define _sym_editing_bgcolor (_common_symbols->s_editing_bgcolor)
#define _sym_editmetadata (_common_symbols->s_editmetadata)
#define _sym_editonclick (_common_symbols->s_editonclick)
#define _sym_editor (_common_symbols->s_editor)
#define _sym_elements (_common_symbols->s_elements)
#define _sym_embed (_common_symbols->s_embed)
#define _sym_emptytext (_common_symbols->s_emptytext)
#define _sym_enable (_common_symbols->s_enable)
#define _sym_enable_rowcomponent (_common_symbols->s_enable_rowcomponent)
#define _sym_enable_setvalue (_common_symbols->s_enable_setvalue)
#define _sym_enablehscroll (_common_symbols->s_enablehscroll)
#define _sym_enabler (_common_symbols->s_enabler)
#define _sym_enablevscroll (_common_symbols->s_enablevscroll)
#define _sym_enddrag (_common_symbols->s_enddrag)
#define _sym_endmoveboxes (_common_symbols->s_endmoveboxes)
#define _sym_endpoint (_common_symbols->s_endpoint)
#define _sym_endprobe (_common_symbols->s_endprobe)
#define _sym_endswith (_common_symbols->s_endswith)
#define _sym_endtransaction (_common_symbols->s_endtransaction)
#define _sym_enter (_common_symbols->s_enter)
#define _sym_entertext (_common_symbols->s_entertext)
#define _sym_enum (_common_symbols->s_enum)
#define _sym_enumindex (_common_symbols->s_enumindex)
#define _sym_enummsg (_common_symbols->s_enummsg)
#define _sym_enumtarget (_common_symbols->s_enumtarget)
#define _sym_enumvals (_common_symbols->s_enumvals)
#define _sym_equalto (_common_symbols->s_equalto)
#define _sym_error (_common_symbols->s_error)
#define _sym_eventinterval (_common_symbols->s_eventinterval)
#define _sym_everything (_common_symbols->s_everything)
#define _sym_excludebg (_common_symbols->s_excludebg)
#define _sym_exec (_common_symbols->s_exec)
#define _sym_execstring (_common_symbols->s_execstring)
#define _sym_execstring_safe (_common_symbols->s_execstring_safe)
#define _sym_execute (_common_symbols->s_execute)
#define _sym_executefind (_common_symbols->s_executefind)
#define _sym_extension (_common_symbols->s_extension)
#define _sym_extra (_common_symbols->s_extra)
#define _sym_ezquery (_common_symbols->s_ezquery)
#define _sym_fadetinge (_common_symbols->s_fadetinge)
#define _sym_fgcolor (_common_symbols->s_fgcolor)
#define _sym_fghidden (_common_symbols->s_fghidden)
#define _sym_field (_common_symbols->s_field)
#define _sym_fieldnamebyindex (_common_symbols->s_fieldnamebyindex)
#define _sym_fields (_common_symbols->s_fields)
#define _sym_file (_common_symbols->s_file)
#define _sym_filefolder (_common_symbols->s_filefolder)
#define _sym_fileformat (_common_symbols->s_fileformat)
#define _sym_filename (_common_symbols->s_filename)
#define _sym_filepath (_common_symbols->s_filepath)
#define _sym_filetypemessage (_common_symbols->s_filetypemessage)
#define _sym_fileusage (_common_symbols->s_fileusage)
#define _sym_filter (_common_symbols->s_filter)
#define _sym_filterget (_common_symbols->s_filterget)
#define _sym_filterset (_common_symbols->s_filterset)
#define _sym_find (_common_symbols->s_find)
#define _sym_find_enableselectall (_common_symbols->s_find_enableselectall)
#define _sym_findall (_common_symbols->s_findall)
#define _sym_finddoneclicked (_common_symbols->s_finddoneclicked)
#define _sym_findfirst (_common_symbols->s_findfirst)
#define _sym_findmaster (_common_symbols->s_findmaster)
#define _sym_findnextclicked (_common_symbols->s_findnextclicked)
#define _sym_findprevclicked (_common_symbols->s_findprevclicked)
#define _sym_findreturnkeypressed (_common_symbols->s_findreturnkeypressed)
#define _sym_findselectallclicked (_common_symbols->s_findselectallclicked)
#define _sym_findsize (_common_symbols->s_findsize)
#define _sym_findtextchanged (_common_symbols->s_findtextchanged)
#define _sym_first (_common_symbols->s_first)
#define _sym_firstline (_common_symbols->s_firstline)
#define _sym_firstobject (_common_symbols->s_firstobject)
#define _sym_firstview (_common_symbols->s_firstview)
#define _sym_five (_common_symbols->s_five)
#define _sym_fixed (_common_symbols->s_fixed)
#define _sym_fixwidth (_common_symbols->s_fixwidth)
#define _sym_flags (_common_symbols->s_flags)
#define _sym_flat (_common_symbols->s_flat)
#define _sym_float (_common_symbols->s_float)
#define _sym_float32 (_common_symbols->s_float32)
#define _sym_float64 (_common_symbols->s_float64)
#define _sym_floating (_common_symbols->s_floating)
#define _sym_flonum (_common_symbols->s_flonum)
#define _sym_flush (_common_symbols->s_flush)
#define _sym_focusgained (_common_symbols->s_focusgained)
#define _sym_focuslost (_common_symbols->s_focuslost)
#define _sym_focusonvis (_common_symbols->s_focusonvis)
#define _sym_fold (_common_symbols->s_fold)
#define _sym_folder (_common_symbols->s_folder)
#define _sym_folderdropped (_common_symbols->s_folderdropped)
#define _sym_folderpath (_common_symbols->s_folderpath)
#define _sym_font (_common_symbols->s_font)
#define _sym_fontchanged (_common_symbols->s_fontchanged)
#define _sym_fontface (_common_symbols->s_fontface)
#define _sym_fontfixwidth (_common_symbols->s_fontfixwidth)
#define _sym_fontinfochanged (_common_symbols->s_fontinfochanged)
#define _sym_fontname (_common_symbols->s_fontname)
#define _sym_fontnamechanged (_common_symbols->s_fontnamechanged)
#define _sym_fontpanel_isclientwindow (_common_symbols->s_fontpanel_isclientwindow)
#define _sym_fontpanelfontcolor (_common_symbols->s_fontpanelfontcolor)
#define _sym_fontpanelfontface (_common_symbols->s_fontpanelfontface)
#define _sym_fontpanelfontname (_common_symbols->s_fontpanelfontname)
#define _sym_fontpanelfontsize (_common_symbols->s_fontpanelfontsize)
#define _sym_fontsize (_common_symbols->s_fontsize)
#define _sym_fontsizechanged (_common_symbols->s_fontsizechanged)
#define _sym_fonttarget (_common_symbols->s_fonttarget)
#define _sym_forbidclose (_common_symbols->s_forbidclose)
#define _sym_forward (_common_symbols->s_forward)
#define _sym_four (_common_symbols->s_four)
#define _sym_fpic (_common_symbols->s_fpic)
#define _sym_free (_common_symbols->s_free)
#define _sym_freebang (_common_symbols->s_freebang)
#define _sym_freekeys (_common_symbols->s_freekeys)
#define _sym_freepatcherview (_common_symbols->s_freepatcherview)
#define _sym_frgb (_common_symbols->s_frgb)
#define _sym_frgba (_common_symbols->s_frgba)
#define _sym_fromdictionary (_common_symbols->s_fromdictionary)
#define _sym_fromgworld (_common_symbols->s_fromgworld)
#define _sym_frommatrix (_common_symbols->s_frommatrix)
#define _sym_frommatrix_trunc (_common_symbols->s_frommatrix_trunc)
#define _sym_front (_common_symbols->s_front)
#define _sym_frozen (_common_symbols->s_frozen)
#define _sym_frozen_box_attributes (_common_symbols->s_frozen_box_attributes)
#define _sym_frozen_object_attributes (_common_symbols->s_frozen_object_attributes)
#define _sym_frozen_pendingattrs (_common_symbols->s_frozen_pendingattrs)
#define _sym_frozen_text (_common_symbols->s_frozen_text)
#define _sym_fsaa (_common_symbols->s_fsaa)
#define _sym_fullname (_common_symbols->s_fullname)
#define _sym_fullscreen (_common_symbols->s_fullscreen)
#define _sym_funall (_common_symbols->s_funall)
#define _sym_function (_common_symbols->s_function)
#define _sym_g_inout_binlet (_common_symbols->s_g_inout_binlet)
#define _sym_g_max_newest (_common_symbols->s_g_max_newest)
#define _sym_g_max_newest_box (_common_symbols->s_g_max_newest_box)
#define _sym_gb (_common_symbols->s_gb)
#define _sym_genframe (_common_symbols->s_genframe)
#define _sym_get (_common_symbols->s_get)
#define _sym_get_jit_ob (_common_symbols->s_get_jit_ob)
#define _sym_getargumentlabel (_common_symbols->s_getargumentlabel)
#define _sym_getassoc (_common_symbols->s_getassoc)
#define _sym_getatoms (_common_symbols->s_getatoms)
#define _sym_getattrtext (_common_symbols->s_getattrtext)
#define _sym_getbounds (_common_symbols->s_getbounds)
#define _sym_getboxlayer (_common_symbols->s_getboxlayer)
#define _sym_getcaptioninfo (_common_symbols->s_getcaptioninfo)
#define _sym_getcellcolor (_common_symbols->s_getcellcolor)
#define _sym_getcelldescription (_common_symbols->s_getcelldescription)
#define _sym_getcelleditable (_common_symbols->s_getcelleditable)
#define _sym_getcellfiletypes (_common_symbols->s_getcellfiletypes)
#define _sym_getcellicon (_common_symbols->s_getcellicon)
#define _sym_getcellindentlevel (_common_symbols->s_getcellindentlevel)
#define _sym_getcellmenu (_common_symbols->s_getcellmenu)
#define _sym_getcelltext (_common_symbols->s_getcelltext)
#define _sym_getcelltextlength (_common_symbols->s_getcelltextlength)
#define _sym_getcellunits (_common_symbols->s_getcellunits)
#define _sym_getcellunitsyms (_common_symbols->s_getcellunitsyms)
#define _sym_getcellvalue (_common_symbols->s_getcellvalue)
#define _sym_getcolumnnames (_common_symbols->s_getcolumnnames)
#define _sym_getcomparisonlabel (_common_symbols->s_getcomparisonlabel)
#define _sym_getcomponent (_common_symbols->s_getcomponent)
#define _sym_getcontainedcomponent (_common_symbols->s_getcontainedcomponent)
#define _sym_getdata (_common_symbols->s_getdata)
#define _sym_getdefaultfocuscomponent (_common_symbols->s_getdefaultfocuscomponent)
#define _sym_getdefext (_common_symbols->s_getdefext)
#define _sym_getdeftype (_common_symbols->s_getdeftype)
#define _sym_getdrawparams (_common_symbols->s_getdrawparams)
#define _sym_getdst (_common_symbols->s_getdst)
#define _sym_getfieldlabel (_common_symbols->s_getfieldlabel)
#define _sym_getfindtext (_common_symbols->s_getfindtext)
#define _sym_getflags (_common_symbols->s_getflags)
#define _sym_getfolderpath (_common_symbols->s_getfolderpath)
#define _sym_getfonttarget (_common_symbols->s_getfonttarget)
#define _sym_getfontview (_common_symbols->s_getfontview)
#define _sym_getformat (_common_symbols->s_getformat)
#define _sym_gethintdelay (_common_symbols->s_gethintdelay)
#define _sym_getholder (_common_symbols->s_getholder)
#define _sym_getimage (_common_symbols->s_getimage)
#define _sym_getindex (_common_symbols->s_getindex)
#define _sym_getinfo (_common_symbols->s_getinfo)
#define _sym_getinports (_common_symbols->s_getinports)
#define _sym_getinput (_common_symbols->s_getinput)
#define _sym_getinputlist (_common_symbols->s_getinputlist)
#define _sym_getioproc (_common_symbols->s_getioproc)
#define _sym_getkeys (_common_symbols->s_getkeys)
#define _sym_getlastinsertid (_common_symbols->s_getlastinsertid)
#define _sym_getlayoutinfo (_common_symbols->s_getlayoutinfo)
#define _sym_getlogical (_common_symbols->s_getlogical)
#define _sym_getmatrix (_common_symbols->s_getmatrix)
#define _sym_getmethod (_common_symbols->s_getmethod)
#define _sym_getname (_common_symbols->s_getname)
#define _sym_getnamed (_common_symbols->s_getnamed)
#define _sym_getnamedbox (_common_symbols->s_getnamedbox)
#define _sym_getnextrecord (_common_symbols->s_getnextrecord)
#define _sym_getnthview (_common_symbols->s_getnthview)
#define _sym_getobject (_common_symbols->s_getobject)
#define _sym_getoffset (_common_symbols->s_getoffset)
#define _sym_getoutports (_common_symbols->s_getoutports)
#define _sym_getoutput (_common_symbols->s_getoutput)
#define _sym_getoutputlist (_common_symbols->s_getoutputlist)
#define _sym_getprobevalue (_common_symbols->s_getprobevalue)
#define _sym_getptr (_common_symbols->s_getptr)
#define _sym_getptr_forview (_common_symbols->s_getptr_forview)
#define _sym_getquantifierlabel (_common_symbols->s_getquantifierlabel)
#define _sym_getquery (_common_symbols->s_getquery)
#define _sym_getquerydict (_common_symbols->s_getquerydict)
#define _sym_getquerynames (_common_symbols->s_getquerynames)
#define _sym_getquerytype (_common_symbols->s_getquerytype)
#define _sym_getrect (_common_symbols->s_getrect)
#define _sym_getrowcolor (_common_symbols->s_getrowcolor)
#define _sym_getrowobject (_common_symbols->s_getrowobject)
#define _sym_getselected (_common_symbols->s_getselected)
#define _sym_getsize (_common_symbols->s_getsize)
#define _sym_getsort (_common_symbols->s_getsort)
#define _sym_getspecial (_common_symbols->s_getspecial)
#define _sym_getsrc (_common_symbols->s_getsrc)
#define _sym_getstackbase (_common_symbols->s_getstackbase)
#define _sym_getsyswind (_common_symbols->s_getsyswind)
#define _sym_gettextptr (_common_symbols->s_gettextptr)
#define _sym_gettitle (_common_symbols->s_gettitle)
#define _sym_gettype (_common_symbols->s_gettype)
#define _sym_gettypelist (_common_symbols->s_gettypelist)
#define _sym_getunitstext (_common_symbols->s_getunitstext)
#define _sym_getunitsyms (_common_symbols->s_getunitsyms)
#define _sym_getvalueof (_common_symbols->s_getvalueof)
#define _sym_getvisiblecanvasrect (_common_symbols->s_getvisiblecanvasrect)
#define _sym_getwind (_common_symbols->s_getwind)
#define _sym_getwindowrect (_common_symbols->s_getwindowrect)
#define _sym_gl_line_loop (_common_symbols->s_gl_line_loop)
#define _sym_gl_line_strip (_common_symbols->s_gl_line_strip)
#define _sym_gl_lines (_common_symbols->s_gl_lines)
#define _sym_gl_points (_common_symbols->s_gl_points)
#define _sym_gl_polygon (_common_symbols->s_gl_polygon)
#define _sym_gl_quad_grid (_common_symbols->s_gl_quad_grid)
#define _sym_gl_quad_strip (_common_symbols->s_gl_quad_strip)
#define _sym_gl_quads (_common_symbols->s_gl_quads)
#define _sym_gl_tri_fan (_common_symbols->s_gl_tri_fan)
#define _sym_gl_tri_grid (_common_symbols->s_gl_tri_grid)
#define _sym_gl_tri_strip (_common_symbols->s_gl_tri_strip)
#define _sym_gl_triangles (_common_symbols->s_gl_triangles)
#define _sym_global (_common_symbols->s_global)
#define _sym_globalpatchername (_common_symbols->s_globalpatchername)
#define _sym_go (_common_symbols->s_go)
#define _sym_grabfocus (_common_symbols->s_grabfocus)
#define _sym_greaterthan (_common_symbols->s_greaterthan)
#define _sym_green (_common_symbols->s_green)
#define _sym_grid (_common_symbols->s_grid)
#define _sym_gridonopen (_common_symbols->s_gridonopen)
#define _sym_gridsize (_common_symbols->s_gridsize)
#define _sym_gridsnap (_common_symbols->s_gridsnap)
#define _sym_gridsnaponopen (_common_symbols->s_gridsnaponopen)
#define _sym_group (_common_symbols->s_group)
#define _sym_grow (_common_symbols->s_grow)
#define _sym_growboth (_common_symbols->s_growboth)
#define _sym_growy (_common_symbols->s_growy)
#define _sym_hasclose (_common_symbols->s_hasclose)
#define _sym_hasdatatype (_common_symbols->s_hasdatatype)
#define _sym_hasgrow (_common_symbols->s_hasgrow)
#define _sym_hashorizscroll (_common_symbols->s_hashorizscroll)
#define _sym_hashtab_entry_free (_common_symbols->s_hashtab_entry_free)
#define _sym_hashtab_entry_new (_common_symbols->s_hashtab_entry_new)
#define _sym_hashtab_free (_common_symbols->s_hashtab_free)
#define _sym_hasmenu (_common_symbols->s_hasmenu)
#define _sym_hasminimize (_common_symbols->s_hasminimize)
#define _sym_hastitlebar (_common_symbols->s_hastitlebar)
#define _sym_hasvertscroll (_common_symbols->s_hasvertscroll)
#define _sym_haszoom (_common_symbols->s_haszoom)
#define _sym_head (_common_symbols->s_head)
#define _sym_height (_common_symbols->s_height)
#define _sym_help (_common_symbols->s_help)
#define _sym_helpfile (_common_symbols->s_helpfile)
#define _sym_helpmenu (_common_symbols->s_helpmenu)
#define _sym_helpname (_common_symbols->s_helpname)
#define _sym_hidden (_common_symbols->s_hidden)
#define _sym_hiddenconnect (_common_symbols->s_hiddenconnect)
#define _sym_hide (_common_symbols->s_hide)
#define _sym_hideablechanged (_common_symbols->s_hideablechanged)
#define _sym_hidecaption (_common_symbols->s_hidecaption)
#define _sym_hidewindow (_common_symbols->s_hidewindow)
#define _sym_hint (_common_symbols->s_hint)
#define _sym_hint_disabled (_common_symbols->s_hint_disabled)
#define _sym_hinttrack (_common_symbols->s_hinttrack)
#define _sym_history (_common_symbols->s_history)
#define _sym_history_entry (_common_symbols->s_history_entry)
#define _sym_hittest (_common_symbols->s_hittest)
#define _sym_holderoptions (_common_symbols->s_holderoptions)
#define _sym_hz (_common_symbols->s_hz)
#define _sym_icon (_common_symbols->s_icon)
#define _sym_id (_common_symbols->s_id)
#define _sym_identifier (_common_symbols->s_identifier)
#define _sym_ignoreclick (_common_symbols->s_ignoreclick)
#define _sym_image (_common_symbols->s_image)
#define _sym_imagefile (_common_symbols->s_imagefile)
#define _sym_imbed (_common_symbols->s_imbed)
#define _sym_imprint (_common_symbols->s_imprint)
#define _sym_includebg (_common_symbols->s_includebg)
#define _sym_index (_common_symbols->s_index)
#define _sym_info (_common_symbols->s_info)
#define _sym_init (_common_symbols->s_init)
#define _sym_inlet (_common_symbols->s_inlet)
#define _sym_inletinfo (_common_symbols->s_inletinfo)
#define _sym_inletnum (_common_symbols->s_inletnum)
#define _sym_inletoutlet (_common_symbols->s_inletoutlet)
#define _sym_inletscaleratio (_common_symbols->s_inletscaleratio)
#define _sym_inputcount (_common_symbols->s_inputcount)
#define _sym_insert (_common_symbols->s_insert)
#define _sym_insertboxtext (_common_symbols->s_insertboxtext)
#define _sym_insertindex (_common_symbols->s_insertindex)
#define _sym_insertpatcher (_common_symbols->s_insertpatcher)
#define _sym_insertsegment (_common_symbols->s_insertsegment)
#define _sym_insetchanged (_common_symbols->s_insetchanged)
#define _sym_insp (_common_symbols->s_insp)
#define _sym_inspectee (_common_symbols->s_inspectee)
#define _sym_inspectees (_common_symbols->s_inspectees)
#define _sym_inspector (_common_symbols->s_inspector)
#define _sym_inspector_clueclass (_common_symbols->s_inspector_clueclass)
#define _sym_inspector_color (_common_symbols->s_inspector_color)
#define _sym_inspector_customize (_common_symbols->s_inspector_customize)
#define _sym_inspector_editor (_common_symbols->s_inspector_editor)
#define _sym_inspector_fontattr (_common_symbols->s_inspector_fontattr)
#define _sym_inspector_rect (_common_symbols->s_inspector_rect)
#define _sym_inspector_tab (_common_symbols->s_inspector_tab)
#define _sym_inspector_tabheight (_common_symbols->s_inspector_tabheight)
#define _sym_inspector_title (_common_symbols->s_inspector_title)
#define _sym_inspector_toolbarid (_common_symbols->s_inspector_toolbarid)
#define _sym_inspectorchange (_common_symbols->s_inspectorchange)
#define _sym_instance_attributes (_common_symbols->s_instance_attributes)
#define _sym_instanceattr (_common_symbols->s_instanceattr)
#define _sym_int (_common_symbols->s_int)
#define _sym_int16 (_common_symbols->s_int16)
#define _sym_int24 (_common_symbols->s_int24)
#define _sym_int32 (_common_symbols->s_int32)
#define _sym_int8 (_common_symbols->s_int8)
#define _sym_interface (_common_symbols->s_interface)
#define _sym_interp (_common_symbols->s_interp)
#define _sym_interp_arg (_common_symbols->s_interp_arg)
#define _sym_interval (_common_symbols->s_interval)
#define _sym_invalidate (_common_symbols->s_invalidate)
#define _sym_invalidateallboxlayers (_common_symbols->s_invalidateallboxlayers)
#define _sym_invalidateboxlayer (_common_symbols->s_invalidateboxlayer)
#define _sym_invalidatetoolbar (_common_symbols->s_invalidatetoolbar)
#define _sym_invis (_common_symbols->s_invis)
#define _sym_invisaction (_common_symbols->s_invisaction)
#define _sym_invisible (_common_symbols->s_invisible)
#define _sym_invlabel (_common_symbols->s_invlabel)
#define _sym_invmsg (_common_symbols->s_invmsg)
#define _sym_ioname (_common_symbols->s_ioname)
#define _sym_ioproc (_common_symbols->s_ioproc)
#define _sym_is (_common_symbols->s_is)
#define _sym_iscolumnvisible (_common_symbols->s_iscolumnvisible)
#define _sym_isfile (_common_symbols->s_isfile)
#define _sym_isfirstin (_common_symbols->s_isfirstin)
#define _sym_isfolder (_common_symbols->s_isfolder)
#define _sym_iso_8859_1 (_common_symbols->s_iso_8859_1)
#define _sym_isproto (_common_symbols->s_isproto)
#define _sym_isselectedqueryremovable (_common_symbols->s_isselectedqueryremovable)
#define _sym_isselectionvalid (_common_symbols->s_isselectionvalid)
#define _sym_issystemquery (_common_symbols->s_issystemquery)
#define _sym_italic (_common_symbols->s_italic)
#define _sym_items (_common_symbols->s_items)
#define _sym_iterate (_common_symbols->s_iterate)
#define _sym_javascript (_common_symbols->s_javascript)
#define _sym_jbogus (_common_symbols->s_jbogus)
#define _sym_jbox (_common_symbols->s_jbox)
#define _sym_jbox_bytecount (_common_symbols->s_jbox_bytecount)
#define _sym_jbox_instances (_common_symbols->s_jbox_instances)
#define _sym_jboxattr (_common_symbols->s_jboxattr)
#define _sym_jdrag (_common_symbols->s_jdrag)
#define _sym_jed (_common_symbols->s_jed)
#define _sym_jgraphics (_common_symbols->s_jgraphics)
#define _sym_jit_attr_offset (_common_symbols->s_jit_attr_offset)
#define _sym_jit_attr_offset_array (_common_symbols->s_jit_attr_offset_array)
#define _sym_jit_attribute (_common_symbols->s_jit_attribute)
#define _sym_jit_gl_texture (_common_symbols->s_jit_gl_texture)
#define _sym_jit_linklist (_common_symbols->s_jit_linklist)
#define _sym_jit_matrix (_common_symbols->s_jit_matrix)
#define _sym_jit_mop (_common_symbols->s_jit_mop)
#define _sym_jit_namespace (_common_symbols->s_jit_namespace)
#define _sym_jpatcher (_common_symbols->s_jpatcher)
#define _sym_jpatcher_bytecount (_common_symbols->s_jpatcher_bytecount)
#define _sym_jpatcher_instances (_common_symbols->s_jpatcher_instances)
#define _sym_jpatchercontroller (_common_symbols->s_jpatchercontroller)
#define _sym_jpatcherholder (_common_symbols->s_jpatcherholder)
#define _sym_jpatchline (_common_symbols->s_jpatchline)
#define _sym_jpg (_common_symbols->s_jpg)
#define _sym_jsave (_common_symbols->s_jsave)
#define _sym_JSON (_common_symbols->s_JSON)
#define _sym_jsonreader (_common_symbols->s_jsonreader)
#define _sym_jsonwriter (_common_symbols->s_jsonwriter)
#define _sym_juibogus (_common_symbols->s_juibogus)
#define _sym_juiobject (_common_symbols->s_juiobject)
#define _sym_jundo_command (_common_symbols->s_jundo_command)
#define _sym_jundo_commandgroup (_common_symbols->s_jundo_commandgroup)
#define _sym_jweb_history (_common_symbols->s_jweb_history)
#define _sym_jwind (_common_symbols->s_jwind)
#define _sym_kb (_common_symbols->s_kb)
#define _sym_key (_common_symbols->s_key)
#define _sym_key_backslash (_common_symbols->s_key_backslash)
#define _sym_key_backspace (_common_symbols->s_key_backspace)
#define _sym_key_clear (_common_symbols->s_key_clear)
#define _sym_key_delete (_common_symbols->s_key_delete)
#define _sym_key_downarrow (_common_symbols->s_key_downarrow)
#define _sym_key_end (_common_symbols->s_key_end)
#define _sym_key_enter (_common_symbols->s_key_enter)
#define _sym_key_esc (_common_symbols->s_key_esc)
#define _sym_key_grave (_common_symbols->s_key_grave)
#define _sym_key_helpkey (_common_symbols->s_key_helpkey)
#define _sym_key_home (_common_symbols->s_key_home)
#define _sym_key_insert (_common_symbols->s_key_insert)
#define _sym_key_leftarrow (_common_symbols->s_key_leftarrow)
#define _sym_key_optionspace (_common_symbols->s_key_optionspace)
#define _sym_key_pagedown (_common_symbols->s_key_pagedown)
#define _sym_key_pageup (_common_symbols->s_key_pageup)
#define _sym_key_return (_common_symbols->s_key_return)
#define _sym_key_rightarrow (_common_symbols->s_key_rightarrow)
#define _sym_key_spacebar (_common_symbols->s_key_spacebar)
#define _sym_key_tab (_common_symbols->s_key_tab)
#define _sym_key_tilde (_common_symbols->s_key_tilde)
#define _sym_key_uparrow (_common_symbols->s_key_uparrow)
#define _sym_key_vertbar (_common_symbols->s_key_vertbar)
#define _sym_keyaction (_common_symbols->s_keyaction)
#define _sym_keyfilter (_common_symbols->s_keyfilter)
#define _sym_keyfocuschanged (_common_symbols->s_keyfocuschanged)
#define _sym_keymessage (_common_symbols->s_keymessage)
#define _sym_kind (_common_symbols->s_kind)
#define _sym_kindenum (_common_symbols->s_kindenum)
#define _sym_kindis (_common_symbols->s_kindis)
#define _sym_kindmenu (_common_symbols->s_kindmenu)
#define _sym_label (_common_symbols->s_label)
#define _sym_labels (_common_symbols->s_labels)
#define _sym_last (_common_symbols->s_last)
#define _sym_last_access (_common_symbols->s_last_access)
#define _sym_lastmessage (_common_symbols->s_lastmessage)
#define _sym_lastmodified (_common_symbols->s_lastmodified)
#define _sym_lastobject (_common_symbols->s_lastobject)
#define _sym_latency (_common_symbols->s_latency)
#define _sym_lessthan (_common_symbols->s_lessthan)
#define _sym_linear (_common_symbols->s_linear)
#define _sym_linechanged (_common_symbols->s_linechanged)
#define _sym_linecontextmenu (_common_symbols->s_linecontextmenu)
#define _sym_linecount (_common_symbols->s_linecount)
#define _sym_linenotify (_common_symbols->s_linenotify)
#define _sym_lines (_common_symbols->s_lines)
#define _sym_lineup (_common_symbols->s_lineup)
#define _sym_list (_common_symbols->s_list)
#define _sym_list_rowcomponent (_common_symbols->s_list_rowcomponent)
#define _sym_list_setvalue (_common_symbols->s_list_setvalue)
#define _sym_listboxprototype (_common_symbols->s_listboxprototype)
#define _sym_listfiles (_common_symbols->s_listfiles)
#define _sym_listwindow (_common_symbols->s_listwindow)
#define _sym_loadbang (_common_symbols->s_loadbang)
#define _sym_local (_common_symbols->s_local)
#define _sym_lock (_common_symbols->s_lock)
#define _sym_locked (_common_symbols->s_locked)
#define _sym_locked_iocolor (_common_symbols->s_locked_iocolor)
#define _sym_lockeddragscroll (_common_symbols->s_lockeddragscroll)
#define _sym_lockedpatchercontextmenu (_common_symbols->s_lockedpatchercontextmenu)
#define _sym_log (_common_symbols->s_log)
#define _sym_long (_common_symbols->s_long)
#define _sym_lookup (_common_symbols->s_lookup)
#define _sym_lookupcommand (_common_symbols->s_lookupcommand)
#define _sym_loop (_common_symbols->s_loop)
#define _sym_macroman (_common_symbols->s_macroman)
#define _sym_mainsearchentry (_common_symbols->s_mainsearchentry)
#define _sym_makearray (_common_symbols->s_makearray)
#define _sym_makeview (_common_symbols->s_makeview)
#define _sym_margin (_common_symbols->s_margin)
#define _sym_matchdragrole (_common_symbols->s_matchdragrole)
#define _sym_matchinspectees (_common_symbols->s_matchinspectees)
#define _sym_matrix (_common_symbols->s_matrix)
#define _sym_matrix_calc (_common_symbols->s_matrix_calc)
#define _sym_matrixctrl (_common_symbols->s_matrixctrl)
#define _sym_matrixname (_common_symbols->s_matrixname)
#define _sym_max (_common_symbols->s_max)
#define _sym_max_jit_classex (_common_symbols->s_max_jit_classex)
#define _sym_maxapplication (_common_symbols->s_maxapplication)
#define _sym_maxclass (_common_symbols->s_maxclass)
#define _sym_maxdebug (_common_symbols->s_maxdebug)
#define _sym_maxdim (_common_symbols->s_maxdim)
#define _sym_maximize (_common_symbols->s_maximize)
#define _sym_maxmessage (_common_symbols->s_maxmessage)
#define _sym_maxplanecount (_common_symbols->s_maxplanecount)
#define _sym_maxwindow (_common_symbols->s_maxwindow)
#define _sym_mb (_common_symbols->s_mb)
#define _sym_measuretext (_common_symbols->s_measuretext)
#define _sym_menu (_common_symbols->s_menu)
#define _sym_menubar (_common_symbols->s_menubar)
#define _sym_menus (_common_symbols->s_menus)
#define _sym_menus_runtime (_common_symbols->s_menus_runtime)
#define _sym_message (_common_symbols->s_message)
#define _sym_messages (_common_symbols->s_messages)
#define _sym_metadata (_common_symbols->s_metadata)
#define _sym_metadatalist (_common_symbols->s_metadatalist)
#define _sym_metadatawindow (_common_symbols->s_metadatawindow)
#define _sym_methodall (_common_symbols->s_methodall)
#define _sym_methodindex (_common_symbols->s_methodindex)
#define _sym_methods (_common_symbols->s_methods)
#define _sym_midpoints (_common_symbols->s_midpoints)
#define _sym_min (_common_symbols->s_min)
#define _sym_mindim (_common_symbols->s_mindim)
#define _sym_minimize (_common_symbols->s_minimize)
#define _sym_minplanecount (_common_symbols->s_minplanecount)
#define _sym_minus (_common_symbols->s_minus)
#define _sym_mode (_common_symbols->s_mode)
#define _sym_modified (_common_symbols->s_modified)
#define _sym_monitor (_common_symbols->s_monitor)
#define _sym_months (_common_symbols->s_months)
#define _sym_mousedoubleclick (_common_symbols->s_mousedoubleclick)
#define _sym_mousedown (_common_symbols->s_mousedown)
#define _sym_mousedownonchar (_common_symbols->s_mousedownonchar)
#define _sym_mousedrag (_common_symbols->s_mousedrag)
#define _sym_mousedragdelta (_common_symbols->s_mousedragdelta)
#define _sym_mouseenter (_common_symbols->s_mouseenter)
#define _sym_mouseleave (_common_symbols->s_mouseleave)
#define _sym_mousemove (_common_symbols->s_mousemove)
#define _sym_mousescale (_common_symbols->s_mousescale)
#define _sym_mouseup (_common_symbols->s_mouseup)
#define _sym_mousewheel (_common_symbols->s_mousewheel)
#define _sym_move (_common_symbols->s_move)
#define _sym_moveboxes (_common_symbols->s_moveboxes)
#define _sym_moved (_common_symbols->s_moved)
#define _sym_moveifoffdisplay (_common_symbols->s_moveifoffdisplay)
#define _sym_movelines (_common_symbols->s_movelines)
#define _sym_movesegment (_common_symbols->s_movesegment)
#define _sym_moviedim (_common_symbols->s_moviedim)
#define _sym_moviefile (_common_symbols->s_moviefile)
#define _sym_ms (_common_symbols->s_ms)
#define _sym_ms_ansi (_common_symbols->s_ms_ansi)
#define _sym_mulaw (_common_symbols->s_mulaw)
#define _sym_mult (_common_symbols->s_mult)
#define _sym_multiboxcontextmenu (_common_symbols->s_multiboxcontextmenu)
#define _sym_multilinecontextmenu (_common_symbols->s_multilinecontextmenu)
#define _sym_mute (_common_symbols->s_mute)
#define _sym_name (_common_symbols->s_name)
#define _sym_name_changed (_common_symbols->s_name_changed)
#define _sym_name_rowcomponent (_common_symbols->s_name_rowcomponent)
#define _sym_name_setvalue (_common_symbols->s_name_setvalue)
#define _sym_name_textcolor (_common_symbols->s_name_textcolor)
#define _sym_name_textstyle (_common_symbols->s_name_textstyle)
#define _sym_name_width (_common_symbols->s_name_width)
#define _sym_nameinspector (_common_symbols->s_nameinspector)
#define _sym_nativewindow (_common_symbols->s_nativewindow)
#define _sym_navkey (_common_symbols->s_navkey)
#define _sym_new (_common_symbols->s_new)
#define _sym_newcopy (_common_symbols->s_newcopy)
#define _sym_newdefault (_common_symbols->s_newdefault)
#define _sym_newex (_common_symbols->s_newex)
#define _sym_newfilebrowser (_common_symbols->s_newfilebrowser)
#define _sym_newfolder (_common_symbols->s_newfolder)
#define _sym_newlines (_common_symbols->s_newlines)
#define _sym_newobj (_common_symbols->s_newobj)
#define _sym_newobject (_common_symbols->s_newobject)
#define _sym_newobjects (_common_symbols->s_newobjects)
#define _sym_newpatcherview (_common_symbols->s_newpatcherview)
#define _sym_newpatchline (_common_symbols->s_newpatchline)
#define _sym_newquery (_common_symbols->s_newquery)
#define _sym_next (_common_symbols->s_next)
#define _sym_nextline (_common_symbols->s_nextline)
#define _sym_nextobject (_common_symbols->s_nextobject)
#define _sym_nextrecord (_common_symbols->s_nextrecord)
#define _sym_nextview (_common_symbols->s_nextview)
#define _sym_nfilters (_common_symbols->s_nfilters)
#define _sym_No (_common_symbols->s_No)
#define _sym_noactivate (_common_symbols->s_noactivate)
#define _sym_nobox (_common_symbols->s_nobox)
#define _sym_noclipse (_common_symbols->s_noclipse)
#define _sym_noclose (_common_symbols->s_noclose)
#define _sym_noedit (_common_symbols->s_noedit)
#define _sym_noeval (_common_symbols->s_noeval)
#define _sym_nofloat (_common_symbols->s_nofloat)
#define _sym_nofontpanel (_common_symbols->s_nofontpanel)
#define _sym_nogrow (_common_symbols->s_nogrow)
#define _sym_nomad (_common_symbols->s_nomad)
#define _sym_nomenu (_common_symbols->s_nomenu)
#define _sym_nominimize (_common_symbols->s_nominimize)
#define _sym_none (_common_symbols->s_none)
#define _sym_nonomad (_common_symbols->s_nonomad)
#define _sym_normalheight (_common_symbols->s_normalheight)
#define _sym_normalwidth (_common_symbols->s_normalwidth)
#define _sym_noscroll (_common_symbols->s_noscroll)
#define _sym_not (_common_symbols->s_not)
#define _sym_notevalues (_common_symbols->s_notevalues)
#define _sym_nothing (_common_symbols->s_nothing)
#define _sym_notify (_common_symbols->s_notify)
#define _sym_notifyall (_common_symbols->s_notifyall)
#define _sym_notifyall_delete (_common_symbols->s_notifyall_delete)
#define _sym_notifyall_new (_common_symbols->s_notifyall_new)
#define _sym_notitle (_common_symbols->s_notitle)
#define _sym_nozoom (_common_symbols->s_nozoom)
#define _sym_nth (_common_symbols->s_nth)
#define _sym_number (_common_symbols->s_number)
#define _sym_number_paint (_common_symbols->s_number_paint)
#define _sym_number_rowcomponent (_common_symbols->s_number_rowcomponent)
#define _sym_number_setvalue (_common_symbols->s_number_setvalue)
#define _sym_numfields (_common_symbols->s_numfields)
#define _sym_nummidpoints (_common_symbols->s_nummidpoints)
#define _sym_numrecords (_common_symbols->s_numrecords)
#define _sym_numresults (_common_symbols->s_numresults)
#define _sym_numrowschanged (_common_symbols->s_numrowschanged)
#define _sym_numtabs (_common_symbols->s_numtabs)
#define _sym_numviews (_common_symbols->s_numviews)
#define _sym_numwindowviews (_common_symbols->s_numwindowviews)
#define _sym_ob_sym (_common_symbols->s_ob_sym)
#define _sym_obex_container (_common_symbols->s_obex_container)
#define _sym_objargs (_common_symbols->s_objargs)
#define _sym_object (_common_symbols->s_object)
#define _sym_object_id (_common_symbols->s_object_id)
#define _sym_objectcount (_common_symbols->s_objectcount)
#define _sym_objectfilename (_common_symbols->s_objectfilename)
#define _sym_objectlist (_common_symbols->s_objectlist)
#define _sym_objectpalette (_common_symbols->s_objectpalette)
#define _sym_objectview_doubleclick (_common_symbols->s_objectview_doubleclick)
#define _sym_objectview_selected (_common_symbols->s_objectview_selected)
#define _sym_objptr2index (_common_symbols->s_objptr2index)
#define _sym_objtype (_common_symbols->s_objtype)
#define _sym_obtrusiveerror (_common_symbols->s_obtrusiveerror)
#define _sym_offset (_common_symbols->s_offset)
#define _sym_offset_rowcomponent (_common_symbols->s_offset_rowcomponent)
#define _sym_offset_setvalue (_common_symbols->s_offset_setvalue)
#define _sym_offsetfrom (_common_symbols->s_offsetfrom)
#define _sym_offsetmidpoints (_common_symbols->s_offsetmidpoints)
#define _sym_okclose (_common_symbols->s_okclose)
#define _sym_oksize (_common_symbols->s_oksize)
#define _sym_one (_common_symbols->s_one)
#define _sym_onoff (_common_symbols->s_onoff)
#define _sym_opaque (_common_symbols->s_opaque)
#define _sym_open (_common_symbols->s_open)
#define _sym_openassoc (_common_symbols->s_openassoc)
#define _sym_openfile (_common_symbols->s_openfile)
#define _sym_openinpresentation (_common_symbols->s_openinpresentation)
#define _sym_openquery (_common_symbols->s_openquery)
#define _sym_openrect (_common_symbols->s_openrect)
#define _sym_openweb (_common_symbols->s_openweb)
#define _sym_optional (_common_symbols->s_optional)
#define _sym_optionsdirty (_common_symbols->s_optionsdirty)
#define _sym_order (_common_symbols->s_order)
#define _sym_order_by (_common_symbols->s_order_by)
#define _sym_orderbefore (_common_symbols->s_orderbefore)
#define _sym_orderfront (_common_symbols->s_orderfront)
#define _sym_orientation (_common_symbols->s_orientation)
#define _sym_outlet (_common_symbols->s_outlet)
#define _sym_outletnum (_common_symbols->s_outletnum)
#define _sym_outline (_common_symbols->s_outline)
#define _sym_outmode (_common_symbols->s_outmode)
#define _sym_output (_common_symbols->s_output)
#define _sym_outputcount (_common_symbols->s_outputcount)
#define _sym_outputmatrix (_common_symbols->s_outputmatrix)
#define _sym_outputmode (_common_symbols->s_outputmode)
#define _sym_overdrive (_common_symbols->s_overdrive)
#define _sym_owner (_common_symbols->s_owner)
#define _sym_ownervis (_common_symbols->s_ownervis)
#define _sym_p (_common_symbols->s_p)
#define _sym_paint (_common_symbols->s_paint)
#define _sym_paintsbackground (_common_symbols->s_paintsbackground)
#define _sym_palette_action (_common_symbols->s_palette_action)
#define _sym_palette_caption (_common_symbols->s_palette_caption)
#define _sym_palette_category (_common_symbols->s_palette_category)
#define _sym_palette_numerical_order (_common_symbols->s_palette_numerical_order)
#define _sym_palette_order (_common_symbols->s_palette_order)
#define _sym_palette_protocount (_common_symbols->s_palette_protocount)
#define _sym_palette_tab_action (_common_symbols->s_palette_tab_action)
#define _sym_parameter_enable (_common_symbols->s_parameter_enable)
#define _sym_parent (_common_symbols->s_parent)
#define _sym_parentclass (_common_symbols->s_parentclass)
#define _sym_parentpatcher (_common_symbols->s_parentpatcher)
#define _sym_parse (_common_symbols->s_parse)
#define _sym_parsefile (_common_symbols->s_parsefile)
#define _sym_paste (_common_symbols->s_paste)
#define _sym_pastefileintoobject (_common_symbols->s_pastefileintoobject)
#define _sym_pastefrom (_common_symbols->s_pastefrom)
#define _sym_pastereplace (_common_symbols->s_pastereplace)
#define _sym_patcher (_common_symbols->s_patcher)
#define _sym_patchercomponent (_common_symbols->s_patchercomponent)
#define _sym_patchercontextmenu (_common_symbols->s_patchercontextmenu)
#define _sym_patchereditor (_common_symbols->s_patchereditor)
#define _sym_patchername (_common_symbols->s_patchername)
#define _sym_patchernotify (_common_symbols->s_patchernotify)
#define _sym_patcherview (_common_symbols->s_patcherview)
#define _sym_patcherview_instances (_common_symbols->s_patcherview_instances)
#define _sym_patcherview_invis (_common_symbols->s_patcherview_invis)
#define _sym_patcherview_notify_locked (_common_symbols->s_patcherview_notify_locked)
#define _sym_patcherview_notify_presentation (_common_symbols->s_patcherview_notify_presentation)
#define _sym_patcherview_vis (_common_symbols->s_patcherview_vis)
#define _sym_patching_position (_common_symbols->s_patching_position)
#define _sym_patching_rect (_common_symbols->s_patching_rect)
#define _sym_patching_size (_common_symbols->s_patching_size)
#define _sym_patchline (_common_symbols->s_patchline)
#define _sym_path (_common_symbols->s_path)
#define _sym_pattrstorage (_common_symbols->s_pattrstorage)
#define _sym_pclose (_common_symbols->s_pclose)
#define _sym_pending (_common_symbols->s_pending)
#define _sym_pic (_common_symbols->s_pic)
#define _sym_pictctrl (_common_symbols->s_pictctrl)
#define _sym_plane (_common_symbols->s_plane)
#define _sym_planecount (_common_symbols->s_planecount)
#define _sym_planelink (_common_symbols->s_planelink)
#define _sym_plugconfig (_common_symbols->s_plugconfig)
#define _sym_plus (_common_symbols->s_plus)
#define _sym_png (_common_symbols->s_png)
#define _sym_pointer (_common_symbols->s_pointer)
#define _sym_popupmenu (_common_symbols->s_popupmenu)
#define _sym_portenable (_common_symbols->s_portenable)
#define _sym_position (_common_symbols->s_position)
#define _sym_postname (_common_symbols->s_postname)
#define _sym_pound_B (_common_symbols->s_pound_B)
#define _sym_pound_D (_common_symbols->s_pound_D)
#define _sym_pound_N (_common_symbols->s_pound_N)
#define _sym_pound_P (_common_symbols->s_pound_P)
#define _sym_pound_X (_common_symbols->s_pound_X)
#define _sym_preferences (_common_symbols->s_preferences)
#define _sym_preload (_common_symbols->s_preload)
#define _sym_presentation (_common_symbols->s_presentation)
#define _sym_presentation_linecount (_common_symbols->s_presentation_linecount)
#define _sym_presentation_position (_common_symbols->s_presentation_position)
#define _sym_presentation_rect (_common_symbols->s_presentation_rect)
#define _sym_presentation_size (_common_symbols->s_presentation_size)
#define _sym_preset (_common_symbols->s_preset)
#define _sym_preset_data (_common_symbols->s_preset_data)
#define _sym_preview (_common_symbols->s_preview)
#define _sym_preview_image (_common_symbols->s_preview_image)
#define _sym_previewheight (_common_symbols->s_previewheight)
#define _sym_previewimagedata (_common_symbols->s_previewimagedata)
#define _sym_prevobject (_common_symbols->s_prevobject)
#define _sym_print (_common_symbols->s_print)
#define _sym_priority (_common_symbols->s_priority)
#define _sym_prototype (_common_symbols->s_prototype)
#define _sym_prototype_binbuf (_common_symbols->s_prototype_binbuf)
#define _sym_prototypename (_common_symbols->s_prototypename)
#define _sym_psave (_common_symbols->s_psave)
#define _sym_pulsate (_common_symbols->s_pulsate)
#define _sym_pupdate (_common_symbols->s_pupdate)
#define _sym_quantifier (_common_symbols->s_quantifier)
#define _sym_quantifier_exists (_common_symbols->s_quantifier_exists)
#define _sym_quantifiers (_common_symbols->s_quantifiers)
#define _sym_quantize (_common_symbols->s_quantize)
#define _sym_queries (_common_symbols->s_queries)
#define _sym_query (_common_symbols->s_query)
#define _sym_query_selected (_common_symbols->s_query_selected)
#define _sym_querycontroller (_common_symbols->s_querycontroller)
#define _sym_queryid (_common_symbols->s_queryid)
#define _sym_querylist (_common_symbols->s_querylist)
#define _sym_queryname (_common_symbols->s_queryname)
#define _sym_querypreview (_common_symbols->s_querypreview)
#define _sym_querysearch (_common_symbols->s_querysearch)
#define _sym_quickmap (_common_symbols->s_quickmap)
#define _sym_quit (_common_symbols->s_quit)
#define _sym_quitting (_common_symbols->s_quitting)
#define _sym_radial (_common_symbols->s_radial)
#define _sym_range (_common_symbols->s_range)
#define _sym_rawfind (_common_symbols->s_rawfind)
#define _sym_rawwindsave (_common_symbols->s_rawwindsave)
#define _sym_rawwindsaveas (_common_symbols->s_rawwindsaveas)
#define _sym_read (_common_symbols->s_read)
#define _sym_readonly (_common_symbols->s_readonly)
#define _sym_realclass (_common_symbols->s_realclass)
#define _sym_rebuilding (_common_symbols->s_rebuilding)
#define _sym_recordbyindex (_common_symbols->s_recordbyindex)
#define _sym_recreate_invis (_common_symbols->s_recreate_invis)
#define _sym_recreate_vis (_common_symbols->s_recreate_vis)
#define _sym_rect (_common_symbols->s_rect)
#define _sym_rectangle (_common_symbols->s_rectangle)
#define _sym_rectangular (_common_symbols->s_rectangular)
#define _sym_red (_common_symbols->s_red)
#define _sym_redostack (_common_symbols->s_redostack)
#define _sym_redraw (_common_symbols->s_redraw)
#define _sym_redrawcontents (_common_symbols->s_redrawcontents)
#define _sym_reference (_common_symbols->s_reference)
#define _sym_reffile (_common_symbols->s_reffile)
#define _sym_refinequery (_common_symbols->s_refinequery)
#define _sym_refresh (_common_symbols->s_refresh)
#define _sym_register (_common_symbols->s_register)
#define _sym_remove (_common_symbols->s_remove)
#define _sym_removeattr (_common_symbols->s_removeattr)
#define _sym_removeattr_enable (_common_symbols->s_removeattr_enable)
#define _sym_removeboxlayer (_common_symbols->s_removeboxlayer)
#define _sym_removeclient (_common_symbols->s_removeclient)
#define _sym_removefrompresentation (_common_symbols->s_removefrompresentation)
#define _sym_removelines (_common_symbols->s_removelines)
#define _sym_removeobjects (_common_symbols->s_removeobjects)
#define _sym_removesegment (_common_symbols->s_removesegment)
#define _sym_removeslot (_common_symbols->s_removeslot)
#define _sym_removewiretap (_common_symbols->s_removewiretap)
#define _sym_rename (_common_symbols->s_rename)
#define _sym_renumberslot (_common_symbols->s_renumberslot)
#define _sym_replace (_common_symbols->s_replace)
#define _sym_replaced_args (_common_symbols->s_replaced_args)
#define _sym_reschedule (_common_symbols->s_reschedule)
#define _sym_reset (_common_symbols->s_reset)
#define _sym_resize (_common_symbols->s_resize)
#define _sym_resizeaction (_common_symbols->s_resizeaction)
#define _sym_resized (_common_symbols->s_resized)
#define _sym_resizelimits (_common_symbols->s_resizelimits)
#define _sym_resizenotify (_common_symbols->s_resizenotify)
#define _sym_resolve_name (_common_symbols->s_resolve_name)
#define _sym_resolve_raw (_common_symbols->s_resolve_raw)
#define _sym_resort (_common_symbols->s_resort)
#define _sym_resource (_common_symbols->s_resource)
#define _sym_respondtoclick (_common_symbols->s_respondtoclick)
#define _sym_restore (_common_symbols->s_restore)
#define _sym_restrict_dim (_common_symbols->s_restrict_dim)
#define _sym_restrict_planecount (_common_symbols->s_restrict_planecount)
#define _sym_restrict_type (_common_symbols->s_restrict_type)
#define _sym_result (_common_symbols->s_result)
#define _sym_retain (_common_symbols->s_retain)
#define _sym_revealinfinder (_common_symbols->s_revealinfinder)
#define _sym_reverse (_common_symbols->s_reverse)
#define _sym_rgb (_common_symbols->s_rgb)
#define _sym_rgba (_common_symbols->s_rgba)
#define _sym_rolename (_common_symbols->s_rolename)
#define _sym_rotate (_common_symbols->s_rotate)
#define _sym_rounded (_common_symbols->s_rounded)
#define _sym_rowcolorchanged (_common_symbols->s_rowcolorchanged)
#define _sym_rowcomponent (_common_symbols->s_rowcomponent)
#define _sym_rowenabled (_common_symbols->s_rowenabled)
#define _sym_rowhead (_common_symbols->s_rowhead)
#define _sym_rowheightchanged (_common_symbols->s_rowheightchanged)
#define _sym_safebang (_common_symbols->s_safebang)
#define _sym_safeclear (_common_symbols->s_safeclear)
#define _sym_samples (_common_symbols->s_samples)
#define _sym_save (_common_symbols->s_save)
#define _sym_save2 (_common_symbols->s_save2)
#define _sym_saveas (_common_symbols->s_saveas)
#define _sym_saveboxprototype (_common_symbols->s_saveboxprototype)
#define _sym_saved_object_attributes (_common_symbols->s_saved_object_attributes)
#define _sym_savefilepath (_common_symbols->s_savefilepath)
#define _sym_savelasttab (_common_symbols->s_savelasttab)
#define _sym_savequery (_common_symbols->s_savequery)
#define _sym_saveto (_common_symbols->s_saveto)
#define _sym_savewindow (_common_symbols->s_savewindow)
#define _sym_savingdefault (_common_symbols->s_savingdefault)
#define _sym_scale (_common_symbols->s_scale)
#define _sym_script (_common_symbols->s_script)
#define _sym_scrollanimatetime (_common_symbols->s_scrollanimatetime)
#define _sym_scrolloffset (_common_symbols->s_scrolloffset)
#define _sym_scrollorigin (_common_symbols->s_scrollorigin)
#define _sym_scrollposition (_common_symbols->s_scrollposition)
#define _sym_scrollselectedobjectsintoview (_common_symbols->s_scrollselectedobjectsintoview)
#define _sym_scrollto (_common_symbols->s_scrollto)
#define _sym_scrollviewtoshow (_common_symbols->s_scrollviewtoshow)
#define _sym_search (_common_symbols->s_search)
#define _sym_searchterm (_common_symbols->s_searchterm)
#define _sym_searchtext (_common_symbols->s_searchtext)
#define _sym_select (_common_symbols->s_select)
#define _sym_selectallonedit (_common_symbols->s_selectallonedit)
#define _sym_selectbox (_common_symbols->s_selectbox)
#define _sym_selectcategory (_common_symbols->s_selectcategory)
#define _sym_selectcell (_common_symbols->s_selectcell)
#define _sym_selectdropped (_common_symbols->s_selectdropped)
#define _sym_selected (_common_symbols->s_selected)
#define _sym_selectedboxes (_common_symbols->s_selectedboxes)
#define _sym_selectedlines (_common_symbols->s_selectedlines)
#define _sym_selectedrow (_common_symbols->s_selectedrow)
#define _sym_selectedrow_contextual (_common_symbols->s_selectedrow_contextual)
#define _sym_selfsave (_common_symbols->s_selfsave)
#define _sym_selmode (_common_symbols->s_selmode)
#define _sym_send (_common_symbols->s_send)
#define _sym_sendbackward (_common_symbols->s_sendbackward)
#define _sym_sendbox (_common_symbols->s_sendbox)
#define _sym_sendboxmsg (_common_symbols->s_sendboxmsg)
#define _sym_senderclasssym (_common_symbols->s_senderclasssym)
#define _sym_sendtoback (_common_symbols->s_sendtoback)
#define _sym_session_usage_count (_common_symbols->s_session_usage_count)
#define _sym_set (_common_symbols->s_set)
#define _sym_setall (_common_symbols->s_setall)
#define _sym_setassoc (_common_symbols->s_setassoc)
#define _sym_setatoms (_common_symbols->s_setatoms)
#define _sym_setattr (_common_symbols->s_setattr)
#define _sym_setboxrect (_common_symbols->s_setboxrect)
#define _sym_setcellunits (_common_symbols->s_setcellunits)
#define _sym_setcellvalue (_common_symbols->s_setcellvalue)
#define _sym_setcontainedcomponent (_common_symbols->s_setcontainedcomponent)
#define _sym_setdata (_common_symbols->s_setdata)
#define _sym_setdefaults (_common_symbols->s_setdefaults)
#define _sym_setdirty (_common_symbols->s_setdirty)
#define _sym_seteditboxcaretposition (_common_symbols->s_seteditboxcaretposition)
#define _sym_seteditboxhighlightedregion (_common_symbols->s_seteditboxhighlightedregion)
#define _sym_seteditview (_common_symbols->s_seteditview)
#define _sym_setfilter (_common_symbols->s_setfilter)
#define _sym_setflags (_common_symbols->s_setflags)
#define _sym_setfont (_common_symbols->s_setfont)
#define _sym_setglobalcoords (_common_symbols->s_setglobalcoords)
#define _sym_setinfo (_common_symbols->s_setinfo)
#define _sym_setinfo_ex (_common_symbols->s_setinfo_ex)
#define _sym_setmethod (_common_symbols->s_setmethod)
#define _sym_setmidpoint (_common_symbols->s_setmidpoint)
#define _sym_setpatcherattr (_common_symbols->s_setpatcherattr)
#define _sym_setptr (_common_symbols->s_setptr)
#define _sym_setrect (_common_symbols->s_setrect)
#define _sym_setspecialrow (_common_symbols->s_setspecialrow)
#define _sym_settext (_common_symbols->s_settext)
#define _sym_setunitsym (_common_symbols->s_setunitsym)
#define _sym_setvalue (_common_symbols->s_setvalue)
#define _sym_setvalueof (_common_symbols->s_setvalueof)
#define _sym_setvaluetext (_common_symbols->s_setvaluetext)
#define _sym_setwindowrect (_common_symbols->s_setwindowrect)
#define _sym_setwindowsize (_common_symbols->s_setwindowsize)
#define _sym_setzorder (_common_symbols->s_setzorder)
#define _sym_shortcut (_common_symbols->s_shortcut)
#define _sym_show (_common_symbols->s_show)
#define _sym_showcaption (_common_symbols->s_showcaption)
#define _sym_showdoc (_common_symbols->s_showdoc)
#define _sym_showfind (_common_symbols->s_showfind)
#define _sym_showpreview (_common_symbols->s_showpreview)
#define _sym_showrecent (_common_symbols->s_showrecent)
#define _sym_showrow (_common_symbols->s_showrow)
#define _sym_showsaveable (_common_symbols->s_showsaveable)
#define _sym_showtarget (_common_symbols->s_showtarget)
#define _sym_shuffle (_common_symbols->s_shuffle)
#define _sym_signal (_common_symbols->s_signal)
#define _sym_sinceyesterday (_common_symbols->s_sinceyesterday)
#define _sym_singleinspector (_common_symbols->s_singleinspector)
#define _sym_size (_common_symbols->s_size)
#define _sym_sizeboxes (_common_symbols->s_sizeboxes)
#define _sym_slot_definition (_common_symbols->s_slot_definition)
#define _sym_slot_modified (_common_symbols->s_slot_modified)
#define _sym_slots (_common_symbols->s_slots)
#define _sym_smpte (_common_symbols->s_smpte)
#define _sym_snaptogrid (_common_symbols->s_snaptogrid)
#define _sym_sort (_common_symbols->s_sort)
#define _sym_sortablechanged (_common_symbols->s_sortablechanged)
#define _sym_sortcolumn (_common_symbols->s_sortcolumn)
#define _sym_sortdata (_common_symbols->s_sortdata)
#define _sym_sorted (_common_symbols->s_sorted)
#define _sym_sorted_by_column (_common_symbols->s_sorted_by_column)
#define _sym_source (_common_symbols->s_source)
#define _sym_spacing (_common_symbols->s_spacing)
#define _sym_special (_common_symbols->s_special)
#define _sym_specialclick (_common_symbols->s_specialclick)
#define _sym_specialcount (_common_symbols->s_specialcount)
#define _sym_sql (_common_symbols->s_sql)
#define _sym_sql2 (_common_symbols->s_sql2)
#define _sym_sqlite (_common_symbols->s_sqlite)
#define _sym_sqlite_result (_common_symbols->s_sqlite_result)
#define _sym_sqlstring (_common_symbols->s_sqlstring)
#define _sym_sr (_common_symbols->s_sr)
#define _sym_start (_common_symbols->s_start)
#define _sym_startdrag (_common_symbols->s_startdrag)
#define _sym_startmoveboxes (_common_symbols->s_startmoveboxes)
#define _sym_startpoint (_common_symbols->s_startpoint)
#define _sym_startprobe (_common_symbols->s_startprobe)
#define _sym_starttransaction (_common_symbols->s_starttransaction)
#define _sym_startwindow (_common_symbols->s_startwindow)
#define _sym_state (_common_symbols->s_state)
#define _sym_sticky_attr (_common_symbols->s_sticky_attr)
#define _sym_sticky_method (_common_symbols->s_sticky_method)
#define _sym_stop (_common_symbols->s_stop)
#define _sym_store (_common_symbols->s_store)
#define _sym_straighten (_common_symbols->s_straighten)
#define _sym_straightend (_common_symbols->s_straightend)
#define _sym_straightstart (_common_symbols->s_straightstart)
#define _sym_straightthresh (_common_symbols->s_straightthresh)
#define _sym_string (_common_symbols->s_string)
#define _sym_style (_common_symbols->s_style)
#define _sym_sub (_common_symbols->s_sub)
#define _sym_subpatcher (_common_symbols->s_subpatcher)
#define _sym_surfacebuffer (_common_symbols->s_surfacebuffer)
#define _sym_svg (_common_symbols->s_svg)
#define _sym_swap (_common_symbols->s_swap)
#define _sym_swatches (_common_symbols->s_swatches)
#define _sym_symbol (_common_symbols->s_symbol)
#define _sym_sysqelem (_common_symbols->s_sysqelem)
#define _sym_t (_common_symbols->s_t)
#define _sym_tab_bgcolor (_common_symbols->s_tab_bgcolor)
#define _sym_table (_common_symbols->s_table)
#define _sym_tabledata (_common_symbols->s_tabledata)
#define _sym_tag (_common_symbols->s_tag)
#define _sym_tags (_common_symbols->s_tags)
#define _sym_tapcontroller_show (_common_symbols->s_tapcontroller_show)
#define _sym_tapwindow (_common_symbols->s_tapwindow)
#define _sym_target (_common_symbols->s_target)
#define _sym_template (_common_symbols->s_template)
#define _sym_tempo (_common_symbols->s_tempo)
#define _sym_text (_common_symbols->s_text)
#define _sym_text_commaseparated (_common_symbols->s_text_commaseparated)
#define _sym_text_large (_common_symbols->s_text_large)
#define _sym_text_onesymbol (_common_symbols->s_text_onesymbol)
#define _sym_textchanged (_common_symbols->s_textchanged)
#define _sym_textcolor (_common_symbols->s_textcolor)
#define _sym_textfield (_common_symbols->s_textfield)
#define _sym_textfile (_common_symbols->s_textfile)
#define _sym_textmargins (_common_symbols->s_textmargins)
#define _sym_textstyle (_common_symbols->s_textstyle)
#define _sym_thismonth (_common_symbols->s_thismonth)
#define _sym_thisweek (_common_symbols->s_thisweek)
#define _sym_threadpriority (_common_symbols->s_threadpriority)
#define _sym_threadsafe (_common_symbols->s_threadsafe)
#define _sym_three (_common_symbols->s_three)
#define _sym_ticks (_common_symbols->s_ticks)
#define _sym_time (_common_symbols->s_time)
#define _sym_timeobj (_common_symbols->s_timeobj)
#define _sym_timesigchanged (_common_symbols->s_timesigchanged)
#define _sym_timeupdate (_common_symbols->s_timeupdate)
#define _sym_tinge (_common_symbols->s_tinge)
#define _sym_title (_common_symbols->s_title)
#define _sym_titleassoc (_common_symbols->s_titleassoc)
#define _sym_tobinbuf (_common_symbols->s_tobinbuf)
#define _sym_toc (_common_symbols->s_toc)
#define _sym_today (_common_symbols->s_today)
#define _sym_todictionary (_common_symbols->s_todictionary)
#define _sym_togworld (_common_symbols->s_togworld)
#define _sym_tool (_common_symbols->s_tool)
#define _sym_tool_paint (_common_symbols->s_tool_paint)
#define _sym_tool_rowcomponent (_common_symbols->s_tool_rowcomponent)
#define _sym_tool_setvalue (_common_symbols->s_tool_setvalue)
#define _sym_tool_sort (_common_symbols->s_tool_sort)
#define _sym_toolbarheight (_common_symbols->s_toolbarheight)
#define _sym_toolbarid (_common_symbols->s_toolbarid)
#define _sym_toolbars (_common_symbols->s_toolbars)
#define _sym_toolbarvisible (_common_symbols->s_toolbarvisible)
#define _sym_top_inset (_common_symbols->s_top_inset)
#define _sym_topmost (_common_symbols->s_topmost)
#define _sym_toppatcher (_common_symbols->s_toppatcher)
#define _sym_topredoname (_common_symbols->s_topredoname)
#define _sym_topundoname (_common_symbols->s_topundoname)
#define _sym_trackaction (_common_symbols->s_trackaction)
#define _sym_transparent (_common_symbols->s_transparent)
#define _sym_transport (_common_symbols->s_transport)
#define _sym_traverse (_common_symbols->s_traverse)
#define _sym_triangle (_common_symbols->s_triangle)
#define _sym_tutorial (_common_symbols->s_tutorial)
#define _sym_two (_common_symbols->s_two)
#define _sym_twobytecomment (_common_symbols->s_twobytecomment)
#define _sym_type (_common_symbols->s_type)
#define _sym_typed_usage_count (_common_symbols->s_typed_usage_count)
#define _sym_typedwrapper (_common_symbols->s_typedwrapper)
#define _sym_typelink (_common_symbols->s_typelink)
#define _sym_types (_common_symbols->s_types)
#define _sym_underline (_common_symbols->s_underline)
#define _sym_understands (_common_symbols->s_understands)
#define _sym_undo (_common_symbols->s_undo)
#define _sym_undostack (_common_symbols->s_undostack)
#define _sym_unimbed (_common_symbols->s_unimbed)
#define _sym_uninitialized (_common_symbols->s_uninitialized)
#define _sym_unique (_common_symbols->s_unique)
#define _sym_unit (_common_symbols->s_unit)
#define _sym_units (_common_symbols->s_units)
#define _sym_unlocked_iocolor (_common_symbols->s_unlocked_iocolor)
#define _sym_unlockedinteraction (_common_symbols->s_unlockedinteraction)
#define _sym_unset (_common_symbols->s_unset)
#define _sym_up (_common_symbols->s_up)
#define _sym_update (_common_symbols->s_update)
#define _sym_update_metadata (_common_symbols->s_update_metadata)
#define _sym_updatecommand (_common_symbols->s_updatecommand)
#define _sym_updatecontent (_common_symbols->s_updatecontent)
#define _sym_updatefind (_common_symbols->s_updatefind)
#define _sym_updatelookandfeel (_common_symbols->s_updatelookandfeel)
#define _sym_updatemenu (_common_symbols->s_updatemenu)
#define _sym_updateprototypes (_common_symbols->s_updateprototypes)
#define _sym_updatequery (_common_symbols->s_updatequery)
#define _sym_updatequerydict (_common_symbols->s_updatequerydict)
#define _sym_updaterect (_common_symbols->s_updaterect)
#define _sym_url (_common_symbols->s_url)
#define _sym_us_ascii (_common_symbols->s_us_ascii)
#define _sym_usage_count (_common_symbols->s_usage_count)
#define _sym_usedslotlist (_common_symbols->s_usedslotlist)
#define _sym_useellipsis (_common_symbols->s_useellipsis)
#define _sym_useimagebuffer (_common_symbols->s_useimagebuffer)
#define _sym_usemax (_common_symbols->s_usemax)
#define _sym_usemin (_common_symbols->s_usemin)
#define _sym_user (_common_symbols->s_user)
#define _sym_usercanget (_common_symbols->s_usercanget)
#define _sym_usercanset (_common_symbols->s_usercanset)
#define _sym_utf_16 (_common_symbols->s_utf_16)
#define _sym_utf_16be (_common_symbols->s_utf_16be)
#define _sym_utf_16le (_common_symbols->s_utf_16le)
#define _sym_utf_8 (_common_symbols->s_utf_8)
#define _sym_val (_common_symbols->s_val)
#define _sym_value (_common_symbols->s_value)
#define _sym_value_endchange (_common_symbols->s_value_endchange)
#define _sym_value_rowcomponent (_common_symbols->s_value_rowcomponent)
#define _sym_valuebyindex (_common_symbols->s_valuebyindex)
#define _sym_varname (_common_symbols->s_varname)
#define _sym_varname_set (_common_symbols->s_varname_set)
#define _sym_varname_unset (_common_symbols->s_varname_unset)
#define _sym_version (_common_symbols->s_version)
#define _sym_videofile (_common_symbols->s_videofile)
#define _sym_views (_common_symbols->s_views)
#define _sym_viewspan (_common_symbols->s_viewspan)
#define _sym_vignette (_common_symbols->s_vignette)
#define _sym_vis (_common_symbols->s_vis)
#define _sym_visibilitychanged (_common_symbols->s_visibilitychanged)
#define _sym_visible (_common_symbols->s_visible)
#define _sym_visiblecanvasrect (_common_symbols->s_visiblecanvasrect)
#define _sym_vol (_common_symbols->s_vol)
#define _sym_vpicture (_common_symbols->s_vpicture)
#define _sym_vpreset (_common_symbols->s_vpreset)
#define _sym_wantfree (_common_symbols->s_wantfree)
#define _sym_wantsreturn (_common_symbols->s_wantsreturn)
#define _sym_wantstab (_common_symbols->s_wantstab)
#define _sym_watch (_common_symbols->s_watch)
#define _sym_watchpoint_flags (_common_symbols->s_watchpoint_flags)
#define _sym_watchpoint_id (_common_symbols->s_watchpoint_id)
#define _sym_wclose (_common_symbols->s_wclose)
#define _sym_webpage (_common_symbols->s_webpage)
#define _sym_weeks (_common_symbols->s_weeks)
#define _sym_wind (_common_symbols->s_wind)
#define _sym_window (_common_symbols->s_window)
#define _sym_windowbounds (_common_symbols->s_windowbounds)
#define _sym_windowrect (_common_symbols->s_windowrect)
#define _sym_windsave (_common_symbols->s_windsave)
#define _sym_wiretap (_common_symbols->s_wiretap)
#define _sym_withinlast (_common_symbols->s_withinlast)
#define _sym_wobjectname (_common_symbols->s_wobjectname)
#define _sym_wordwrap (_common_symbols->s_wordwrap)
#define _sym_workspace (_common_symbols->s_workspace)
#define _sym_write (_common_symbols->s_write)
#define _sym_writedictionary (_common_symbols->s_writedictionary)
#define _sym_xmlfile (_common_symbols->s_xmlfile)
#define _sym_years (_common_symbols->s_years)
#define _sym_zero (_common_symbols->s_zero)
#define _sym_zoom (_common_symbols->s_zoom)
#define _sym_zoombox (_common_symbols->s_zoombox)
#define _sym_zoomfactor (_common_symbols->s_zoomfactor)
#define _sym_zorder (_common_symbols->s_zorder)
#define _sym_zzz (_common_symbols->s_zzz)
#define _sym_Sans_Serif (_common_symbols->s_Sans_Serif)

extern t_common_symbols_table *_common_symbols;

void common_symbols_init(void);
t_common_symbols_table *common_symbols_gettable(void);

END_USING_C_LINKAGE

#endif // __COMMON_SYMBOLS_H__
