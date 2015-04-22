{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 29.0, 70.0, 640.0, 506.0 ],
		"bglocked" : 0,
		"defrect" : [ 29.0, 70.0, 640.0, 506.0 ],
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
		"metadata" : [  ],
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print b",
					"fontname" : "Verdana",
					"numinlets" : 1,
					"id" : "obj-5",
					"numoutlets" : 0,
					"fontsize" : 10.0,
					"patching_rect" : [ 200.0, 270.0, 46.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print a",
					"fontname" : "Verdana",
					"numinlets" : 1,
					"id" : "obj-4",
					"numoutlets" : 0,
					"fontsize" : 10.0,
					"patching_rect" : [ 150.0, 270.0, 46.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"id" : "obj-3",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 150.0, 150.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "urner 12",
					"fontname" : "Verdana",
					"numinlets" : 1,
					"id" : "obj-1",
					"numoutlets" : 2,
					"fontsize" : 10.0,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 150.0, 195.0, 57.0, 19.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"id" : "obj-2",
					"numoutlets" : 1,
					"fontsize" : 10.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 173.0, 165.0, 50.0, 17.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
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
					"source" : [ "obj-1", 1 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
