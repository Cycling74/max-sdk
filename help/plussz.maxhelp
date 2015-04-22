{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 68.0, 110.0, 605.0, 327.0 ],
		"bglocked" : 0,
		"defrect" : [ 68.0, 110.0, 605.0, 327.0 ],
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
					"maxclass" : "comment",
					"text" : "...and stored in p_value1 field of the t_plussz data structure",
					"linecount" : 2,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 304.315125, 227.746109, 214.0, 34.0 ],
					"id" : "obj-1",
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "plussz_in1",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 276.553345, 116.870468, 72.0, 20.0 ],
					"id" : "obj-2",
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "plussz_int",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 90.111664, 116.870468, 70.0, 20.0 ],
					"id" : "obj-3",
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"patching_rect" : [ 142.590576, 166.880829, 20.0, 20.0 ],
					"id" : "obj-4",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 171.679901, 115.331604, 50.0, 19.0 ],
					"id" : "obj-5",
					"numoutlets" : 2,
					"fontname" : "Verdana",
					"outlettype" : [ "int", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "plussz 5",
					"fontsize" : 12.0,
					"numinlets" : 2,
					"patching_rect" : [ 171.679901, 209.202072, 69.0, 20.0 ],
					"id" : "obj-6",
					"numoutlets" : 1,
					"fontname" : "Arial",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 171.679901, 287.683929, 38.0, 20.0 ],
					"id" : "obj-7",
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "like the + object...",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 25.652605, 42.854923, 129.0, 20.0 ],
					"id" : "obj-8",
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 222.660049, 115.331604, 50.0, 19.0 ],
					"id" : "obj-9",
					"numoutlets" : 2,
					"fontname" : "Verdana",
					"outlettype" : [ "int", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 219.746902, 289.222809, 50.0, 19.0 ],
					"id" : "obj-10",
					"numoutlets" : 2,
					"fontname" : "Verdana",
					"outlettype" : [ "int", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "plussz",
					"fontface" : 1,
					"fontsize" : 14.0,
					"numinlets" : 1,
					"patching_rect" : [ 10.0, 23.0, 68.0, 23.0 ],
					"id" : "obj-11",
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "this object is provided as a VERY simple programming example for beginning Max external object developers.",
					"linecount" : 2,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 178.679901, 27.616581, 310.0, 34.0 ],
					"id" : "obj-12",
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "plussz_bang",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 59.369728, 166.419693, 81.0, 20.0 ],
					"id" : "obj-13",
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "argument 5 is passed to plussz_new",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 243.138962, 209.279785, 226.0, 20.0 ],
					"id" : "obj-14",
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "values in the inlets are stored in p_value0 and p_value1 fields of the t_plussz data structure",
					"linecount" : 2,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 243.332504, 154.03627, 343.0, 34.0 ],
					"id" : "obj-15",
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-6", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
