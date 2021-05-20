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
        "rect": [53, 79, 871, 801],
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
                    "patching_rect": [210, 225, 157, 20],
                    "saved_object_attributes": {
                        "filename": "helpstarter.js",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter.js jit.charmap"
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
                        "rect": [53, 105, 871, 775],
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
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-4",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demovideo2.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["jit_matrix"],
                                    "patching_rect": [27, 199, 135, 95],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-1",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [488, 152, 154, 19],
                                    "style": "",
                                    "text": "linear (restore original map)"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "hidden": 1,
                                    "id": "obj-8",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [485, 152, 18, 21],
                                    "style": "",
                                    "text": "0"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-3",
                                    "maxclass": "button",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [465, 151, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-17",
                                    "maxclass": "jit.fpsgui",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [27, 728, 80, 34],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-21",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [447, 620, 174, 19],
                                    "style": "",
                                    "text": "supports: char, any planecount."
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-22",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [50, 44, 179, 217],
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
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        71,
                                                        134,
                                                        23,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-2",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        71,
                                                        83,
                                                        23,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-3",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", ""],
                                                    "patching_rect": [
                                                        71,
                                                        107,
                                                        69,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "bondo 2 20"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-4",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        71,
                                                        160,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-5",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        71,
                                                        51,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
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
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [133, 383, 49, 21],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p group"
                                }
                            },
                            {
                                "box": {
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-23",
                                    "items": [
                                        "sin",
                                        ",",
                                        "cos",
                                        ",",
                                        "sqrt",
                                        ",",
                                        "x^2"
                                    ],
                                    "maxclass": "umenu",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["int", "", ""],
                                    "parameter_enable": 0,
                                    "patching_rect": [636, 145, 53, 21],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-24",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [437, 38, 509, 668],
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
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        160,
                                                        60,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-2",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        196,
                                                        99,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-3",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        255,
                                                        347,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "expr $f1*$f1"
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
                                                        255,
                                                        322,
                                                        79,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "expr sqrt($f1)"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        255,
                                                        300,
                                                        165,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "expr (cos($f1*6.28)*0.5) + 0.5"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-6",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 8,
                                                    "outlettype": [
                                                        "",
                                                        "",
                                                        "",
                                                        "",
                                                        "",
                                                        "",
                                                        "",
                                                        ""
                                                    ],
                                                    "patching_rect": [
                                                        196,
                                                        240,
                                                        105,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "gate 8"
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
                                                        291,
                                                        195,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "- 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        141,
                                                        403,
                                                        40,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        255,
                                                        276,
                                                        162,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "expr (sin($f1*6.28)*0.5) + 0.5"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-10",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        291,
                                                        216,
                                                        38,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-11",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        89,
                                                        444,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack set 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-12",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        141,
                                                        423,
                                                        66,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "clip 0. 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-13",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "int",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        89,
                                                        127,
                                                        62,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-14",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        89,
                                                        470,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-15",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        57,
                                                        105,
                                                        49,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "Uzi 256"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-16",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        160,
                                                        36,
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
                                                        "obj-15",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        169.5,
                                                        91,
                                                        66.5,
                                                        91
                                                    ],
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-11", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-11",
                                                        2
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-11",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-11",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        81.5,
                                                        464,
                                                        98,
                                                        464
                                                    ],
                                                    "source": ["obj-15", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-1", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-4", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 3]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-9", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 0]
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
                                    "patching_rect": [636, 168, 45, 21],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p math"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-25",
                                    "maxclass": "button",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [465, 173, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "hidden": 1,
                                    "id": "obj-26",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [404, 175, 68, 21],
                                    "style": "",
                                    "text": "onscreen 0"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "hidden": 1,
                                    "id": "obj-27",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [533, 155, 18, 21],
                                    "style": "",
                                    "text": "1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "format": 6,
                                    "id": "obj-28",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [490, 173, 50, 21],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "format": 6,
                                    "id": "obj-29",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [542, 173, 50, 21],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "hidden": 1,
                                    "id": "obj-30",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [526, 139, 58, 21],
                                    "style": "",
                                    "text": "loadbang"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "format": 6,
                                    "id": "obj-31",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [781, 199, 43, 21],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "format": 6,
                                    "id": "obj-32",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [735, 199, 43, 21],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-33",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [437, 44, 347, 423],
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
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        143,
                                                        169,
                                                        32.5,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "- 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-2",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        294.714294,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        58,
                                                        70,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        58,
                                                        93,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "speedlim 30"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        223,
                                                        188,
                                                        87,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "expr ($f1-1.)/2."
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
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        269.714294,
                                                        32,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "- 0."
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
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        244.714279,
                                                        32,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 1."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        219.714279,
                                                        55,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        194.714279,
                                                        40,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-10",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        89,
                                                        347.714294,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack set 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-11",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        143,
                                                        319.714294,
                                                        67,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "clip 0. 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-12",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "int",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        89,
                                                        144,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-13",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        89,
                                                        381,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-14",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        58,
                                                        118,
                                                        50,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "Uzi 256"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-15",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        254,
                                                        15,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-16",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        179,
                                                        15,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-9", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        2
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-11", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-1", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 0]
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
                                                    "source": ["obj-14", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        83,
                                                        376,
                                                        98.5,
                                                        376
                                                    ],
                                                    "source": ["obj-14", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-11",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-4", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 0]
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
                                    "patching_rect": [735, 221, 65, 21],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p brco"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "format": 6,
                                    "id": "obj-34",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [626, 199, 43, 21],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "format": 6,
                                    "id": "obj-35",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [580, 199, 43, 21],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-36",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [437, 44, 347, 423],
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
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        143,
                                                        169,
                                                        32.5,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "- 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-2",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        294.714294,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        58,
                                                        70,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        58,
                                                        93,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "speedlim 30"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        223,
                                                        188,
                                                        87,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "expr ($f1-1.)/2."
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
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        269.714294,
                                                        32,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "- 0."
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
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        244.714279,
                                                        32,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 1."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        219.714279,
                                                        55,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        194.714279,
                                                        40,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-10",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        89,
                                                        347.714294,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack set 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-11",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        143,
                                                        319.714294,
                                                        67,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "clip 0. 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-12",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "int",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        89,
                                                        144,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-13",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        89,
                                                        381,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-14",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        58,
                                                        118,
                                                        50,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "Uzi 256"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-15",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        254,
                                                        15,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-16",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        179,
                                                        15,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-9", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        2
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-11", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-1", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 0]
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
                                                    "source": ["obj-14", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        83,
                                                        376,
                                                        98.5,
                                                        376
                                                    ],
                                                    "source": ["obj-14", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-11",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-4", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 0]
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
                                    "patching_rect": [580, 221, 65, 21],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p brco"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "format": 6,
                                    "id": "obj-37",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [467, 199, 43, 21],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "format": 6,
                                    "id": "obj-38",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [421, 199, 43, 21],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-39",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [437, 44, 347, 423],
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
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        143,
                                                        169,
                                                        32.5,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "- 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-2",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        294.714294,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        58,
                                                        70,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        58,
                                                        93,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "speedlim 30"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        223,
                                                        188,
                                                        87,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "expr ($f1-1.)/2."
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
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        269.714294,
                                                        32,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "- 0."
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
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        244.714279,
                                                        32,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 1."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        219.714279,
                                                        55,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        194.714279,
                                                        40,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-10",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        89,
                                                        347.714294,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack set 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-11",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        143,
                                                        319.714294,
                                                        67,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "clip 0. 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-12",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "int",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        89,
                                                        144,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-13",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        89,
                                                        381,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-14",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        58,
                                                        118,
                                                        50,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "Uzi 256"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-15",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        254,
                                                        15,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-16",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        179,
                                                        15,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-9", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        2
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-11", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-1", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 0]
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
                                                    "source": ["obj-14", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        83,
                                                        376,
                                                        98.5,
                                                        376
                                                    ],
                                                    "source": ["obj-14", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-11",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-4", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 0]
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
                                    "patching_rect": [421, 221, 65, 21],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p brco"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "format": 6,
                                    "id": "obj-40",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [310, 199, 43, 21],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "format": 6,
                                    "id": "obj-41",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [264, 199, 43, 21],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-42",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [437, 44, 347, 423],
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
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        143,
                                                        169,
                                                        32.5,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "- 1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-2",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        294.714294,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        58,
                                                        70,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        58,
                                                        93,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "speedlim 30"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        223,
                                                        188,
                                                        87,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "expr ($f1-1.)/2."
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
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        269.714294,
                                                        32,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "- 0."
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
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        244.714279,
                                                        32,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "* 1."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        219.714279,
                                                        55,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        143,
                                                        194.714279,
                                                        40,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-10",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        89,
                                                        347.714294,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack set 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-11",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        143,
                                                        319.714294,
                                                        67,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "clip 0. 255."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-12",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "int",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        89,
                                                        144,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-13",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        89,
                                                        381,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-14",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        58,
                                                        118,
                                                        50,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "Uzi 256"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-15",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        254,
                                                        15,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-16",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        179,
                                                        15,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-9", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        2
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-11", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-1", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-10",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 0]
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
                                                    "source": ["obj-14", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        83,
                                                        376,
                                                        98.5,
                                                        376
                                                    ],
                                                    "source": ["obj-14", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-11",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-4", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 0]
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
                                    "patching_rect": [264, 221, 65, 21],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p brco"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-43",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [519, 357, 80, 21],
                                    "style": "",
                                    "text": "jit.fill lookup 2"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-44",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [676, 357, 80, 21],
                                    "style": "",
                                    "text": "jit.fill lookup 3"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-45",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [205, 357, 80, 21],
                                    "style": "",
                                    "text": "jit.fill lookup 0"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-46",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [409, 568, 56, 21],
                                    "style": "",
                                    "text": "jit.pack 4"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-47",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [409, 539, 56, 21],
                                    "style": "",
                                    "text": "jit.pack 4"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-48",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [408, 508, 56, 21],
                                    "style": "",
                                    "text": "jit.pack 4"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-53",
                                    "maxclass": "newobj",
                                    "numinlets": 4,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [408, 474, 56, 21],
                                    "style": "",
                                    "text": "jit.pack 4"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-54",
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
                                    "patching_rect": [408, 438, 69, 21],
                                    "style": "",
                                    "text": "jit.unpack 4"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-55",
                                    "maxclass": "button",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [676, 199, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-56",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [50, 40, 670, 561],
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
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        386,
                                                        337,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-2",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        431,
                                                        315,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        548,
                                                        291,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        356,
                                                        336,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        256,
                                                        299,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-6",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        170,
                                                        300,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-7",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        87,
                                                        300,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        363,
                                                        370,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack set 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        172,
                                                        129,
                                                        42,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-10",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        172,
                                                        76,
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
                                                        415,
                                                        102,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-12",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        240,
                                                        128,
                                                        42,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-13",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        395,
                                                        232,
                                                        170,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-14",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        310,
                                                        91,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-15",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        334,
                                                        91,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-16",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        577,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-17",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-18",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-19",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        577,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-20",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-21",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-22",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        440,
                                                        180,
                                                        34,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "set 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-23",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": ["", "", ""],
                                                    "patching_rect": [
                                                        415,
                                                        203,
                                                        173,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "cycle 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-24",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        167,
                                                        451,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-25",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        94,
                                                        192,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-26",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        124,
                                                        194,
                                                        34,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "set 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-27",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        172,
                                                        101,
                                                        146,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-28",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        308,
                                                        299,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-29",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        238,
                                                        298,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-30",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        155,
                                                        298,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-31",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": ["", "", ""],
                                                    "patching_rect": [
                                                        94,
                                                        217,
                                                        162,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "cycle 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-32",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        249,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-33",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        62,
                                                        173,
                                                        49,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "Uzi 253"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-34",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        170,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-35",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        87,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-27",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-23",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-11", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-19",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-20",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-21",
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
                                                        "obj-15",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-14", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-14", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 2],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-19",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-20",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-17", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-21",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-18", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-19", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-19", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-15",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-20", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-15",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-21", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-23",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        449.5,
                                                        199,
                                                        424.5,
                                                        199
                                                    ],
                                                    "source": ["obj-22", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-16",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-17",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-18",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-31",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-25", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-31",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        133.5,
                                                        213,
                                                        103.5,
                                                        213
                                                    ],
                                                    "source": ["obj-26", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-1", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-27", 2]
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
                                                    "source": ["obj-27", 1]
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
                                                    "source": ["obj-27", 2]
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
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-29",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        308.5,
                                                        249,
                                                        245,
                                                        249
                                                    ],
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-30",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        308.5,
                                                        249,
                                                        162,
                                                        249
                                                    ],
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-9", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-27", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-28", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-29", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-30", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-32", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        86.5,
                                                        449,
                                                        176,
                                                        449
                                                    ],
                                                    "source": ["obj-33", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-25",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-33", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-33", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        71.5,
                                                        292,
                                                        372.5,
                                                        292
                                                    ],
                                                    "source": ["obj-33", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-34", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-35", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-4", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-8", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-26",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-33",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 1]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [676, 221, 58, 21],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p smooth"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-57",
                                    "maxclass": "button",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [519, 199, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-58",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [50, 40, 670, 561],
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
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        386,
                                                        337,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-2",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        431,
                                                        315,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        548,
                                                        291,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        356,
                                                        336,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        256,
                                                        299,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-6",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        170,
                                                        300,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-7",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        87,
                                                        300,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        363,
                                                        370,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack set 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        172,
                                                        129,
                                                        42,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-10",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        172,
                                                        76,
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
                                                        415,
                                                        102,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-12",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        240,
                                                        128,
                                                        42,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-13",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        395,
                                                        232,
                                                        170,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-14",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        310,
                                                        91,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-15",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        334,
                                                        91,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-16",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        577,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-17",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-18",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-19",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        577,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-20",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-21",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-22",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        440,
                                                        180,
                                                        34,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "set 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-23",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": ["", "", ""],
                                                    "patching_rect": [
                                                        415,
                                                        203,
                                                        173,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "cycle 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-24",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        167,
                                                        451,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-25",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        94,
                                                        192,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-26",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        124,
                                                        194,
                                                        34,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "set 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-27",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        172,
                                                        101,
                                                        146,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-28",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        308,
                                                        299,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-29",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        238,
                                                        298,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-30",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        155,
                                                        298,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-31",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": ["", "", ""],
                                                    "patching_rect": [
                                                        94,
                                                        217,
                                                        162,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "cycle 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-32",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        249,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-33",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        62,
                                                        173,
                                                        49,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "Uzi 253"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-34",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        170,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-35",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        87,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-27",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-23",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-11", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-19",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-20",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-21",
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
                                                        "obj-15",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-14", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-14", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 2],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-19",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-20",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-17", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-21",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-18", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-19", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-19", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-15",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-20", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-15",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-21", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-23",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        449.5,
                                                        199,
                                                        424.5,
                                                        199
                                                    ],
                                                    "source": ["obj-22", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-16",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-17",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-18",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-31",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-25", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-31",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        133.5,
                                                        213,
                                                        103.5,
                                                        213
                                                    ],
                                                    "source": ["obj-26", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-1", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-27", 2]
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
                                                    "source": ["obj-27", 1]
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
                                                    "source": ["obj-27", 2]
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
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-29",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        308.5,
                                                        249,
                                                        245,
                                                        249
                                                    ],
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-30",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        308.5,
                                                        249,
                                                        162,
                                                        249
                                                    ],
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-9", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-27", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-28", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-29", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-30", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-32", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        86.5,
                                                        449,
                                                        176,
                                                        449
                                                    ],
                                                    "source": ["obj-33", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-25",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-33", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-33", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        71.5,
                                                        292,
                                                        372.5,
                                                        292
                                                    ],
                                                    "source": ["obj-33", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-34", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-35", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-4", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-8", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-26",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-33",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 1]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [519, 221, 58, 21],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p smooth"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-59",
                                    "maxclass": "button",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [362, 199, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-60",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [50, 40, 670, 561],
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
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        386,
                                                        337,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-2",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        431,
                                                        315,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        548,
                                                        291,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        356,
                                                        336,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        256,
                                                        299,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-6",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        170,
                                                        300,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-7",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        87,
                                                        300,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        363,
                                                        370,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack set 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        172,
                                                        129,
                                                        42,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-10",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        172,
                                                        76,
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
                                                        415,
                                                        102,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-12",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        240,
                                                        128,
                                                        42,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-13",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        395,
                                                        232,
                                                        170,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-14",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        310,
                                                        91,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-15",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        334,
                                                        91,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-16",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        577,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-17",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-18",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-19",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        577,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-20",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-21",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-22",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        440,
                                                        180,
                                                        34,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "set 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-23",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": ["", "", ""],
                                                    "patching_rect": [
                                                        415,
                                                        203,
                                                        173,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "cycle 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-24",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        167,
                                                        451,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-25",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        94,
                                                        192,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-26",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        124,
                                                        194,
                                                        34,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "set 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-27",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        172,
                                                        101,
                                                        146,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-28",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        308,
                                                        299,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-29",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        238,
                                                        298,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-30",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        155,
                                                        298,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-31",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": ["", "", ""],
                                                    "patching_rect": [
                                                        94,
                                                        217,
                                                        162,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "cycle 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-32",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        249,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-33",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        62,
                                                        173,
                                                        49,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "Uzi 253"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-34",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        170,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-35",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        87,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-27",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-23",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-11", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-19",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-20",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-21",
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
                                                        "obj-15",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-14", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-14", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 2],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-19",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-20",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-17", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-21",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-18", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-19", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-19", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-15",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-20", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-15",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-21", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-23",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        449.5,
                                                        199,
                                                        424.5,
                                                        199
                                                    ],
                                                    "source": ["obj-22", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-16",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-17",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-18",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-31",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-25", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-31",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        133.5,
                                                        213,
                                                        103.5,
                                                        213
                                                    ],
                                                    "source": ["obj-26", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-1", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-27", 2]
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
                                                    "source": ["obj-27", 1]
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
                                                    "source": ["obj-27", 2]
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
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-29",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        308.5,
                                                        249,
                                                        245,
                                                        249
                                                    ],
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-30",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        308.5,
                                                        249,
                                                        162,
                                                        249
                                                    ],
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-9", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-27", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-28", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-29", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-30", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-32", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        86.5,
                                                        449,
                                                        176,
                                                        449
                                                    ],
                                                    "source": ["obj-33", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-25",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-33", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-33", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        71.5,
                                                        292,
                                                        372.5,
                                                        292
                                                    ],
                                                    "source": ["obj-33", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-34", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-35", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-4", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-8", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-26",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-33",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 1]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [362, 221, 58, 21],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p smooth"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-61",
                                    "maxclass": "button",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [205, 199, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-62",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patcher": {
                                        "fileversion": 1,
                                        "appversion": {
                                            "major": 7,
                                            "minor": 0,
                                            "revision": 0,
                                            "architecture": "x86",
                                            "modernui": 1
                                        },
                                        "rect": [50, 44, 670, 561],
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
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-1",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        386,
                                                        337,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-2",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        431,
                                                        315,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "id": "obj-3",
                                                    "maxclass": "button",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        548,
                                                        291,
                                                        24,
                                                        24
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-4",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        356,
                                                        336,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-5",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        256,
                                                        299,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-6",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        170,
                                                        300,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-7",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": [
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        87,
                                                        300,
                                                        28,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b i"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 3,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        363,
                                                        370,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack set 0 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-9",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        172,
                                                        129,
                                                        42,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-10",
                                                    "maxclass": "inlet",
                                                    "numinlets": 0,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        172,
                                                        76,
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
                                                        415,
                                                        102,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-12",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        240,
                                                        128,
                                                        42,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-13",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        395,
                                                        232,
                                                        170,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-14",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        310,
                                                        91,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-15",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        334,
                                                        91,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-16",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        577,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-17",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-18",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        265,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "/ 3."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-19",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        577,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-20",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        496,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-21",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["float"],
                                                    "patching_rect": [
                                                        415,
                                                        289,
                                                        41,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "float 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-22",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        440,
                                                        180,
                                                        34,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "set 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-23",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": ["", "", ""],
                                                    "patching_rect": [
                                                        415,
                                                        203,
                                                        173,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "cycle 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-24",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        167,
                                                        451,
                                                        15,
                                                        15
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-25",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": ["int"],
                                                    "patching_rect": [
                                                        94,
                                                        192,
                                                        27,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "+ 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-26",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        124,
                                                        194,
                                                        34,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "set 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-27",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "bang"
                                                    ],
                                                    "patching_rect": [
                                                        172,
                                                        101,
                                                        146,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "t b b b"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-28",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        308,
                                                        299,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-29",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        238,
                                                        298,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "2"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-30",
                                                    "maxclass": "message",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        155,
                                                        298,
                                                        18,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "1"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-31",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 3,
                                                    "outlettype": ["", "", ""],
                                                    "patching_rect": [
                                                        94,
                                                        217,
                                                        162,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "cycle 3"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-32",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        249,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-33",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 3,
                                                    "outlettype": [
                                                        "bang",
                                                        "bang",
                                                        "int"
                                                    ],
                                                    "patching_rect": [
                                                        62,
                                                        173,
                                                        49,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "Uzi 253"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-34",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        170,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 11.595187,
                                                    "id": "obj-35",
                                                    "maxclass": "newobj",
                                                    "numinlets": 2,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        87,
                                                        326,
                                                        73,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pack fetch 0"
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-1", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-27",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-23",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-11", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-12", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-19",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-20",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-13", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-21",
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
                                                        "obj-15",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-14", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-14", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 2],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-15", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-19",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-16", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-20",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-17", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-21",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-18", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-19", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-19", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-15",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-20", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-15",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-21", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-23",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        449.5,
                                                        199,
                                                        424.5,
                                                        199
                                                    ],
                                                    "source": ["obj-22", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-16",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-17",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-18",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-23", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-31",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-25", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-31",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        133.5,
                                                        213,
                                                        103.5,
                                                        213
                                                    ],
                                                    "source": ["obj-26", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-1", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-27", 2]
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
                                                    "source": ["obj-27", 1]
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
                                                    "source": ["obj-27", 2]
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
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-29",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        308.5,
                                                        249,
                                                        245,
                                                        249
                                                    ],
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-30",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        308.5,
                                                        249,
                                                        162,
                                                        249
                                                    ],
                                                    "source": ["obj-27", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-9", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-27", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-28", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-29", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-14",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-30", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-5", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-6", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-7", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-31", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-32", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        86.5,
                                                        449,
                                                        176,
                                                        449
                                                    ],
                                                    "source": ["obj-33", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-25",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-33", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-33", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "midpoints": [
                                                        71.5,
                                                        292,
                                                        372.5,
                                                        292
                                                    ],
                                                    "source": ["obj-33", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-34", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-35", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 1],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-4", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-32",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-34",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        1
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 1]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-35",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-7", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-24",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-8", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-13",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-26",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 2]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": [
                                                        "obj-33",
                                                        0
                                                    ],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-9", 1]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [205, 221, 58, 21],
                                    "saved_object_attributes": {
                                        "description": "",
                                        "digest": "",
                                        "fontsize": 10,
                                        "globalpatchername": "",
                                        "style": "",
                                        "tags": ""
                                    },
                                    "style": "",
                                    "text": "p smooth"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-63",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [362, 357, 80, 21],
                                    "style": "",
                                    "text": "jit.fill lookup 1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-65",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [133, 406, 151, 21],
                                    "style": "",
                                    "text": "jit.matrix lookup 4 char 256"
                                }
                            },
                            {
                                "box": {
                                    "bgcolor": [
                                        0.760784,
                                        0.760784,
                                        0.760784,
                                        1
                                    ],
                                    "candicane2": [
                                        0.145098,
                                        0.203922,
                                        0.356863,
                                        1
                                    ],
                                    "candicane3": [
                                        0.290196,
                                        0.411765,
                                        0.713726,
                                        1
                                    ],
                                    "candicane4": [
                                        0.439216,
                                        0.619608,
                                        0.070588,
                                        1
                                    ],
                                    "candicane5": [
                                        0.584314,
                                        0.827451,
                                        0.431373,
                                        1
                                    ],
                                    "candicane6": [
                                        0.733333,
                                        0.035294,
                                        0.788235,
                                        1
                                    ],
                                    "candicane7": [
                                        0.878431,
                                        0.243137,
                                        0.145098,
                                        1
                                    ],
                                    "candicane8": [
                                        0.027451,
                                        0.447059,
                                        0.501961,
                                        1
                                    ],
                                    "compatibility": 1,
                                    "contdata": 1,
                                    "id": "obj-66",
                                    "maxclass": "multislider",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "parameter_enable": 0,
                                    "patching_rect": [205, 250, 154, 103],
                                    "peakcolor": [
                                        0.498039,
                                        0.498039,
                                        0.498039,
                                        1
                                    ],
                                    "setminmax": [0, 255],
                                    "setstyle": 1,
                                    "settype": 0,
                                    "size": 256,
                                    "slidercolor": [
                                        0.364706,
                                        0.364706,
                                        0.364706,
                                        1
                                    ],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "bgcolor": [
                                        0.588235,
                                        0.588235,
                                        0.980392,
                                        1
                                    ],
                                    "candicane2": [
                                        0.145098,
                                        0.203922,
                                        0.356863,
                                        1
                                    ],
                                    "candicane3": [
                                        0.290196,
                                        0.411765,
                                        0.713726,
                                        1
                                    ],
                                    "candicane4": [
                                        0.439216,
                                        0.619608,
                                        0.070588,
                                        1
                                    ],
                                    "candicane5": [
                                        0.584314,
                                        0.827451,
                                        0.431373,
                                        1
                                    ],
                                    "candicane6": [
                                        0.733333,
                                        0.035294,
                                        0.788235,
                                        1
                                    ],
                                    "candicane7": [
                                        0.878431,
                                        0.243137,
                                        0.145098,
                                        1
                                    ],
                                    "candicane8": [
                                        0.027451,
                                        0.447059,
                                        0.501961,
                                        1
                                    ],
                                    "compatibility": 1,
                                    "contdata": 1,
                                    "id": "obj-67",
                                    "maxclass": "multislider",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "parameter_enable": 0,
                                    "patching_rect": [676, 250, 154, 103],
                                    "peakcolor": [
                                        0.498039,
                                        0.498039,
                                        0.498039,
                                        1
                                    ],
                                    "setminmax": [0, 255],
                                    "setstyle": 1,
                                    "settype": 0,
                                    "size": 256,
                                    "slidercolor": [
                                        0.196078,
                                        0.196078,
                                        0.588235,
                                        1
                                    ],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "bgcolor": [
                                        0.588235,
                                        0.980392,
                                        0.588235,
                                        1
                                    ],
                                    "candicane2": [
                                        0.145098,
                                        0.203922,
                                        0.356863,
                                        1
                                    ],
                                    "candicane3": [
                                        0.290196,
                                        0.411765,
                                        0.713726,
                                        1
                                    ],
                                    "candicane4": [
                                        0.439216,
                                        0.619608,
                                        0.070588,
                                        1
                                    ],
                                    "candicane5": [
                                        0.584314,
                                        0.827451,
                                        0.431373,
                                        1
                                    ],
                                    "candicane6": [
                                        0.733333,
                                        0.035294,
                                        0.788235,
                                        1
                                    ],
                                    "candicane7": [
                                        0.878431,
                                        0.243137,
                                        0.145098,
                                        1
                                    ],
                                    "candicane8": [
                                        0.027451,
                                        0.447059,
                                        0.501961,
                                        1
                                    ],
                                    "compatibility": 1,
                                    "contdata": 1,
                                    "id": "obj-68",
                                    "maxclass": "multislider",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "parameter_enable": 0,
                                    "patching_rect": [519, 250, 154, 103],
                                    "peakcolor": [
                                        0.498039,
                                        0.498039,
                                        0.498039,
                                        1
                                    ],
                                    "setminmax": [0, 255],
                                    "setstyle": 1,
                                    "settype": 0,
                                    "size": 256,
                                    "slidercolor": [
                                        0.196078,
                                        0.588235,
                                        0.196078,
                                        1
                                    ],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "bgcolor": [
                                        0.980392,
                                        0.588235,
                                        0.588235,
                                        1
                                    ],
                                    "candicane2": [
                                        0.145098,
                                        0.203922,
                                        0.356863,
                                        1
                                    ],
                                    "candicane3": [
                                        0.290196,
                                        0.411765,
                                        0.713726,
                                        1
                                    ],
                                    "candicane4": [
                                        0.439216,
                                        0.619608,
                                        0.070588,
                                        1
                                    ],
                                    "candicane5": [
                                        0.584314,
                                        0.827451,
                                        0.431373,
                                        1
                                    ],
                                    "candicane6": [
                                        0.733333,
                                        0.035294,
                                        0.788235,
                                        1
                                    ],
                                    "candicane7": [
                                        0.878431,
                                        0.243137,
                                        0.145098,
                                        1
                                    ],
                                    "candicane8": [
                                        0.027451,
                                        0.447059,
                                        0.501961,
                                        1
                                    ],
                                    "compatibility": 1,
                                    "contdata": 1,
                                    "id": "obj-69",
                                    "maxclass": "multislider",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "parameter_enable": 0,
                                    "patching_rect": [362, 250, 154, 103],
                                    "peakcolor": [
                                        0.498039,
                                        0.498039,
                                        0.498039,
                                        1
                                    ],
                                    "setminmax": [0, 255],
                                    "setstyle": 1,
                                    "settype": 0,
                                    "size": 256,
                                    "slidercolor": [
                                        0.588235,
                                        0.196078,
                                        0.196078,
                                        1
                                    ],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-71",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [75, 452, 33, 21],
                                    "style": "",
                                    "text": "print"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-72",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [27, 431, 67, 21],
                                    "style": "",
                                    "text": "jit.charmap"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.595187,
                                    "id": "obj-79",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [691, 145, 118, 19],
                                    "style": "",
                                    "text": "a few math functions"
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["jit.charmap"],
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
                                    "border": 1,
                                    "id": "obj-49",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "onscreen": 0,
                                    "outlettype": ["", ""],
                                    "patching_rect": [559, 504, 256, 32]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "border": 1,
                                    "id": "obj-50",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "onscreen": 0,
                                    "outlettype": ["", ""],
                                    "patching_rect": [559, 464, 256, 32]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "border": 1,
                                    "id": "obj-51",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "onscreen": 0,
                                    "outlettype": ["", ""],
                                    "patching_rect": [559, 425, 256, 32]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "border": 1,
                                    "id": "obj-52",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "onscreen": 0,
                                    "outlettype": ["", ""],
                                    "patching_rect": [559, 387, 256, 32]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "border": 1,
                                    "id": "obj-64",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "onscreen": 0,
                                    "outlettype": ["", ""],
                                    "patching_rect": [294, 386, 256, 32]
                                }
                            },
                            {
                                "box": {
                                    "background": 1,
                                    "id": "obj-70",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [27, 476, 320, 240]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-65", 0],
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
                                    "source": ["obj-23", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-66", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-24", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-67", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-24", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-68", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-24", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-69", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-24", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-55", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [474.5, 195, 685.5, 195],
                                    "source": ["obj-25", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-57", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [474.5, 195, 528.5, 195],
                                    "source": ["obj-25", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-59", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [474.5, 195, 371.5, 195],
                                    "source": ["obj-25", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-61", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [474.5, 195, 214.5, 195],
                                    "source": ["obj-25", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-49", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-26", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-50", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-26", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-51", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-26", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-52", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-26", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-64", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-26", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-29", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-27", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.156863, 0.8, 0.54902, 1],
                                    "destination": ["obj-32", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [499.5, 195, 744.5, 195],
                                    "source": ["obj-28", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.156863, 0.8, 0.54902, 1],
                                    "destination": ["obj-35", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [499.5, 195, 589.5, 195],
                                    "source": ["obj-28", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.156863, 0.8, 0.54902, 1],
                                    "destination": ["obj-38", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [499.5, 195, 430.5, 195],
                                    "source": ["obj-28", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.156863, 0.8, 0.54902, 1],
                                    "destination": ["obj-41", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [499.5, 195, 273.5, 195],
                                    "source": ["obj-28", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.611765, 0.701961, 1, 1],
                                    "destination": ["obj-31", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [551.5, 195, 790.5, 195],
                                    "source": ["obj-29", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.611765, 0.701961, 1, 1],
                                    "destination": ["obj-34", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [551.5, 195, 635.5, 195],
                                    "source": ["obj-29", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.611765, 0.701961, 1, 1],
                                    "destination": ["obj-37", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [551.5, 195, 476.5, 195],
                                    "source": ["obj-29", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.611765, 0.701961, 1, 1],
                                    "destination": ["obj-40", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [551.5, 195, 319.5, 195],
                                    "source": ["obj-29", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-27", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-3", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-8", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-3", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-26", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-30", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-27", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-30", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-33", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-31", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-33", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-32", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-67", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [744.5, 244, 685.5, 244],
                                    "source": ["obj-33", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-36", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-34", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-36", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-35", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-68", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [589.5, 245, 528.5, 245],
                                    "source": ["obj-36", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-39", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-37", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-39", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-38", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-69", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [430.5, 245, 371.5, 245],
                                    "source": ["obj-39", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-72", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-4", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-42", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-40", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-42", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-41", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-66", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [273.5, 244, 214.5, 244],
                                    "source": ["obj-42", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-22", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [528.5, 381, 142.5, 381],
                                    "source": ["obj-43", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-22", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [685.5, 381, 142.5, 381],
                                    "source": ["obj-44", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-22", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [214.5, 381, 142.5, 381],
                                    "source": ["obj-45", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.6, 1, 1],
                                    "destination": ["obj-49", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        418.5,
                                        591,
                                        551,
                                        591,
                                        551,
                                        501,
                                        568.5,
                                        501
                                    ],
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 0.890196, 0.090196, 1],
                                    "destination": ["obj-50", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        418.5,
                                        558,
                                        537,
                                        558,
                                        537,
                                        459,
                                        568.5,
                                        459
                                    ],
                                    "source": ["obj-47", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.4, 0.6, 1],
                                    "destination": ["obj-51", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        417.5,
                                        527,
                                        548,
                                        527,
                                        548,
                                        425,
                                        568.5,
                                        425
                                    ],
                                    "source": ["obj-48", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 1, 1, 1],
                                    "destination": ["obj-52", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        417.5,
                                        496,
                                        556,
                                        496,
                                        556,
                                        382,
                                        568.5,
                                        382
                                    ],
                                    "source": ["obj-53", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.6, 1, 1],
                                    "destination": ["obj-46", 3],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [455, 564, 455.5, 564],
                                    "source": ["obj-54", 3]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.6, 1, 1],
                                    "destination": ["obj-46", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [455, 564, 418.5, 564],
                                    "source": ["obj-54", 3]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 0.890196, 0.090196, 1],
                                    "destination": ["obj-47", 2],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [442.5, 535, 443.166656, 535],
                                    "source": ["obj-54", 2]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 0.890196, 0.090196, 1],
                                    "destination": ["obj-47", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [442.5, 535, 418.5, 535],
                                    "source": ["obj-54", 2]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.4, 0.6, 1],
                                    "destination": ["obj-48", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [430, 502, 429.833344, 502],
                                    "source": ["obj-54", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [0.6, 0.4, 0.6, 1],
                                    "destination": ["obj-48", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [430, 502, 417.5, 502],
                                    "source": ["obj-54", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 1, 1, 1],
                                    "destination": ["obj-53", 3],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [417.5, 464, 454.5, 464],
                                    "source": ["obj-54", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 1, 1, 1],
                                    "destination": ["obj-53", 2],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [417.5, 464, 442.166656, 464],
                                    "source": ["obj-54", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 1, 1, 1],
                                    "destination": ["obj-53", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [417.5, 464, 429.833344, 464],
                                    "source": ["obj-54", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "color": [1, 1, 1, 1],
                                    "destination": ["obj-53", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [417.5, 464, 417.5, 464],
                                    "source": ["obj-54", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-56", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-55", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-67", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-56", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-58", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-57", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-68", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-58", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-60", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-59", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-69", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-60", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-62", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-61", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-66", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-62", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-22", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [371.5, 381, 142.5, 381],
                                    "source": ["obj-63", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-54", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        142.5,
                                        433,
                                        289,
                                        433,
                                        289,
                                        433,
                                        417.5,
                                        433
                                    ],
                                    "source": ["obj-65", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-64", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        142.5,
                                        433,
                                        290,
                                        433,
                                        290,
                                        385,
                                        303.5,
                                        385
                                    ],
                                    "source": ["obj-65", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-72", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [142.5, 428, 84.5, 428],
                                    "source": ["obj-65", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-45", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [214.5, 351, 214.5, 351],
                                    "source": ["obj-66", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-62", 1],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-66", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-44", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [685.5, 351, 685.5, 351],
                                    "source": ["obj-67", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-56", 1],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-67", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-43", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [528.5, 351, 528.5, 351],
                                    "source": ["obj-68", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-58", 1],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-68", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-60", 1],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-69", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-63", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [371.5, 351, 371.5, 351],
                                    "source": ["obj-69", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-17", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [36.5, 726, 36.5, 726],
                                    "source": ["obj-70", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-70", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-72", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-71", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-72", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-28", 0],
                                    "disabled": 0,
                                    "hidden": 1,
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
                    "jsarguments": ["jit.charmap"],
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
                        "rect": [0, 26, 871, 775],
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
            "obj-2::obj-4::obj-4::obj-21": ["number", "number", 0],
            "obj-2::obj-4::obj-4::obj-20": ["live.tab[1]", "live.tab[1]", 0],
            "obj-2::obj-4::obj-4::obj-18": ["number[1]", "number[1]", 0]
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