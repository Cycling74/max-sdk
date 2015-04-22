#ifndef _JPATCHER_SYMS_H_
#define _JPATCHER_SYMS_H_

BEGIN_USING_C_LINKAGE

void jpatcher_syms_init(void);

extern t_symbol *ps_patcher; 
extern t_symbol *ps_jpatchline; 
extern t_symbol *ps_jpatcher; 
extern t_symbol *ps_patcherview; 
extern t_symbol *ps_juiobject;		// attribute who's existence means we are a new style UI object

extern t_symbol *ps__set;

// notifications
extern t_symbol *ps_patchernotify;
extern t_symbol *ps_boxnotify;
extern t_symbol *ps_linenotify;

extern t_symbol *ps_user;
extern t_symbol *ps_defaultname;

// patchernotify
extern t_symbol *ps_rect;
extern t_symbol *ps_free;
extern t_symbol *ps_imbed; 
extern t_symbol *ps_unimbed; 
extern t_symbol *ps_snaptogrid; 
extern t_symbol *ps_invis; 
extern t_symbol *ps_toolbarvisible;

// boxnotify
extern t_symbol *ps_newobject;
extern t_symbol *ps_free;		
extern t_symbol *ps_redraw;
extern t_symbol *ps_redrawcontents; 
extern t_symbol *ps_textchanged; 
extern t_symbol *ps_textcolor; 
extern t_symbol *ps_color; 
extern t_symbol *ps_grabfocus; 
extern t_symbol *ps_fontchanged; 
extern t_symbol *ps_inletoutlet;
extern t_symbol *ps_bfixwidth; 
extern t_symbol *ps_showcaption;
extern t_symbol *ps_hidecaption;
extern t_symbol *ps_freecontainedview;
extern t_symbol *ps_rebuildcontainedview;
extern t_symbol *ps_viewvisibility;
extern t_symbol *ps_viewvisibilitychanged;

// linenotify
extern t_symbol *ps_newobject;
extern t_symbol *ps_free;
extern t_symbol *ps_linechanged; 

// if a box attribute changes a boxnotify message containing the attribute name will be sent. 
// I won't repeat the attributes here as they are listed below. 

// linenotify
extern t_symbol *ps_newobject;   

// Attributes of the patcher class
extern t_symbol *ps_box;
extern t_symbol *ps_count;
extern t_symbol *ps_locked;
extern t_symbol *ps_firstobject;
extern t_symbol *ps_lastobject;
extern t_symbol *ps_firstline;
extern t_symbol *ps_firstview; 
extern t_symbol *ps_title;
extern t_symbol *ps_name;
extern t_symbol *ps_filepath; 
extern t_symbol *ps_savefilepath;
extern t_symbol *ps_filename; 
extern t_symbol *ps_dirty;
extern t_symbol *ps_bglocked;
extern t_symbol *ps_bghidden;
extern t_symbol *ps_fghidden;
extern t_symbol *ps_font;
extern t_symbol *ps_bgcolor; 
extern t_symbol *ps_editing_bgcolor;
extern t_symbol *ps_locked_bgcolor;
extern t_symbol *ps_gridsize; 
extern t_symbol *ps_controller;
extern t_symbol *ps_parentpatcher;
extern t_symbol *ps_toppatcher;
extern t_symbol *ps_maxclass;
extern t_symbol *ps_parentclass;
extern t_symbol *ps_scrolloffset;
extern t_symbol *ps_scrollorigin;
extern t_symbol *ps_wind;
extern t_symbol *ps_noedit; 
extern t_symbol *ps_collective; 
extern t_symbol *ps_cansave; 
extern t_symbol *ps_presentation;

// methods of the patcher class
extern t_symbol *ps_newobject;	
extern t_symbol *ps_newdefault;
extern t_symbol *ps_connect;
extern t_symbol *ps_hiddenconnect;
extern t_symbol *ps_disconnect;
extern t_symbol *ps_apply;
extern t_symbol *ps_applydeep;
extern t_symbol *ps_applyif;
extern t_symbol *ps_applydeepif;
extern t_symbol *ps_remove;
extern t_symbol *ps_getnamed;
extern t_symbol *ps_getlogical;
extern t_symbol *ps_bringtofront;
extern t_symbol *ps_sendtoback;

// Attributes of the Maxobj class
extern t_symbol *ps_rect;
extern t_symbol *ps_presentation_rect; 
extern t_symbol *ps_patching_rect; 
extern t_symbol *ps_jp_position;
extern t_symbol *ps_presentation_position; 
extern t_symbol *ps_patching_position; 
extern t_symbol *ps_size;
extern t_symbol *ps_presentation_size; 
extern t_symbol *ps_patching_size; 
extern t_symbol *ps_object;
extern t_symbol *ps_maxclass;
extern t_symbol *ps_patcher;
extern t_symbol *ps_hint; 
extern t_symbol *ps_hidden;		
extern t_symbol *ps_fontname;
extern t_symbol *ps_fontsize;
extern t_symbol *ps_fontface;
extern t_symbol *ps_textcolor;
extern t_symbol *ps_color; 
extern t_symbol *ps_nextobject;
extern t_symbol *ps_prevobject;
extern t_symbol *ps_varname;
extern t_symbol *ps_id; 
extern t_symbol *ps_canhilite;  
extern t_symbol *ps_zorder; 
extern t_symbol *ps_background;
extern t_symbol *ps_ignoreclick; 
extern t_symbol *ps_drawfirstin;
extern t_symbol *ps_outline;
extern t_symbol *ps_growy;
extern t_symbol *ps_growboth;
extern t_symbol *ps_nogrow;
extern t_symbol *ps_drawinlast; 
extern t_symbol *ps_transparent;
extern t_symbol *ps_mousedragdelta;
extern t_symbol *ps_textfield; 
extern t_symbol *ps_presentation_rect;
extern t_symbol *ps_opaque; 
extern t_symbol *ps_useimagebuffer; 
extern t_symbol *ps_hide;
extern t_symbol *ps_show;
extern t_symbol *ps_move;
extern t_symbol *ps_offset;
extern t_symbol *ps_respondtoclick;

// Methods of the Maxobj class
extern t_symbol *ps_message; 
extern t_symbol *ps_help;
extern t_symbol *ps_subpatcher;
extern t_symbol *ps_understands;

// attributes of the jpatchline
extern t_symbol *ps_startpoint;
extern t_symbol *ps_endpoint;
extern t_symbol *ps_pending;
extern t_symbol *ps_nummidpoints; 
extern t_symbol *ps_midpoints;
extern t_symbol *ps_box1;
extern t_symbol *ps_outletnum; 
extern t_symbol *ps_box2;
extern t_symbol *ps_inletnum; 
extern t_symbol *ps_hidden;
extern t_symbol *ps_color; 
extern t_symbol *ps_boundingbox; 
extern t_symbol *ps_straightthresh;
extern t_symbol *ps_straightstart;
extern t_symbol *ps_straightend; 
extern t_symbol *ps_nextline; 

// attributes of the patcherview
extern t_symbol *ps_visible;
extern t_symbol *ps_locked;
extern t_symbol *ps_unlockedinteraction; 
extern t_symbol *ps_zoomfactor;
extern t_symbol *ps_nextview;
extern t_symbol *ps_jgraphics;
extern t_symbol *ps_patcher;
extern t_symbol *ps_topview;

// methods of the jpatchline
extern t_symbol *ps_insertsegment;
extern t_symbol *ps_removesegment; 
extern t_symbol *ps_setmidpoint;
extern t_symbol *ps_completeconnection; 

// Messages to UI objects from the view
extern t_symbol *ps_focusgained;
extern t_symbol *ps_focuslost;
extern t_symbol *ps_key;
extern t_symbol *ps_keyfilter; 
extern t_symbol *ps_mouseenter;
extern t_symbol *ps_mousemove;
extern t_symbol *ps_mousedown;
extern t_symbol *ps_mousedrag;
extern t_symbol *ps_mouseup;
extern t_symbol *ps_mousedoubleclick;
extern t_symbol *ps_mousewheel;
extern t_symbol *ps_mouseleave;
extern t_symbol *ps_dropfiles;
extern t_symbol *ps_moved;
extern t_symbol *ps_resized;
extern t_symbol *ps_vis; 
extern t_symbol *ps_bcut; 
extern t_symbol *ps_bcopy; 
extern t_symbol *ps_bpaste; 
extern t_symbol *ps_bpastepic; 
extern t_symbol *ps_bclear; 
extern t_symbol *ps_bundo; 
extern t_symbol *ps_bredo; 

// Textfield attributes
extern t_symbol *ps_owner;
extern t_symbol *ps_textcolor;
extern t_symbol *ps_textmargins; 
extern t_symbol *ps_editonclick; 
extern t_symbol *ps_selectallonedit;
extern t_symbol *ps_noactivate; 
extern t_symbol *ps_readonly;
extern t_symbol *ps_wordwrap;
extern t_symbol *ps_useellipsis;
extern t_symbol *ps_autoscroll;
extern t_symbol *ps_wantsreturn;
extern t_symbol *ps_wantstab; 
extern t_symbol *ps_underline;
extern t_symbol *ps_autofixwidth;
extern t_symbol *ps_emptytext;
extern t_symbol *ps_justification;

// jcolor attributes
extern t_symbol *ps_red;
extern t_symbol *ps_green;
extern t_symbol *ps_blue;
extern t_symbol *ps_alpha; 
extern t_symbol *ps_rgba; 

// scripting names
extern t_symbol *ps_varname_set;
extern t_symbol *ps_varname_unset;

END_USING_C_LINKAGE

#endif // #ifndef _JPATCHER_SYMS_H_

