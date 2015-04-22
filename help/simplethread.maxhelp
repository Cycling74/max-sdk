{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 575.0, 64.0, 640.0, 506.0 ],
		"bglocked" : 0,
		"defrect" : [ 575.0, 64.0, 640.0, 506.0 ],
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
					"maxclass" : "comment",
					"text" : "set our \"foo\" value",
					"numinlets" : 1,
					"patching_rect" : [ 480.0, 54.0, 116.0, 19.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"id" : "obj-14",
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "how long to sleep between \"ticks\" default 1000, min 10",
					"linecount" : 3,
					"numinlets" : 1,
					"patching_rect" : [ 324.0, 33.0, 119.0, 43.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"id" : "obj-13",
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "cancel thread",
					"numinlets" : 1,
					"patching_rect" : [ 203.0, 87.0, 79.0, 19.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"id" : "obj-12",
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "start thread",
					"numinlets" : 1,
					"patching_rect" : [ 97.0, 86.0, 79.0, 19.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"id" : "obj-11",
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numinlets" : 1,
					"patching_rect" : [ 331.0, 78.0, 50.0, 19.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 2,
					"id" : "obj-8",
					"outlettype" : [ "int", "bang" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "sleeptime $1",
					"numinlets" : 2,
					"patching_rect" : [ 331.0, 108.0, 75.0, 17.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"id" : "obj-2",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numinlets" : 1,
					"patching_rect" : [ 480.0, 78.0, 50.0, 19.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 2,
					"id" : "obj-9",
					"outlettype" : [ "int", "bang" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "foo $1",
					"numinlets" : 2,
					"patching_rect" : [ 480.0, 108.0, 42.0, 17.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"id" : "obj-7",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print output",
					"numinlets" : 1,
					"patching_rect" : [ 235.0, 213.0, 70.0, 19.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"id" : "obj-6",
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "cancel",
					"numinlets" : 2,
					"patching_rect" : [ 203.0, 109.0, 42.0, 17.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"id" : "obj-5",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"patching_rect" : [ 99.0, 108.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"id" : "obj-3",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "simplethread",
					"numinlets" : 1,
					"patching_rect" : [ 235.0, 168.0, 76.0, 19.0 ],
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"id" : "obj-1",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-2", 0 ],
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
 ]
	}

}
