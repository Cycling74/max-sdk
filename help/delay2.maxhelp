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
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "button",
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 90.0, 280.0, 20.0, 20.0 ],
					"id" : "obj-8",
					"numinlets" : 1,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 90.0, 200.0, 20.0, 20.0 ],
					"id" : "obj-6",
					"numinlets" : 1,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "delaytime 2n",
					"outlettype" : [ "" ],
					"presentation_rect" : [ 219.0, 211.0, 0.0, 0.0 ],
					"patching_rect" : [ 195.0, 210.0, 76.0, 17.0 ],
					"id" : "obj-4",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "rewind",
					"patching_rect" : [ 430.0, 237.0, 50.0, 20.0 ],
					"id" : "obj-154",
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "0.",
					"outlettype" : [ "" ],
					"patching_rect" : [ 407.0, 237.0, 22.235294, 18.0 ],
					"id" : "obj-153",
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "start/stop the transport",
					"patching_rect" : [ 411.0, 214.0, 133.0, 20.0 ],
					"id" : "obj-152",
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "transport",
					"outlettype" : [ "int", "int", "float", "float", "float", "", "int", "float", "" ],
					"patching_rect" : [ 389.0, 265.0, 96.352936, 20.0 ],
					"id" : "obj-151",
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 9,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "set tempo in bpm",
					"patching_rect" : [ 340.0, 120.0, 103.0, 20.0 ],
					"id" : "obj-131",
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"outlettype" : [ "float", "bang" ],
					"patching_rect" : [ 342.0, 144.0, 50.0, 20.0 ],
					"id" : "obj-129",
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "tempo $1",
					"outlettype" : [ "" ],
					"patching_rect" : [ 342.0, 166.0, 59.0, 18.0 ],
					"id" : "obj-128",
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"outlettype" : [ "int" ],
					"patching_rect" : [ 389.0, 213.0, 20.0, 20.0 ],
					"id" : "obj-122",
					"numinlets" : 1,
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "delay2",
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 90.0, 240.0, 44.0, 19.0 ],
					"id" : "obj-1",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "delaytime 4n",
					"outlettype" : [ "" ],
					"patching_rect" : [ 110.0, 210.0, 76.0, 17.0 ],
					"id" : "obj-2",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-128", 0 ],
					"destination" : [ "obj-151", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-129", 0 ],
					"destination" : [ "obj-128", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-122", 0 ],
					"destination" : [ "obj-151", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-153", 0 ],
					"destination" : [ "obj-151", 1 ],
					"hidden" : 0,
					"midpoints" : [ 416.5, 261.0, 475.852936, 261.0 ]
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
