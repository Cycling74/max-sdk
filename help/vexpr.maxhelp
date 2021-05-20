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
        "rect": [48, 79, 616, 565],
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
                    "id": "obj-2",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "patching_rect": [478, 419, 127, 20],
                    "saved_object_attributes": {
                        "filename": "helpstarter.js",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter.js vexpr"
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
                        "rect": [48, 105, 616, 539],
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
                                    "id": "obj-3",
                                    "linecount": 2,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [50, 357, 155, 40],
                                    "style": "",
                                    "text": "compare result with scalarmode on and off"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-5",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [10, 324, 572, 21],
                                    "style": "",
                                    "text": "when scalarmode 1 is sent to vexpr, input of length 1 is applied to each element of the other lists"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-37",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [293, 397, 258, 21],
                                    "style": "",
                                    "text": "scalarmode can also be set as an attribute:",
                                    "textcolor": [
                                        0.501961,
                                        0.501961,
                                        0.501961,
                                        1
                                    ]
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-1",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [314, 493, 138, 23],
                                    "style": "",
                                    "text": "500 1000 1500 2000"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-6",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [315, 463, 191, 23],
                                    "style": "",
                                    "text": "vexpr $i1 * $i2 @scalarmode 1"
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "bgcolor": [1, 0.788235, 0.470588, 1],
                                    "bgoncolor": [0.55, 0.55, 0.55, 1],
                                    "fontface": 1,
                                    "hint": "",
                                    "id": "obj-28",
                                    "ignoreclick": 1,
                                    "legacytextcolor": 1,
                                    "maxclass": "textbutton",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", "int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [465, 433, 20, 20],
                                    "rounded": 60,
                                    "style": "",
                                    "text": "1",
                                    "textcolor": [0.34902, 0.34902, 0.34902, 1],
                                    "textoncolor": [1, 1, 1, 1],
                                    "textovercolor": [0.2, 0.2, 0.2, 1],
                                    "usebgoncolor": 1,
                                    "usetextovercolor": 1
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "bgcolor": [1, 0.788235, 0.470588, 1],
                                    "bgoncolor": [0.55, 0.55, 0.55, 1],
                                    "fontface": 1,
                                    "hint": "",
                                    "id": "obj-29",
                                    "ignoreclick": 1,
                                    "legacytextcolor": 1,
                                    "maxclass": "textbutton",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", "int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [293, 433, 20, 20],
                                    "rounded": 60,
                                    "style": "",
                                    "text": "2",
                                    "textcolor": [0.34902, 0.34902, 0.34902, 1],
                                    "textoncolor": [1, 1, 1, 1],
                                    "textovercolor": [0.2, 0.2, 0.2, 1],
                                    "usebgoncolor": 1,
                                    "usetextovercolor": 1
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
                                    "patching_rect": [487, 434, 23, 23],
                                    "style": "",
                                    "text": "50"
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
                                    "patching_rect": [315, 434, 79, 23],
                                    "style": "",
                                    "text": "10 20 30 40"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-8",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [73, 493, 124, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-9",
                                    "maxclass": "toggle",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [28, 367, 20, 20],
                                    "style": ""
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
                                    "patching_rect": [28, 406, 96, 23],
                                    "style": "",
                                    "text": "scalarmode $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-11",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [73, 463, 148, 23],
                                    "style": "",
                                    "text": "vexpr $i1 * $i2"
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "bgcolor": [1, 0.788235, 0.470588, 1],
                                    "bgoncolor": [0.55, 0.55, 0.55, 1],
                                    "fontface": 1,
                                    "hint": "",
                                    "id": "obj-12",
                                    "ignoreclick": 1,
                                    "legacytextcolor": 1,
                                    "maxclass": "textbutton",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", "int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [180, 433, 20, 20],
                                    "rounded": 60,
                                    "style": "",
                                    "text": "1",
                                    "textcolor": [0.34902, 0.34902, 0.34902, 1],
                                    "textoncolor": [1, 1, 1, 1],
                                    "textovercolor": [0.2, 0.2, 0.2, 1],
                                    "usebgoncolor": 1,
                                    "usetextovercolor": 1
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "bgcolor": [1, 0.788235, 0.470588, 1],
                                    "bgoncolor": [0.55, 0.55, 0.55, 1],
                                    "fontface": 1,
                                    "hint": "",
                                    "id": "obj-13",
                                    "ignoreclick": 1,
                                    "legacytextcolor": 1,
                                    "maxclass": "textbutton",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", "int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [51, 433, 20, 20],
                                    "rounded": 60,
                                    "style": "",
                                    "text": "2",
                                    "textcolor": [0.34902, 0.34902, 0.34902, 1],
                                    "textoncolor": [1, 1, 1, 1],
                                    "textovercolor": [0.2, 0.2, 0.2, 1],
                                    "usebgoncolor": 1,
                                    "usetextovercolor": 1
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
                                    "patching_rect": [202, 434, 23, 23],
                                    "style": "",
                                    "text": "50"
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
                                    "patching_rect": [73, 433, 79, 23],
                                    "style": "",
                                    "text": "10 20 30 40"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-17",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [26, 194, 256, 23],
                                    "style": "",
                                    "text": "vexpr $i1 + $i2"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-18",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [282, 143, 100, 21],
                                    "style": "",
                                    "text": "Click on this list"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-19",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [47, 143, 103, 21],
                                    "style": "",
                                    "text": "then on this one"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-20",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [263, 168, 98, 23],
                                    "style": "",
                                    "text": "50 60 70 80 90"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-21",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [26, 168, 79, 23],
                                    "style": "",
                                    "text": "10 20 30 40"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-22",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 5,
                                    "outlettype": [
                                        "int",
                                        "int",
                                        "int",
                                        "int",
                                        "int"
                                    ],
                                    "patching_rect": [26, 230, 229, 23],
                                    "style": "",
                                    "text": "unpack 0 0 0 0 0"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-23",
                                    "maxclass": "number",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [26, 259, 46, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-24",
                                    "maxclass": "number",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [79, 259, 46, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-25",
                                    "maxclass": "number",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [131, 259, 46, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-26",
                                    "maxclass": "number",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [184, 259, 46, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-27",
                                    "maxclass": "number",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [236, 259, 46, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["vexpr", 85],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [10, 10, 512, 114]
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpargs.js",
                                    "id": "obj-4",
                                    "ignoreclick": 1,
                                    "jsarguments": ["vexpr"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [286, 195, 135.372208, 99],
                                    "presentation_rect": [
                                        286,
                                        195,
                                        135.372208,
                                        99
                                    ]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "bgcolor": [1, 0.788235, 0.470588, 1],
                                    "bgoncolor": [0.55, 0.55, 0.55, 1],
                                    "fontface": 1,
                                    "hint": "",
                                    "id": "obj-7",
                                    "ignoreclick": 1,
                                    "legacytextcolor": 1,
                                    "maxclass": "textbutton",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", "int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [26, 143, 20, 20],
                                    "rounded": 60,
                                    "style": "",
                                    "text": "2",
                                    "textcolor": [0.34902, 0.34902, 0.34902, 1],
                                    "textoncolor": [1, 1, 1, 1],
                                    "textovercolor": [0.2, 0.2, 0.2, 1],
                                    "usebgoncolor": 1,
                                    "usetextovercolor": 1
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "bgcolor": [1, 0.788235, 0.470588, 1],
                                    "bgoncolor": [0.55, 0.55, 0.55, 1],
                                    "fontface": 1,
                                    "hint": "",
                                    "id": "obj-93",
                                    "ignoreclick": 1,
                                    "legacytextcolor": 1,
                                    "maxclass": "textbutton",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", "int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [263, 143, 20, 20],
                                    "rounded": 60,
                                    "style": "",
                                    "text": "1",
                                    "textcolor": [0.34902, 0.34902, 0.34902, 1],
                                    "textoncolor": [1, 1, 1, 1],
                                    "textovercolor": [0.2, 0.2, 0.2, 1],
                                    "usebgoncolor": 1,
                                    "usetextovercolor": 1
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-11", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [37.5, 459, 82.5, 459],
                                    "source": ["obj-10", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-8", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [82.5, 486, 187.5, 486],
                                    "source": ["obj-11", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-11", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-14", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-11", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-15", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-22", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-17", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-17", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-20", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-17", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-21", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-23", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-22", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-24", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-22", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-25", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-22", 2]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-26", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-22", 3]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-27", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-22", 4]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-35", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-36", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-1", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [324.5, 487, 442.5, 487],
                                    "source": ["obj-6", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-10", 0],
                                    "disabled": 0,
                                    "hidden": 0,
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
                    "id": "obj-5",
                    "ignoreclick": 1,
                    "jsarguments": ["vexpr"],
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
                    "id": "obj-1",
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
                        "rect": [0, 26, 616, 539],
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
        "dependency_cache": [
            {
                "name": "helpname.js",
                "bootpath": "/Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
                "patcherrelativepath": "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
                "type": "TEXT",
                "implicit": 1
            },
            {
                "name": "helpargs.js",
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