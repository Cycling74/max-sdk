{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 46.0, 79.0, 645.0, 361.0 ],
		"bglocked" : 0,
		"defrect" : [ 46.0, 79.0, 645.0, 361.0 ],
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
					"text" : "sends the value to simplejs, calculates the absolute value, returns the result in js",
					"numinlets" : 1,
					"patching_rect" : [ 181.0, 180.0, 421.0, 19.0 ],
					"numoutlets" : 0,
					"id" : "obj-14",
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"presentation_rect" : [ 180.0, 204.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "abs $1",
					"numinlets" : 2,
					"patching_rect" : [ 128.0, 209.0, 44.0, 17.0 ],
					"numoutlets" : 1,
					"id" : "obj-12",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0,
					"presentation_rect" : [ 140.0, 195.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numinlets" : 1,
					"patching_rect" : [ 128.0, 179.0, 50.0, 19.0 ],
					"numoutlets" : 2,
					"id" : "obj-13",
					"fontname" : "Verdana",
					"outlettype" : [ "float", "bang" ],
					"fontsize" : 10.0,
					"presentation_rect" : [ 140.0, 165.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "get the value of myattr",
					"numinlets" : 1,
					"patching_rect" : [ 164.0, 107.0, 126.0, 19.0 ],
					"numoutlets" : 0,
					"id" : "obj-11",
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"presentation_rect" : [ 164.0, 131.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "get",
					"numinlets" : 2,
					"patching_rect" : [ 127.0, 107.0, 32.5, 17.0 ],
					"numoutlets" : 1,
					"id" : "obj-10",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0,
					"presentation_rect" : [ 127.0, 131.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "set the value of myattr",
					"numinlets" : 1,
					"patching_rect" : [ 123.0, 78.0, 126.0, 19.0 ],
					"numoutlets" : 0,
					"id" : "obj-8",
					"fontname" : "Verdana",
					"fontsize" : 10.0,
					"presentation_rect" : [ 123.0, 102.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numinlets" : 1,
					"patching_rect" : [ 46.0, 293.0, 50.0, 19.0 ],
					"numoutlets" : 2,
					"id" : "obj-7",
					"fontname" : "Verdana",
					"outlettype" : [ "float", "bang" ],
					"fontsize" : 10.0,
					"presentation_rect" : [ 46.0, 212.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "print the value of myattr in the Max window",
					"numinlets" : 1,
					"patching_rect" : [ 72.0, 41.0, 232.0, 19.0 ],
					"numoutlets" : 0,
					"id" : "obj-4",
					"fontname" : "Verdana",
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "js simplejs_test.js",
					"numinlets" : 1,
					"patching_rect" : [ 46.0, 255.0, 102.0, 19.0 ],
					"numoutlets" : 1,
					"id" : "obj-1",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"patching_rect" : [ 46.0, 41.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"id" : "obj-2",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "set $1",
					"numinlets" : 2,
					"patching_rect" : [ 70.0, 107.0, 42.0, 17.0 ],
					"numoutlets" : 1,
					"id" : "obj-5",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numinlets" : 1,
					"patching_rect" : [ 70.0, 77.0, 50.0, 19.0 ],
					"numoutlets" : 2,
					"id" : "obj-6",
					"fontname" : "Verdana",
					"outlettype" : [ "float", "bang" ],
					"fontsize" : 10.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-5", 0 ],
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
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
