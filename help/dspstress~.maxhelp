{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 436.0, 289.0, 640.0, 506.0 ],
		"bglocked" : 0,
		"defrect" : [ 436.0, 289.0, 640.0, 506.0 ],
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
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "ezdac~",
					"numoutlets" : 0,
					"patching_rect" : [ 180.0, 255.0, 45.0, 45.0 ],
					"id" : "obj-4",
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "dspstress~",
					"numoutlets" : 0,
					"fontname" : "Verdana",
					"patching_rect" : [ 175.0, 175.0, 66.0, 19.0 ],
					"id" : "obj-1",
					"fontsize" : 10.0,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"fontname" : "Verdana",
					"patching_rect" : [ 175.0, 145.0, 50.0, 19.0 ],
					"id" : "obj-2",
					"fontsize" : 10.0,
					"numinlets" : 1
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
 ]
	}

}
