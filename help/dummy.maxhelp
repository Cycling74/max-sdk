{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 25.0, 69.0, 751.0, 602.0 ],
		"bglocked" : 0,
		"defrect" : [ 25.0, 69.0, 751.0, 602.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 18.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"metadata" : [  ],
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : ";\rmax refgen dummy 1",
					"linecount" : 2,
					"numoutlets" : 1,
					"presentation_rect" : [ 456.0, 225.0, 0.0, 0.0 ],
					"outlettype" : [ "" ],
					"patching_rect" : [ 456.0, 225.0, 180.0, 46.0 ],
					"id" : "obj-14",
					"fontname" : "Arial",
					"numinlets" : 2,
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : ";\rmax refgen dummy",
					"linecount" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 455.0, 160.0, 165.0, 46.0 ],
					"id" : "obj-13",
					"fontname" : "Arial",
					"numinlets" : 2,
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "identify",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 296.0, 156.0, 68.0, 25.0 ],
					"id" : "obj-11",
					"fontname" : "Arial",
					"numinlets" : 2,
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 224.0, 262.0, 50.0, 27.0 ],
					"id" : "obj-9",
					"fontname" : "Arial",
					"numinlets" : 1,
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 217.0, 156.0, 50.0, 27.0 ],
					"id" : "obj-7",
					"fontname" : "Arial",
					"numinlets" : 1,
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numoutlets" : 2,
					"outlettype" : [ "int", "bang" ],
					"patching_rect" : [ 147.0, 260.0, 50.0, 27.0 ],
					"id" : "obj-5",
					"fontname" : "Arial",
					"numinlets" : 1,
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numoutlets" : 2,
					"outlettype" : [ "int", "bang" ],
					"patching_rect" : [ 151.0, 153.0, 50.0, 27.0 ],
					"id" : "obj-3",
					"fontname" : "Arial",
					"numinlets" : 1,
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "dummy foo",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 181.0, 205.0, 100.0, 27.0 ],
					"id" : "obj-1",
					"fontname" : "Arial",
					"numinlets" : 1,
					"fontsize" : 18.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
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
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
