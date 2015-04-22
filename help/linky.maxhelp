{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 168.0, 119.0, 605.0, 366.0 ],
		"bglocked" : 0,
		"defrect" : [ 168.0, 119.0, 605.0, 366.0 ],
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
					"text" : "reverse",
					"presentation_rect" : [ 200.0, 231.0, 0.0, 0.0 ],
					"numinlets" : 2,
					"patching_rect" : [ 155.0, 250.0, 48.0, 17.0 ],
					"numoutlets" : 1,
					"id" : "obj-2",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "linky",
					"numinlets" : 1,
					"patching_rect" : [ 125.0, 275.0, 34.0, 19.0 ],
					"numoutlets" : 1,
					"id" : "obj-12",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "post",
					"numinlets" : 2,
					"patching_rect" : [ 155.0, 230.0, 32.5, 17.0 ],
					"numoutlets" : 1,
					"id" : "obj-10",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "1 2 3",
					"numinlets" : 2,
					"patching_rect" : [ 200.0, 120.0, 37.0, 17.0 ],
					"numoutlets" : 1,
					"id" : "obj-9",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "c",
					"numinlets" : 2,
					"patching_rect" : [ 245.0, 120.0, 32.5, 17.0 ],
					"numoutlets" : 1,
					"id" : "obj-7",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "b",
					"numinlets" : 2,
					"patching_rect" : [ 160.0, 120.0, 32.5, 17.0 ],
					"numoutlets" : 1,
					"id" : "obj-5",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "a",
					"numinlets" : 2,
					"patching_rect" : [ 115.0, 120.0, 32.5, 17.0 ],
					"numoutlets" : 1,
					"id" : "obj-3",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend append",
					"numinlets" : 1,
					"patching_rect" : [ 125.0, 195.0, 92.0, 19.0 ],
					"numoutlets" : 1,
					"id" : "obj-1",
					"fontname" : "Verdana",
					"outlettype" : [ "" ],
					"fontsize" : 10.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-12", 0 ],
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
					"source" : [ "obj-9", 0 ],
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
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
