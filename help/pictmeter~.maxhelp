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
					"maxclass" : "ezdac~",
					"patching_rect" : [ 120.0, 45.0, 45.0, 45.0 ],
					"id" : "obj-4",
					"numinlets" : 2,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "phasor~ 0.5",
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 230.0, 85.0, 73.0, 19.0 ],
					"id" : "obj-3",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "pictmeter~",
					"patching_rect" : [ 100.0, 135.0, 128.0, 128.0 ],
					"id" : "obj-1",
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read fpic_house.png",
					"outlettype" : [ "" ],
					"patching_rect" : [ 100.0, 105.0, 112.0, 17.0 ],
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
					"source" : [ "obj-3", 0 ],
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
