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
        "rect": [41, 83, 791, 557],
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
                    "id": "obj-6",
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
                        "rect": [0, 26, 791, 531],
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
                                    "border": 0,
                                    "filename": "helpname.js",
                                    "id": "obj-4",
                                    "ignoreclick": 1,
                                    "jsarguments": ["jit.eclipse"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [
                                        10,
                                        10,
                                        202.414062,
                                        53.625
                                    ]
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-16",
                                    "maxclass": "toggle",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [721.200012, 265, 24, 24],
                                    "style": ""
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
                                    "patching_rect": [721.200012, 295, 42, 23],
                                    "style": "",
                                    "text": "op $1"
                                }
                            },
                            {
                                "box": {
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
                                    "id": "obj-38",
                                    "maxclass": "multislider",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "parameter_enable": 0,
                                    "patching_rect": [536, 245, 37, 40],
                                    "peakcolor": [
                                        0.498039,
                                        0.498039,
                                        0.498039,
                                        1
                                    ],
                                    "setminmax": [-1.01, 1.01],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-39",
                                    "maxclass": "toggle",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [667.099976, 265, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-40",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [667.099976, 295, 44, 23],
                                    "style": "",
                                    "text": "inv $1"
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-41",
                                    "maxclass": "toggle",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [614, 265, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-42",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [614, 295, 45, 23],
                                    "style": "",
                                    "text": "tint $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-43",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [536, 295, 64, 23],
                                    "style": "",
                                    "text": "thresh $1"
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-45",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [498, 130, 177, 25],
                                    "style": "",
                                    "text": "try these yummy presets."
                                }
                            },
                            {
                                "box": {
                                    "bubblesize": 10,
                                    "fontsize": 12.754706,
                                    "id": "obj-46",
                                    "maxclass": "preset",
                                    "numinlets": 1,
                                    "numoutlets": 4,
                                    "outlettype": [
                                        "preset",
                                        "int",
                                        "preset",
                                        "int"
                                    ],
                                    "patching_rect": [386, 132, 105, 21],
                                    "preset_data": [
                                        {
                                            "number": 1,
                                            "data": [
                                                5,
                                                "obj-16",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-39",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-41",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-38",
                                                "multislider",
                                                "list",
                                                -1.01,
                                                5,
                                                "obj-49",
                                                "number",
                                                "int",
                                                16,
                                                5,
                                                "obj-50",
                                                "number",
                                                "int",
                                                16,
                                                5,
                                                "obj-54",
                                                "multislider",
                                                "list",
                                                -0.5,
                                                5,
                                                "obj-56",
                                                "multislider",
                                                "list",
                                                -0.5,
                                                5,
                                                "obj-58",
                                                "multislider",
                                                "list",
                                                -0.5,
                                                5,
                                                "obj-48",
                                                "number",
                                                "int",
                                                0
                                            ]
                                        },
                                        {
                                            "number": 2,
                                            "data": [
                                                5,
                                                "obj-16",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-39",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-41",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-38",
                                                "multislider",
                                                "list",
                                                0.526316,
                                                5,
                                                "obj-49",
                                                "number",
                                                "int",
                                                16,
                                                5,
                                                "obj-50",
                                                "number",
                                                "int",
                                                16,
                                                5,
                                                "obj-54",
                                                "multislider",
                                                "list",
                                                -0.5,
                                                5,
                                                "obj-56",
                                                "multislider",
                                                "list",
                                                -0.5,
                                                5,
                                                "obj-58",
                                                "multislider",
                                                "list",
                                                -0.5,
                                                5,
                                                "obj-48",
                                                "number",
                                                "int",
                                                0
                                            ]
                                        },
                                        {
                                            "number": 3,
                                            "data": [
                                                5,
                                                "obj-16",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-39",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-41",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-38",
                                                "multislider",
                                                "list",
                                                -0.578947,
                                                5,
                                                "obj-49",
                                                "number",
                                                "int",
                                                5,
                                                5,
                                                "obj-50",
                                                "number",
                                                "int",
                                                1,
                                                5,
                                                "obj-54",
                                                "multislider",
                                                "list",
                                                -0.105263,
                                                5,
                                                "obj-56",
                                                "multislider",
                                                "list",
                                                -0.894737,
                                                5,
                                                "obj-58",
                                                "multislider",
                                                "list",
                                                0.131579,
                                                5,
                                                "obj-48",
                                                "number",
                                                "int",
                                                0
                                            ]
                                        },
                                        {
                                            "number": 4,
                                            "data": [
                                                5,
                                                "obj-16",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-39",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-41",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-38",
                                                "multislider",
                                                "list",
                                                -0.421053,
                                                5,
                                                "obj-49",
                                                "number",
                                                "int",
                                                5,
                                                5,
                                                "obj-50",
                                                "number",
                                                "int",
                                                11,
                                                5,
                                                "obj-54",
                                                "multislider",
                                                "list",
                                                -0.105263,
                                                5,
                                                "obj-56",
                                                "multislider",
                                                "list",
                                                -0.105263,
                                                5,
                                                "obj-58",
                                                "multislider",
                                                "list",
                                                -1.131579,
                                                5,
                                                "obj-48",
                                                "number",
                                                "int",
                                                0
                                            ]
                                        },
                                        {
                                            "number": 5,
                                            "data": [
                                                5,
                                                "obj-16",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-39",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-41",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-38",
                                                "multislider",
                                                "list",
                                                -0.421053,
                                                5,
                                                "obj-49",
                                                "number",
                                                "int",
                                                62,
                                                5,
                                                "obj-50",
                                                "number",
                                                "int",
                                                11,
                                                5,
                                                "obj-54",
                                                "multislider",
                                                "list",
                                                -0.105263,
                                                5,
                                                "obj-56",
                                                "multislider",
                                                "list",
                                                -1.210526,
                                                5,
                                                "obj-58",
                                                "multislider",
                                                "list",
                                                -1.131579,
                                                5,
                                                "obj-48",
                                                "number",
                                                "int",
                                                0
                                            ]
                                        },
                                        {
                                            "number": 6,
                                            "data": [
                                                5,
                                                "obj-16",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-39",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-41",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-38",
                                                "multislider",
                                                "list",
                                                0.421053,
                                                5,
                                                "obj-49",
                                                "number",
                                                "int",
                                                62,
                                                5,
                                                "obj-50",
                                                "number",
                                                "int",
                                                71,
                                                5,
                                                "obj-54",
                                                "multislider",
                                                "list",
                                                -0.894737,
                                                5,
                                                "obj-56",
                                                "multislider",
                                                "list",
                                                0.447368,
                                                5,
                                                "obj-58",
                                                "multislider",
                                                "list",
                                                -1.526316,
                                                5,
                                                "obj-48",
                                                "number",
                                                "int",
                                                0
                                            ]
                                        },
                                        {
                                            "number": 7,
                                            "data": [
                                                5,
                                                "obj-16",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-39",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-41",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-38",
                                                "multislider",
                                                "list",
                                                0.421053,
                                                5,
                                                "obj-49",
                                                "number",
                                                "int",
                                                10,
                                                5,
                                                "obj-50",
                                                "number",
                                                "int",
                                                36,
                                                5,
                                                "obj-54",
                                                "multislider",
                                                "list",
                                                -1.605263,
                                                5,
                                                "obj-56",
                                                "multislider",
                                                "list",
                                                -1.526316,
                                                5,
                                                "obj-58",
                                                "multislider",
                                                "list",
                                                -0.263158,
                                                5,
                                                "obj-48",
                                                "number",
                                                "int",
                                                0
                                            ]
                                        },
                                        {
                                            "number": 8,
                                            "data": [
                                                5,
                                                "obj-16",
                                                "toggle",
                                                "int",
                                                1,
                                                5,
                                                "obj-39",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-41",
                                                "toggle",
                                                "int",
                                                0,
                                                5,
                                                "obj-38",
                                                "multislider",
                                                "list",
                                                0.473684,
                                                5,
                                                "obj-49",
                                                "number",
                                                "int",
                                                25,
                                                5,
                                                "obj-50",
                                                "number",
                                                "int",
                                                48,
                                                5,
                                                "obj-54",
                                                "multislider",
                                                "list",
                                                -1.605263,
                                                5,
                                                "obj-56",
                                                "multislider",
                                                "list",
                                                -1.526316,
                                                5,
                                                "obj-58",
                                                "multislider",
                                                "list",
                                                -0.263158,
                                                5,
                                                "obj-48",
                                                "number",
                                                "int",
                                                0
                                            ]
                                        }
                                    ],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-48",
                                    "maxclass": "number",
                                    "maximum": 3,
                                    "minimum": 0,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [170, 199, 53, 23],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-49",
                                    "maxclass": "number",
                                    "maximum": 240,
                                    "minimum": 1,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [455, 270, 53, 23],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-50",
                                    "maxclass": "number",
                                    "maximum": 320,
                                    "minimum": 1,
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", "bang"],
                                    "parameter_enable": 0,
                                    "patching_rect": [361, 270, 53, 23],
                                    "style": "",
                                    "triscale": 0.9
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-51",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [455, 295, 57, 23],
                                    "style": "",
                                    "text": "rows $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-52",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [361, 295, 77, 23],
                                    "style": "",
                                    "text": "columns $1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-53",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [170, 222, 61, 23],
                                    "style": "",
                                    "text": "mode $1"
                                }
                            },
                            {
                                "box": {
                                    "bgcolor": [0, 0, 1, 1],
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
                                    "id": "obj-54",
                                    "maxclass": "multislider",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "parameter_enable": 0,
                                    "patching_rect": [299, 251, 37, 40],
                                    "peakcolor": [
                                        0.498039,
                                        0.498039,
                                        0.498039,
                                        1
                                    ],
                                    "setminmax": [-2, 1],
                                    "slidercolor": [0, 0, 0, 1],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-55",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [299, 295, 52, 23],
                                    "style": "",
                                    "text": "blue $1"
                                }
                            },
                            {
                                "box": {
                                    "bgcolor": [0, 1, 0, 1],
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
                                    "id": "obj-56",
                                    "maxclass": "multislider",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "parameter_enable": 0,
                                    "patching_rect": [231.5, 251, 37, 40],
                                    "peakcolor": [
                                        0.498039,
                                        0.498039,
                                        0.498039,
                                        1
                                    ],
                                    "setminmax": [-2, 1],
                                    "slidercolor": [0, 0, 0, 1],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-57",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [231.5, 295, 61, 23],
                                    "style": "",
                                    "text": "green $1"
                                }
                            },
                            {
                                "box": {
                                    "bgcolor": [1, 0, 0, 1],
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
                                    "id": "obj-58",
                                    "maxclass": "multislider",
                                    "numinlets": 1,
                                    "numoutlets": 2,
                                    "outlettype": ["", ""],
                                    "parameter_enable": 0,
                                    "patching_rect": [179, 251, 37, 40],
                                    "peakcolor": [
                                        0.498039,
                                        0.498039,
                                        0.498039,
                                        1
                                    ],
                                    "setminmax": [-2, 1],
                                    "slidercolor": [0, 0, 0, 1],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-59",
                                    "maxclass": "message",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [179, 295, 46, 23],
                                    "style": "",
                                    "text": "red $1"
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
                                    "patching_rect": [10, 490, 70, 36],
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
                                    "patching_rect": [10, 363, 160, 120],
                                    "presentation_rect": [30, 30, 160, 120]
                                }
                            },
                            {
                                "box": {
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-1",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demovideo2.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["jit_matrix"],
                                    "patching_rect": [152.5, 82, 135, 96],
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
                                    "patching_rect": [11, 82, 135, 96],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-6",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [11, 330, 85, 23],
                                    "style": "",
                                    "text": "jit.eclipse"
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-6", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-1", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-17", 0],
                                    "disabled": 0,
                                    "hidden": 1,
                                    "source": ["obj-16", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-17", 0]
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
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-24", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-43", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-38", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-40", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-39", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
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
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-42", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-43", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-16", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-38", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-39", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-41", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-48", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-49", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-50", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-54", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-56", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-58", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-46", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-53", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-48", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-51", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-49", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-52", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-50", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-51", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-52", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-53", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-55", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-54", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-55", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-57", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-56", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-57", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-59", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-58", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-59", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-20", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-6", 0]
                                }
                            }
                        ]
                    },
                    "patching_rect": [54, 144, 67, 20],
                    "saved_object_attributes": {
                        "description": "",
                        "digest": "",
                        "fontsize": 13,
                        "globalpatchername": "",
                        "style": "",
                        "tags": ""
                    },
                    "style": "",
                    "text": "p example",
                    "varname": "basic_tab[1]"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12,
                    "id": "obj-5",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "patching_rect": [236, 96, 43, 18],
                    "style": "",
                    "text": "resize"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12,
                    "id": "obj-2",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [""],
                    "patching_rect": [223, 125, 145, 20],
                    "saved_object_attributes": {
                        "filename": "helpstarter.js",
                        "parameter_enable": 0
                    },
                    "style": "",
                    "text": "js helpstarter.js jit.eclipse"
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
                        "rect": [41, 109, 791, 531],
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
                                    "id": "obj-17",
                                    "linecount": 8,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [407, 185, 315, 123],
                                    "style": "helpfile_label",
                                    "text": "jit.eclipse contains extra features to invert the colors of squares in the grid that are above a threshold luminance value. negative threshhold values reverse the square inversions. the tint option switches tinting of the squares on and off (if off, then the only tinting is through inversion). the inv flag sets whether the red, green, and blue work subtractively in the negative (inverted) squares."
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-15",
                                    "linecount": 4,
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [410.5, 425, 303, 65],
                                    "style": "helpfile_label",
                                    "text": "the four modes switch between color tinting of color frames (default), color tinting of monochrome frames, monochrome tinting of color frames, and monochrome tinting of monochrome frames.."
                                }
                            },
                            {
                                "box": {
                                    "attr": "mode",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-14",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [627, 391, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "op",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-13",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [477, 391, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "inv",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-12",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [327, 391, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "tint",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-11",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [627, 363, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "id": "obj-21",
                                    "maxclass": "toggle",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": ["int"],
                                    "parameter_enable": 0,
                                    "patching_rect": [139, 302, 24, 24],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "bubble": 1,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-67",
                                    "maxclass": "comment",
                                    "numinlets": 1,
                                    "numoutlets": 0,
                                    "patching_rect": [159, 299.5, 208, 25],
                                    "style": "",
                                    "text": "off = 1 matrix, on = 2 matrices."
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-9",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 1,
                                    "outlettype": ["int"],
                                    "patching_rect": [76, 275, 36, 23],
                                    "style": "",
                                    "text": "+ 1"
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-10",
                                    "maxclass": "newobj",
                                    "numinlets": 3,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [76, 302, 57, 23],
                                    "style": "",
                                    "text": "switch 2"
                                }
                            },
                            {
                                "box": {
                                    "attr": "columns",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-8",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [477, 363, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "rows",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-7",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [327, 363, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "green",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-5",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [627, 333, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "blue",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-4",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [477, 333, 150, 23],
                                    "style": ""
                                }
                            },
                            {
                                "box": {
                                    "attr": "red",
                                    "fontface": 0,
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-3",
                                    "maxclass": "attrui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "patching_rect": [327, 333, 150, 23],
                                    "style": ""
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
                                    "patching_rect": [10, 490, 70, 36],
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
                                    "patching_rect": [10, 363, 160, 120],
                                    "presentation_rect": [30, 30, 160, 120]
                                }
                            },
                            {
                                "box": {
                                    "bgmode": 0,
                                    "border": 0,
                                    "clickthrough": 0,
                                    "enablehscroll": 0,
                                    "enablevscroll": 0,
                                    "id": "obj-1",
                                    "lockeddragscroll": 0,
                                    "maxclass": "bpatcher",
                                    "name": "demovideo2.maxpat",
                                    "numinlets": 0,
                                    "numoutlets": 1,
                                    "offset": [0, 0],
                                    "outlettype": ["jit_matrix"],
                                    "patching_rect": [151.5, 173, 135, 96],
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
                                    "patching_rect": [10, 173, 135, 96],
                                    "viewvisibility": 1
                                }
                            },
                            {
                                "box": {
                                    "fontname": "Arial",
                                    "fontsize": 13,
                                    "id": "obj-6",
                                    "maxclass": "newobj",
                                    "numinlets": 2,
                                    "numoutlets": 2,
                                    "outlettype": ["jit_matrix", ""],
                                    "patching_rect": [10, 336, 85, 23],
                                    "style": "",
                                    "text": "jit.eclipse"
                                }
                            },
                            {
                                "box": {
                                    "border": 0,
                                    "filename": "helpdetails.js",
                                    "id": "obj-2",
                                    "ignoreclick": 1,
                                    "jsarguments": ["jit.eclipse"],
                                    "maxclass": "jsui",
                                    "numinlets": 1,
                                    "numoutlets": 1,
                                    "outlettype": [""],
                                    "parameter_enable": 0,
                                    "patching_rect": [10, 8, 653, 156]
                                }
                            }
                        ],
                        "lines": [
                            {
                                "patchline": {
                                    "destination": ["obj-10", 2],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-1", 0]
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
                                    "destination": ["obj-6", 0],
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
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-13", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-14", 0]
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
                                    "destination": ["obj-9", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-21", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-10", 1],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-24", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-24", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-3", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-4", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-5", 0]
                                }
                            },
                            {
                                "patchline": {
                                    "destination": ["obj-20", 0],
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
                                    "destination": ["obj-6", 0],
                                    "disabled": 0,
                                    "hidden": 0,
                                    "source": ["obj-8", 0]
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
                    "jsarguments": ["jit.eclipse"],
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
                        "rect": [0, 26, 791, 531],
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
                    "destination": ["obj-2", 0],
                    "disabled": 0,
                    "hidden": 0,
                    "source": ["obj-5", 0]
                }
            }
        ],
        "parameters": {
            "obj-6::obj-1::obj-4::obj-18": ["number[6]", "number[1]", 0],
            "obj-1::obj-1::obj-4::obj-18": ["number[2]", "number[1]", 0],
            "obj-1::obj-24::obj-4::obj-21": ["number", "number", 0],
            "obj-1::obj-24::obj-4::obj-20": ["live.tab[1]", "live.tab[1]", 0],
            "obj-6::obj-24::obj-4::obj-18": ["number[4]", "number[1]", 0],
            "obj-6::obj-24::obj-4::obj-20": ["live.tab[3]", "live.tab[1]", 0],
            "obj-6::obj-1::obj-4::obj-20": ["live.tab[4]", "live.tab[1]", 0],
            "obj-1::obj-24::obj-4::obj-18": ["number[1]", "number[1]", 0],
            "obj-6::obj-1::obj-4::obj-21": ["number[7]", "number", 0],
            "obj-1::obj-1::obj-4::obj-20": ["live.tab[2]", "live.tab[1]", 0],
            "obj-6::obj-24::obj-4::obj-21": ["number[5]", "number", 0],
            "obj-1::obj-1::obj-4::obj-21": ["number[3]", "number", 0]
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