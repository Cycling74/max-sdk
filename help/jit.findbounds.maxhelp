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
        "rect": [34, 79, 928, 579],
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
                    "patching_rect": [206, 142, 169, 20],
                    "saved_object_attributes": {
                        "filename": "helpstarter.js",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter.js jit.findbounds"
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
                        "rect": [34, 105, 928, 553],
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
                                    "id": "obj-15",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [427.5, 488, 73, 21],
                                    "style": "helpfile_label",
                                    "text": "boundmax"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-14",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [307, 488, 69, 21],
                                    "style": "helpfile_label",
                                    "text": "boundmin"
                                }
                            },
                            {
                                "box": {
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "embed": 1,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-13",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [-14, -14],
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
                                        "rect": [381, 304, 230, 26],
                                        "bgcolor": [1, 1, 1, 0],
                                        "bglocked": 0,
                                        "openinpresentation": 1,
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
                                                    "patching_rect": [
                                                        82,
                                                        38,
                                                        32.5,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "0.5"
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
                                                    "patching_rect": [
                                                        24,
                                                        38,
                                                        32.5,
                                                        18
                                                    ],
                                                    "style": "",
                                                    "text": "1."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "id": "obj-10",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": ["bang"],
                                                    "patching_rect": [
                                                        24,
                                                        12,
                                                        61,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "loadbang"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-9",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        24,
                                                        178,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 4,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        24,
                                                        131,
                                                        59.5,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pak f f f f"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "format": 6,
                                                    "id": "obj-7",
                                                    "maxclass": "flonum",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", "bang"],
                                                    "parameter_enable": 0,
                                                    "patching_rect": [
                                                        199,
                                                        62,
                                                        50,
                                                        22
                                                    ],
                                                    "presentation": 1,
                                                    "presentation_rect": [
                                                        193,
                                                        17,
                                                        50,
                                                        22
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "format": 6,
                                                    "id": "obj-6",
                                                    "maxclass": "flonum",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", "bang"],
                                                    "parameter_enable": 0,
                                                    "patching_rect": [
                                                        141,
                                                        62,
                                                        50,
                                                        22
                                                    ],
                                                    "presentation": 1,
                                                    "presentation_rect": [
                                                        135,
                                                        17,
                                                        50,
                                                        22
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "format": 6,
                                                    "id": "obj-4",
                                                    "maxclass": "flonum",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", "bang"],
                                                    "parameter_enable": 0,
                                                    "patching_rect": [
                                                        82,
                                                        62,
                                                        50,
                                                        22
                                                    ],
                                                    "presentation": 1,
                                                    "presentation_rect": [
                                                        76,
                                                        17,
                                                        50,
                                                        22
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "format": 6,
                                                    "id": "obj-2",
                                                    "maxclass": "flonum",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", "bang"],
                                                    "parameter_enable": 0,
                                                    "patching_rect": [
                                                        24,
                                                        62,
                                                        50,
                                                        22
                                                    ],
                                                    "presentation": 1,
                                                    "presentation_rect": [
                                                        18,
                                                        17,
                                                        50,
                                                        22
                                                    ],
                                                    "style": ""
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-3", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
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
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-3", 0]
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
                                                    "destination": ["obj-4", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-5", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 2],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 3],
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
                                                    "source": ["obj-8", 0]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [347, 199, 230, 26],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "embed": 1,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-12",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [-14, -14],
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
                                        "rect": [381, 387, 230, 26],
                                        "bgcolor": [1, 1, 1, 0],
                                        "bglocked": 0,
                                        "openinpresentation": 1,
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
                                        "boxes": [
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "id": "obj-10",
                                                    "maxclass": "newobj",
                                                    "numinlets": 1,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        24,
                                                        21,
                                                        77,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "loadmess 0."
                                                }
                                            },
                                            {
                                                "box": {
                                                    "comment": "",
                                                    "id": "obj-9",
                                                    "maxclass": "outlet",
                                                    "numinlets": 1,
                                                    "numoutlets": 0,
                                                    "patching_rect": [
                                                        24,
                                                        178,
                                                        25,
                                                        25
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "id": "obj-8",
                                                    "maxclass": "newobj",
                                                    "numinlets": 4,
                                                    "numoutlets": 1,
                                                    "outlettype": [""],
                                                    "patching_rect": [
                                                        24,
                                                        131,
                                                        59.5,
                                                        20
                                                    ],
                                                    "style": "",
                                                    "text": "pak f f f f"
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "format": 6,
                                                    "id": "obj-7",
                                                    "maxclass": "flonum",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", "bang"],
                                                    "parameter_enable": 0,
                                                    "patching_rect": [
                                                        199,
                                                        62,
                                                        50,
                                                        22
                                                    ],
                                                    "presentation": 1,
                                                    "presentation_rect": [
                                                        193,
                                                        17,
                                                        50,
                                                        22
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "format": 6,
                                                    "id": "obj-6",
                                                    "maxclass": "flonum",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", "bang"],
                                                    "parameter_enable": 0,
                                                    "patching_rect": [
                                                        141,
                                                        62,
                                                        50,
                                                        22
                                                    ],
                                                    "presentation": 1,
                                                    "presentation_rect": [
                                                        135,
                                                        17,
                                                        50,
                                                        22
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "format": 6,
                                                    "id": "obj-4",
                                                    "maxclass": "flonum",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", "bang"],
                                                    "parameter_enable": 0,
                                                    "patching_rect": [
                                                        82,
                                                        62,
                                                        50,
                                                        22
                                                    ],
                                                    "presentation": 1,
                                                    "presentation_rect": [
                                                        76,
                                                        17,
                                                        50,
                                                        22
                                                    ],
                                                    "style": ""
                                                }
                                            },
                                            {
                                                "box": {
                                                    "fontname": "Arial",
                                                    "fontsize": 12,
                                                    "format": 6,
                                                    "id": "obj-2",
                                                    "maxclass": "flonum",
                                                    "numinlets": 1,
                                                    "numoutlets": 2,
                                                    "outlettype": ["", "bang"],
                                                    "parameter_enable": 0,
                                                    "patching_rect": [
                                                        24,
                                                        62,
                                                        50,
                                                        22
                                                    ],
                                                    "presentation": 1,
                                                    "presentation_rect": [
                                                        18,
                                                        17,
                                                        50,
                                                        22
                                                    ],
                                                    "style": ""
                                                }
                                            }
                                        ],
                                        "lines": [
                                            {
                                                "patchline": {
                                                    "destination": ["obj-2", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-10", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 0],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-2", 0]
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
                                                    "destination": ["obj-8", 2],
                                                    "disabled": 0,
                                                    "hidden": 0,
                                                    "source": ["obj-6", 0]
                                                }
                                            },
                                            {
                                                "patchline": {
                                                    "destination": ["obj-8", 3],
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
                                                    "source": ["obj-8", 0]
                                                }
                                            }
                                        ]
                                    },
                                    "patching_rect": [347, 282, 230, 26],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-10",
                                    "maxclass": "jit.fpsgui",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [659, 480, 55, 36],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-11",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [659, 355, 160, 120],
                                    "presentation_rect": [60, 60, 160, 120]
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-7",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [682, 282, 214, 23],
                                    "style": "",
                                    "text": "srcdimend $1 $2, dstdimend $1 $2"
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
                                    "patching_rect": [659, 229, 221, 23],
                                    "style": "",
                                    "text": "srcdimstart $1 $2, dstdimstart $1 $2"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-18",
                                    "maxclass": "newobj",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [605, 282, 63, 23],
                                    "style": "",
                                    "text": "r bounds"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-9",
                                    "maxclass": "newobj",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [682, 255, 37, 23],
                                    "style": "",
                                    "text": "r mx"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-21",
                                    "maxclass": "newobj",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [659, 199, 38, 23],
                                    "style": "",
                                    "text": "r mn"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-34",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [659, 320, 237, 23],
                                    "style": "",
                                    "text": "jit.matrix @usesrcdim 1 @usedstdim 1"
                                }
                            },
                            {
                                "box": {
                                    "attr": "min",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-6",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [347, 311, 243, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "max",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-4",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [347, 234, 243, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-1",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [484, 436, 39, 23],
                                    "style": "",
                                    "text": "s mx"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-23",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [362, 436, 40, 23],
                                    "style": "",
                                    "text": "s mn"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-40",
                                    "maxclass": "number",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [468, 467, 50, 23],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-41",
                                    "maxclass": "number",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [413, 467, 50, 23],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-42",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["int", "int"],
                                    "patching_rect": [413, 436, 74, 23],
                                    "style": "",
                                    "text": "unpack 0 0"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-45",
                                    "maxclass": "number",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [345, 467, 50, 23],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-46",
                                    "maxclass": "number",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [290, 467, 50, 23],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-47",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["int", "int"],
                                    "patching_rect": [290, 436, 74, 23],
                                    "style": "",
                                    "text": "unpack 0 0"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-49",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [536, 436, 37, 23],
                                    "style": "",
                                    "text": "print"
                                }
                            },
                            {
                                "box": {
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-22",
                                    "maxclass": "jit.fpsgui",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [10, 480, 55, 36],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-20",
                                    "maxclass": "jit.pwindow",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "patching_rect": [10, 355, 160, 120],
                                    "presentation_rect": [15, 15, 160, 120]
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-19",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [221, 331, 67, 23],
                                    "style": "",
                                    "text": "s bounds"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-27",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", "clear"],
                                    "patching_rect": [10, 303, 230, 23],
                                    "style": "",
                                    "text": "t l l clear"
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
                                    "patching_rect": [10, 174, 230, 125],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-5",
                                    "maxclass": "newobj",
                                    "numinlets": 1,
                                    "numoutlets": 3,
                                    "outlettype": ["", "", ""],
                                    "patching_rect": [290, 390, 265, 23],
                                    "style": "",
                                    "text": "jit.findbounds"
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["jit.findbounds"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [10, 10, 643, 157]
                                }
                            }
                        ],
                        "lines": [
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
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-12", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-4", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-13", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-34", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [614.5, 315, 668.5, 315],
                                    "source": ["obj-18", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-22", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-20", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-8", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-21", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-19", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-27", 2]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-19", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-27", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-20", 0],
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
                                    "source": ["obj-27", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-27", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-3", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-11", 0],
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
                                    "source": ["obj-4", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-40", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-42", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-41", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-42", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-45", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-47", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-46", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-47", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-1", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-5", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-23", 0],
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
                                    "source": ["obj-5", 1]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-47", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-5", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-49", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-5", 2]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-5", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-6", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-34", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "midpoints": [691.5, 316, 668.5, 316],
                                    "source": ["obj-7", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-34", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-8", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-7", 0],
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
                    "jsarguments": ["jit.findbounds"],
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
                        "rect": [0, 26, 928, 553],
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
            "obj-2::obj-3::obj-4::obj-21": ["number", "number", 0],
            "obj-2::obj-3::obj-4::obj-20": ["live.tab[1]", "live.tab[1]", 0],
            "obj-2::obj-3::obj-4::obj-18": ["number[1]", "number[1]", 0]
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