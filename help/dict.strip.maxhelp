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
		"rect" : [ 100.0, 100.0, 702.0, 506.0 ],
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
		"showrootpatcherontab" : 0,
		"showontab" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-4",
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
						"rect" : [ 0.0, 26.0, 702.0, 480.0 ],
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
									"fontsize" : 12.0,
									"id" : "obj-14",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 85.0, 190.0, 265.0, 47.0 ],
									"style" : "",
									"text" : "This dict object clones the 'eventlist' dict to create a new dictionary.  We clone before stripping so we don't modify the source dict."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "dict.view",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 360.0, 335.0, 330.0, 130.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 4,
									"outlettype" : [ "dictionary", "", "", "" ],
									"patching_rect" : [ 360.0, 305.0, 117.0, 21.0 ],
									"saved_object_attributes" : 									{
										"embed" : 0,
										"parameter_enable" : 0
									}
,
									"style" : "",
									"text" : "dict stripped-event"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-11",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 360.0, 280.0, 120.0, 21.0 ],
									"style" : "",
									"text" : "route Events::1903"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-10",
									"maxclass" : "dict.view",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 20.0, 335.0, 330.0, 130.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 4,
									"outlettype" : [ "dictionary", "", "", "" ],
									"patching_rect" : [ 20.0, 305.0, 110.0, 21.0 ],
									"saved_object_attributes" : 									{
										"embed" : 0,
										"parameter_enable" : 0
									}
,
									"style" : "",
									"text" : "dict new-eventlist"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-8",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "dictionary", "" ],
									"patching_rect" : [ 20.0, 250.0, 138.0, 21.0 ],
									"style" : "",
									"text" : "dict.strip Events::1903"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-7",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 4,
									"outlettype" : [ "dictionary", "", "", "" ],
									"patching_rect" : [ 20.0, 205.0, 59.5, 21.0 ],
									"saved_object_attributes" : 									{
										"embed" : 0,
										"parameter_enable" : 0
									}
,
									"style" : "",
									"text" : "dict"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "dict.view",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 360.0, 135.0, 330.0, 130.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 20.0, 115.0, 64.0, 21.0 ],
									"style" : "",
									"text" : "loadbang"
								}

							}
, 							{
								"box" : 								{
									"data" : 									{
										"Events" : 										{
											"1903" : 											{
												"ID" : "1903",
												"SoundEvent" : "base_vo_fd",
												"Animation" : "",
												"SupaStartFrame" : "0",
												"Length" : "0",
												"SoundEventDesc" : "",
												"VoiceDirectorComments" : "",
												"Dialogscript" : "",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "",
														"EditorsNotes" : ""
													}

												}

											}
,
											"1979" : 											{
												"ID" : "1979",
												"SoundEvent" : "base_vo_fd_cas",
												"Animation" : "",
												"SupaStartFrame" : "0",
												"Length" : "0",
												"SoundEventDesc" : "",
												"VoiceDirectorComments" : "",
												"Dialogscript" : "",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "",
														"EditorsNotes" : ""
													}

												}

											}
,
											"1904" : 											{
												"ID" : "1904",
												"SoundEvent" : "base_vo_md",
												"Animation" : "",
												"SupaStartFrame" : "0",
												"Length" : "0",
												"SoundEventDesc" : "",
												"VoiceDirectorComments" : "",
												"Dialogscript" : "",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "",
														"EditorsNotes" : ""
													}

												}

											}
,
											"1980" : 											{
												"ID" : "1980",
												"SoundEvent" : "base_vo_md_cas",
												"Animation" : "",
												"SupaStartFrame" : "0",
												"Length" : "0",
												"SoundEventDesc" : "",
												"VoiceDirectorComments" : "",
												"Dialogscript" : "",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "",
														"EditorsNotes" : ""
													}

												}

											}
,
											"2074" : 											{
												"ID" : "2074",
												"SoundEvent" : "vo_bar_idle_highskill_waft_cm",
												"Animation" : "/objects/bar/a2o_bar_idle_highSkill_waft_x.mov",
												"SupaStartFrame" : "60",
												"Length" : "67",
												"SoundEventDesc" : "Sim wafts a scent into her nose. This is a closed mouth sound.",
												"VoiceDirectorComments" : "",
												"Dialogscript" : "",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "11/30/2012",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "11/16/2012",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "11/15/2012",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "11/15/2012",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "11/30/2012",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "11/16/2012",
														"EditorsNotes" : ""
													}

												}

											}
,
											"1862" : 											{
												"ID" : "1862",
												"SoundEvent" : "vo_bar_makedrink_react_approvalwink",
												"Animation" : "/objects/bar/a2o_bar_makeDrink_react_approvalFingerPointWink_x.mov",
												"SupaStartFrame" : "13",
												"Length" : "29",
												"SoundEventDesc" : "Sim approvingly makes a coy stk stk sound as they point and wink",
												"VoiceDirectorComments" : "Rerecord FC and MB -truncated files",
												"Dialogscript" : "",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "11/30/2012",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "11/16/2012",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "11/15/2012",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "11/15/2012",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "11/30/2012",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "11/16/2012",
														"EditorsNotes" : ""
													}

												}

											}
,
											"1159" : 											{
												"ID" : "1159",
												"SoundEvent" : "vo_bar_makedrink_shootthebreeze",
												"Animation" : "/objects/bar/a2o_bar_makeDrink_shootTheBreeze_fail_x.mov",
												"SupaStartFrame" : "4",
												"Length" : "139",
												"SoundEventDesc" : "'When Sim is at or behind the bar shooting the breeze, they make simple chit chat like, 'yeah, I know, this place used to be way more chill until that write up in the paper''",
												"VoiceDirectorComments" : "Rerecord FC and MB -truncated files. Rerecord FD and MD -truncated",
												"Dialogscript" : "'welb, berna giramool... chinebb'",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "11/30/2012",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "11/16/2012",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "11/15/2012",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "11/15/2012",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "11/30/2012",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "11/16/2012",
														"EditorsNotes" : ""
													}

												}

											}
,
											"1188" : 											{
												"ID" : "1188",
												"SoundEvent" : "vo_bar_makedrink_stir_highSkill_fail",
												"Animation" : "/objects/bar/a2o_bar_makeDrink_stir_highSkill_fail_x.mov",
												"SupaStartFrame" : "4",
												"Length" : "128",
												"SoundEventDesc" : "As Sim fails at stirring/balancing their drink from behind the bar, they hum confidently then say 'uh... oh...' as they lose balance and stirring stick falls out of shaker",
												"VoiceDirectorComments" : "",
												"Dialogscript" : " Sim fails at stirring/balancing their drink from behind the bar",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "9/11/2012",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "9/12/2012",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "9/11/2012",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "9/12/2012",
														"EditorsNotes" : ""
													}

												}

											}
,
											"1190" : 											{
												"ID" : "1190",
												"SoundEvent" : "vo_bar_makedrink_stir_highSkill_succ",
												"Animation" : "/objects/bar/a2o_bar_makeDrink_stir_highSkill_succeed_x.mov",
												"SupaStartFrame" : "4",
												"Length" : "105",
												"SoundEventDesc" : "As Sim succeeds at stirring/balancing their drink from behind the bar, they say 'huzzah' as they spin the shaker and complete the trick successfully and with flair",
												"VoiceDirectorComments" : "",
												"Dialogscript" : "Sim does a trick while behind the bar",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "9/11/2012",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "9/12/2012",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "9/11/2012",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "9/12/2012",
														"EditorsNotes" : ""
													}

												}

											}
,
											"1166" : 											{
												"ID" : "1166",
												"SoundEvent" : "vo_bar_makedrink_trick_blowsfireball_fail",
												"Animation" : "/objects/bar/a2o_bar_makeDrink_trick_blowsFireball_fail_x.mov",
												"SupaStartFrame" : "20",
												"Length" : "230",
												"SoundEventDesc" : "When Sim fails at performing a blow fire trick behind the bar, they say 'oh yeah!' in a cocky manner as they set up the trick, gulping sounds as they drink, then 'eegad! whoooaaa, whoooaaa' as they try to recover from the explosion",
												"VoiceDirectorComments" : "",
												"Dialogscript" : "",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "9/11/2012",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "9/12/2012",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "9/11/2012",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "9/12/2012",
														"EditorsNotes" : ""
													}

												}

											}
,
											"1168" : 											{
												"ID" : "1168",
												"SoundEvent" : "vo_bar_makedrink_trick_blowsfireball_succ",
												"Animation" : "/objects/bar/a2o_bar_makeDrink_trick_blowsFireball_succeed_x.mov",
												"SupaStartFrame" : "4",
												"Length" : "186",
												"SoundEventDesc" : "When Sim succeeds at performing a blow fire trick behind the bar, they say 'oh yeah!' in a cocky manner as they set up the trick, gulping sounds as they drink, then blowing sounds as they finish the trick successfully",
												"VoiceDirectorComments" : "",
												"Dialogscript" : "MC & FA 12/3 - there are some closed-mouth sounds in some of the takes -- please be on the lookout for them and cut them as you find them. ",
												"Takes" : "0",
												"Kill" : "False",
												"RecordWild" : "False",
												"RecordDates" : 												{
													"ca" : 													{
														"CharacterName" : "ca",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"cb" : 													{
														"CharacterName" : "cb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fa" : 													{
														"CharacterName" : "fa",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"fb" : 													{
														"CharacterName" : "fb",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"fc" : 													{
														"CharacterName" : "fc",
														"RecDate" : "9/11/2012",
														"EditorsNotes" : ""
													}
,
													"fd" : 													{
														"CharacterName" : "fd",
														"RecDate" : "9/12/2012",
														"EditorsNotes" : ""
													}
,
													"ma" : 													{
														"CharacterName" : "ma",
														"RecDate" : "",
														"EditorsNotes" : ""
													}
,
													"mb" : 													{
														"CharacterName" : "mb",
														"RecDate" : "9/11/2012",
														"EditorsNotes" : ""
													}
,
													"mc" : 													{
														"CharacterName" : "mc",
														"RecDate" : "12/3/2012",
														"EditorsNotes" : ""
													}
,
													"md" : 													{
														"CharacterName" : "md",
														"RecDate" : "9/12/2012",
														"EditorsNotes" : ""
													}

												}

											}

										}
,
										"Suffixes" : "ca, cb, fa, fb, fc, fd, ma, mb, mc, md",
										"ExportDate" : "12/11/2012"
									}
,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 4,
									"outlettype" : [ "dictionary", "", "", "" ],
									"patching_rect" : [ 20.0, 140.0, 149.0, 21.0 ],
									"saved_object_attributes" : 									{
										"embed" : 1,
										"parameter_enable" : 0
									}
,
									"style" : "",
									"text" : "dict eventlist @embed 1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-42",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 65.0, 273.0, 21.0 ],
									"style" : "",
									"text" : "working with hierarchical dictionaries"
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dict.strip" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 183.710938, 53.625 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-13", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-8", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-9", 0 ]
								}

							}
 ],
						"bgfillcolor_type" : "gradient",
						"bgfillcolor_color1" : [ 0.454902, 0.462745, 0.482353, 1.0 ],
						"bgfillcolor_color2" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"bgfillcolor_color" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"bgfillcolor_angle" : 270.0,
						"bgfillcolor_proportion" : 0.39
					}
,
					"patching_rect" : [ 20.0, 110.0, 75.0, 21.0 ],
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
					"text" : "p hierarchy",
					"varname" : "basic_tab[1]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 445.0, 350.0, 164.0, 21.0 ],
					"saved_object_attributes" : 					{
						"filename" : "helpstarter",
						"parameter_enable" : 0
					}
,
					"style" : "",
					"text" : "js helpstarter dict.strip"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
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
						"rect" : [ 100.0, 126.0, 702.0, 480.0 ],
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
									"id" : "obj-3",
									"linecount" : 9,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 355.0, 235.0, 240.0, 137.0 ],
									"style" : "",
									"text" : "While many dict objects create new dictionaries to represent their output, dict.strip simply removes the keys from the incoming dictionary and passes out a reference to that dictionary.\n\nThis is highly efficient, but may lead to side effects as detailed in the 'Dictionaries' vignette documentation."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-62",
									"linecount" : 4,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 55.0, 181.0, 112.0, 67.0 ],
									"style" : "",
									"text" : "cow : moo moo, sheep : baa baa, dog woof woof, bang"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-60",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "dictionary" ],
									"patching_rect" : [ 55.0, 255.0, 69.0, 23.0 ],
									"style" : "",
									"text" : "dict.group"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-59",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 195.0, 420.0, 124.0, 23.0 ],
									"style" : "",
									"text" : "print stripped_keys"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-56",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "dictionary", "" ],
									"patching_rect" : [ 55.0, 340.0, 159.0, 23.0 ],
									"style" : "",
									"text" : "dict.strip cow sheep"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-54",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 55.0, 420.0, 136.0, 23.0 ],
									"style" : "",
									"text" : "print unload_stripped"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-55",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 55.0, 390.0, 55.0, 23.0 ],
									"style" : "",
									"text" : "dict.iter"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-32",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 75.0, 310.0, 132.0, 23.0 ],
									"style" : "",
									"text" : "print unload_original"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-36",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 75.0, 285.0, 55.0, 23.0 ],
									"style" : "",
									"text" : "dict.iter"
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpdetails.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dict.strip" ],
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
									"border" : 0,
									"filename" : "helpargs.js",
									"id" : "obj-4",
									"ignoreclick" : 1,
									"jsarguments" : [ "dict.strip" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 220.0, 340.0, 140.286652, 39.0 ],
									"presentation_rect" : [ 220.0, 340.0, 140.286652, 39.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-36", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-54", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-55", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-55", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-56", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-59", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-56", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-36", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-60", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-56", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-60", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-60", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-62", 0 ]
								}

							}
 ],
						"bgfillcolor_type" : "gradient",
						"bgfillcolor_color1" : [ 0.454902, 0.462745, 0.482353, 1.0 ],
						"bgfillcolor_color2" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"bgfillcolor_color" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"bgfillcolor_angle" : 270.0,
						"bgfillcolor_proportion" : 0.39
					}
,
					"patching_rect" : [ 10.0, 85.0, 51.0, 21.0 ],
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
					"fontname" : "Arial",
					"fontsize" : 13.0,
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
						"rect" : [ 0.0, 26.0, 702.0, 480.0 ],
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
						"boxes" : [  ],
						"lines" : [  ],
						"bgfillcolor_type" : "gradient",
						"bgfillcolor_color1" : [ 0.454902, 0.462745, 0.482353, 1.0 ],
						"bgfillcolor_color2" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"bgfillcolor_color" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"bgfillcolor_angle" : 270.0,
						"bgfillcolor_proportion" : 0.39
					}
,
					"patching_rect" : [ 30.0, 135.0, 50.0, 21.0 ],
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
					"text" : "p ?",
					"varname" : "q_tab"
				}

			}
 ],
		"lines" : [  ],
		"dependency_cache" : [ 			{
				"name" : "helpargs.js",
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
, 			{
				"name" : "helpname.js",
				"bootpath" : "/Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
				"patcherrelativepath" : "../../../../../../Applications/Max 7/Max.app/Contents/Resources/C74/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
 ],
		"embedsnapshot" : 0
	}

}
