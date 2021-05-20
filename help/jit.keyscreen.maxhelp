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
        "rect": [34, 78, 782, 537],
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
                    "patching_rect": [118, 389, 165, 20],
                    "saved_object_attributes": {
                        "filename": "helpstarter.js",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter.js jit.keyscreen"
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
                        "rect": [34, 104, 782, 511],
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
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-39",
                                    "linecount": 4,
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [330, 370, 69, 67],
                                    "style": "",
                                    "text": "alpha $1, red $2, green $3, blue $4"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-25",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [655.65387, 284, 36, 21],
                                    "style": "helpfile_label",
                                    "text": "blue"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-23",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [572.269226, 284, 45, 21],
                                    "style": "helpfile_label",
                                    "text": "green"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-21",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [500.884613, 284, 30, 21],
                                    "style": "helpfile_label",
                                    "text": "red"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-19",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [415.5, 284, 43, 21],
                                    "style": "helpfile_label",
                                    "text": "alpha"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-18",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [483, 263, 151, 21],
                                    "style": "helpfile_label",
                                    "text": "tolerance level by plane"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-17",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [663.65387, 454, 69, 23],
                                    "style": "",
                                    "text": "bluetol $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-16",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [584.769226, 454, 77, 23],
                                    "style": "",
                                    "text": "greentol $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-15",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [505.884613, 454, 63, 23],
                                    "style": "",
                                    "text": "redtol $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-14",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [427, 454, 76, 23],
                                    "style": "",
                                    "text": "alphatol $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-10",
                                    "maxclass": "newobj",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [107, 321, 51, 23],
                                    "style": "",
                                    "text": "r to_ks"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-9",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [427, 482, 53, 23],
                                    "style": "",
                                    "text": "s to_ks"
                                }
                            },
                            {
                                "box": {
                                    "floatoutput": 1,
                                    "id": "obj-8",
                                    "maxclass": "slider",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 1,
                                    "patching_rect": [663.65387, 307, 20, 140],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "slider[2]",
                                            "parameter_shortname": "slider[2]",
                                            "parameter_type": 3,
                                            "parameter_initial_enable": 1,
                                            "parameter_initial": [0.307692],
                                            "parameter_invisible": 1
                                        }
                                    },
                                    "size": 1,
                                    "style": "",
                                    "varname": "slider[2]"
                                }
                            },
                            {
                                "box": {
                                    "floatoutput": 1,
                                    "id": "obj-4",
                                    "maxclass": "slider",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 1,
                                    "patching_rect": [584.769226, 307, 20, 140],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "slider[1]",
                                            "parameter_shortname": "slider[1]",
                                            "parameter_type": 3,
                                            "parameter_initial_enable": 1,
                                            "parameter_initial": [0.323077],
                                            "parameter_invisible": 1
                                        }
                                    },
                                    "size": 1,
                                    "style": "",
                                    "varname": "slider[1]"
                                }
                            },
                            {
                                "box": {
                                    "floatoutput": 1,
                                    "id": "obj-3",
                                    "maxclass": "slider",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 1,
                                    "patching_rect": [505.884613, 307, 20, 140],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "slider",
                                            "parameter_shortname": "slider",
                                            "parameter_type": 3,
                                            "parameter_initial_enable": 1,
                                            "parameter_initial": [0.330769],
                                            "parameter_invisible": 1
                                        }
                                    },
                                    "size": 1,
                                    "style": "",
                                    "varname": "slider"
                                }
                            },
                            {
                                "box": {
                                    "floatoutput": 1,
                                    "id": "obj-1",
                                    "maxclass": "slider",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [427, 307, 20, 140],
                                    "size": 1,
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-32",
                                    "maxclass": "number",
                                    "maximum": 2,
                                    "minimum": 0,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 1,
                                    "patching_rect": [471, 212, 53, 23],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "number[8]",
                                            "parameter_shortname": "number[8]",
                                            "parameter_type": 3,
                                            "parameter_initial_enable": 1,
                                            "parameter_initial": [2],
                                            "parameter_invisible": 1
                                        }
                                    },
                                    "style": "",
                                    "triscale": 0.9,
                                    "varname": "number[2]"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-33",
                                    "maxclass": "number",
                                    "maximum": 2,
                                    "minimum": 0,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 1,
                                    "patching_rect": [471, 179, 53, 23],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "number[7]",
                                            "parameter_shortname": "number[7]",
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
                                    "fontsize": 13,
                                    "id": "obj-34",
                                    "maxclass": "number",
                                    "maximum": 2,
                                    "minimum": 0,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 1,
                                    "patching_rect": [471, 145, 53, 23],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "number[6]",
                                            "parameter_shortname": "number[6]",
                                            "parameter_type": 3,
                                            "parameter_initial_enable": 1,
                                            "parameter_initial": [0],
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
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-35",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [528, 214, 59, 23],
                                    "style": "",
                                    "text": "mask $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-36",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [528, 181, 61, 23],
                                    "style": "",
                                    "text": "target $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-37",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [528, 146, 50, 23],
                                    "style": "",
                                    "text": "key $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-26",
                                    "maxclass": "newobj",
                                    "numinlets": 5,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [576, 282, 544, 451],
                                        "bglocked": 0,
                                        "openinpresentation": 0,
                                        "default_fontsize": 10,
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
                                        "boxes": [
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-16",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [
                                                        "jit_matrix"
                                                    ],
                                                    "patching_rect": [
                                                        122,
                                                        27,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-15",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [
                                                        "jit_matrix"
                                                    ],
                                                    "patching_rect": [
                                                        97.5,
                                                        27,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-14",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [
                                                        "jit_matrix"
                                                    ],
                                                    "patching_rect": [
                                                        70.5,
                                                        27,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 13,
                                                    "id": "obj-22",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        36,
                                                        69,
                                                        30,
                                                        21
                                                    ],
                                                    "style": "",
                                                    "text": "+ 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 13,
                                                    "id": "obj-28",
                                                    "maxclass": "newobj",
                                                    "numinlets": 4,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        36,
                                                        94.5,
                                                        59,
                                                        21
                                                    ],
                                                    "style": "",
                                                    "text": "switch 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        267,
                                                        259,
                                                        83,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "vexpr $i1/255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-2",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", ""],
                                                    "patching_rect": [
                                                        228,
                                                        225,
                                                        54,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "zl slice 4"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-3",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "jit_matrix",
                                                        ""
                                                    ],
                                                    "patching_rect": [
                                                        36,
                                                        156,
                                                        182,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "jit.matrix 4 char 320 240 @thru 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        228,
                                                        194,
                                                        90,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "prepend getcell"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        226,
                                                        162,
                                                        54,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-6",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        261,
                                                        133,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 4"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-7",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        219,
                                                        131,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 4"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "int",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        216,
                                                        108,
                                                        67,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "unpack 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", ""],
                                                    "patching_rect": [
                                                        215,
                                                        83,
                                                        75,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "route mouse"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-10",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        267,
                                                        292,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-11",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        246,
                                                        34,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-12",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        122,
                                                        252,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-13",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        36.5,
                                                        27,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-9", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-11", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-22",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-28",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-14", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-28",
                                                        2
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-28",
                                                        3
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-1", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-28",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-22", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-28", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-12",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-4", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-8", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-8", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 0]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [217, 341, 73, 23],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p cellquery"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "bubbleside": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-58",
                                    "linecount": 2,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [204, 436, 106, 55],
                                    "style": "",
                                    "text": "click on a color for the key"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-13",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [590, 214.710846, 144, 25],
                                    "style": "",
                                    "text": "select mask inlet"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-12",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [590, 178.855423, 144, 25],
                                    "style": "",
                                    "text": "select target inlet"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-27",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [590, 143, 144, 25],
                                    "style": "",
                                    "text": "select key inlet"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-20",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [10, 358, 160, 120],
                                    "presentation_rect": [30, 30, 160, 120]
                                }
                            },
                            {
                                "box": {
                                    "args": ["@file", "dishes.mov"],
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-7",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demovideo2.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["jit_matrix"],
                                    "patching_rect": [312, 145, 135, 96],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "args": ["@file", "blading.mov"],
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-6",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demovideo2.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["jit_matrix"],
                                    "patching_rect": [161, 145, 135, 96],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-24",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demovideo2.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["jit_matrix"],
                                    "patching_rect": [10, 145, 135, 96],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-5",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [10, 320, 85, 23],
                                    "style": "",
                                    "text": "jit.keyscreen"
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["jit.keyscreen"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [10, 10, 620, 125]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "id": "obj-29",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [217, 370, 80, 60]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-14", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-1", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-10", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-9", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-14", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-9", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-15", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-9", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-16", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-9", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-17", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-26", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-24", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-24", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-29", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-26", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-39", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-26", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-26", 4],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        287.5,
                                        434,
                                        305,
                                        434,
                                        305,
                                        332,
                                        280.5,
                                        332
                                    ],
                                    "source": ["obj-29", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-15", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-3", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-35", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-32", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-36", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-33", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-26", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-34", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-37", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-34", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-35", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-36", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-37", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-9", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-39", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-16", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-4", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-20", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-5", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-26", 2],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-6", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-6", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-26", 3],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-7", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 2],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-7", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-17", 0],
                                    "disabled": 0,
                                    "hidden": 0,
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
                    "jsarguments": ["jit.keyscreen"],
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
                        "rect": [0, 26, 782, 511],
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
                    "patching_rect": [118, 354, 50, 20],
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
            "obj-2::obj-7::obj-4::obj-21": ["number[5]", "number", 0],
            "obj-2::obj-7::obj-4::obj-18": ["number[4]", "number[1]", 0],
            "obj-2::obj-3": ["slider", "slider", 0],
            "obj-2::obj-34": ["number[6]", "number[6]", 0],
            "obj-2::obj-7::obj-4::obj-20": ["live.tab[3]", "live.tab[1]", 0],
            "obj-2::obj-33": ["number[7]", "number[7]", 0],
            "obj-2::obj-24::obj-4::obj-20": ["live.tab[1]", "live.tab[1]", 0],
            "obj-2::obj-6::obj-4::obj-20": ["live.tab[2]", "live.tab[1]", 0],
            "obj-2::obj-4": ["slider[1]", "slider[1]", 0],
            "obj-2::obj-32": ["number[8]", "number[8]", 0],
            "obj-2::obj-6::obj-4::obj-21": ["number[3]", "number", 0],
            "obj-2::obj-8": ["slider[2]", "slider[2]", 0],
            "obj-2::obj-24::obj-4::obj-18": ["number[1]", "number[1]", 0],
            "obj-2::obj-24::obj-4::obj-21": ["number", "number", 0],
            "obj-2::obj-6::obj-4::obj-18": ["number[2]", "number[1]", 0]
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