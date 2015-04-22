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
		"rect" : [ 68.0, 89.0, 748.0, 587.0 ],
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
					"id" : "obj-1",
					"linecount" : 2,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 362.0, 131.0, 100.0, 34.0 ],
					"saved_object_attributes" : 					{
						"filename" : "helpstarter",
						"parameter_enable" : 0
					}
,
					"style" : "",
					"text" : "js helpstarter jit.split"
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
						"rect" : [ 68.0, 115.0, 748.0, 561.0 ],
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
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 516.259644, 146.0, 183.0, 25.0 ],
									"style" : "",
									"text" : "Clear matrix after output"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-8",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 516.259644, 234.5, 183.0, 40.0 ],
									"style" : "",
									"text" : "The point BEFORE which the split will be made"
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
									"patching_rect" : [ 516.259644, 202.0, 183.0, 25.0 ],
									"style" : "",
									"text" : "Dimension to split across"
								}

							}
, 							{
								"box" : 								{
									"attr" : "splitpoint",
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-7",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 366.259644, 244.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"attr" : "autoclear",
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-6",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 366.259644, 146.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"attr" : "splitdim",
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-5",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 366.259644, 204.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bgmode" : 0,
									"border" : 0,
									"clickthrough" : 0,
									"enablehscroll" : 0,
									"enablevscroll" : 0,
									"id" : "obj-4",
									"lockeddragscroll" : 0,
									"maxclass" : "bpatcher",
									"name" : "demovideo.maxpat",
									"numinlets" : 0,
									"numoutlets" : 1,
									"offset" : [ 0.0, 0.0 ],
									"outlettype" : [ "jit_matrix" ],
									"patching_rect" : [ 32.0, 137.59375, 230.0, 125.0 ],
									"viewvisibility" : 1
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-17",
									"maxclass" : "jit.fpsgui",
									"mode" : 3,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 208.0, 481.0, 80.0, 36.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-18",
									"maxclass" : "jit.fpsgui",
									"mode" : 3,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 32.0, 481.0, 80.0, 36.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-19",
									"items" : [ 0, "-", "horizontal", "(dim[0])", ",", 1, "-", "vertical", "(dim[1])", ",", 2, "-", "dim[2]", ",", 3, "-", "dim[3]", ",", 4, "-", "dim[4]", ",", 5, "-", "dim[5]", ",", 6, "-", "dim[6]", ",", 7, "-", "dim[7]", ",", 8, "-", "dim[8]", ",", "etc." ],
									"maxclass" : "umenu",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 366.259644, 177.46875, 165.118256, 23.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "umenu",
											"parameter_shortname" : "umenu",
											"parameter_type" : 3,
											"parameter_initial_enable" : 1,
											"parameter_initial" : [ 0 ],
											"parameter_invisible" : 1
										}

									}
,
									"style" : "",
									"varname" : "umenu"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-31",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "jit_matrix", "jit_matrix", "" ],
									"patching_rect" : [ 32.0, 295.0, 371.0, 23.0 ],
									"style" : "",
									"text" : "jit.split @splitdim 2 @splitpoint 160 @autoclear 1"
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpdetails.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "jit.split" ],
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
									"background" : 1,
									"id" : "obj-29",
									"maxclass" : "jit.pwindow",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 208.0, 352.0, 160.0, 120.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"id" : "obj-30",
									"maxclass" : "jit.pwindow",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 32.0, 352.0, 160.0, 120.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 217.5, 331.0, 217.5, 331.0 ],
									"source" : [ "obj-31", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-30", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 41.5, 337.0, 41.5, 337.0 ],
									"source" : [ "obj-31", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 375.759644, 279.5, 41.5, 279.5 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 375.759644, 279.5, 41.5, 279.5 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-31", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 375.759644, 278.5, 41.5, 278.5 ],
									"source" : [ "obj-7", 0 ]
								}

							}
 ],
						"bgfillcolor_type" : "gradient",
						"bgfillcolor_color1" : [ 0.435294, 0.462745, 0.498039, 1.0 ],
						"bgfillcolor_color2" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"bgfillcolor_color" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"bgfillcolor_angle" : 270.0,
						"bgfillcolor_proportion" : 0.39
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
					"jsarguments" : [ "jit.split" ],
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
						"rect" : [ 0.0, 26.0, 748.0, 561.0 ],
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
						"lines" : [  ],
						"bgfillcolor_type" : "gradient",
						"bgfillcolor_color1" : [ 0.435294, 0.462745, 0.498039, 1.0 ],
						"bgfillcolor_color2" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"bgfillcolor_color" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"bgfillcolor_angle" : 270.0,
						"bgfillcolor_proportion" : 0.39
					}
,
					"patching_rect" : [ 205.0, 205.0, 50.0, 20.0 ],
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
			"obj-2::obj-19" : [ "umenu", "umenu", 0 ],
			"obj-2::obj-4::obj-4::obj-20" : [ "live.tab[1]", "live.tab[1]", 0 ],
			"obj-2::obj-4::obj-4::obj-18" : [ "number[1]", "number[1]", 0 ],
			"obj-2::obj-4::obj-4::obj-21" : [ "number", "number", 0 ]
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
				"name" : "demovideo.maxpat",
				"bootpath" : "/Volumes/Underdog/max/maxmsp-misc/help/jitter-help",
				"patcherrelativepath" : ".",
				"type" : "JSON",
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
