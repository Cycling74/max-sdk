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
        "rect": [133, 79, 586, 459],
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
                    "fontsize": 11.595187,
                    "id": "obj-27",
                    "linecount": 2,
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [354, 320, 154, 33],
                    "style": "",
                    "text": "A special shout out to Jean Laroche for the formula."
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12,
                    "id": "obj-3",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "patching_rect": [463, 18.5, 92, 18],
                    "style": "",
                    "text": "resize 700 540"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12,
                    "id": "obj-8",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "patching_rect": [364, 18.5, 92, 18],
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
                    "patching_rect": [364, 45, 134, 20],
                    "saved_object_attributes": {
                        "filename": "helpstarter.js",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter.js buffer~"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12,
                    "id": "obj-4",
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
                        "rect": [133, 105, 586, 433],
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
                                    "id": "obj-1",
                                    "ignoreclick": 1,
                                    "legacytextcolor": 1,
                                    "maxclass": "textbutton",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", "int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [182, 388, 20, 20],
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
                                    "id": "obj-3",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [72, 385.5, 108, 25],
                                    "style": "",
                                    "text": "turn on audio"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-27",
                                    "linecount": 2,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [438, 277, 122, 40],
                                    "style": "",
                                    "text": "set resonance (signal or float)"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-26",
                                    "linecount": 2,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [438, 211, 100, 40],
                                    "style": "",
                                    "text": "sweep filter frequency"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-25",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [312, 168, 144, 25],
                                    "style": "",
                                    "text": "set cutoff frequency"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "format": 6,
                                    "id": "obj-22",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [388, 287, 50, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "format": 6,
                                    "id": "obj-21",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [260, 170, 50, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-6",
                                    "linecount": 2,
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [335, 211, 98, 38],
                                    "style": "",
                                    "text": "200, 2000 500 200 1000"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-19",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [260, 222, 54, 23],
                                    "style": "",
                                    "text": "$1 30"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-33",
                                    "local": 1,
                                    "maxclass": "ezdac~",
                                    "numinlets": 2,
                                    "numoutlets": 0,
                                    "patching_rect": [26, 376, 44, 44],
                                    "prototypename": "helpfile",
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "args": ["@module", 3],
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-32",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demosound.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [-4, -3],
                                    "outlettype": ["signal"],
                                    "patching_rect": [25, 170, 219, 89],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-42",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": ["signal", "bang"],
                                    "patching_rect": [260, 268.5, 63, 23],
                                    "style": "",
                                    "text": "line~ 200"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-5",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 1,
                                    "outlettype": ["signal"],
                                    "patching_rect": [26, 327, 121, 23],
                                    "style": "",
                                    "text": "lores~ 200 0.75"
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["lores~", 90],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [11, 10, 549, 140]
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpargs.js",
                                    "id": "obj-4",
                                    "ignoreclick": 1,
                                    "jsarguments": ["lores~"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [146, 327, 200.729019, 54],
                                    "presentation_rect": [
                                        146,
                                        327,
                                        200.729019,
                                        54
                                    ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-42", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-19", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-19", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-21", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 2],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-22", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-32", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-42", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-33", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-5", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-33", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-5", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-42", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-6", 0]
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
                    "id": "obj-6",
                    "ignoreclick": 1,
                    "jsarguments": ["buffer~"],
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
                        "rect": [0, 26, 586, 433],
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
        "lines": [
            {
                "patchline": {
                    "destination": ["obj-1", 0],
                    "disabled": 0,
                    "hidden": 0,
                    "source": ["obj-3", 0]
                }
            },
            {
                "patchline": {
                    "destination": ["obj-1", 0],
                    "disabled": 0,
                    "hidden": 0,
                    "source": ["obj-8", 0]
                }
            }
        ],
        "parameters": {
            "obj-4::obj-32::obj-21::obj-6": ["live.tab[3]", "live.tab[1]", 0],
            "obj-4::obj-32::obj-35": ["[5]", "Level", 0]
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