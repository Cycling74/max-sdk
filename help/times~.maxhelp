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
        "rect": [41, 79, 393, 519],
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
                        "rect": [0, 26, 393, 493],
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
                        "boxes": [
                            {
                                "box": {
                                    "bubble": 1,
                                    "bubbleside": 2,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-16",
                                    "linecount": 2,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [280, 110, 83, 55],
                                    "style": "",
                                    "text": "try different frequencies"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 12,
                                    "format": 6,
                                    "id": "obj-10",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [296.5, 170, 50, 22],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 12,
                                    "id": "obj-8",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": ["signal"],
                                    "patching_rect": [296.5, 200, 66, 22],
                                    "style": "",
                                    "text": "cycle~ 10."
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 12,
                                    "id": "obj-6",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [10, 60, 175, 20],
                                    "style": "",
                                    "text": "Ring Modulation example"
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpname.js",
                                    "id": "obj-4",
                                    "ignoreclick": 1,
                                    "jsarguments": ["*~"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [10, 10, 51.710938, 53.625]
                                }
                            },
                            {
                                "box": {
                                    "channels": 1,
                                    "id": "obj-2",
                                    "maxclass": "live.gain~",
                                    "numinlets": 1,
                                    "numoutlets": 4,
                                    "orientation": 1,
                                    "outlettype": [
                                        "signal",
                                        "",
                                        "float",
                                        "list"
                                    ],
                                    "parameter_enable": 1,
                                    "patching_rect": [30, 315, 135, 41],
                                    "presentation_rect": [0, 0, 50, 41],
                                    "saved_attribute_attributes": {
                                        "valueof": {
                                            "parameter_longname": "live.gain~",
                                            "parameter_shortname": "level",
                                            "parameter_type": 0,
                                            "parameter_mmin": -70,
                                            "parameter_mmax": 6,
                                            "parameter_initial": [0],
                                            "parameter_unitstyle": 4
                                        }
                                    },
                                    "varname": "live.gain~"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-7",
                                    "local": 1,
                                    "maxclass": "ezdac~",
                                    "numinlets": 2,
                                    "numoutlets": 0,
                                    "patching_rect": [30, 411, 44, 44],
                                    "prototypename": "helpfile",
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "args": [1],
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-1",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demosound.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["signal"],
                                    "patching_rect": [30, 125, 225, 95],
                                    "viewvisibility": 1
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
                                    "outlettype": ["signal"],
                                    "patching_rect": [30, 285, 75, 23],
                                    "style": "",
                                    "text": "*~"
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-17", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-1", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-8", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-10", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-2", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-17", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-7", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-2", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-7", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-2", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-17", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-8", 0]
                                }
                            }
                        ]
                    },
                    "patching_rect": [79, 85, 39, 20],
                    "saved_object_attributes": {
                        "description": "",
                        "digest": "",
                        "globalpatchername": "",
                        "style": "",
                        "tags": ""
                    },
                    "style": "",
                    "text": "p RM"
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
                    "patching_rect": [150, 85, 109, 20],
                    "saved_object_attributes": {
                        "filename": "helpstarter.js",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter.js *~"
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
                        "rect": [41, 105, 393, 493],
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
                                    "bgcolor": [1, 0.788235, 0.470588, 1],
                                    "fontname": "Arial Bold",
                                    "hint": "",
                                    "id": "obj-25",
                                    "ignoreclick": 1,
                                    "legacytextcolor": 1,
                                    "maxclass": "textbutton",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", "int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [175.5, 426, 20, 20],
                                    "rounded": 60,
                                    "style": "",
                                    "text": "1",
                                    "textcolor": [0.34902, 0.34902, 0.34902, 1]
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-26",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [75.5, 436, 108, 25],
                                    "style": "",
                                    "text": "turn on audio"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-7",
                                    "local": 1,
                                    "maxclass": "ezdac~",
                                    "numinlets": 2,
                                    "numoutlets": 0,
                                    "patching_rect": [30, 435, 44, 44],
                                    "prototypename": "helpfile",
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-19",
                                    "linecount": 2,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [84, 380.5, 182, 40],
                                    "style": "",
                                    "text": "signal multiply implements an amplitude envelope"
                                }
                            },
                            {
                                "box": {
                                    "args": [1],
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-1",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demosound.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["signal"],
                                    "patching_rect": [30, 125, 225, 95],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-9",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [60, 325, 86, 23],
                                    "style": "",
                                    "text": "1 100 0 1000"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-10",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": ["signal", "bang"],
                                    "patching_rect": [60, 355, 39, 23],
                                    "style": "",
                                    "text": "line~"
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
                                    "outlettype": ["signal"],
                                    "patching_rect": [30, 390, 49, 23],
                                    "style": "",
                                    "text": "*~"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "format": 6,
                                    "id": "obj-12",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [130, 230, 54, 23],
                                    "style": ""
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
                                    "outlettype": ["signal"],
                                    "patching_rect": [30, 256, 119, 23],
                                    "style": "",
                                    "text": "*~ 0.2"
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["*~", 63],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [10, 10, 360, 110]
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpargs.js",
                                    "id": "obj-4",
                                    "ignoreclick": 1,
                                    "jsarguments": ["*~"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [153, 256, 231.697784, 39],
                                    "presentation_rect": [
                                        153,
                                        256,
                                        231.697784,
                                        39
                                    ]
                                }
                            },
                            {
                                "box": {
                                    "bgcolor": [1, 0.788235, 0.470588, 1],
                                    "fontname": "Arial Bold",
                                    "hint": "",
                                    "id": "obj-93",
                                    "ignoreclick": 1,
                                    "legacytextcolor": 1,
                                    "maxclass": "textbutton",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", "int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [316.5, 312.5, 20, 20],
                                    "rounded": 60,
                                    "style": "",
                                    "text": "2",
                                    "textcolor": [0.34902, 0.34902, 0.34902, 1]
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-24",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [153, 322, 172, 25],
                                    "style": "",
                                    "text": "click here to make a note"
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-17", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-1", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-11", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-10", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-7", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-11", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-7", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [39.5, 430.5, 39.5, 430.5],
                                    "source": ["obj-11", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-17", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-12", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-11", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-17", 0]
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
                    "id": "obj-4",
                    "ignoreclick": 1,
                    "jsarguments": ["*~"],
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
                        "rect": [0, 26, 393, 493],
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
        "lines": [],
        "parameters": {
            "obj-3::obj-1::obj-21::obj-6": ["live.tab[1]", "live.tab[1]", 0],
            "obj-2::obj-1::obj-35": ["[5]", "Level", 0],
            "obj-3::obj-2": ["live.gain~", "level", 0],
            "obj-3::obj-1::obj-35": ["[1]", "Level", 0],
            "obj-2::obj-1::obj-21::obj-6": ["live.tab[3]", "live.tab[1]", 0]
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
                "name": "demosound.maxpat",
                "bootpath": "/Volumes/Underdog/max/maxmsp-misc/help/msp-help",
                "patcherrelativepath": ".",
                "type": "JSON",
                "implicit": 1
            },
            {
                "name": "sine.svg",
                "bootpath": "/Applications/Max 7/Max.app/Contents/Resources/C74/media/max/picts/m4l-picts",
                "patcherrelativepath": "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/media/max/picts/m4l-picts",
                "type": "svg ",
                "implicit": 1
            },
            {
                "name": "saw.svg",
                "bootpath": "/Applications/Max 7/Max.app/Contents/Resources/C74/media/max/picts/m4l-picts",
                "patcherrelativepath": "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/media/max/picts/m4l-picts",
                "type": "svg ",
                "implicit": 1
            },
            {
                "name": "square.svg",
                "bootpath": "/Applications/Max 7/Max.app/Contents/Resources/C74/media/max/picts/m4l-picts",
                "patcherrelativepath": "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/media/max/picts/m4l-picts",
                "type": "svg ",
                "implicit": 1
            },
            {
                "name": "random.svg",
                "bootpath": "/Applications/Max 7/Max.app/Contents/Resources/C74/media/max/picts/m4l-picts",
                "patcherrelativepath": "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/media/max/picts/m4l-picts",
                "type": "svg ",
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