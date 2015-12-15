var NAVTREE =
[
  [ "Max API", "index.html", [
    [ "Objects in C: A Roadmap", "index.html", [
      [ "Max Objects", "index.html#chapter_roadmap_max_objects", null ],
      [ "MSP Objects", "index.html#chapter_roadmap_msp_objects", null ],
      [ "Jitter Objects", "index.html#chapter_roadmap_jit_objects", null ]
    ] ],
    [ "Development System Information", "chapter_platform.html", [
      [ "Building", "chapter_platform.html#chapter_platform_building", null ],
      [ "Build Script", "chapter_platform.html#chapter_platform_buildscript", null ],
      [ "Mac", "chapter_platform.html#chapter_platform_mac", [
        [ "XCode Project Setup", "chapter_platform.html#chapter_platform_mac_xcodeproj", null ],
        [ "Linking and Frameworks", "chapter_platform.html#chapter_platform_mac_linking", null ]
      ] ],
      [ "Windows", "chapter_platform.html#chapter_platform_win", [
        [ "Compiling with Visual Studio", "chapter_platform.html#chapter_platform_win_vs", null ]
      ] ],
      [ "Important Project Settings", "chapter_platform.html#chapter_platform_settings", [
        [ "Mac", "chapter_platform.html#chapter_platform_settings_mac", null ],
        [ "Windows", "chapter_platform.html#chapter_platform_settings_win", null ]
      ] ],
      [ "Platform-specificity", "chapter_platform.html#chapter_platform_specificity", null ],
      [ "Configuration", "chapter_platform.html#chapter_platform_configuration", null ]
    ] ],
    [ "Anatomy of a Max Object", "chapter_anatomy.html", [
      [ "Include Files", "chapter_anatomy.html#chapter_anatomy_includes", null ],
      [ "The Object Declaration", "chapter_anatomy.html#chapter_anatomy_object_decl", null ],
      [ "Initialization Routine", "chapter_anatomy.html#chapter_anatomy_object_init", null ],
      [ "New Instance Routine", "chapter_anatomy.html#chapter_anatomy_object_new", null ],
      [ "Message Handlers", "chapter_anatomy.html#chapter_anatomy_object_mess_handlers", null ]
    ] ],
    [ "Inlets and Outlets", "chapter_inout.html", [
      [ "Creating and Using Inlets", "chapter_inout.html#chapter_inout_inlets", null ],
      [ "Creating and Using Outlets", "chapter_inout.html#chapter_inout_outlets", null ],
      [ "Creating and Using Proxies", "chapter_inout.html#chapter_inout_proxies", null ],
      [ "Example", "chapter_inout.html#chapter_inout_example", null ]
    ] ],
    [ "Atoms and Messages", "chapter_atoms.html", [
      [ "Argument Type Specifiers", "chapter_atoms.html#chapter_atoms_types", null ],
      [ "Writing A_GIMME Functions", "chapter_atoms.html#chapter_atoms_gimme_funcs", null ],
      [ "Writing \"Anything\" Methods", "chapter_atoms.html#chapter_atoms_anything_methods", null ]
    ] ],
    [ "The Scheduler", "chapter_scheduler.html", [
      [ "Creating and Using Clocks", "chapter_scheduler.html#chapter_scheduler_clocks", null ],
      [ "Creating and Using Qelems", "chapter_scheduler.html#chapter_scheduler_qelems", null ],
      [ "Defer", "chapter_scheduler.html#chapter_scheduler_defer", [
        [ "Defer Variants", "chapter_scheduler.html#chapter_scheduler_defer_variants", null ]
      ] ],
      [ "Schedule", "chapter_scheduler.html#chapter_scheduler_sechedule", null ]
    ] ],
    [ "Memory Allocation", "chapter_memory.html", null ],
    [ "Anatomy of a MSP Object", "chapter_msp_anatomy.html", [
      [ "Additional Header Files", "chapter_msp_anatomy.html#chapter_msp_anatomy_headers", null ],
      [ "C Structure Declaration", "chapter_msp_anatomy.html#chapter_msp_anatomy_struct", null ],
      [ "Initialization Routine", "chapter_msp_anatomy.html#chapter_msp_anatomy_init", null ],
      [ "New Instance Routine", "chapter_msp_anatomy.html#chapter_msp_anatomy_new", null ],
      [ "The DSP Method and Perform Routine", "chapter_msp_anatomy.html#chapter_msp_anatomy_dsp", null ],
      [ "Free Function", "chapter_msp_anatomy.html#chapter_msp_anatomy_free", null ]
    ] ],
    [ "Advanced Signal Object Topics", "chapter_msp_advanced.html", [
      [ "Saving Internal State", "chapter_msp_advanced.html#chapter_msp_advanced_internal_state", null ],
      [ "Using Connection Information", "chapter_msp_advanced.html#chapter_msp_advanced_connections", null ],
      [ "Working with Buffer Objects", "chapter_msp_advanced.html#chapter_msp_advanced_buffers", null ]
    ] ],
    [ "Sending Messages, Calling Methods", "chapter_msgattached.html", [
      [ "Attributes", "chapter_msgattached.html#chapter_msgattached_attrs", [
        [ "Attribute Basics", "chapter_msgattached.html#chapter_msgattached_attr_basics", null ],
        [ "Defining Attributes", "chapter_msgattached.html#chapter_msgattached_attr_def", null ],
        [ "Attributes With Custom Getters and Setters", "chapter_msgattached.html#chapter_msgattached_attr_custom", null ]
      ] ],
      [ "Receiving Notifications", "chapter_msgattached.html#chapter_msgattached_receiving", null ]
    ] ],
    [ "Anatomy of a UI Object", "chapter_ui_anatomy.html", [
      [ "Required Headers", "chapter_ui_anatomy.html#chapter_ui_anatomy_headers", null ],
      [ "UI Object Data Structure", "chapter_ui_anatomy.html#chapter_ui_anatomy_struct", null ],
      [ "Initialization Routine for UI Objects", "chapter_ui_anatomy.html#chapter_ui_anatomy_init", null ],
      [ "UI Object Methods", "chapter_ui_anatomy.html#chapter_ui_anatomy_methods", null ],
      [ "Defining Attributes", "chapter_ui_anatomy.html#chapter_ui_anatomy_attributes", [
        [ "Standard Color Attribute", "chapter_ui_anatomy.html#chapter_ui_anatomy_attributes_color", null ],
        [ "Setting a Default Size", "chapter_ui_anatomy.html#chapter_ui_anatomy_attributes_size", null ]
      ] ],
      [ "New Instance Routine", "chapter_ui_anatomy.html#chapter_ui_anatomy_new", null ],
      [ "Dynamic Updating", "chapter_ui_anatomy.html#chapter_ui_anatomy_updating", null ],
      [ "The Paint Method", "chapter_ui_anatomy.html#chapter_ui_anatomy_paint", null ],
      [ "Handling Mouse Gestures", "chapter_ui_anatomy.html#chapter_ui_anatomy_mouse", null ],
      [ "Freeing a UI Object", "chapter_ui_anatomy.html#chapter_ui_anatomy_freeing", null ]
    ] ],
    [ "File Handling", "chapter_files.html", [
      [ "Reading Text Files", "chapter_files.html#chapter_files_reading_text_files", null ],
      [ "Reading Data Files", "chapter_files.html#chapter_files_reading_data_files", null ],
      [ "Writing Files", "chapter_files.html#chapter_files_writing_files", null ]
    ] ],
    [ "Scripting the Patcher", "chapter_scripting.html", [
      [ "Knowing the Patcher", "chapter_scripting.html#chapter_scripting_knowing", [
        [ "Patcher Name and File Path", "chapter_scripting.html#chapter_scripting_knowing_name", null ],
        [ "Patcher Hierarchy", "chapter_scripting.html#chapter_scripting_knowing_heirarchy", null ],
        [ "Getting Objects in a Patcher", "chapter_scripting.html#chapter_scripting_knowing_objects", null ],
        [ "Iteration Using Callbacks", "chapter_scripting.html#chapter_scripting_knowing_iteration", null ]
      ] ],
      [ "Creating Objects", "chapter_scripting.html#chapter_scripting_objects", [
        [ "Connecting Objects", "chapter_scripting.html#chapter_scripting_objects_connecting", null ]
      ] ],
      [ "Deleting Objects", "chapter_scripting.html#chapter_scripting_objects_deleting", null ],
      [ "Obtaining and Changing Patcher and Object Attributes", "chapter_scripting.html#chapter_scripting_attrs", [
        [ "Patcher Attributes", "chapter_scripting.html#chapter_scripting_attrs_patcher", null ],
        [ "Box Attributes", "chapter_scripting.html#chapter_scripting_attrs_box", null ]
      ] ]
    ] ],
    [ "Enhancements to Objects", "chapter_enhancements.html", [
      [ "Preset Support", "chapter_enhancements.html#chapter_enhancements_presets", null ],
      [ "Pattr Support", "chapter_enhancements.html#chapter_enhancements_pattr", null ],
      [ "Assistance", "chapter_enhancements.html#chapter_enhancements_assistance", null ],
      [ "Hot and Cold Inlets", "chapter_enhancements.html#chapter_enhancements_hotness", null ],
      [ "Showing a Text Editor", "chapter_enhancements.html#chapter_enhancements_ed", null ],
      [ "Accessing Data in table Objects", "chapter_enhancements.html#chapter_enhancements_tables", null ]
    ] ],
    [ "Data Structures", "chapter_datastructures.html", [
      [ "Available Data Structures", "chapter_datastructures.html#chapter_datastructures_types", null ],
      [ "Passing Data Structures", "chapter_datastructures.html#chapter_datastructures_passing", null ]
    ] ],
    [ "Threading", "chapter_threading.html", [
      [ "Max Threading Operation", "chapter_threading.html#chapter_threading_op", null ],
      [ "Thread Protection", "chapter_threading.html#chapter_threading_protection", [
        [ "When Messages Arrive", "chapter_threading.html#chapter_threading_protection_arrival", null ],
        [ "Critical Section Example", "chapter_threading.html#chapter_threading_protection_example", null ]
      ] ]
    ] ],
    [ "Drag'n'Drop", "chapter_dragndrop.html", [
      [ "Discussion", "chapter_dragndrop.html#chapter_dragndrop_discussion", null ]
    ] ],
    [ "ITM", "chapter_itm.html", [
      [ "Scheduling Temporary Events", "chapter_itm.html#chapter_itm_temp", null ],
      [ "Permanent Events", "chapter_itm.html#chapter_itm_permanent", null ],
      [ "Cleaning Up", "chapter_itm.html#chapter_itm_clean", null ]
    ] ],
    [ "Jitter Object Model", "chapter_jit_objectmodel.html", [
      [ "Jitter Object Model Basics", "chapter_jit_objectmodel.html#chapter_jit_objectmodel_basics", null ],
      [ "Defining a Jitter Class", "chapter_jit_objectmodel.html#chapter_jit_objectmodel_classdef", null ],
      [ "Object Struct", "chapter_jit_objectmodel.html#chapter_jit_objectmodel_struct", null ],
      [ "Constructor/Destructor", "chapter_jit_objectmodel.html#chapter_jit_objectmodel_ctordtor", null ],
      [ "Methods", "chapter_jit_objectmodel.html#chapter_jit_objectmodel_methods", null ],
      [ "Attributes", "chapter_jit_objectmodel.html#chapter_jit_objectmodel_attrs", null ],
      [ "Array Attributes", "chapter_jit_objectmodel.html#chapter_jit_objectmodel_arrayattrs", null ],
      [ "Attribute Notification", "chapter_jit_objectmodel.html#chapter_jit_objectmodel_attrnotifications", null ]
    ] ],
    [ "Jitter Max Wrappers", "chapter_jit_maxwrappers.html", [
      [ "Max Wrapper Classes", "chapter_jit_maxwrappers.html#chapter_jit_maxwrappers_classes", null ],
      [ "Object Struct", "chapter_jit_maxwrappers.html#chapter_jit_maxwrappers_struct", null ],
      [ "Defining Your Max Class", "chapter_jit_maxwrappers.html#chapter_jit_maxwrappers_classdef", null ],
      [ "Constructor", "chapter_jit_maxwrappers.html#chapter_jit_maxwrappers_ctor", null ],
      [ "Destructor", "chapter_jit_maxwrappers.html#chapter_jit_maxwrappers_dtor", null ],
      [ "Dumpout", "chapter_jit_maxwrappers.html#chapter_jit_maxwrappers_dumpout", null ],
      [ "Additional inlets/outlets", "chapter_jit_maxwrappers.html#chapter_jit_maxwrappers_inout", null ],
      [ "Max Wrapper Attributes", "chapter_jit_maxwrappers.html#chapter_jit_maxwrappers_attrs", null ]
    ] ],
    [ "Matrix Operator QuickStart", "chapter_jit_mopqs.html", [
      [ "Defining the MOP Jitter Class", "chapter_jit_mopqs.html#chapter_jit_mopqs_classes", null ],
      [ "The Jitter Class Constructor/Destructor", "chapter_jit_mopqs.html#chapter_jit_mopqs_ctordtor", null ],
      [ "The Matrix Calculation Method", "chapter_jit_mopqs.html#chapter_jit_mopqs_calc", null ],
      [ "Processing N-Dimensional Matrices", "chapter_jit_mopqs.html#chapter_jit_mopqs_ndim", null ],
      [ "Defining the MOP Max Wrapper Class", "chapter_jit_mopqs.html#chapter_jit_mopqs_wrapperdef", null ],
      [ "The Max Class Constructor/Destructor", "chapter_jit_mopqs.html#chapter_jit_mopqs_maxctordtor", null ]
    ] ],
    [ "Matrix Operator Details", "chapter_jit_mopdetails.html", [
      [ "Defining the MOP Jitter Class", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_classes", null ],
      [ "The jit_mop_io Object", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_io", null ],
      [ "Restricting Input/Output Attributes", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_restrictingattrs", null ],
      [ "The ioproc Function", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_ioproc", null ],
      [ "Variable Inputs/Outputs", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_vario", null ],
      [ "Adding jit_mop as a Class Adornment", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_adorn", null ],
      [ "The Matrix Calculation Method", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_calc", null ],
      [ "Accessing the Input and Output Lists", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_access", null ],
      [ "Locking and Unlocking Matrices", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_locking", null ],
      [ "Retrieving Matrix Information", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_info", null ],
      [ "Retrieving the Data Pointer", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_data", null ],
      [ "Processing the Data", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_dataproc", null ],
      [ "Processing N-Dimensional Matrices", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_ndim", null ],
      [ "Defining the MOP Max Wrapper Class", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_mopwrapdef", null ],
      [ "Overriding the jit_matrix Method", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_override", null ],
      [ "Overriding the bang and outputmatrix Methods", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_overridebang", null ],
      [ "Overriding the name, type, dim, and planecount Attributes", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_overridemore", null ],
      [ "Overriding the clear and notify Methods", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_overrideclear", null ],
      [ "Overriding the adapt and outputmode Attributes", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_overrideadapt", null ],
      [ "Defining an mproc Method", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_mproc", null ],
      [ "The Max Class Constructor/Destructor", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_maxclassctor", [
        [ "Variable Inputs/Outputs", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_maxclassctor_vario", null ],
        [ "Matrix Arguments", "chapter_jit_mopdetails.html#chapter_jit_mopdetails_maxclassctor_matargs", null ]
      ] ]
    ] ],
    [ "OB3D QuickStart", "chapter_jit_ob3dqs.html", [
      [ "Defining the OB3D Jitter Class", "chapter_jit_ob3dqs.html#chapter_jit_ob3dqs_classdef", null ],
      [ "The Jitter Class Constructor/Destructor", "chapter_jit_ob3dqs.html#chapter_jit_ob3dqs_ctordtor", null ],
      [ "The OB3D draw Method", "chapter_jit_ob3dqs.html#chapter_jit_ob3dqs_draw", null ],
      [ "Defining the OB3D Max Wrapper Class", "chapter_jit_ob3dqs.html#chapter_jit_ob3dqs_maxwrap", null ],
      [ "The Max Class Constructor/Destructor", "chapter_jit_ob3dqs.html#chapter_jit_ob3dqs_wrapctor", null ]
    ] ],
    [ "OB3D Details", "chapter_jit_ob3ddetails.html", [
      [ "Defining the OB3D Jitter Class", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_classdef", null ],
      [ "Declaring a Draw Method", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_draw", null ],
      [ "Declaring Destination and Geometry Related Methods", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_geom", null ],
      [ "Declaring a Register Method", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_reg", null ],
      [ "Overriding Rotation and Scale Related Attributes", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_rot", null ],
      [ "Overriding Color Related Attributes", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_color", null ],
      [ "Overriding Texture Related Attributes", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_texture", null ],
      [ "Overriding Lighting and Material Related Attributes", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_lighting", null ],
      [ "Overriding Fog Related Attributes", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_fog", null ],
      [ "Overriding Polygon Variable Related Attributes", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_poly", null ],
      [ "Overriding Blending Related Attributes", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_blend", null ],
      [ "Overriding Depth Buffer and Antialiasing Related Attributes", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_aa", null ],
      [ "Overriding Matrixoutput and Automatic Attributes", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_matout", null ],
      [ "Declaring a User Interface Object", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_ui", null ],
      [ "The Jitter Class Constructor and Destructor", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_jitclassctor", null ],
      [ "The OB3D Draw Method", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_ob3ddraw", null ],
      [ "The t_jit_glchunk Structure and Matrix Output", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_glstruct", null ],
      [ "OB3D OpenGL Caveats", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_caveats", null ],
      [ "Getting Information About the OB3D Attributes", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_attrinfo", null ],
      [ "Getting Information About the Context", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_context", null ],
      [ "Playing Well with Others", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_play", null ],
      [ "Defining the OB3D Max Wrapper Class", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_wrapdef", null ],
      [ "Matrix Input", "chapter_jit_ob3ddetails.html#chapter_jit_ob3ddetails_matin", null ]
    ] ],
    [ "Scheduler and Low Priority Queue Issues", "chapter_jit_sched.html", [
      [ "Defer and Usurp", "chapter_jit_sched.html#chapter_jit_sched_usurp", null ],
      [ "Using Defer and Usurp in Jitter Object Methods", "chapter_jit_sched.html#chapter_jit_sched_using", null ],
      [ "Using Defer and Usurp in Jitter Object Attributes", "chapter_jit_sched.html#chapter_jit_sched_attrs", null ],
      [ "Using Defer and Usurp in the Max Wrapper Object", "chapter_jit_sched.html#chapter_jit_sched_wrapper", null ],
      [ "When Not to Use the Usurp Mechanism", "chapter_jit_sched.html#chapter_jit_sched_justsayno", null ],
      [ "Overriding Defer and Usurp", "chapter_jit_sched.html#chapter_jit_sched_override", null ]
    ] ],
    [ "Jitter Object Registration and Notification", "chapter_jit_notification.html", [
      [ "Registering Named Objects", "chapter_jit_notification.html#chapter_jit_notification_reg", null ],
      [ "Looking Up an Object by Name", "chapter_jit_notification.html#chapter_jit_notification_lookup", null ],
      [ "Attaching to Named Objects", "chapter_jit_notification.html#chapter_jit_notification_attach", null ],
      [ "Notifying Clients", "chapter_jit_notification.html#chapter_jit_notification_notify", null ]
    ] ],
    [ "Using Jitter Objects in C", "chapter_jit_usingobjs.html", [
      [ "Example 1: the t_jit_qt_movie object", "chapter_jit_usingobjs.html#chapter_jit_usingobjs_ex1", null ]
    ] ],
    [ "JXF File Specification", "chapter_jit_jxf.html", [
      [ "The Binary JXF API", "chapter_jit_jxf.html#chapter_jit_jxf_api", null ],
      [ "Specification of the JXF Format", "chapter_jit_jxf.html#chapter_jit_jxf_spec", null ]
    ] ],
    [ "Jitter Networking Specification", "chapter_jit_networking.html", null ],
    [ "Appendix: Messages sent to Objects", "chapter_appendix_a.html", [
      [ "Messages for All Objects", "chapter_appendix_a.html#appendix_a_all", null ],
      [ "Messages for Non-UI Objects", "chapter_appendix_a.html#appendix_a_nonui", null ],
      [ "Messages for User Interface Objects", "chapter_appendix_a.html#appendix_a_ui", null ],
      [ "Message for Audio Objects", "chapter_appendix_a.html#appendix_a_audio", null ],
      [ "Messages for Objects Containing Text Fields", "chapter_appendix_a.html#appendix_a_textedit", null ],
      [ "Messages for Objects with Text Editor Windows", "chapter_appendix_a.html#appendix_a_ed", null ],
      [ "Messages for Dataview Client Objects", "chapter_appendix_a.html#appendix_a_dataview", null ]
    ] ],
    [ "Appendix: Providing Icons for UI Objects", "chapter_appendix_b.html", [
      [ "Object SVG Icon", "chapter_appendix_b.html#appendix_b_svg", null ],
      [ "Quick Lookup Definition", "chapter_appendix_b.html#appendix_b_icon", null ]
    ] ],
    [ "Appendix: Additional Resources", "chapter_appendix_c.html", null ],
    [ "Appendix: Updating Externals for Max 6", "chapter_appendix_d.html", [
      [ "Updating MSP Externals for 64-bit Audio Processing", "chapter_appendix_d.html#chapter_appendix_d_msp64", [
        [ "Background", "chapter_appendix_d.html#chapter_appendix_d_background", null ],
        [ "API", "chapter_appendix_d.html#chapter_appendix_d_api", null ],
        [ "Example Code", "chapter_appendix_d.html#chapter_appendix_d_examples", null ]
      ] ],
      [ "Updating Max Externals for Cocoa", "chapter_appendix_d.html#chapter_appendix_d_cocoa", null ]
    ] ],
    [ "Appendix: Updating Externals for Max 6.1 (x64 architecture)", "chapter_appendix_e.html", [
      [ "Background", "chapter_appendix_e.html#chapter_appendix_e_background", [
        [ "New Types", "chapter_appendix_e.html#chapter_appendix_e_types", null ]
      ] ],
      [ "Xcode and Visual Studio Projects", "chapter_appendix_e.html#chapter_appendix_e_projects", [
        [ "Mac / Xcode", "chapter_appendix_e.html#chapter_appendix_e_projects_mac", null ],
        [ "Windows / Visual Studio", "chapter_appendix_e.html#chapter_appendix_e_projects_win", null ]
      ] ],
      [ "Changes to Code", "chapter_appendix_e.html#chapter_appendix_e_code", [
        [ "Atoms", "chapter_appendix_e.html#chapter_appendix_e_code_atoms", null ],
        [ "Return Values", "chapter_appendix_e.html#chapter_appendix_e_code_returnvals", null ],
        [ "File Code", "chapter_appendix_e.html#chapter_appendix_e_code_files", null ],
        [ "Miscellaneous Gotchas", "chapter_appendix_e.html#chapter_appendix_e_gotchas", null ]
      ] ],
      [ "Common Scenarios", "chapter_appendix_e.html#chapter_appendix_e_scenarios", [
        [ "\"Long\" integers", "chapter_appendix_e.html#chapter_appendix_e_scenarios_long", null ],
        [ "Floating point values", "chapter_appendix_e.html#chapter_appendix_e_scenarios_float", null ],
        [ "Deprecated Apple types", "chapter_appendix_e.html#chapter_appendix_e_scenarios_apple", null ]
      ] ],
      [ "Additional Miscellaneous Changes", "chapter_appendix_e.html#chapter_appendix_e_misc", null ],
      [ "Additional Resources", "chapter_appendix_e.html#chapter_appendix_e_resources", null ]
    ] ],
    [ "Appendix: SDK changes for Max 7", "chapter_appendix_f.html", [
      [ "Using ext_main for Entry Point", "chapter_appendix_f.html#chapter_appendix_f_main", null ],
      [ "Support for Max 7 UI Object Styles", "chapter_appendix_f.html#chapter_appendix_f_styles", null ]
    ] ],
    [ "Modules", "modules.html", "modules" ],
    [ "Data Structures", "annotated.html", [
      [ "Data Structures", "annotated.html", "annotated_dup" ],
      [ "Data Structure Index", "classes.html", null ],
      [ "Data Fields", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Variables", "functions_vars.html", "functions_vars" ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"annotated.html",
"functions_m.html",
"group__attr.html#gaababb47839dc4396bddfbf8149214e21",
"group__console.html#gaef84325d992e0afa14b2e7b0c0515601",
"group__hashtab.html#gab5cb27719ed31725c46ff3ff52356aa8",
"group__jgraphics.html#gga3519fa317c6811b619af2d70e3c1eca7ab3d013abb01bb8b776878740c806be4f",
"group__jmouse.html#ggae6e0f3193b01069c1bce512ab787a681a7ce9f8e318648eef4ca2c0cdcf02d388",
"group__matrixmod.html#ga12b4661428435cba18ab80d25c7581b1",
"group__ob3dmod.html#ga354e6daa1b458570e2528e12819b0c2a",
"group__opvecmod.html#gaba8a6b1cff6bf9770ea3994d8be30e38",
"group__time.html#gacad240f629ef5619c9949ba7a3adec95",
"structt__jgraphics__font__extents.html#af187e59f203debcb25545a5427f0a105"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';