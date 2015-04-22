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
					"maxclass" : "number~",
					"outlettype" : [ "signal", "float" ],
					"presentation_rect" : [ 248.0, 140.0, 0.0, 0.0 ],
					"patching_rect" : [ 250.0, 140.0, 56.0, 19.0 ],
					"id" : "obj-5",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"sig" : 6.9,
					"numoutlets" : 2,
					"mode" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ezdac~",
					"patching_rect" : [ 180.0, 255.0, 45.0, 45.0 ],
					"id" : "obj-4",
					"numinlets" : 2,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number~",
					"outlettype" : [ "signal", "float" ],
					"patching_rect" : [ 175.0, 215.0, 56.0, 19.0 ],
					"id" : "obj-3",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"sig" : 0.0,
					"numoutlets" : 2,
					"mode" : 2,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number~",
					"outlettype" : [ "signal", "float" ],
					"patching_rect" : [ 175.0, 140.0, 56.0, 19.0 ],
					"id" : "obj-2",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"sig" : 2.0,
					"numoutlets" : 2,
					"mode" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "plussz~",
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 175.0, 175.0, 50.0, 19.0 ],
					"id" : "obj-1",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-1", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-3", 0 ],
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
