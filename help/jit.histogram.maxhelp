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
        "rect": [69, 78, 853, 742],
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
                    "patching_rect": [472, 333, 92, 18],
                    "style": "",
                    "text": "resize 800 640"
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
                    "patching_rect": [472, 381, 151, 20],
                    "saved_object_attributes": {
                        "filename": "helpstarter",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter jit.histogram"
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
                        "rect": [69, 104, 853, 716],
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
                                    "id": "obj-20",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [420, 473.5, 306, 21],
                                    "style": "",
                                    "text": "alpha"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "id": "obj-19",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [519, 277, 239, 25],
                                    "style": "",
                                    "text": "Set the value used for normalization"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "id": "obj-18",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [497, 224, 222, 25],
                                    "style": "",
                                    "text": "Set the normalization mode (0-2)"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "id": "obj-15",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [473, 167, 226, 25],
                                    "style": "",
                                    "text": "Clear the matrix after each output"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-13",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [421, 660, 306, 21],
                                    "style": "",
                                    "text": "blue "
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-14",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [420, 598, 306, 21],
                                    "style": "",
                                    "text": "green"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-12",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [420, 536, 306, 21],
                                    "style": "",
                                    "text": "red "
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-11",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [420, 412, 306, 21],
                                    "style": "",
                                    "text": "output for all four planes"
                                }
                            },
                            {
                                "box": {
                                    "attr": "normval",
                                    "attrfilter": ["normval"],
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-10",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [369, 277, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "autoclear",
                                    "attrfilter": ["autoclear"],
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-9",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [323, 171, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "normalize",
                                    "attrfilter": ["normalize"],
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-8",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [347, 226, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-3",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demovideo.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["jit_matrix"],
                                    "patching_rect": [11, 143, 230, 125],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-16",
                                    "maxclass": "number",
                                    "maximum": 2,
                                    "minimum": 0,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 1,
                                    "patching_rect": [347, 202, 50, 23],
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
                                    "id": "obj-17",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [11, 374, 125, 23],
                                    "style": "",
                                    "text": "jit.matrix 4 char 256"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-21",
                                    "maxclass": "number",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 1,
                                    "patching_rect": [369, 253, 50, 23],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "number[2]",
                                            "parameter_shortname": "number[2]",
                                            "parameter_type": 3,
                                            "parameter_initial_enable": 1,
                                            "parameter_initial": [255],
                                            "parameter_invisible": 1
                                        }
                                    },
                                    "style": "",
                                    "triscale": 0.9,
                                    "varname": "number"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-24",
                                    "maxclass": "toggle",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["int"],
                                    "parameter_enable": 1,
                                    "patching_rect": [323, 142, 24, 24],
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
                                    "id": "obj-28",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [40, 483, 61, 23],
                                    "style": "",
                                    "text": "jit.pack 4"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-29",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [25, 516, 61, 23],
                                    "style": "",
                                    "text": "jit.pack 4"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-34",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [11, 548.5, 61, 23],
                                    "style": "",
                                    "text": "jit.pack 4"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-35",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 5,
                                    "outlettype": [
                                        "jit_matrix",
                                        "jit_matrix",
                                        "jit_matrix",
                                        "jit_matrix",
                                        ""
                                    ],
                                    "patching_rect": [11, 413, 76, 23],
                                    "style": "",
                                    "text": "jit.unpack 4"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-39",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [11, 337, 150, 23],
                                    "style": "",
                                    "text": "jit.histogram 4 long 256"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-50",
                                    "linecount": 4,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [179.5, 337, 607, 65],
                                    "style": "",
                                    "text": "The output matrix must be of type long and will only be one dimensional. The size of this matrix can be as large as you like, but has a minimum of size 256. Values falling outside of the range 0 to (size-1), will be ignored. If you wish to take a histogram of floating point numbers, you must quantize them to an integer range first."
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["jit.histogram"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [11, 10, 620, 125]
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-27",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [53.5, 449.5, 61, 23],
                                    "style": "",
                                    "text": "jit.pack 4"
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "id": "obj-30",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [165, 660, 256, 35]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "id": "obj-31",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [165, 598, 256, 30]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "id": "obj-32",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [165, 536, 256, 30]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "id": "obj-33",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [165, 473.5, 256, 30]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "id": "obj-36",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [165, 412, 256, 30]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-39", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [378.5, 332, 20.5, 332],
                                    "source": ["obj-10", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-8", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-16", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-35", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-17", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-36", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [20.5, 403, 174.5, 403],
                                    "source": ["obj-17", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-10", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-21", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-9", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-24", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.6, 1, 1],
                                    "destination": ["obj-30", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [63, 638.75, 174.5, 638.75],
                                    "source": ["obj-27", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-31", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        49.5,
                                        601,
                                        150,
                                        601,
                                        150,
                                        579,
                                        174.5,
                                        579
                                    ],
                                    "source": ["obj-28", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.4, 0.6, 1],
                                    "destination": ["obj-32", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        34.5,
                                        589,
                                        143,
                                        589,
                                        143,
                                        520,
                                        174.5,
                                        520
                                    ],
                                    "source": ["obj-29", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-39", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-3", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-33", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        20.5,
                                        578.5,
                                        128.5,
                                        578.5,
                                        128.5,
                                        461.5,
                                        174.5,
                                        461.5
                                    ],
                                    "source": ["obj-34", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.6, 1, 1],
                                    "destination": ["obj-27", 3],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [63.25, 441.25, 105, 441.25],
                                    "source": ["obj-35", 3]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.6, 1, 1],
                                    "destination": ["obj-27", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [63.25, 441.25, 63, 441.25],
                                    "source": ["obj-35", 3]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 0.890196, 0.090196, 1],
                                    "destination": ["obj-28", 2],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [49, 477, 77.5, 477],
                                    "source": ["obj-35", 2]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 0.890196, 0.090196, 1],
                                    "destination": ["obj-28", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [49, 456, 49.5, 456],
                                    "source": ["obj-35", 2]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.4, 0.6, 1],
                                    "destination": ["obj-29", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [34.75, 508, 48.5, 508],
                                    "source": ["obj-35", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.4, 0.6, 1],
                                    "destination": ["obj-29", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [34.75, 511, 34.5, 511],
                                    "source": ["obj-35", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 1, 1, 1],
                                    "destination": ["obj-34", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [20.5, 488, 20.5, 488],
                                    "source": ["obj-35", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-17", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [20.5, 381, 20.5, 381],
                                    "source": ["obj-39", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-39", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [356.5, 308.5, 20.5, 308.5],
                                    "source": ["obj-8", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-39", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [332.5, 309.5, 20.5, 309.5],
                                    "source": ["obj-9", 0]
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
                    "jsarguments": ["jit.histogram"],
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
                        "rect": [0, 26, 853, 716],
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
            "obj-2::obj-3::obj-4::obj-20": ["live.tab[1]", "live.tab[1]", 0],
            "obj-2::obj-16": ["number[3]", "number[3]", 0],
            "obj-2::obj-24": ["toggle", "toggle", 0],
            "obj-2::obj-3::obj-4::obj-18": ["number[1]", "number[1]", 0],
            "obj-2::obj-3::obj-4::obj-21": ["number", "number", 0],
            "obj-2::obj-21": ["number[2]", "number[2]", 0]
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
                "name": "demovideo.maxpat",
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