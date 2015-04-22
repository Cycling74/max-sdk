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
					"maxclass" : "number",
					"patching_rect" : [ 157.0, 95.0, 50.0, 19.0 ],
					"numinlets" : 1,
					"id" : "obj-9",
					"fontname" : "Verdana",
					"numoutlets" : 2,
					"outlettype" : [ "int", "bang" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"patching_rect" : [ 157.0, 39.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"id" : "obj-7",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "counter 0 199",
					"patching_rect" : [ 157.0, 67.0, 81.0, 19.0 ],
					"numinlets" : 5,
					"id" : "obj-3",
					"fontname" : "Verdana",
					"numoutlets" : 4,
					"outlettype" : [ "int", "", "", "int" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "task $1",
					"patching_rect" : [ 157.0, 120.0, 48.0, 17.0 ],
					"numinlets" : 2,
					"id" : "obj-2",
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 154.0, 118.0, 0.0, 0.0 ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "cancel all tasks",
					"patching_rect" : [ 364.0, 95.0, 148.0, 19.0 ],
					"numinlets" : 1,
					"id" : "obj-12",
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "start task",
					"patching_rect" : [ 59.0, 79.0, 79.0, 19.0 ],
					"numinlets" : 1,
					"id" : "obj-11",
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print output",
					"patching_rect" : [ 235.0, 213.0, 70.0, 19.0 ],
					"numinlets" : 1,
					"id" : "obj-6",
					"fontname" : "Verdana",
					"numoutlets" : 0,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "cancel",
					"patching_rect" : [ 364.0, 117.0, 42.0, 17.0 ],
					"numinlets" : 2,
					"id" : "obj-5",
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "threadpool",
					"patching_rect" : [ 235.0, 168.0, 64.0, 19.0 ],
					"numinlets" : 1,
					"id" : "obj-1",
					"fontname" : "Verdana",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-6", 0 ],
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
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
