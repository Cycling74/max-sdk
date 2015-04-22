{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 45.0, 70.0, 774.0, 581.0 ],
		"bglocked" : 0,
		"defrect" : [ 45.0, 70.0, 774.0, 581.0 ],
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
					"maxclass" : "newobj",
					"text" : "*~ 10.",
					"id" : "obj-32",
					"patching_rect" : [ 235.0, 195.0, 45.0, 19.0 ],
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "tanh~",
					"id" : "obj-31",
					"patching_rect" : [ 235.0, 220.0, 41.0, 19.0 ],
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "average~ 100 absolute",
					"id" : "obj-29",
					"patching_rect" : [ 235.0, 170.0, 128.0, 19.0 ],
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"id" : "obj-12",
					"patching_rect" : [ 225.0, 115.0, 56.0, 19.0 ],
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description[1]",
					"text" : "If an audio signal is connected, it sets the gain.",
					"linecount" : 2,
					"id" : "obj-18",
					"patching_rect" : [ 545.0, 145.0, 180.0, 33.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 0,
					"frgb" : [ 0.658824, 0.658824, 0.658824, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "loop $1",
					"id" : "obj-14",
					"patching_rect" : [ 375.0, 110.0, 48.0, 17.0 ],
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "gain~",
					"id" : "obj-10",
					"patching_rect" : [ 360.0, 220.0, 114.0, 24.0 ],
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "dac~",
					"id" : "obj-5",
					"patching_rect" : [ 360.0, 260.0, 36.0, 19.0 ],
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess open drumloop.aif",
					"id" : "obj-2",
					"patching_rect" : [ 360.0, 70.0, 153.0, 19.0 ],
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sfplay~",
					"id" : "obj-1",
					"patching_rect" : [ 360.0, 130.0, 48.0, 19.0 ],
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read dishes.mov",
					"id" : "obj-3",
					"patching_rect" : [ 140.0, 140.0, 96.0, 18.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"id" : "obj-6",
					"patching_rect" : [ 128.0, 106.0, 32.5, 18.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"id" : "obj-7",
					"patching_rect" : [ 162.0, 79.0, 50.0, 20.0 ],
					"fontname" : "Arial",
					"triscale" : 0.9,
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rate $1",
					"id" : "obj-8",
					"patching_rect" : [ 162.0, 106.0, 47.0, 18.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read",
					"id" : "obj-24",
					"patching_rect" : [ 92.0, 106.0, 34.0, 18.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"id" : "obj-25",
					"patching_rect" : [ 68.0, 78.0, 50.0, 20.0 ],
					"fontname" : "Arial",
					"triscale" : 0.9,
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"id" : "obj-27",
					"patching_rect" : [ 20.0, 15.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "qmetro 30",
					"id" : "obj-28",
					"patching_rect" : [ 24.0, 106.0, 63.0, 20.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.qt.movie 320 240",
					"id" : "obj-50",
					"patching_rect" : [ 24.0, 138.0, 111.0, 20.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "jit_matrix", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.fpsgui",
					"id" : "obj-13",
					"patching_rect" : [ 24.0, 510.0, 80.0, 35.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "supports: any type/planecount.",
					"id" : "obj-16",
					"patching_rect" : [ 545.0, 180.0, 166.0, 20.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 0,
					"frgb" : [ 0.658824, 0.658824, 0.658824, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print",
					"id" : "obj-20",
					"patching_rect" : [ 65.0, 240.0, 33.0, 20.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "jit.simple~",
					"id" : "obj-23",
					"patching_rect" : [ 24.0, 217.0, 62.0, 20.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "jit_matrix", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description",
					"text" : "The jit.simple object multiplies a constant against every cell in the matrix",
					"linecount" : 3,
					"id" : "obj-11",
					"patching_rect" : [ 545.0, 95.0, 180.0, 46.0 ],
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 0,
					"frgb" : [ 0.658824, 0.658824, 0.658824, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "jit.pwindow",
					"id" : "obj-19",
					"patching_rect" : [ 24.0, 263.0, 320.0, 240.0 ],
					"background" : 1,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-32", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-31", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-31", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-5", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-10", 0 ],
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
					"source" : [ "obj-23", 1 ],
					"destination" : [ "obj-20", 0 ],
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
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"midpoints" : [ 101.5, 129.0, 33.5, 129.0 ]
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
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"midpoints" : [ 171.5, 129.0, 33.5, 129.0 ]
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
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-8", 0 ],
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
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
