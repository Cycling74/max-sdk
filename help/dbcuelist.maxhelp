{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 69.0, 69.0, 640.0, 506.0 ],
		"bglocked" : 0,
		"defrect" : [ 69.0, 69.0, 640.0, 506.0 ],
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
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "step through these sequentially from top to bottom to see how it works...",
					"linecount" : 2,
					"patching_rect" : [ 40.0, 5.0, 202.0, 31.0 ],
					"id" : "obj-22",
					"fontname" : "Verdana",
					"frgb" : [ 0.333333, 0.333333, 0.333333, 1.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontsize" : 10.0,
					"presentation_rect" : [ 26.0, 4.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "this side is just to display the table contents for diagnostic purposes.  it requires that you build the 'dbviewer' example project.",
					"linecount" : 3,
					"patching_rect" : [ 305.0, 5.0, 270.0, 43.0 ],
					"id" : "obj-21",
					"fontname" : "Verdana",
					"frgb" : [ 0.333333, 0.333333, 0.333333, 1.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "query \"SELECT * FROM events\"",
					"patching_rect" : [ 315.0, 275.0, 169.0, 17.0 ],
					"id" : "obj-2",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "dbviewer",
					"patching_rect" : [ 295.0, 300.0, 299.0, 188.0 ],
					"id" : "obj-3",
					"database" : "my_cool_show",
					"numinlets" : 1,
					"query" : "SELECT * FROM events",
					"numoutlets" : 1,
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "database my_cool_show",
					"patching_rect" : [ 295.0, 255.0, 134.0, 17.0 ],
					"id" : "obj-6",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "event.create three contact!",
					"patching_rect" : [ 75.0, 330.0, 148.0, 17.0 ],
					"id" : "obj-19",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "event.create three 2 1",
					"patching_rect" : [ 75.0, 305.0, 123.0, 17.0 ],
					"id" : "obj-20",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "event.create dos your partner",
					"patching_rect" : [ 75.0, 265.0, 161.0, 17.0 ],
					"id" : "obj-18",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "event.create dos si dos",
					"patching_rect" : [ 75.0, 240.0, 127.0, 17.0 ],
					"id" : "obj-17",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print output",
					"patching_rect" : [ 50.0, 475.0, 70.0, 19.0 ],
					"id" : "obj-16",
					"fontname" : "Verdana",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "cue.do dos",
					"patching_rect" : [ 80.0, 415.0, 65.0, 17.0 ],
					"id" : "obj-15",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "cue.do three",
					"patching_rect" : [ 65.0, 395.0, 74.0, 17.0 ],
					"id" : "obj-14",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "cue.destroy one",
					"patching_rect" : [ 70.0, 190.0, 91.0, 17.0 ],
					"id" : "obj-13",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "cue.rename two dos",
					"patching_rect" : [ 70.0, 155.0, 113.0, 17.0 ],
					"id" : "obj-12",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "cue.create three",
					"patching_rect" : [ 80.0, 115.0, 93.0, 17.0 ],
					"id" : "obj-11",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "cue.create two",
					"patching_rect" : [ 65.0, 95.0, 85.0, 17.0 ],
					"id" : "obj-10",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "dbviewer",
					"patching_rect" : [ 295.0, 120.0, 299.0, 114.0 ],
					"id" : "obj-4",
					"database" : "my_cool_show",
					"numinlets" : 1,
					"query" : "SELECT * FROM cues",
					"numoutlets" : 1,
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "dbcuelist @name my_cool_show",
					"patching_rect" : [ 50.0, 445.0, 174.0, 19.0 ],
					"id" : "obj-1",
					"fontname" : "Verdana",
					"numinlets" : 1,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "database my_cool_show",
					"patching_rect" : [ 295.0, 75.0, 134.0, 17.0 ],
					"id" : "obj-5",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "query \"SELECT * FROM cues\"",
					"patching_rect" : [ 315.0, 95.0, 159.0, 17.0 ],
					"id" : "obj-7",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "cue.create one",
					"patching_rect" : [ 50.0, 75.0, 85.0, 17.0 ],
					"id" : "obj-9",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 74.5, 125.5, 59.5, 125.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 89.5, 137.5, 59.5, 137.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 79.5, 181.5, 59.5, 181.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 79.5, 216.0, 59.5, 216.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 74.5, 419.0, 59.5, 419.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 89.5, 437.0, 59.5, 437.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 84.5, 259.0, 59.5, 259.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 84.5, 288.0, 59.5, 288.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 84.5, 353.0, 59.5, 353.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 84.5, 326.0, 59.5, 326.0 ]
				}

			}
 ]
	}

}
