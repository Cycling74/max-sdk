{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 87.0, 71.0, 415.0, 271.0 ],
		"bglocked" : 0,
		"defrect" : [ 87.0, 71.0, 415.0, 271.0 ],
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
					"text" : "read counter.maxhelp from disk",
					"numoutlets" : 0,
					"fontsize" : 12.0,
					"presentation_rect" : [ 200.322311, 95.112785, 0.0, 0.0 ],
					"id" : "obj-13",
					"fontname" : "Arial",
					"patching_rect" : [ 200.322311, 95.112785, 178.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open counter.maxhelp",
					"numoutlets" : 1,
					"fontsize" : 12.0,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 69.0, 89.0, 0.0, 0.0 ],
					"id" : "obj-12",
					"fontname" : "Arial",
					"patching_rect" : [ 69.0, 95.0, 129.0, 18.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "byte in file at given offset",
					"numoutlets" : 0,
					"fontsize" : 12.0,
					"id" : "obj-1",
					"fontname" : "Arial",
					"patching_rect" : [ 105.36364, 223.744354, 154.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numoutlets" : 2,
					"fontsize" : 10.0,
					"outlettype" : [ "int", "bang" ],
					"id" : "obj-2",
					"fontname" : "Verdana",
					"patching_rect" : [ 51.619835, 225.406021, 50.0, 19.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "fclose",
					"numoutlets" : 1,
					"fontsize" : 12.0,
					"outlettype" : [ "" ],
					"id" : "obj-3",
					"fontname" : "Arial",
					"patching_rect" : [ 78.231407, 130.81955, 50.0, 18.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "close file",
					"numoutlets" : 0,
					"fontsize" : 12.0,
					"id" : "obj-4",
					"fontname" : "Arial",
					"patching_rect" : [ 132.975204, 133.045105, 126.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"numoutlets" : 1,
					"fontsize" : 12.0,
					"outlettype" : [ "" ],
					"id" : "obj-5",
					"fontname" : "Arial",
					"patching_rect" : [ 52.0, 62.0, 41.0, 18.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "read a file from disk",
					"numoutlets" : 0,
					"fontsize" : 12.0,
					"id" : "obj-6",
					"fontname" : "Arial",
					"patching_rect" : [ 103.322311, 63.112785, 129.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numoutlets" : 2,
					"fontsize" : 10.0,
					"outlettype" : [ "int", "bang" ],
					"id" : "obj-7",
					"fontname" : "Verdana",
					"patching_rect" : [ 97.619835, 157.526321, 50.0, 19.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "filebyte",
					"numoutlets" : 1,
					"fontsize" : 12.0,
					"outlettype" : [ "int" ],
					"id" : "obj-8",
					"fontname" : "Arial",
					"patching_rect" : [ 51.619835, 192.022552, 54.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "filebyte is an example of reading files from disk",
					"numoutlets" : 0,
					"fontface" : 1,
					"fontsize" : 14.0,
					"id" : "obj-9",
					"fontname" : "Arial",
					"patching_rect" : [ 17.0, 20.0, 326.0, 23.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "read byte at offset",
					"numoutlets" : 0,
					"fontsize" : 12.0,
					"id" : "obj-10",
					"fontname" : "Arial",
					"patching_rect" : [ 148.504135, 157.639099, 116.0, 20.0 ],
					"numinlets" : 1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
