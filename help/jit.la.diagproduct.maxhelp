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
        "rect": [57, 90, 642, 487],
        "bglocked": 0,
        "openinpresentation": 0,
        "default_fontsize": 12,
        "default_fontface": 0,
        "default_fontname": "Verdana",
        "gridonopen": 0,
        "gridsize": [10, 10],
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
                    "fontname": "Verdana",
                    "fontsize": 12,
                    "id": "obj-7",
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
                        "rect": [0, 26, 642, 461],
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
                                    "fontsize": 11.934731,
                                    "id": "obj-1",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [35, 134, 52, 18],
                                    "style": "",
                                    "text": "plane -1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "id": "obj-2",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [86, 103, 58, 20],
                                    "style": "",
                                    "text": "loadbang"
                                }
                            },
                            {
                                "box": {
                                    "cols": 2,
                                    "colwidth": 78,
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "hscroll": 0,
                                    "id": "obj-3",
                                    "maxclass": "jit.cellblock",
                                    "numinlets": 2,
                                    "numoutlets": 4,
                                    "outlettype": ["list", "", "", ""],
                                    "patching_rect": [115, 160, 158, 36],
                                    "precision": 4,
                                    "rowheight": 17,
                                    "rows": 2,
                                    "selmode": 5,
                                    "vscroll": 0
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-5",
                                    "maxclass": "button",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [86, 133, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "id": "obj-6",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [63, 205, 23, 20],
                                    "style": "",
                                    "text": "t b"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "id": "obj-7",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [86, 232, 123, 20],
                                    "style": "",
                                    "text": "jit.matrix 2 float64 2 2"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "format": 6,
                                    "id": "obj-8",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [148, 327, 50, 20],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "format": 6,
                                    "id": "obj-9",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [86, 327, 50, 20],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "id": "obj-10",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["float", "float"],
                                    "patching_rect": [86, 294, 81, 20],
                                    "style": "",
                                    "text": "unpack 0. 0."
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "id": "obj-11",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [86, 263, 95, 20],
                                    "style": "",
                                    "text": "jit.la.diagproduct"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "id": "obj-12",
                                    "linecount": 2,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [86, 360, 300, 33],
                                    "style": "",
                                    "text": "when using two planes, the entries are assumed to be complex numbers. plane 0 is real. plane 1 is imaginary."
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpname.js",
                                    "id": "obj-4",
                                    "ignoreclick": 1,
                                    "jsarguments": ["jit.la.diagproduct"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [
                                        10,
                                        10,
                                        354.546875,
                                        53.625
                                    ]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-3", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [44.5, 157, 124.5, 157],
                                    "source": ["obj-1", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-8", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-10", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-9", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-10", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-10", 0],
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
                                    "midpoints": [95.5, 127, 44.5, 127],
                                    "source": ["obj-2", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-2", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [124.5, 198, 72.5, 198],
                                    "source": ["obj-3", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-7", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-5", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-7", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [72.5, 227, 95.5, 227],
                                    "source": ["obj-6", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-11", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-7", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-3", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        95.5,
                                        258,
                                        276,
                                        258,
                                        276,
                                        130,
                                        124.5,
                                        130
                                    ],
                                    "source": ["obj-7", 0]
                                }
                            }
                        ]
                    },
                    "patching_rect": [10, 124, 136, 21],
                    "saved_object_attributes": {
                        "description": "",
                        "digest": "",
                        "fontsize": 13,
                        "globalpatchername": "",
                        "style": "",
                        "tags": ""
                    },
                    "style": "",
                    "text": "p complex+float64",
                    "varname": "basic_tab[1]"
                }
            },
            {
                "box": {
                    "fontname": "Verdana",
                    "fontsize": 12,
                    "id": "obj-1",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "patching_rect": [220, 120, 198, 21],
                    "saved_object_attributes": {
                        "filename": "helpstarter",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter jit.la.diagproduct"
                }
            },
            {
                "box": {
                    "fontname": "Verdana",
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
                        "rect": [57, 116, 642, 461],
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
                                    "fontsize": 11.934731,
                                    "id": "obj-24",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [255, 311, 325, 20],
                                    "style": "",
                                    "text": "supports: float32, float64, 1 or 2 planes (1=real, 2=complex)"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "id": "obj-5",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [65, 190, 58, 22],
                                    "style": "",
                                    "text": "loadbang"
                                }
                            },
                            {
                                "box": {
                                    "cols": 3,
                                    "colwidth": 45,
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "hscroll": 0,
                                    "id": "obj-6",
                                    "maxclass": "jit.cellblock",
                                    "numinlets": 2,
                                    "numoutlets": 4,
                                    "outlettype": ["list", "", "", ""],
                                    "patching_rect": [94, 226, 136, 52],
                                    "precision": 4,
                                    "rowheight": 17,
                                    "rows": 3,
                                    "selmode": 5,
                                    "vscroll": 0
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-7",
                                    "maxclass": "button",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [65, 214, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "id": "obj-8",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["bang"],
                                    "patching_rect": [42, 285, 23, 22],
                                    "style": "",
                                    "text": "t b"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "id": "obj-9",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [65, 311, 123, 22],
                                    "style": "",
                                    "text": "jit.matrix 1 float32 3 3"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "format": 6,
                                    "id": "obj-21",
                                    "maxclass": "flonum",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [65, 396, 50, 22],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 11.934731,
                                    "id": "obj-25",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [65, 349, 95, 22],
                                    "style": "",
                                    "text": "jit.la.diagproduct"
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["jit.la.diagproduct"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [10, 10, 570, 160]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-21", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-25", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-7", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-5", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-8", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [103.5, 281, 51.5, 281],
                                    "source": ["obj-6", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-9", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-7", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-9", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [51.5, 308, 74.5, 308],
                                    "source": ["obj-8", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-25", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-9", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [
                                        74.5,
                                        336,
                                        234,
                                        336,
                                        234,
                                        219,
                                        103.5,
                                        219
                                    ],
                                    "source": ["obj-9", 0]
                                }
                            }
                        ]
                    },
                    "patching_rect": [10, 85, 52, 21],
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
                    "jsarguments": ["jit.la.diagproduct"],
                    "maxclass": "jsui",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "parameter_enable": 0,
                    "patching_rect": [10, 10, 354.546875, 53.625]
                }
            },
            {
                "box": {
                    "fontname": "Verdana",
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
                        "rect": [0, 26, 642, 461],
                        "bglocked": 0,
                        "openinpresentation": 0,
                        "default_fontsize": 12,
                        "default_fontface": 0,
                        "default_fontname": "Verdana",
                        "gridonopen": 0,
                        "gridsize": [10, 10],
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
                    "patching_rect": [205, 205, 50, 21],
                    "saved_object_attributes": {
                        "description": "",
                        "digest": "",
                        "fontname": "Verdana",
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