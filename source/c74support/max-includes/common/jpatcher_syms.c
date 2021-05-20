#include "ext.h"

#include "jpatcher_syms.h"

BEGIN_USING_C_LINKAGE

C74_HIDDEN t_symbol *ps_patcher;
C74_HIDDEN t_symbol *ps_topview;
C74_HIDDEN t_symbol *ps_jpatcher;
C74_HIDDEN t_symbol *ps_jpatchline;
C74_HIDDEN t_symbol *ps_patcherview;
C74_HIDDEN t_symbol *ps_juiobject;

C74_HIDDEN t_symbol *ps__set;		// avoids conflict with this commonly defined symbol

// notifications
C74_HIDDEN t_symbol *ps_patchernotify;
C74_HIDDEN t_symbol *ps_boxnotify;
C74_HIDDEN t_symbol *ps_linenotify;

C74_HIDDEN t_symbol *ps_user;
C74_HIDDEN t_symbol *ps_defaultname;

// patchernotify
C74_HIDDEN t_symbol *ps_rect;
C74_HIDDEN t_symbol *ps_free;
C74_HIDDEN t_symbol *ps_imbed;
C74_HIDDEN t_symbol *ps_unimbed;
C74_HIDDEN t_symbol *ps_snaptogrid;
C74_HIDDEN t_symbol *ps_invis;
C74_HIDDEN t_symbol *ps_toolbarvisible;

// boxnotify
C74_HIDDEN t_symbol *ps_newobject;
C74_HIDDEN t_symbol *ps_free;
C74_HIDDEN t_symbol *ps_redraw;
C74_HIDDEN t_symbol *ps_redrawcontents; // textfield text has changed
C74_HIDDEN t_symbol *ps_textchanged;
C74_HIDDEN t_symbol *ps_textcolor;
C74_HIDDEN t_symbol *ps_color;
C74_HIDDEN t_symbol *ps_grabfocus;
C74_HIDDEN t_symbol *ps_fontchanged;
C74_HIDDEN t_symbol *ps_inletoutlet;
C74_HIDDEN t_symbol *ps_bfixwidth;
C74_HIDDEN t_symbol *ps_showcaption;
C74_HIDDEN t_symbol *ps_hidecaption;
C74_HIDDEN t_symbol *ps_freecontainedview;
C74_HIDDEN t_symbol *ps_rebuildcontainedview;
C74_HIDDEN t_symbol *ps_viewvisibility;
C74_HIDDEN t_symbol *ps_viewvisibilitychanged;

// if a box attribute changes a boxnotify message containing the attribute name will be sent. 
// I won't repeat the attributes here as they are listed below. 

// linenotify
//C74_HIDDEN t_symbol *ps_newobject;
//C74_HIDDEN t_symbol *ps_free;
C74_HIDDEN t_symbol *ps_linechanged;

// Attributes of the patcher class
C74_HIDDEN t_symbol *ps_box;
C74_HIDDEN t_symbol *ps_count;
C74_HIDDEN t_symbol *ps_firstobject;
C74_HIDDEN t_symbol *ps_lastobject;
C74_HIDDEN t_symbol *ps_firstline;
C74_HIDDEN t_symbol *ps_firstview;
C74_HIDDEN t_symbol *ps_title;
C74_HIDDEN t_symbol *ps_name;
C74_HIDDEN t_symbol *ps_filepath;
C74_HIDDEN t_symbol *ps_savefilepath;
C74_HIDDEN t_symbol *ps_filename;
C74_HIDDEN t_symbol *ps_locked;
C74_HIDDEN t_symbol *ps_dirty;
C74_HIDDEN t_symbol *ps_fontname;
C74_HIDDEN t_symbol *ps_fontsize;
C74_HIDDEN t_symbol *ps_fontface;
C74_HIDDEN t_symbol *ps_fontcolor;
C74_HIDDEN t_symbol *ps_bglocked;
C74_HIDDEN t_symbol *ps_bghidden;
C74_HIDDEN t_symbol *ps_fghidden;
C74_HIDDEN t_symbol *ps_font;
C74_HIDDEN t_symbol *ps_bgcolor;
C74_HIDDEN t_symbol *ps_editing_bgcolor;
C74_HIDDEN t_symbol *ps_locked_bgcolor;
C74_HIDDEN t_symbol *ps_gridsize;
C74_HIDDEN t_symbol *ps_controller;
C74_HIDDEN t_symbol *ps_maxclass;
C74_HIDDEN t_symbol *ps_parentclass;
C74_HIDDEN t_symbol *ps_parentpatcher;
C74_HIDDEN t_symbol *ps_toppatcher;
C74_HIDDEN t_symbol *ps_scrolloffset;
C74_HIDDEN t_symbol *ps_scrollorigin;
C74_HIDDEN t_symbol *ps_wind;
C74_HIDDEN t_symbol *ps_noedit;
C74_HIDDEN t_symbol *ps_collective;
C74_HIDDEN t_symbol *ps_cansave;

// methods of the patcher class
//C74_HIDDEN t_symbol *ps_newobject;
C74_HIDDEN t_symbol *ps_newdefault;
C74_HIDDEN t_symbol *ps_connect;
C74_HIDDEN t_symbol *ps_hiddenconnect;
C74_HIDDEN t_symbol *ps_disconnect;
C74_HIDDEN t_symbol *ps_apply;
C74_HIDDEN t_symbol *ps_applydeep;
C74_HIDDEN t_symbol *ps_applyif;
C74_HIDDEN t_symbol *ps_applydeepif;
C74_HIDDEN t_symbol *ps_remove;
C74_HIDDEN t_symbol *ps_getnamed;
C74_HIDDEN t_symbol *ps_getlogical;
C74_HIDDEN t_symbol *ps_bringtofront;
C74_HIDDEN t_symbol *ps_sendtoback;

// patcher dictionary syms
C74_HIDDEN t_symbol *ps_pound_PD;
C74_HIDDEN t_symbol *ps_appversion;
C74_HIDDEN t_symbol *ps_major;
C74_HIDDEN t_symbol *ps_minor;
C74_HIDDEN t_symbol *ps_revision;
C74_HIDDEN t_symbol *ps_architecture;
C74_HIDDEN t_symbol *ps_x86;
C74_HIDDEN t_symbol *ps_x64;
C74_HIDDEN t_symbol *ps_modernui;
C74_HIDDEN t_symbol *ps_dynamiccolor;


// Attributes of the Maxobj class
//C74_HIDDEN t_symbol *ps_rect;
C74_HIDDEN t_symbol *ps_presentation_rect;
C74_HIDDEN t_symbol *ps_patching_rect;
C74_HIDDEN t_symbol *ps_jp_position;
C74_HIDDEN t_symbol *ps_presentation_position;
C74_HIDDEN t_symbol *ps_patching_position;
C74_HIDDEN t_symbol *ps_size;
C74_HIDDEN t_symbol *ps_presentation_size;
C74_HIDDEN t_symbol *ps_patching_size;
C74_HIDDEN t_symbol *ps_object;
//C74_HIDDEN t_symbol *ps_maxclass;
//C74_HIDDEN t_symbol *ps_patcher;
C74_HIDDEN t_symbol *ps_hint;
C74_HIDDEN t_symbol *ps_hidden;
//C74_HIDDEN t_symbol *ps_fontname;
//C74_HIDDEN t_symbol *ps_fontsize;
C74_HIDDEN t_symbol *ps_color;
C74_HIDDEN t_symbol *ps_nextobject;
C74_HIDDEN t_symbol *ps_prevobject;
C74_HIDDEN t_symbol *ps_varname;
C74_HIDDEN t_symbol *ps_id;
C74_HIDDEN t_symbol *ps_canhilite;
C74_HIDDEN t_symbol *ps_zorder;
C74_HIDDEN t_symbol *ps_background;
C74_HIDDEN t_symbol *ps_ignoreclick;
C74_HIDDEN t_symbol *ps_drawfirstin;
C74_HIDDEN t_symbol *ps_outline;
C74_HIDDEN t_symbol *ps_growy;
C74_HIDDEN t_symbol *ps_growboth;
C74_HIDDEN t_symbol *ps_nogrow;
C74_HIDDEN t_symbol *ps_drawinlast;
C74_HIDDEN t_symbol *ps_transparent;
C74_HIDDEN t_symbol *ps_mousedragdelta;
C74_HIDDEN t_symbol *ps_textfield;
//C74_HIDDEN t_symbol *ps_presentation_rect;
C74_HIDDEN t_symbol *ps_opaque;
C74_HIDDEN t_symbol *ps_useimagebuffer;
C74_HIDDEN t_symbol *ps_hide;
C74_HIDDEN t_symbol *ps_show;
C74_HIDDEN t_symbol *ps_move;
C74_HIDDEN t_symbol *ps_offset;
C74_HIDDEN t_symbol *ps_respondtoclick;

// Methods of the Maxobj class
C74_HIDDEN t_symbol *ps_message;
C74_HIDDEN t_symbol *ps_help;
C74_HIDDEN t_symbol *ps_subpatcher;
C74_HIDDEN t_symbol *ps_understands;

// attributes of the jpatchline
C74_HIDDEN t_symbol *ps_startpoint;
C74_HIDDEN t_symbol *ps_endpoint;
C74_HIDDEN t_symbol *ps_pending;
C74_HIDDEN t_symbol *ps_nummidpoints;
C74_HIDDEN t_symbol *ps_midpoints;
C74_HIDDEN t_symbol *ps_box1;
C74_HIDDEN t_symbol *ps_outletnum;
C74_HIDDEN t_symbol *ps_box2;
C74_HIDDEN t_symbol *ps_inletnum;
//C74_HIDDEN t_symbol *ps_hidden;
//C74_HIDDEN t_symbol *ps_color;
C74_HIDDEN t_symbol *ps_boundingbox;
C74_HIDDEN t_symbol *ps_straightthresh;
C74_HIDDEN t_symbol *ps_straightstart;
C74_HIDDEN t_symbol *ps_straightend;
C74_HIDDEN t_symbol *ps_nextline;

// attributes of the patcherview
C74_HIDDEN t_symbol *ps_visible;
//C74_HIDDEN t_symbol *ps_locked;
C74_HIDDEN t_symbol *ps_unlockedinteraction;
C74_HIDDEN t_symbol *ps_presentation;
C74_HIDDEN t_symbol *ps_zoomfactor;
C74_HIDDEN t_symbol *ps_nextview;
C74_HIDDEN t_symbol *ps_jgraphics;
//C74_HIDDEN t_symbol *ps_patcher;

// methods of the jpatchline
C74_HIDDEN t_symbol *ps_insertsegment;
C74_HIDDEN t_symbol *ps_removesegment;
C74_HIDDEN t_symbol *ps_setmidpoint;
C74_HIDDEN t_symbol *ps_completeconnection;

// Messages to UI objects from the view
C74_HIDDEN t_symbol *ps_focusgained;
C74_HIDDEN t_symbol *ps_focuslost;
C74_HIDDEN t_symbol *ps_key;
C74_HIDDEN t_symbol *ps_keyfilter;
C74_HIDDEN t_symbol *ps_mouseenter;
C74_HIDDEN t_symbol *ps_mousemove;
C74_HIDDEN t_symbol *ps_mousedown;
C74_HIDDEN t_symbol *ps_mousedrag;
C74_HIDDEN t_symbol *ps_mouseup;
C74_HIDDEN t_symbol *ps_mousedoubleclick;
C74_HIDDEN t_symbol *ps_mousewheel;
C74_HIDDEN t_symbol *ps_mouseleave;
C74_HIDDEN t_symbol *ps_dropfiles;
C74_HIDDEN t_symbol *ps_moved;
C74_HIDDEN t_symbol *ps_resized;
C74_HIDDEN t_symbol *ps_vis;
C74_HIDDEN t_symbol *ps_bcut;
C74_HIDDEN t_symbol *ps_bcopy;
C74_HIDDEN t_symbol *ps_bpaste;
C74_HIDDEN t_symbol *ps_bpastepic;
C74_HIDDEN t_symbol *ps_bclear;
C74_HIDDEN t_symbol *ps_bundo;
C74_HIDDEN t_symbol *ps_bredo;

// Textfield attributes
C74_HIDDEN t_symbol *ps_owner;
C74_HIDDEN t_symbol *ps_textcolor;
C74_HIDDEN t_symbol *ps_textmargins;
C74_HIDDEN t_symbol *ps_editonclick;
C74_HIDDEN t_symbol *ps_selectallonedit;
C74_HIDDEN t_symbol *ps_noactivate;
C74_HIDDEN t_symbol *ps_readonly;
C74_HIDDEN t_symbol *ps_wordwrap;
C74_HIDDEN t_symbol *ps_useellipsis;
C74_HIDDEN t_symbol *ps_autoscroll;
C74_HIDDEN t_symbol *ps_wantsreturn;
C74_HIDDEN t_symbol *ps_wantstab;
C74_HIDDEN t_symbol *ps_underline;
C74_HIDDEN t_symbol *ps_autofixwidth;
C74_HIDDEN t_symbol *ps_emptytext;
C74_HIDDEN t_symbol *ps_justification;

// jcolor attributes
C74_HIDDEN t_symbol *ps_red;
C74_HIDDEN t_symbol *ps_green;
C74_HIDDEN t_symbol *ps_blue;
C74_HIDDEN t_symbol *ps_alpha;
C74_HIDDEN t_symbol *ps_rgba;

// scripting names
C74_HIDDEN t_symbol *ps_varname_set;
C74_HIDDEN t_symbol *ps_varname_unset;

END_USING_C_LINKAGE

C74_HIDDEN void jpatcher_syms_init()
{
	ps__set = gensym("set");
	ps_alpha = gensym("alpha");
	ps_apply = gensym("apply");
	ps_applydeep = gensym("applydeep");
	ps_applydeepif = gensym("applydeepif");
	ps_applyif = gensym("applyif");
	ps_appversion = gensym("appversion");
	ps_architecture = gensym("architecture");
	ps_autofixwidth = gensym("autofixwidth");
	ps_autoscroll = gensym("autoscroll");
	ps_background = gensym("background");
	ps_bclear = gensym("bclear");
	ps_bcopy = gensym("bcopy");
	ps_bcut = gensym("bcut");
	ps_bfixwidth = gensym("bfixwidth");
	ps_bgcolor = gensym("bgcolor");
	ps_bghidden = gensym("bghidden");
	ps_bglocked = gensym("bglocked");
	ps_blue = gensym("blue");
	ps_boundingbox = gensym("boundingbox");
	ps_box = gensym("box");
	ps_box1 = gensym("box1");
	ps_box2 = gensym("box2");
	ps_boxnotify = gensym("boxnotify");
	ps_bpaste = gensym("bpaste");
	ps_bpastepic = gensym("bpastepic");
	ps_bredo = gensym("bredo");
	ps_bringtofront = gensym("bringtofront");
	ps_bundo = gensym("bundo");
	ps_canhilite = gensym("canhilite");
	ps_cansave = gensym("cansave");
	ps_collective = gensym("collective");
	ps_color = gensym("color");
	ps_completeconnection = gensym("completeconnection");
	ps_connect = gensym("connect");
	ps_controller = gensym("controller");
	ps_count = gensym("count");
	ps_defaultname = gensym("defaultname");
	ps_dirty = gensym("dirty");
	ps_disconnect = gensym("disconnect");
	ps_drawfirstin = gensym("drawfirstin");
	ps_drawinlast = gensym("drawinlast");
	ps_dropfiles = gensym("dropfiles");
	ps_dynamiccolor = gensym("dynamiccolor");
	ps_editing_bgcolor = gensym("editing_bgcolor");
	ps_editonclick = gensym("editonclick");
	ps_emptytext = gensym("emptytext");
	ps_endpoint = gensym("endpoint");
	ps_fghidden = gensym("fghidden");
	ps_filename = gensym("filename");
	ps_filepath = gensym("filepath");
	ps_firstline = gensym("firstline");
	ps_firstobject = gensym("firstobject");
	ps_firstview = gensym("firstview");
	ps_focusgained = gensym("focusgained");
	ps_focuslost = gensym("focuslost");
	ps_font = gensym("font");
	ps_fontchanged = gensym("fontchanged");
	ps_fontface = gensym("fontface");
	ps_fontname = gensym("fontname");
	ps_fontsize = gensym("fontsize");
	ps_free = gensym("free");
	ps_freecontainedview = gensym("freecontainedview");
	ps_getlogical = gensym("getlogical");
	ps_getnamed = gensym("getnamed");
	ps_grabfocus = gensym("grabfocus");
	ps_green = gensym("green");
	ps_gridsize = gensym("gridsize");
	ps_growboth = gensym("growboth");
	ps_growy = gensym("growy");
	ps_help = gensym("help");
	ps_hidden = gensym("hidden");
	ps_hiddenconnect = gensym("hiddenconnect");
	ps_hide = gensym("hide");
	ps_hidecaption = gensym("hidecaption");
	ps_hint = gensym("hint");
	ps_id = gensym("id");
	ps_ignoreclick = gensym("ignoreclick");
	ps_imbed = gensym("imbed");
	ps_inletnum = gensym("inletnum");
	ps_inletoutlet = gensym("inletoutlet");
	ps_insertsegment = gensym("insertsegment");
	ps_invis = gensym("invis");
	ps_jgraphics = gensym("jgraphics");
	ps_jp_position = gensym("position");
	ps_jpatcher = gensym("jpatcher");
	ps_jpatchline = gensym("jpatchline");
	ps_juiobject = gensym("juiobject");
	ps_justification = gensym("justification");
	ps_key = gensym("key");
	ps_keyfilter = gensym("keyfilter");
	ps_lastobject = gensym("lastobject");
	ps_linechanged = gensym("linechanged");
	ps_linenotify = gensym("linenotify");
	ps_locked = gensym("locked");
	ps_locked_bgcolor = gensym("locked_bgcolor");
	ps_major = gensym("major");
	ps_maxclass = gensym("maxclass");
	ps_message = gensym("message");
	ps_midpoints = gensym("midpoints");
	ps_minor = gensym("minor");
	ps_modernui = gensym("modernui");
	ps_mousedoubleclick = gensym("mousedoubleclick");
	ps_mousedown = gensym("mousedown");
	ps_mousedrag = gensym("mousedrag");
	ps_mousedragdelta = gensym("mousedragdelta");
	ps_mouseenter = gensym("mouseenter");
	ps_mouseleave = gensym("mouseleave");
	ps_mousemove = gensym("mousemove");
	ps_mouseup = gensym("mouseup");
	ps_mousewheel = gensym("mousewheel");
	ps_move = gensym("move");
	ps_moved = gensym("moved");
	ps_name = gensym("name");
	ps_newdefault = gensym("newdefault");
	ps_newobject = gensym("newobject");
	ps_nextline = gensym("nextline");
	ps_nextobject = gensym("nextobject");
	ps_nextview = gensym("nextview");
	ps_noactivate = gensym("noactivate");
	ps_noedit = gensym("noedit");
	ps_nogrow = gensym("nogrow");
	ps_nummidpoints = gensym("nummidpoints");
	ps_object = gensym("object");
	ps_offset = gensym("offset");
	ps_opaque = gensym("opaque");
	ps_outletnum = gensym("outletnum");
	ps_outline = gensym("outline");
	ps_owner = gensym("owner");
	ps_parentclass = gensym("parentclass");
	ps_parentpatcher = gensym("parentpatcher");
	ps_patcher = gensym("patcher");
	ps_patchernotify = gensym("patchernotify");
	ps_patcherview = gensym("patcherview");
	ps_patching_position = gensym("patching_position");
	ps_patching_rect = gensym("patching_rect");
	ps_patching_size = gensym("patching_size");
	ps_pending = gensym("pending");
	ps_pound_PD = gensym("#PD");
	ps_presentation = gensym("presentation");
	ps_presentation_position = gensym("presentation_position");
	ps_presentation_rect = gensym("presentation_rect");
	ps_presentation_size = gensym("presentation_size");
	ps_prevobject = gensym("prevobject");
	ps_readonly = gensym("readonly");
	ps_rebuildcontainedview = gensym("rebuildcontainedview");
	ps_rect = gensym("rect");
	ps_red = gensym("red");
	ps_redraw = gensym("redraw");
	ps_redrawcontents = gensym("redrawcontents");
	ps_remove = gensym("remove");
	ps_removesegment = gensym("removesegment");
	ps_resized = gensym("resized");
	ps_respondtoclick = gensym("respondtoclick");
	ps_revision = gensym("revision");
	ps_rgba = gensym("rgba");
	ps_savefilepath = gensym("savefilepath");
	ps_scrolloffset = gensym("scrolloffset");
	ps_scrollorigin = gensym("scrollorigin");
	ps_selectallonedit = gensym("selectallonedit");
	ps_sendtoback = gensym("sendtoback");
	ps_setmidpoint = gensym("setmidpoint");
	ps_show = gensym("show");
	ps_showcaption = gensym("showcaption");
	ps_size = gensym("size");
	ps_snaptogrid = gensym("snaptogrid");
	ps_startpoint = gensym("startpoint");
	ps_straightend = gensym("straightend");
	ps_straightstart = gensym("straightstart");
	ps_straightthresh = gensym("straightthresh");
	ps_subpatcher = gensym("subpatcher");
	ps_textchanged = gensym("textchanged");
	ps_textcolor = gensym("textcolor");
	ps_textfield = gensym("textfield");
	ps_textmargins = gensym("textmargins");
	ps_title = gensym("title");
	ps_toolbarvisible = gensym("toolbarvisible");
	ps_toppatcher = gensym("toppatcher");
	ps_topview = gensym("topview");
	ps_transparent = gensym("transparent");
	ps_underline = gensym("underline");
	ps_understands = gensym("understands");
	ps_unimbed = gensym("unimbed");
	ps_unlockedinteraction = gensym("unlockedinteraction");
	ps_useellipsis = gensym("useellipsis");
	ps_useimagebuffer = gensym("useimagebuffer");
	ps_user = gensym("user");
	ps_varname = gensym("varname");
	ps_varname_set = gensym("varname_set");
	ps_varname_unset = gensym("varname_unset");
	ps_viewvisibility = gensym("viewvisibility");
	ps_viewvisibilitychanged = gensym("viewvisibilitychanged");
	ps_vis = gensym("vis");
	ps_visible = gensym("visible");
	ps_wantsreturn = gensym("wantsreturn");
	ps_wantstab = gensym("wantstab");
	ps_wind = gensym("wind");
	ps_wordwrap = gensym("wordwrap");
	ps_x64 = gensym("x64");
	ps_x86 = gensym("x86");
	ps_zoomfactor = gensym("zoomfactor");
	ps_zorder = gensym("zorder");
}

