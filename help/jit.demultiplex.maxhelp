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
        "rect": [34, 79, 821, 672],
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
                    "id": "obj-5",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "patching_rect": [473, 398, 92, 18],
                    "style": "",
                    "text": "resize 700 640"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12,
                    "id": "obj-1",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "patching_rect": [473, 442, 159, 20],
                    "saved_object_attributes": {
                        "filename": "helpstarter",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter jit.demultiplex"
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
                        "rect": [34, 105, 821, 646],
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
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-35",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [494, 363.5, 250, 25],
                                    "style": "",
                                    "text": "Choose the demultiplexing dimension"
                                }
                            },
                            {
                                "box": {
                                    "attr": "demultiplexdim",
                                    "attrfilter": ["demultiplexdim"],
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-34",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [344, 367.5, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-14",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [494, 299, 222, 25],
                                    "style": "",
                                    "text": "Clear the output between frames"
                                }
                            },
                            {
                                "box": {
                                    "attr": "autoclear",
                                    "attrfilter": ["autoclear"],
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-17",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [344, 301, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-32",
                                    "maxclass": "toggle",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["int"],
                                    "parameter_enable": 1,
                                    "patching_rect": [344, 276, 24, 24],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "toggle",
                                            "parameter_shortname": "toggle",
                                            "parameter_type": 3,
                                            "parameter_initial_enable": 1,
                                            "parameter_initial": [1],
                                            "parameter_invisible": 1
                                        }
                                    },
                                    "style": "",
                                    "varname": "toggle"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-10",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [419, 474.5, 66, 23],
                                    "style": "",
                                    "text": "160 240"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-11",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [356, 474.5, 37, 23],
                                    "style": "",
                                    "text": "char"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-12",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [293, 474.5, 32.5, 23],
                                    "style": "",
                                    "text": "4"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-13",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 4,
                                    "outlettype": ["", "", "", ""],
                                    "patching_rect": [293, 442.5, 164, 23],
                                    "style": "",
                                    "text": "route planecount type dim"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-23",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [155, 474.5, 74, 23],
                                    "style": "",
                                    "text": "160 240"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-24",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [92, 474.5, 37, 23],
                                    "style": "",
                                    "text": "char"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-25",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [29, 474.5, 32.5, 23],
                                    "style": "",
                                    "text": "4"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-28",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 4,
                                    "outlettype": ["", "", "", ""],
                                    "patching_rect": [29, 442.5, 164, 23],
                                    "style": "",
                                    "text": "route planecount type dim"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-30",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [29, 413.5, 80, 23],
                                    "style": "",
                                    "text": "jit.matrixinfo"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-38",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [293, 412.5, 80, 23],
                                    "style": "",
                                    "text": "jit.matrixinfo"
                                }
                            },
                            {
                                "box": {
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-43",
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
                                        "dim[2]",
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
                                    "patching_rect": [344, 338, 145, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-51",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": [
                                        "jit_matrix",
                                        "jit_matrix",
                                        ""
                                    ],
                                    "patching_rect": [10, 357.5, 90, 23],
                                    "style": "",
                                    "text": "jit.demultiplex"
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["jit.demultiplex"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [10, 10, 688, 152]
                                }
                            },
                            {
                                "box": {
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-27",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demovideo.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["jit_matrix"],
                                    "patching_rect": [10, 167.5, 230, 125],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-18",
                                    "linecount": 2,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [494, 241.5, 250, 40],
                                    "style": "",
                                    "text": "Set the amount between scan_a passes sent to outlet 2"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-15",
                                    "linecount": 2,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [494, 190.5, 244, 40],
                                    "style": "",
                                    "text": "Set the amount grabbed from incoming matrix, sent to outlet 1"
                                }
                            },
                            {
                                "box": {
                                    "attr": "scan_b",
                                    "attrfilter": ["scan_b"],
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-16",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [343, 251, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "scan_a",
                                    "attrfilter": ["scan_a"],
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-26",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [343, 200, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-29",
                                    "maxclass": "number",
                                    "minimum": 0,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 1,
                                    "patching_rect": [343, 176, 50, 21],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "number[3]",
                                            "parameter_shortname": "number[3]",
                                            "parameter_type": 3,
                                            "parameter_initial_enable": 1,
                                            "parameter_initial": [1],
                                            "parameter_invisible": 1
                                        }
                                    },
                                    "style": "",
                                    "triscale": 0.9,
                                    "varname": "number[1]"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-31",
                                    "maxclass": "number",
                                    "minimum": 0,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 1,
                                    "patching_rect": [343, 227, 50, 21],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "number[2]",
                                            "parameter_shortname": "number[2]",
                                            "parameter_type": 3,
                                            "parameter_initial_enable": 1,
                                            "parameter_initial": [1],
                                            "parameter_invisible": 1
                                        }
                                    },
                                    "style": "",
                                    "triscale": 0.9,
                                    "varname": "number[3]"
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "id": "obj-49",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [274, 502, 160, 120]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "id": "obj-50",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [10, 502, 160, 120]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-10", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        399.166656,
                                        467.5,
                                        475.5,
                                        467.5
                                    ],
                                    "source": ["obj-13", 2]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-11", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        350.833344,
                                        467.5,
                                        383.5,
                                        467.5
                                    ],
                                    "source": ["obj-13", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-12", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [302.5, 467.5, 316, 467.5],
                                    "source": ["obj-13", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-51", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [352.5, 330.25, 19.5, 330.25],
                                    "source": ["obj-16", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-51", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [353.5, 330.25, 19.5, 330.25],
                                    "source": ["obj-17", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-51", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [352.5, 330.75, 19.5, 330.75],
                                    "source": ["obj-26", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-51", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [19.5, 345],
                                    "source": ["obj-27", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-23", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        135.166672,
                                        467.5,
                                        219.5,
                                        467.5
                                    ],
                                    "source": ["obj-28", 2]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-24", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        86.833336,
                                        467.5,
                                        119.5,
                                        467.5
                                    ],
                                    "source": ["obj-28", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-25", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [38.5, 467.5, 52, 467.5],
                                    "source": ["obj-28", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-26", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-29", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-28", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-30", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-16", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-31", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-17", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-32", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-51", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        353.5,
                                        396.5,
                                        323,
                                        396.5,
                                        323,
                                        330.5,
                                        19.5,
                                        330.5
                                    ],
                                    "source": ["obj-34", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-13", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-38", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-34", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-43", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-30", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [19.5, 389.5, 38.5, 389.5],
                                    "source": ["obj-51", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-38", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [55, 394, 302.5, 394],
                                    "source": ["obj-51", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-49", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [55, 394.75, 283.5, 394.75],
                                    "source": ["obj-51", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-50", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [19.5, 433.75, 19.5, 433.75],
                                    "source": ["obj-51", 0]
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
                    "jsarguments": ["jit.demultiplex"],
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
                    "id": "obj-3",
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
                        "rect": [0, 26, 821, 646],
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
                        "boxes": [],
                        "lines": []
                    },
                    "patching_rect": [205, 205, 50, 20],
                    "saved_object_attributes": {
                        "description": "",
                        "digest": "",
                        "fontsize": 13,
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
        "lines": [
            {
                "patchline": {
                    "destination": ["obj-1", 0],
                    "disabled": 0,
                    "hidden": 0,
                    "source": ["obj-5", 0]
                }
            }
        ],
        "parameters": {
            "obj-2::obj-31": ["number[2]", "number[2]", 0],
            "obj-2::obj-32": ["toggle", "toggle", 0],
            "obj-2::obj-27::obj-4::obj-21": ["number", "number", 0],
            "obj-2::obj-27::obj-4::obj-20": ["live.tab[1]", "live.tab[1]", 0],
            "obj-2::obj-27::obj-4::obj-18": ["number[1]", "number[1]", 0],
            "obj-2::obj-29": ["number[3]", "number[3]", 0]
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
                "name": "demovideo.maxpat",
                "bootpath": "/Volumes/Underdog/max/maxmsp-misc/help/jitter-help",
                "patcherrelativepath": ".",
                "type": "JSON",
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