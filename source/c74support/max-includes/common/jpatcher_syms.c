#include "ext.h"

#include "jpatcher_syms.h"

BEGIN_USING_C_LINKAGE

// keycodes
t_symbol *ps_key_return;
t_symbol *ps_key_enter;
t_symbol *ps_key_spacebar;
t_symbol *ps_key_leftarrow; 
t_symbol *ps_key_rightarrow;
t_symbol *ps_key_uparrow; 
t_symbol *ps_key_downarrow; 
t_symbol *ps_key_home;	
t_symbol *ps_key_end;		
t_symbol *ps_key_pageup;	
t_symbol *ps_key_pagedown;
t_symbol *ps_key_backspace;
t_symbol *ps_key_clear; 
t_symbol *ps_key_delete;		
t_symbol *ps_key_tab; 
t_symbol *ps_key_insert;		
t_symbol *ps_key_esc;	
t_symbol *ps_key_backslash;
t_symbol *ps_key_vertbar;
t_symbol *ps_key_grave; 
t_symbol *ps_key_tilde;
t_symbol *ps_key_optionspace; 
t_symbol *ps_key_helpkey;

t_symbol *ps_patcher; 
t_symbol *ps_jpatcher; 
t_symbol *ps_jpatchline; 
t_symbol *ps_patcherview; 
t_symbol *ps_juiobject;

t_symbol *ps__set;		// avoids conflict with this commonly defined symbol

// notifications
t_symbol *ps_patchernotify;
t_symbol *ps_boxnotify;
t_symbol *ps_linenotify;

t_symbol *ps_user;
t_symbol *ps_defaultname;

// patchernotify
t_symbol *ps_rect;
t_symbol *ps_free;
t_symbol *ps_imbed;
t_symbol *ps_unimbed; 
t_symbol *ps_snaptogrid; 
t_symbol *ps_invis; 
t_symbol *ps_toolbarvisible;

// boxnotify
t_symbol *ps_newobject;
// t_symbol *ps_free;		
t_symbol *ps_redraw;
t_symbol *ps_textchanged;	// textfield text has changed
t_symbol *ps_grabfocus; 
t_symbol *ps_bfixwidth; 
t_symbol *ps_fontchanged; 

// if a box attribute changes a boxnotify message containing the attribute name will be sent. 
// I won't repeat the attributes here as they are listed below. 

// linenotify
//t_symbol *ps_newobject;   
//t_symbol *ps_free;
t_symbol *ps_linechanged; 

// Attributes of the patcher class
t_symbol *ps_box;
t_symbol *ps_count;
t_symbol *ps_firstobject;
t_symbol *ps_lastobject;
t_symbol *ps_firstline;
t_symbol *ps_firstview; 
t_symbol *ps_title;
t_symbol *ps_name;
t_symbol *ps_filepath;
t_symbol *ps_filename;
t_symbol *ps_locked;
t_symbol *ps_dirty;
t_symbol *ps_fontname;
t_symbol *ps_fontsize; 
t_symbol *ps_fontface;
t_symbol *ps_fontcolor;
t_symbol *ps_bglocked;
t_symbol *ps_bghidden;
t_symbol *ps_fghidden;
t_symbol *ps_font;
t_symbol *ps_bgcolor; 
t_symbol *ps_gridsize; 
t_symbol *ps_controller;
t_symbol *ps_maxclass;
t_symbol *ps_parentclass;
t_symbol *ps_parentpatcher;
t_symbol *ps_toppatcher;
t_symbol *ps_scrolloffset;
t_symbol *ps_scrollorigin;
t_symbol *ps_wind;
t_symbol *ps_noedit;
t_symbol *ps_collective;
t_symbol *ps_cansave;

// methods of the patcher class
//t_symbol *ps_newobject;	
t_symbol *ps_newdefault;
t_symbol *ps_connect;
t_symbol *ps_hiddenconnect;
t_symbol *ps_disconnect;
t_symbol *ps_apply;
t_symbol *ps_applydeep;
t_symbol *ps_applyif;
t_symbol *ps_applydeepif;
t_symbol *ps_remove;
t_symbol *ps_getnamed;
t_symbol *ps_getlogical;
t_symbol *ps_bringtofront;
t_symbol *ps_sendtoback;

// Attributes of the Maxobj class
//t_symbol *ps_rect;		
t_symbol *ps_presentation_rect; 
t_symbol *ps_patching_rect; 
t_symbol *ps_jp_position;
t_symbol *ps_presentation_position; 
t_symbol *ps_patching_position; 
t_symbol *ps_size;
t_symbol *ps_presentation_size; 
t_symbol *ps_patching_size; 
t_symbol *ps_object;
//t_symbol *ps_maxclass;
//t_symbol *ps_patcher;
t_symbol *ps_hint; 
t_symbol *ps_hidden;		
//t_symbol *ps_fontname;
//t_symbol *ps_fontsize; 
t_symbol *ps_color; 
t_symbol *ps_nextobject;
t_symbol *ps_prevobject;
t_symbol *ps_varname;
t_symbol *ps_id; 
t_symbol *ps_canhilite;  
t_symbol *ps_zorder; 
t_symbol *ps_background;
t_symbol *ps_ignoreclick; 
t_symbol *ps_drawfirstin;
t_symbol *ps_outline;
t_symbol *ps_growy;
t_symbol *ps_growboth;
t_symbol *ps_nogrow;
t_symbol *ps_drawinlast;
t_symbol *ps_transparent;
t_symbol *ps_mousedragdelta;
t_symbol *ps_textfield; 
//t_symbol *ps_presentation_rect;
t_symbol *ps_opaque; 
t_symbol *ps_useimagebuffer; 

// Methods of the Maxobj class
t_symbol *ps_message; 
t_symbol *ps_help;
t_symbol *ps_subpatcher;
t_symbol *ps_understands;

// attributes of the jpatchline
t_symbol *ps_startpoint;
t_symbol *ps_endpoint;
t_symbol *ps_pending;
t_symbol *ps_nummidpoints; 
t_symbol *ps_midpoints;
t_symbol *ps_box1;
t_symbol *ps_outletnum; 
t_symbol *ps_box2;
t_symbol *ps_inletnum; 
//t_symbol *ps_hidden;
//t_symbol *ps_color;
t_symbol *ps_boundingbox; 
t_symbol *ps_straightthresh;
t_symbol *ps_straightstart;
t_symbol *ps_straightend; 
t_symbol *ps_nextline; 

// attributes of the patcherview
t_symbol *ps_visible;
//t_symbol *ps_locked;
t_symbol *ps_unlockedinteraction;
t_symbol *ps_presentation;
t_symbol *ps_zoomfactor;
t_symbol *ps_nextview;
t_symbol *ps_jgraphics;
//t_symbol *ps_patcher;

// methods of the jpatchline
t_symbol *ps_insertsegment;
t_symbol *ps_removesegment; 
t_symbol *ps_setmidpoint; 
t_symbol *ps_completeconnection; 

// Messages to UI objects from the view
t_symbol *ps_focusgained;
t_symbol *ps_focuslost;
t_symbol *ps_key;
t_symbol *ps_keyfilter; 
t_symbol *ps_mouseenter;
t_symbol *ps_mousemove;
t_symbol *ps_mousedown;
t_symbol *ps_mousedrag;
t_symbol *ps_mouseup;
t_symbol *ps_mousedoubleclick;
t_symbol *ps_mousewheel;
t_symbol *ps_mouseleave;
t_symbol *ps_dropfiles;
t_symbol *ps_moved;
t_symbol *ps_resized;
t_symbol *ps_vis;

// Textfield attributes
t_symbol *ps_owner;
t_symbol *ps_textcolor;
t_symbol *ps_textmargins; 
t_symbol *ps_editonclick; 
t_symbol *ps_selectallonedit; 
t_symbol *ps_noactivate; 
t_symbol *ps_readonly;
t_symbol *ps_wordwrap;
t_symbol *ps_useellipsis;
t_symbol *ps_autoscroll;
t_symbol *ps_wantsreturn;
t_symbol *ps_autofixwidth;
t_symbol *ps_emptytext;

// jcolor attributes
t_symbol *ps_red;
t_symbol *ps_green;
t_symbol *ps_blue;
t_symbol *ps_alpha; 
t_symbol *ps_rgba;

// scripting names
t_symbol *ps_varname_set;
t_symbol *ps_varname_unset;

END_USING_C_LINKAGE

void jpatcher_syms_init()
{
	ps_key_return = gensym("key_return");
	ps_key_enter = gensym("key_enter");
	ps_key_spacebar = gensym("key_spacebar");
	ps_key_leftarrow = gensym("key_leftarrow"); 
	ps_key_rightarrow = gensym("key_rightarrow");
	ps_key_uparrow = gensym("key_uparrow"); 
	ps_key_downarrow = gensym("key_downarrow"); 
	ps_key_home = gensym("key_home");	
	ps_key_end = gensym("key_end");		
	ps_key_pageup = gensym("key_pageup");	
	ps_key_pagedown = gensym("key_pagedown");
	ps_key_backspace = gensym("key_backspace");
	ps_key_clear = gensym("key_clear"); 
	ps_key_delete = gensym("key_delete");		
	ps_key_tab = gensym("key_tab"); 
	ps_key_insert = gensym("key_insert");		
	ps_key_esc = gensym("key_esc");	
	ps_key_backslash = gensym("key_backslash");
	ps_key_vertbar = gensym("key_vertbar");
	ps_key_grave = gensym("key_grave"); 
	ps_key_tilde = gensym("key_tilde"); 
	ps_key_optionspace = gensym("key_optionspace"); 
	ps_key_helpkey = gensym("key_helpkey");
	ps_object = gensym("object");
	ps_patcher = gensym("patcher");
	ps_jpatcher = gensym("jpatcher"); 
	ps_jpatchline = gensym("jpatchline"); 
	ps_patcherview = gensym("patcherview");
	ps_juiobject = gensym("juiobject");
	ps_patchernotify = gensym("patchernotify");
	ps_boxnotify = gensym("boxnotify");
	ps_linenotify = gensym("linenotify");
	ps_user = gensym("user");
	ps_rect = gensym("rect");
	ps_free = gensym("free");
	ps_imbed = gensym("imbed");
	ps_unimbed = gensym("unimbed"); 
	ps_snaptogrid = gensym("snaptogrid"); 
	ps_invis = gensym("invis"); 
	ps_toolbarvisible = gensym("toolbarvisible"); 
	ps_newobject = gensym("newobject");
	ps_free = gensym("free");		
	ps_redraw = gensym("redraw");
	ps_textchanged = gensym("textchanged"); 
	ps_grabfocus = gensym("grabfocus"); 
	ps_bfixwidth = gensym("bfixwidth"); 
	ps_fontchanged = gensym("fontchanged"); 
	ps_newobject = gensym("newobject");   
	ps_free = gensym("free");
	ps_linechanged = gensym("linechanged"); 
	ps_box = gensym("box");
	ps_count = gensym("count");
	ps_locked = gensym("locked");
	ps_firstobject = gensym("firstobject");
	ps_lastobject = gensym("lastobject");
	ps_firstline = gensym("firstline"); 
	ps_firstview = gensym("firstview"); 
	ps_title = gensym("title");
	ps_name = gensym("name");
	ps_filepath = gensym("filepath");
	ps_filename = gensym("filename"); 
	ps_dirty = gensym("dirty");
	ps_bglocked = gensym("bglocked");
	ps_bghidden = gensym("bghidden");
	ps_fghidden = gensym("fghidden");
	ps_font = gensym("font");
	ps_bgcolor = gensym("bgcolor"); 
	ps_gridsize = gensym("gridsize"); 
	ps_controller = gensym("controller"); 
	ps_maxclass = gensym("maxclass");
	ps_parentclass = gensym("parentclass");
	ps_parentpatcher = gensym("parentpatcher");
	ps_toppatcher = gensym("toppatcher");
	ps_scrolloffset = gensym("scrolloffset");
	ps_scrollorigin = gensym("scrollorigin");
	ps_wind = gensym("wind");
	ps_noedit = gensym("noedit");
	ps_collective = gensym("collective");
	ps_cansave = gensym("cansave");
	ps_newobject = gensym("newobject");	
	ps_newdefault = gensym("newdefault");
	ps_connect = gensym("connect");
	ps_hiddenconnect = gensym("hiddenconnect");
	ps_disconnect = gensym("disconnect");
	ps_apply = gensym("apply");
	ps_applydeep = gensym("applydeep");
	ps_applyif = gensym("applyif");
	ps_applydeepif = gensym("applydeepif");
	ps_remove = gensym("remove");
	ps_getnamed = gensym("getnamed");
	ps_getlogical = gensym("getlogical");
	ps_bringtofront = gensym("bringtofront");
	ps_sendtoback = gensym("sendtoback");
	ps_rect = gensym("rect");		
	ps_unlockedinteraction = gensym("unlockedinteraction");
	ps_presentation_rect = gensym("presentation_rect"); 
	ps_patching_rect = gensym("patching_rect"); 
	ps_jp_position = gensym("position");
	ps_presentation_position = gensym("presentation_position"); 
	ps_patching_position = gensym("patching_position"); 
	ps_size = gensym("size");
	ps_presentation_size = gensym("presentation_size"); 
	ps_patching_size = gensym("patching_size"); 
	ps_maxclass = gensym("maxclass");
	ps_patcher = gensym("patcher");
	ps_hint = gensym("hint"); 
	ps_fontname = gensym("fontname");
	ps_fontsize = gensym("fontsize"); 
	ps_fontface = gensym("fontface"); 
	ps_textcolor = gensym("textcolor");
	ps_hidden = gensym("hidden");		
	ps_nextobject = gensym("nextobject");
	ps_prevobject = gensym("prevobject");
	ps_varname = gensym("varname");
	ps_id = gensym("id");
	ps_canhilite = gensym("canhilite");  
	ps_zorder = gensym("zorder");
	ps_color = gensym("color"); 
	ps_background = gensym("background");
	ps_ignoreclick = gensym("ignoreclick"); 
	ps_drawfirstin = gensym("drawfirstin");
	ps_outline = gensym("outline");
	ps_growy = gensym("growy");
	ps_growboth = gensym("growboth");
	ps_nogrow = gensym("nogrow");
	ps_drawinlast = gensym("drawinlast"); 
	ps_transparent = gensym("transparent");
	ps_mousedragdelta = gensym("mousedragdelta"); 
	ps_textfield = gensym("textfield");
	ps_presentation_rect = gensym("presentation_rect");
	ps_opaque = gensym("opaque"); 
	ps_useimagebuffer = gensym("useimagebuffer"); 

	ps_message = gensym("message"); 
	ps_help = gensym("help");
	ps_subpatcher = gensym("subpatcher");
	ps_understands = gensym("understands");
	ps_startpoint = gensym("startpoint");
	ps_endpoint = gensym("endpoint");
	ps_pending = gensym("pending"); 
	ps_nummidpoints = gensym("nummidpoints"); 
	ps_midpoints = gensym("midpoints");
	ps_box1 = gensym("box1");
	ps_outletnum = gensym("outletnum");
	ps_box2 = gensym("box2");
	ps_inletnum = gensym("inletnum");
	ps_hidden = gensym("hidden");
	ps_color = gensym("color"); 
	ps_boundingbox = gensym("boundingbox"); 
	ps_straightthresh = gensym("straightthresh"); 
	ps_straightstart = gensym("straightstart");
	ps_straightend = gensym("straightend"); 
	ps_nextline = gensym("nextline"); 
	ps_visible = gensym("visible");
	ps_locked = gensym("locked");
	ps_presentation = gensym("presentation");
	ps_zoomfactor = gensym("zoomfactor");
	ps_nextview = gensym("nextview");
	ps_jgraphics = gensym("jgraphics");
	ps_patcher = gensym("patcher");
	ps_insertsegment = gensym("insertsegment");
	ps_removesegment = gensym("removesegment"); 
	ps_setmidpoint = gensym("setmidpoint"); 
	ps_completeconnection = gensym("completeconnection"); 
	ps_focusgained = gensym("focusgained");
	ps_focuslost = gensym("focuslost");
	ps_key = gensym("key");
	ps_keyfilter = gensym("keyfilter"); 
	ps_mouseenter = gensym("mouseenter");
	ps_mousemove = gensym("mousemove");
	ps_mousedown = gensym("mousedown");
	ps_mousedrag = gensym("mousedrag");
	ps_mouseup = gensym("mouseup");
	ps_mousedoubleclick = gensym("mousedoubleclick");
	ps_mousewheel = gensym("mousewheel");
	ps_mouseleave = gensym("mouseleave");
	ps_dropfiles = gensym("dropfiles");
	ps_moved = gensym("moved");
	ps_resized = gensym("resized");
	ps_vis = gensym("vis");
	ps_owner = gensym("owner");
	ps_textcolor = gensym("textcolor");
	ps_textmargins = gensym("textmargins"); 
	ps_editonclick = gensym("editonclick"); 
	ps_selectallonedit = gensym("selectallonedit"); 
	ps_noactivate = gensym("noactivate"); 
	ps_readonly = gensym("readonly");
	ps_wordwrap = gensym("wordwrap");
	ps_useellipsis = gensym("useellipsis");
	ps_autoscroll = gensym("autoscroll");
	ps_wantsreturn = gensym("wantsreturn");
	ps_autofixwidth = gensym("autofixwidth");
	ps_emptytext = gensym("emptytext");
	ps_red = gensym("red");
	ps_green = gensym("green");
	ps_blue = gensym("blue");
	ps_alpha = gensym("alpha"); 
	ps_rgba = gensym("rgba"); 
	ps__set = gensym("set");
	ps_defaultname = gensym("defaultname");
	
	ps_varname_set = gensym("varname_set");
	ps_varname_unset = gensym("varname_unset");
}

