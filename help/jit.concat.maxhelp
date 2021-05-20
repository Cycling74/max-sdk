{
    "patcher": {
        "fileversion": 1,
        "appversion": {
            "major": 7,
            "minor": 0,
            "revision": 0,
            "architecture": "x86",
            "modernui": 1
        },
        "rect": [52, 79, 564, 665],
        "bglocked": 0,
        "openinpresentation": 0,
        "default_fontsize": 12,
        "default_fontface": 0,
        "default_fontname": "Arial",
        "gridonopen": 0,
        "gridsize": [15, 15],
        "gridsnaponopen": 0,
        "statusbarvisible": 2,
        "toolbarvisible": 1,
        "lefttoolbarpinned": 0,
        "toptoolbarpinned": 0,
        "righttoolbarpinned": 0,
        "bottomtoolbarpinned": 0,
        "toolbars_unpinned_last_save": 0,
        "tallnewobj": 0,
        "boxanimatetime": 200,
        "enablehscroll": 1,
        "enablevscroll": 1,
        "devicewidth": 0,
        "description": "",
        "digest": "",
        "tags": "",
        "style": "",
        "showrootpatcherontab": 0,
        "showontab": 0,
        "boxes": [
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12,
                    "id": "obj-1",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "patching_rect": [195, 225, 145, 20],
                    "saved_object_attributes": {
                        "filename": "helpstarter.js",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter.js jit.concat"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12,
                    "id": "obj-2",
                    "maxclass": "newobj",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patcher": {
                        "fileversion": 1,
                        "appversion": {
                            "major": 7,
                            "minor": 0,
                            "revision": 0,
                            "architecture": "x86",
                            "modernui": 1
                        },
                        "rect": [52, 105, 564, 639],
                        "bglocked": 0,
                        "openinpresentation": 0,
                        "default_fontsize": 13,
                        "default_fontface": 0,
                        "default_fontname": "Arial",
                        "gridonopen": 0,
                        "gridsize": [15, 15],
                        "gridsnaponopen": 0,
                        "statusbarvisible": 2,
                        "toolbarvisible": 1,
                        "lefttoolbarpinned": 0,
                        "toptoolbarpinned": 0,
                        "righttoolbarpinned": 0,
                        "bottomtoolbarpinned": 0,
                        "toolbars_unpinned_last_save": 0,
                        "tallnewobj": 0,
                        "boxanimatetime": 200,
                        "enablehscroll": 1,
                        "enablevscroll": 1,
                        "devicewidth": 0,
                        "description": "",
                        "digest": "",
                        "tags": "",
                        "style": "",
                        "showontab": 1,
                        "boxes": [
                            {
                                "box": {
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-4",
                                    "maxclass": "jit.fpsgui",
                                    "mode": 3,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [183.5, 586, 80, 36],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-3",
                                    "maxclass": "jit.fpsgui",
                                    "mode": 2,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [100.5, 586, 80, 36],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-1",
                                    "maxclass": "jit.fpsgui",
                                    "mode": 4,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [17, 586, 80, 36],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-18",
                                    "linecount": 3,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [166, 112, 381, 50],
                                    "style": "helpfile_label",
                                    "text": "For all dimensions except the concat dimension, the truncate message truncates the right input's dimensions to the left input's dimensions if the right dimensions are greater than the left"
                                }
                            },
                            {
                                "box": {
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-35",
                                    "items": [
                                        0,
                                        "-",
                                        "horizontal",
                                        "(dim[0])",
                                        ",",
                                        1,
                                        "-",
                                        "vertical",
                                        "(dim[1])",
                                        ",",
                                        2,
                                        "-",
                                        "depth",
                                        "(dim[2])",
                                        ",",
                                        3,
                                        "-",
                                        "dim[3]",
                                        ",",
                                        4,
                                        "-",
                                        "dim[4]",
                                        ",",
                                        5,
                                        "-",
                                        "dim[5]",
                                        ",",
                                        6,
                                        "-",
                                        "dim[6]",
                                        ",",
                                        7,
                                        "-",
                                        "dim[7]",
                                        ",",
                                        8,
                                        "-",
                                        "dim[8]",
                                        ",",
                                        "etc."
                                    ],
                                    "maxclass": "umenu",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["int", "", ""],
                                    "parameter_enable": 0,
                                    "patching_rect": [252, 168, 153, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-39",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [252, 194, 89, 23],
                                    "style": "",
                                    "text": "concatdim $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-43",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [64, 260, 189, 23],
                                    "style": "",
                                    "text": "jit.matrix 4 char 40 40 @thru 1"
                                }
                            },
                            {
                                "box": {
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-46",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demovideo2.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["jit_matrix"],
                                    "patching_rect": [17, 112, 135, 100],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-47",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [17, 307, 66, 23],
                                    "style": "",
                                    "text": "jit.concat"
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["jit.concat"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [10, 10, 443, 96]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "id": "obj-44",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [17, 335, 320, 240]
                                }
                            },
                            {
                                "box": {
                                    "attr": "dim",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-5",
                                    "lock": 1,
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [64, 217, 132, 23],
                                    "style": "",
                                    "text_width": 33
                                }
                            },
                            {
                                "box": {
                                    "attr": "autoclear",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-6",
                                    "lock": 1,
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [283, 249, 92, 23],
                                    "style": "",
                                    "text_width": 67
                                }
                            },
                            {
                                "box": {
                                    "attr": "truncate",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-7",
                                    "lock": 1,
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [
                                        297.379089,
                                        275.274475,
                                        86,
                                        23
                                    ],
                                    "style": "",
                                    "text_width": 61
                                }
                            },
                            {
                                "box": {
                                    "attr": "mode",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-8",
                                    "lock": 1,
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [266, 221, 179, 23],
                                    "style": "",
                                    "text_width": 45
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-39", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-35", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-47", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        261.5,
                                        302.120911,
                                        26.5,
                                        302.120911
                                    ],
                                    "source": ["obj-39", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-47", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-43", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-1", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-44", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-3", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-44", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-4", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-44", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-43", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [26.5, 247, 73.5, 247],
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-47", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-44", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [26.5, 332.5, 26.5, 332.5],
                                    "source": ["obj-47", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-43", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-5", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-47", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [292.5, 301, 26.5, 301],
                                    "source": ["obj-6", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-47", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        306.879089,
                                        302.379089,
                                        26.5,
                                        302.379089
                                    ],
                                    "source": ["obj-7", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-47", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [275.5, 302, 26.5, 302],
                                    "source": ["obj-8", 0]
                                }
                            }
                        ]
                    },
                    "patching_rect": [10, 85, 50, 20],
                    "saved_object_attributes": {
                        "description": "",
                        "digest": "",
                        "fontsize": 13,
                        "globalpatchername": "",
                        "style": "",
                        "tags": ""
                    },
                    "style": "",
                    "text": "p basic",
                    "varname": "basic_tab"
                }
            },
            {
                "box": {
                    "border": 0,
                    "filename": "helpname.js",
                    "id": "obj-4",
                    "ignoreclick": 1,
                    "jsarguments": ["jit.concat"],
                    "maxclass": "jsui",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "parameter_enable": 0,
                    "patching_rect": [10, 10, 305, 55]
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12,
                    "id": "obj-5",
                    "maxclass": "newobj",
                    "numinlets": 0,
                    "numoutlets": 0,
                    "patcher": {
                        "fileversion": 1,
                        "appversion": {
                            "major": 7,
                            "minor": 0,
                            "revision": 0,
                            "architecture": "x86",
                            "modernui": 1
                        },
                        "rect": [0, 26, 564, 639],
                        "bglocked": 0,
                        "openinpresentation": 0,
                        "default_fontsize": 12,
                        "default_fontface": 0,
                        "default_fontname": "Arial",
                        "gridonopen": 0,
                        "gridsize": [15, 15],
                        "gridsnaponopen": 0,
                        "statusbarvisible": 2,
                        "toolbarvisible": 1,
                        "lefttoolbarpinned": 0,
                        "toptoolbarpinned": 0,
                        "righttoolbarpinned": 0,
                        "bottomtoolbarpinned": 0,
                        "toolbars_unpinned_last_save": 0,
                        "tallnewobj": 0,
                        "boxanimatetime": 200,
                        "enablehscroll": 1,
                        "enablevscroll": 1,
                        "devicewidth": 0,
                        "description": "",
                        "digest": "",
                        "tags": "",
                        "style": "",
                        "showontab": 1,
                        "boxes": [],
                        "lines": []
                    },
                    "patching_rect": [205, 205, 50, 20],
                    "saved_object_attributes": {
                        "description": "",
                        "digest": "",
                        "globalpatchername": "",
                        "style": "",
                        "tags": ""
                    },
                    "style": "",
                    "text": "p ?",
                    "varname": "q_tab"
                }
            }
        ],
        "lines": [],
        "parameters": {
            "obj-2::obj-46::obj-4::obj-21": ["number", "number", 0],
            "obj-2::obj-46::obj-4::obj-20": ["live.tab[1]", "live.tab[1]", 0],
            "obj-2::obj-46::obj-4::obj-18": ["number[1]", "number[1]", 0]
        },
        "dependency_cache": [
            {
                "name": "helpname.js",
                "bootpath": "/Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
                "patcherrelativepath": "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
                "type": "TEXT",
                "implicit": 1
            },
            {
                "name": "helpdetails.js",
                "bootpath": "/Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
                "patcherrelativepath": "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
                "type": "TEXT",
                "implicit": 1
            },
            {
                "name": "demovideo2.maxpat",
                "bootpath": "/Volumes/Underdog/max/maxmsp-misc/help/jitter-help",
                "patcherrelativepath": ".",
                "type": "JSON",
                "implicit": 1
            },
            {
                "name": "helpstarter.js",
                "bootpath": "/Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
                "patcherrelativepath": "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
                "type": "TEXT",
                "implicit": 1
            }
        ],
        "embedsnapshot": 0
    }
}