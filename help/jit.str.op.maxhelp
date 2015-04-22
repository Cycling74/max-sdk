{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 0,
			"revision" : 0,
			"architecture" : "x86",
			"modernui" : 1
		}
,
		"rect" : [ 34.0, 78.0, 1142.0, 646.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"showrootpatcherontab" : 0,
		"showontab" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 0,
							"revision" : 0,
							"architecture" : "x86",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 1142.0, 620.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-4",
									"ignoreclick" : 1,
									"jsarguments" : [ "jit.str.op" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 305.0, 55.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-22",
									"items" : [ "ies", ",", "gasm", 19, ",", "ussed" ],
									"maxclass" : "umenu",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 124.235901, 258.658295, 100.0, 21.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 165.235901, 287.350494, 109.0, 21.0 ],
									"style" : "",
									"text" : "jit.str.fromsymbol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-21",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 328.0, 376.037933, 162.0, 66.0 ],
									"style" : "",
									"text" : "strcmp and strlen return data, rather than strings. this information is sent via the dumpout outlet",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-20",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 165.011627, 487.61499, 164.0, 36.0 ],
									"style" : "",
									"text" : "convert from a string matrix to a Max symbol",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-17",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 359.011627, 449.615021, 261.0, 36.0 ],
									"style" : "",
									"text" : "Look in the Max window to see what's \"really happening.\"",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 499.0, 230.965515, 103.0, 25.0 ],
									"style" : "",
									"text" : "String length"
								}

							}
, 							{
								"box" : 								{
									"attr" : "dim",
									"attrfilter" : [ "dim" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-11",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 374.0, 232.965515, 125.0, 21.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 51.235901, 133.990936, 251.976776, 21.0 ],
									"style" : "",
									"text" : "Select two string and see what happens"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-10",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 359.011627, 134.5, 145.976776, 21.0 ],
									"style" : "",
									"text" : "Choose an operation"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-27",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 623.0, 187.13475, 144.0, 25.0 ],
									"style" : "",
									"text" : "Operation"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-13",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 184.0, 195.965515, 114.0, 51.0 ],
									"style" : "",
									"text" : "convert from a Max symbol to a string matrix",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-19",
									"items" : [ "strcat", ",", "strcmp" ],
									"maxclass" : "umenu",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 333.5, 161.13475, 100.0, 21.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"attr" : "op",
									"attrfilter" : [ "op" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-18",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 374.0, 189.13475, 249.0, 21.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-33",
									"items" : [ "23 cruMBL", ",", "CLUnky", ",", "noti cABL" ],
									"maxclass" : "umenu",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 29.212677, 162.273315, 100.0, 21.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-37",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 202.0, 383.615021, 110.0, 19.0 ],
									"style" : "",
									"text" : "strcmp 67 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-44",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 69.712677, 543.61499, 252.0, 19.0 ],
									"style" : "",
									"text" : "yknULC"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-47",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 69.712677, 195.965515, 109.0, 21.0 ],
									"style" : "",
									"text" : "jit.str.fromsymbol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-51",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 69.712677, 338.943298, 114.0, 21.0 ],
									"style" : "",
									"text" : "jit.str.op 1 char 12"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-52",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 69.712677, 502.61499, 93.0, 21.0 ],
									"style" : "",
									"text" : "jit.str.tosymbol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-53",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 178.0, 449.615021, 176.0, 21.0 ],
									"style" : "",
									"text" : "jit.print @title strtest @info 1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-60",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 641.0, 526.61499, 177.0, 36.0 ],
									"style" : "",
									"text" : "Original object code by Adam Florin. Thanks, Adam!"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-63",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 627.712646, 216.0, 325.0, 21.0 ],
									"style" : "",
									"text" : "strcat: (concatenate 2 strings)",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-66",
									"linecount" : 7,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 627.712646, 237.0, 337.0, 111.0 ],
									"style" : "",
									"text" : "strcmp: (compare 2 strings lexicographically). Returns the difference between the 2 characters at the point that the strings become dissimilar, plus the point at which the two strings diverge (e.g. comparing 'binky' with binko' causes the message 'strcmp 10 4' to be returned, since y is 10 characters \"bigger\" than o, and the comparison failed after 4 characters).",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-1",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 65.0, 604.0, 21.0 ],
									"style" : "",
									"text" : "jit.str.op also lets you perform comcatenation and comparison operations on two string matrices"
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"bgoncolor" : [ 0.55, 0.55, 0.55, 1.0 ],
									"fontface" : 1,
									"hint" : "",
									"id" : "obj-93",
									"ignoreclick" : 1,
									"legacytextcolor" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 339.011627, 134.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"style" : "",
									"text" : "1",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textoncolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ],
									"usebgoncolor" : 1,
									"usetextovercolor" : 1
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"bgoncolor" : [ 0.55, 0.55, 0.55, 1.0 ],
									"fontface" : 1,
									"hint" : "",
									"id" : "obj-16",
									"ignoreclick" : 1,
									"legacytextcolor" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 31.235901, 133.990936, 20.0, 20.0 ],
									"rounded" : 60.0,
									"style" : "",
									"text" : "2",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textoncolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ],
									"usebgoncolor" : 1,
									"usetextovercolor" : 1
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 383.5, 322.954407, 79.212677, 322.954407 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 383.5, 322.039032, 79.212677, 322.039032 ],
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-19", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 174.235901, 283.823059, 174.735901, 283.823059 ],
									"source" : [ "obj-22", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 79.212677, 208.43808, 79.212677, 208.43808 ],
									"source" : [ "obj-33", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-37", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 174.212677, 369.615021, 302.5, 369.615021 ],
									"source" : [ "obj-51", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-52", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-51", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-53", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 79.212677, 408.615021, 187.5, 408.615021 ],
									"source" : [ "obj-51", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 79.212677, 533.61499, 312.212677, 533.61499 ],
									"source" : [ "obj-52", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 20.0, 115.0, 93.0, 20.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p \"2-string ops\"",
					"varname" : "basic_tab[2]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 0,
							"revision" : 0,
							"architecture" : "x86",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 1142.0, 620.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-53",
									"ignoreclick" : 1,
									"jsarguments" : [ "jit.str.op" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 305.0, 55.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-54",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 65.0, 604.0, 21.0 ],
									"style" : "",
									"text" : "You can also work with 2d matrices. Each row is interpreted as a CR-terminated string"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-50",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 523.988403, 415.537933, 100.0, 21.0 ],
									"style" : "",
									"text" : "s 2d-slice"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-46",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 653.988403, 365.943298, 275.967834, 55.0 ],
									"style" : "",
									"text" : "You may create a 2D slice (only valid for 2D input) by specifying the slice as two coordinates (x y) for both start and end."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-39",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 96.712677, 323.0, 100.0, 21.0 ],
									"style" : "",
									"text" : "r 2d-slice"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-38",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 528.988403, 299.465515, 570.0, 55.0 ],
									"style" : "",
									"text" : "multiline_out will cause jit.str.op to convert any CR to the start of a new row in a 2D output matrix and output an 'expanded' 2D matrix. If disabled, a 'collapsed', single-row matrix is output. (default = 0)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-36",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 528.988403, 255.965515, 569.967834, 40.0 ],
									"style" : "",
									"text" : "multiline_in enables jit.str.op to work with 2D matrices, with each row interpreted as a CR-terminated string. If disabled, only the first row of an incoming 2D matrix is used."
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-1",
									"linecount" : 2,
									"maxclass" : "textedit",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "int", "", "" ],
									"outputmode" : 1,
									"parameter_enable" : 1,
									"patching_rect" : [ 69.712677, 169.990936, 127.0, 41.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "textedit",
											"parameter_shortname" : "textedit",
											"parameter_type" : 3,
											"parameter_initial_enable" : 1,
											"parameter_initial" : [ "Now", "is", "the", "winter", "of", "our", "discontent" ],
											"parameter_invisible" : 1
										}

									}
,
									"style" : "",
									"tabmode" : 0,
									"text" : "Now is the winter of our discontent",
									"textjustification" : 0,
									"varname" : "textedit"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-21",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 284.0, 425.537933, 162.0, 66.0 ],
									"style" : "",
									"text" : "strcmp and strlen return data, rather than strings. this information is sent via the dumpout outlet",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-20",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 165.011627, 498.61499, 164.0, 36.0 ],
									"style" : "",
									"text" : "convert from a string matrix to a Max symbol",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-11",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 511.0, 228.716309, 103.0, 25.0 ],
									"style" : "",
									"text" : "String length"
								}

							}
, 							{
								"box" : 								{
									"attr" : "dim",
									"attrfilter" : [ "dim" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-18",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 388.988373, 230.716309, 125.0, 21.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-23",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 109.034851, 144.856186, 229.976776, 21.0 ],
									"style" : "",
									"text" : "Click on the button"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-24",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 374.0, 144.856186, 145.976776, 21.0 ],
									"style" : "",
									"text" : "Choose an operation"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-27",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 635.0, 195.885544, 144.0, 25.0 ],
									"style" : "",
									"text" : "Operation"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-25",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 184.0, 251.965515, 114.0, 51.0 ],
									"style" : "",
									"text" : "convert from a Max symbol to a string matrix",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-26",
									"items" : [ "strrev", ",", "slice", ",", "strlen", ",", "toupper", ",", "tolower", ",", "thru" ],
									"maxclass" : "umenu",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 348.488373, 171.490936, 100.0, 21.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"attr" : "op",
									"attrfilter" : [ "op" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-28",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 388.988373, 199.490936, 249.0, 21.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-37",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 164.0, 425.537933, 110.0, 19.0 ],
									"style" : "",
									"text" : "strlen 9"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-44",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 69.712677, 554.61499, 252.0, 19.0 ],
									"style" : "",
									"text" : "Now is the winter of our discontent"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-47",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 69.712677, 251.965515, 109.0, 21.0 ],
									"style" : "",
									"text" : "jit.str.fromsymbol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-48",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 523.988403, 382.037933, 130.0, 19.0 ],
									"style" : "",
									"text" : "start 7 0, end 9 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-51",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 69.712677, 382.943298, 390.0, 21.0 ],
									"style" : "",
									"text" : "jit.str.op 2 char 24 @multiline_in 1 @multiline_out 1 @adapt 1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-52",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 69.712677, 513.61499, 93.0, 21.0 ],
									"style" : "",
									"text" : "jit.str.tosymbol"
								}

							}
, 							{
								"box" : 								{
									"attr" : "multiline_out",
									"attrfilter" : [ "multiline_out" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-6",
									"lock" : 1,
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 388.988373, 316.134766, 140.0, 21.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 69.712677, 219.924942, 109.0, 21.0 ],
									"style" : "",
									"text" : "route text"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 69.712677, 144.856186, 20.0, 20.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"attr" : "multiline_in",
									"attrfilter" : [ "multiline_in" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-9",
									"lock" : 1,
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 388.988373, 264.794342, 140.0, 21.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1013.956238, 334.493591, 20.0, 20.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"bgoncolor" : [ 0.55, 0.55, 0.55, 1.0 ],
									"fontface" : 1,
									"hint" : "",
									"id" : "obj-93",
									"ignoreclick" : 1,
									"legacytextcolor" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 354.0, 144.856186, 20.0, 20.0 ],
									"rounded" : 60.0,
									"style" : "",
									"text" : "1",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textoncolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ],
									"usebgoncolor" : 1,
									"usetextovercolor" : 1
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"bgoncolor" : [ 0.55, 0.55, 0.55, 1.0 ],
									"fontface" : 1,
									"hint" : "",
									"id" : "obj-35",
									"ignoreclick" : 1,
									"legacytextcolor" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 89.034851, 144.856186, 20.0, 20.0 ],
									"rounded" : 60.0,
									"style" : "",
									"text" : "2",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textoncolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ],
									"usebgoncolor" : 1,
									"usetextovercolor" : 1
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 398.488373, 366.954407, 79.212677, 366.954407 ],
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-28", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 398.488373, 366.039032, 79.212677, 366.039032 ],
									"source" : [ "obj-28", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 106.212677, 365.971649, 79.212677, 365.971649 ],
									"source" : [ "obj-39", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-50", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-48", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-37", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 450.212677, 413.615021, 264.5, 413.615021 ],
									"source" : [ "obj-51", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-52", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-51", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 79.212677, 544.61499, 312.212677, 544.61499 ],
									"source" : [ "obj-52", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 398.488373, 365.539032, 79.212677, 365.539032 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 398.488373, 366.868835, 79.212677, 366.868835 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 37.0, 146.0, 76.0, 20.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p multiline",
					"varname" : "basic_tab[1]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-1",
					"linecount" : 2,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 539.0, 244.0, 100.0, 34.0 ],
					"saved_object_attributes" : 					{
						"filename" : "helpstarter",
						"parameter_enable" : 0
					}
,
					"style" : "",
					"text" : "js helpstarter jit.str.op"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 0,
							"revision" : 0,
							"architecture" : "x86",
							"modernui" : 1
						}
,
						"rect" : [ 34.0, 104.0, 1142.0, 620.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-21",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 313.0, 405.037933, 162.0, 65.0 ],
									"style" : "",
									"text" : "strcmp and strlen return data, rather than strings. this information is sent via the dumpout outlet",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-20",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 150.011627, 516.61499, 164.0, 36.0 ],
									"style" : "",
									"text" : "convert from a string matrix to a Max symbol",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-17",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 344.011627, 478.615021, 261.0, 36.0 ],
									"style" : "",
									"text" : "Look in the Max window to see what's \"really happening.\"",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 484.0, 259.965515, 103.0, 25.0 ],
									"style" : "",
									"text" : "String length"
								}

							}
, 							{
								"box" : 								{
									"attr" : "dim",
									"attrfilter" : [ "dim" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-11",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 359.0, 261.965515, 125.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-8",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 612.712646, 426.943298, 294.0, 36.0 ],
									"style" : "",
									"text" : "thru: (properly truncate (if necessary) and pass string matrices",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-12",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 612.712646, 390.375916, 294.0, 36.0 ],
									"style" : "",
									"text" : "toupper and tolower: (uppercase/lowercase converters)",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-5",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 36.235901, 162.990936, 229.976776, 21.0 ],
									"style" : "",
									"text" : "Select a string and watch the fun"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-4",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 344.011627, 163.5, 145.976776, 21.0 ],
									"style" : "",
									"text" : "Choose an operation"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-27",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 608.0, 216.13475, 144.0, 25.0 ],
									"style" : "",
									"text" : "Operation"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-10",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 169.0, 224.965515, 114.0, 50.0 ],
									"style" : "",
									"text" : "convert from a Max symbol to a string matrix",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-19",
									"items" : [ "strrev", ",", "slice", ",", "strlen", ",", "toupper", ",", "tolower", ",", "thru" ],
									"maxclass" : "umenu",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 318.5, 190.13475, 100.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"attr" : "op",
									"attrfilter" : [ "op" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-18",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 359.0, 218.13475, 249.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-33",
									"items" : [ "23 cruMBL", ",", "CLUnky", ",", "noti cABL" ],
									"maxclass" : "umenu",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 14.212677, 191.273315, 100.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-37",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 187.0, 412.615021, 110.0, 23.0 ],
									"style" : "",
									"text" : "strlen 9"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-44",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 54.712677, 572.61499, 252.0, 23.0 ],
									"style" : "",
									"text" : "yknULC"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-47",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 54.712677, 224.965515, 109.0, 23.0 ],
									"style" : "",
									"text" : "jit.str.fromsymbol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-48",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 379.148193, 324.218536, 87.0, 23.0 ],
									"style" : "",
									"text" : "start 3, end 0"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-49",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 359.0, 296.702148, 87.0, 23.0 ],
									"style" : "",
									"text" : "start 1, end 3"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-51",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 54.712677, 367.943298, 114.0, 23.0 ],
									"style" : "",
									"text" : "jit.str.op 1 char 12"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-52",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 54.712677, 531.61499, 93.0, 23.0 ],
									"style" : "",
									"text" : "jit.str.tosymbol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-53",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "jit_matrix", "" ],
									"patching_rect" : [ 163.0, 478.615021, 176.0, 23.0 ],
									"style" : "",
									"text" : "jit.print @title strtest @info 1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-57",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 391.551575, 351.702148, 146.0, 36.0 ],
									"style" : "",
									"text" : "start and end are used by the slice function."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-60",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 626.0, 555.61499, 177.0, 36.0 ],
									"style" : "",
									"text" : "Original object code by Adam Florin. Thanks, Adam!"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-63",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 612.712646, 245.0, 323.0, 36.0 ],
									"style" : "",
									"text" : "jit.str.op performs several operations to single strings\n(for 2-string ops, see the next tab)",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-65",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 612.712646, 302.702148, 297.0, 50.0 ],
									"style" : "",
									"text" : "slice: (output an arbitary substring). The slice uses 2 attributes: start and end. You may place the end before the start to get a backward slice.",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-66",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 612.712646, 284.134766, 264.0, 21.0 ],
									"style" : "",
									"text" : "strrev: (reverse a string)",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpdetails.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "jit.str.op" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 620.0, 125.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-13",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 612.712646, 353.702148, 294.0, 36.0 ],
									"style" : "",
									"text" : "strlen: (get the length of a string [as distinct from its dimensions, which could be different])",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"bgoncolor" : [ 0.55, 0.55, 0.55, 1.0 ],
									"fontface" : 1,
									"hint" : "",
									"id" : "obj-93",
									"ignoreclick" : 1,
									"legacytextcolor" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 324.011627, 163.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"style" : "",
									"text" : "1",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textoncolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ],
									"usebgoncolor" : 1,
									"usetextovercolor" : 1
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"bgoncolor" : [ 0.55, 0.55, 0.55, 1.0 ],
									"fontface" : 1,
									"hint" : "",
									"id" : "obj-6",
									"ignoreclick" : 1,
									"legacytextcolor" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 16.235901, 162.990936, 20.0, 20.0 ],
									"rounded" : 60.0,
									"style" : "",
									"text" : "2",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textoncolor" : [ 1.0, 1.0, 1.0, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ],
									"usebgoncolor" : 1,
									"usetextovercolor" : 1
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 368.5, 351.954407, 64.212677, 351.954407 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 368.5, 351.039032, 64.212677, 351.039032 ],
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-19", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 64.212677, 237.43808, 64.212677, 237.43808 ],
									"source" : [ "obj-33", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 388.648193, 351.580933, 64.212677, 351.580933 ],
									"source" : [ "obj-48", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 368.5, 351.322723, 64.212677, 351.322723 ],
									"source" : [ "obj-49", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-37", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 159.212677, 398.615021, 287.5, 398.615021 ],
									"source" : [ "obj-51", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-52", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-51", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-53", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 64.212677, 437.615021, 172.5, 437.615021 ],
									"source" : [ "obj-51", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 64.212677, 562.61499, 297.212677, 562.61499 ],
									"source" : [ "obj-52", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 10.0, 85.0, 50.0, 20.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p basic",
					"varname" : "basic_tab"
				}

			}
, 			{
				"box" : 				{
					"border" : 0,
					"filename" : "helpname.js",
					"id" : "obj-4",
					"ignoreclick" : 1,
					"jsarguments" : [ "jit.str.op" ],
					"maxclass" : "jsui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 10.0, 10.0, 305.0, 55.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 0,
							"revision" : 0,
							"architecture" : "x86",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 1142.0, 620.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"showontab" : 1,
						"boxes" : [  ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 63.0, 175.0, 50.0, 20.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p ?",
					"varname" : "q_tab"
				}

			}
 ],
		"lines" : [  ],
		"parameters" : 		{
			"obj-3::obj-1" : [ "textedit", "textedit", 0 ]
		}
,
		"dependency_cache" : [ 			{
				"name" : "helpname.js",
				"bootpath" : "/Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
				"patcherrelativepath" : "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "helpdetails.js",
				"bootpath" : "/Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
				"patcherrelativepath" : "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "helpstarter.js",
				"bootpath" : "/Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
				"patcherrelativepath" : "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
 ],
		"embedsnapshot" : 0
	}

}
