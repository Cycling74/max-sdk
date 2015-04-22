{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 71.0, 69.0, 640.0, 506.0 ],
		"bglocked" : 0,
		"defrect" : [ 71.0, 69.0, 640.0, 506.0 ],
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
					"maxclass" : "comment",
					"text" : "change mode",
					"patching_rect" : [ 320.0, 125.0, 150.0, 19.0 ],
					"id" : "obj-5",
					"fontname" : "Verdana",
					"numinlets" : 1,
					"numoutlets" : 0,
					"frgb" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"outlettype" : [ "int", "bang" ],
					"patching_rect" : [ 270.0, 125.0, 50.0, 19.0 ],
					"id" : "obj-3",
					"fontname" : "Verdana",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "uitester",
					"patching_rect" : [ 270.0, 175.0, 128.0, 128.0 ],
					"id" : "obj-1",
					"numinlets" : 1,
					"numoutlets" : 0
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
 ]
	}

}
