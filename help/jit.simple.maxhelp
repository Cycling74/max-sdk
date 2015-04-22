{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 45.0, 70.0, 926.0, 622.0 ],
		"bglocked" : 0,
		"defrect" : [ 45.0, 70.0, 926.0, 622.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 10.0,
		"default_fontface" : 0,
		"default_fontname" : "Verdana",
		"gridonopen" : 0,
		"gridsize" : [ 5.0, 5.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "setall 4.",
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 749.0, 294.0, 0.0, 0.0 ],
					"id" : "obj-41",
					"fontname" : "Verdana",
					"patching_rect" : [ 750.0, 295.0, 51.0, 17.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.cellblock",
					"numoutlets" : 4,
					"fontsize" : 10.0,
					"outlettype" : [ "list", "", "", "" ],
					"selmode" : 5,
					"presentation_rect" : [ 744.0, 354.0, 0.0, 0.0 ],
					"cols" : 2,
					"outmode" : 1,
					"id" : "obj-42",
					"fontname" : "Verdana",
					"patching_rect" : [ 745.0, 355.0, 139.0, 43.0 ],
					"rows" : 2,
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"presentation_rect" : [ 724.0, 264.0, 0.0, 0.0 ],
					"id" : "obj-43",
					"patching_rect" : [ 725.0, 265.0, 20.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.cellblock",
					"numoutlets" : 4,
					"fontsize" : 10.0,
					"outlettype" : [ "list", "", "", "" ],
					"presentation_rect" : [ 724.0, 454.0, 0.0, 0.0 ],
					"cols" : 2,
					"id" : "obj-44",
					"fontname" : "Verdana",
					"patching_rect" : [ 725.0, 455.0, 139.0, 43.0 ],
					"rows" : 2,
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.matrix 1 long 2 2",
					"numoutlets" : 2,
					"fontsize" : 10.0,
					"outlettype" : [ "jit_matrix", "" ],
					"id" : "obj-45",
					"fontname" : "Verdana",
					"patching_rect" : [ 725.0, 325.0, 111.0, 19.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.simple @gain 0.5",
					"numoutlets" : 2,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 724.0, 414.0, 0.0, 0.0 ],
					"id" : "obj-46",
					"fontname" : "Arial",
					"patching_rect" : [ 725.0, 415.0, 112.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "setall 4.",
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 581.0, 295.0, 0.0, 0.0 ],
					"id" : "obj-35",
					"fontname" : "Verdana",
					"patching_rect" : [ 580.0, 295.0, 51.0, 17.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.cellblock",
					"numoutlets" : 4,
					"fontsize" : 10.0,
					"outlettype" : [ "list", "", "", "" ],
					"selmode" : 5,
					"presentation_rect" : [ 576.0, 355.0, 0.0, 0.0 ],
					"cols" : 2,
					"outmode" : 1,
					"id" : "obj-36",
					"fontname" : "Verdana",
					"patching_rect" : [ 575.0, 355.0, 139.0, 43.0 ],
					"rows" : 2,
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"presentation_rect" : [ 556.0, 265.0, 0.0, 0.0 ],
					"id" : "obj-37",
					"patching_rect" : [ 555.0, 265.0, 20.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.cellblock",
					"numoutlets" : 4,
					"fontsize" : 10.0,
					"outlettype" : [ "list", "", "", "" ],
					"presentation_rect" : [ 556.0, 455.0, 0.0, 0.0 ],
					"cols" : 2,
					"id" : "obj-38",
					"fontname" : "Verdana",
					"patching_rect" : [ 555.0, 455.0, 139.0, 43.0 ],
					"rows" : 2,
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.matrix 1 float32 2 2",
					"numoutlets" : 2,
					"fontsize" : 10.0,
					"outlettype" : [ "jit_matrix", "" ],
					"id" : "obj-39",
					"fontname" : "Verdana",
					"patching_rect" : [ 555.0, 325.0, 125.0, 19.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.simple @gain 0.5",
					"numoutlets" : 2,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"presentation_rect" : [ 556.0, 415.0, 0.0, 0.0 ],
					"id" : "obj-40",
					"fontname" : "Arial",
					"patching_rect" : [ 555.0, 415.0, 112.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "setall 4.",
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 611.0, 302.0, 0.0, 0.0 ],
					"id" : "obj-34",
					"fontname" : "Verdana",
					"patching_rect" : [ 420.0, 295.0, 51.0, 17.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.cellblock",
					"numoutlets" : 4,
					"fontsize" : 10.0,
					"outlettype" : [ "list", "", "", "" ],
					"selmode" : 5,
					"presentation_rect" : [ 542.0, 242.0, 0.0, 0.0 ],
					"cols" : 2,
					"outmode" : 1,
					"id" : "obj-30",
					"fontname" : "Verdana",
					"patching_rect" : [ 415.0, 355.0, 139.0, 43.0 ],
					"rows" : 2,
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-26",
					"patching_rect" : [ 395.0, 265.0, 20.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.cellblock",
					"numoutlets" : 4,
					"fontsize" : 10.0,
					"outlettype" : [ "list", "", "", "" ],
					"cols" : 2,
					"id" : "obj-17",
					"fontname" : "Verdana",
					"patching_rect" : [ 395.0, 455.0, 139.0, 43.0 ],
					"rows" : 2,
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.matrix 1 float64 2 2",
					"numoutlets" : 2,
					"fontsize" : 10.0,
					"outlettype" : [ "jit_matrix", "" ],
					"id" : "obj-15",
					"fontname" : "Verdana",
					"patching_rect" : [ 395.0, 325.0, 125.0, 19.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.simple @gain 0.5",
					"numoutlets" : 2,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"id" : "obj-9",
					"fontname" : "Arial",
					"patching_rect" : [ 395.0, 415.0, 112.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0.5",
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ],
					"id" : "obj-4",
					"fontname" : "Verdana",
					"patching_rect" : [ 190.0, 165.0, 78.0, 19.0 ],
					"numinlets" : 1,
					"hidden" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read dishes.mov",
					"numoutlets" : 1,
					"fontsize" : 11.595187,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 203.0, 142.0, 0.0, 0.0 ],
					"id" : "obj-3",
					"fontname" : "Arial",
					"patching_rect" : [ 140.0, 140.0, 96.0, 18.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"numoutlets" : 1,
					"fontsize" : 11.595187,
					"outlettype" : [ "" ],
					"id" : "obj-6",
					"fontname" : "Arial",
					"patching_rect" : [ 128.0, 106.0, 32.5, 18.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numoutlets" : 2,
					"fontsize" : 11.595187,
					"outlettype" : [ "float", "bang" ],
					"triscale" : 0.9,
					"id" : "obj-7",
					"fontname" : "Arial",
					"patching_rect" : [ 162.0, 79.0, 50.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rate $1",
					"numoutlets" : 1,
					"fontsize" : 11.595187,
					"outlettype" : [ "" ],
					"id" : "obj-8",
					"fontname" : "Arial",
					"patching_rect" : [ 162.0, 106.0, 47.0, 18.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read",
					"numoutlets" : 1,
					"fontsize" : 11.595187,
					"outlettype" : [ "" ],
					"id" : "obj-24",
					"fontname" : "Arial",
					"patching_rect" : [ 92.0, 106.0, 34.0, 18.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numoutlets" : 2,
					"fontsize" : 11.595187,
					"outlettype" : [ "int", "bang" ],
					"triscale" : 0.9,
					"id" : "obj-25",
					"fontname" : "Arial",
					"patching_rect" : [ 68.0, 78.0, 50.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"id" : "obj-27",
					"patching_rect" : [ 24.0, 78.0, 20.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "qmetro 30",
					"numoutlets" : 1,
					"fontsize" : 11.595187,
					"outlettype" : [ "bang" ],
					"id" : "obj-28",
					"fontname" : "Arial",
					"patching_rect" : [ 24.0, 106.0, 63.0, 20.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.qt.movie 320 240",
					"numoutlets" : 2,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"id" : "obj-50",
					"fontname" : "Arial",
					"patching_rect" : [ 24.0, 138.0, 111.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.fpsgui",
					"numoutlets" : 2,
					"fontsize" : 11.595187,
					"outlettype" : [ "", "" ],
					"id" : "obj-13",
					"fontname" : "Arial",
					"patching_rect" : [ 24.0, 510.0, 80.0, 35.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "supports: any type/planecount.",
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-16",
					"fontname" : "Arial",
					"patching_rect" : [ 290.0, 190.0, 166.0, 20.0 ],
					"numinlets" : 1,
					"frgb" : [ 0.658824, 0.658824, 0.658824, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print",
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-20",
					"fontname" : "Arial",
					"patching_rect" : [ 65.0, 240.0, 33.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numoutlets" : 2,
					"fontsize" : 11.595187,
					"outlettype" : [ "float", "bang" ],
					"triscale" : 0.9,
					"id" : "obj-21",
					"fontname" : "Arial",
					"patching_rect" : [ 133.0, 165.0, 50.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "gain $1",
					"numoutlets" : 1,
					"fontsize" : 11.595187,
					"outlettype" : [ "" ],
					"id" : "obj-22",
					"fontname" : "Arial",
					"patching_rect" : [ 133.0, 190.0, 49.0, 18.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.simple",
					"numoutlets" : 2,
					"fontsize" : 11.595187,
					"outlettype" : [ "jit_matrix", "" ],
					"id" : "obj-23",
					"fontname" : "Arial",
					"patching_rect" : [ 24.0, 217.0, 60.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description",
					"text" : "The jit.simple object multiplies a constant against every cell in the matrix",
					"linecount" : 3,
					"numoutlets" : 0,
					"fontsize" : 11.595187,
					"id" : "obj-11",
					"fontname" : "Arial",
					"patching_rect" : [ 290.0, 135.0, 177.0, 46.0 ],
					"numinlets" : 1,
					"frgb" : [ 0.658824, 0.658824, 0.658824, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.pwindow",
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"background" : 1,
					"id" : "obj-19",
					"patching_rect" : [ 24.0, 263.0, 320.0, 240.0 ],
					"numinlets" : 1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-41", 0 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-43", 0 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 0 ],
					"destination" : [ "obj-46", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-43", 0 ],
					"destination" : [ "obj-41", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-44", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-39", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-39", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-40", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-36", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-38", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-34", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [ 142.5, 213.0, 33.5, 213.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 1 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-28", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"midpoints" : [ 171.5, 129.0, 33.5, 129.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"midpoints" : [ 137.5, 129.0, 33.5, 129.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"midpoints" : [ 101.5, 129.0, 33.5, 129.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
