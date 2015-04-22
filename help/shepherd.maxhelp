{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 45.0, 70.0, 640.0, 506.0 ],
		"bglocked" : 0,
		"defrect" : [ 45.0, 70.0, 640.0, 506.0 ],
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
					"text" : "baah",
					"id" : "obj-13",
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 151.0, 127.0, 0.0, 0.0 ],
					"fontsize" : 10.0,
					"patching_rect" : [ 151.0, 127.0, 35.0, 17.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sheep",
					"id" : "obj-14",
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"presentation_rect" : [ 151.0, 153.0, 0.0, 0.0 ],
					"fontsize" : 10.0,
					"patching_rect" : [ 151.0, 153.0, 40.0, 19.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "baah",
					"id" : "obj-11",
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 262.0, 132.0, 0.0, 0.0 ],
					"fontsize" : 10.0,
					"patching_rect" : [ 258.0, 126.0, 35.0, 17.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sheep",
					"id" : "obj-12",
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"presentation_rect" : [ 262.0, 158.0, 0.0, 0.0 ],
					"fontsize" : 10.0,
					"patching_rect" : [ 258.0, 152.0, 40.0, 19.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "baah",
					"id" : "obj-10",
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontsize" : 10.0,
					"patching_rect" : [ 371.0, 124.0, 35.0, 17.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "try adding and removing sheep objects, sending the 'baah' and 'boo' messages",
					"linecount" : 3,
					"id" : "obj-8",
					"fontname" : "Verdana",
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"fontsize" : 10.0,
					"patching_rect" : [ 203.0, 47.0, 150.0, 43.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sheep",
					"id" : "obj-6",
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"presentation_rect" : [ 371.0, 111.0, 0.0, 0.0 ],
					"fontsize" : 10.0,
					"patching_rect" : [ 371.0, 150.0, 40.0, 19.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "boo",
					"id" : "obj-3",
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontsize" : 10.0,
					"patching_rect" : [ 245.0, 221.0, 32.5, 17.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "shepherd",
					"id" : "obj-1",
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"fontsize" : 10.0,
					"patching_rect" : [ 245.0, 258.0, 57.0, 19.0 ],
					"numinlets" : 1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-6", 0 ],
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
 ]
	}

}
