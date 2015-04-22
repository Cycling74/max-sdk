{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 176.0, 51.0, 806.0, 765.0 ],
		"bglocked" : 0,
		"defrect" : [ 176.0, 51.0, 806.0, 765.0 ],
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
		"metadata" : [  ],
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : ";\rmax db.addmetadata 01iMIDIBasics patcher tag MIDI",
					"linecount" : 2,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 395.0, 325.0, 0.0, 0.0 ],
					"patching_rect" : [ 395.0, 325.0, 282.0, 29.0 ],
					"id" : "obj-8",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : ";\rmax db.addmetadata kazoo patcher tag MIDI",
					"linecount" : 2,
					"outlettype" : [ "" ],
					"patching_rect" : [ 395.0, 240.0, 240.0, 29.0 ],
					"id" : "obj-7",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : ";\rmax db.addmetadata seq object tag MIDI",
					"linecount" : 2,
					"outlettype" : [ "" ],
					"patching_rect" : [ 395.0, 200.0, 221.0, 29.0 ],
					"id" : "obj-6",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "add some metadata to an object in the database, and the dbview will receive a notification and automatically update, thus updating the dbviewer.",
					"linecount" : 3,
					"frgb" : [ 0.658824, 0.658824, 0.658824, 1.0 ],
					"patching_rect" : [ 395.0, 105.0, 303.0, 43.0 ],
					"id" : "obj-9",
					"fontname" : "Verdana",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : ";\rmax db.addmetadata borax object tag MIDI",
					"linecount" : 2,
					"outlettype" : [ "" ],
					"patching_rect" : [ 395.0, 160.0, 232.0, 29.0 ],
					"id" : "obj-5",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "query \"SELECT object_name,class,data FROM metadata WHERE class='tag' AND data='MIDI'\"",
					"outlettype" : [ "" ],
					"patching_rect" : [ 195.0, 45.0, 484.0, 17.0 ],
					"id" : "obj-4",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "dbviewer",
					"outlettype" : [ "" ],
					"database" : "__max5db__",
					"patching_rect" : [ 20.0, 75.0, 363.0, 676.0 ],
					"id" : "obj-1",
					"color" : [ 1.0, 1.0, 1.0, 1.0 ],
					"numinlets" : 1,
					"query" : "SELECT * FROM metadata",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "query \"SELECT * FROM metadata\"",
					"outlettype" : [ "" ],
					"patching_rect" : [ 165.0, 15.0, 184.0, 17.0 ],
					"id" : "obj-3",
					"fontname" : "Verdana",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "database __max5db__",
					"outlettype" : [ "" ],
					"patching_rect" : [ 20.0, 15.0, 125.0, 17.0 ],
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
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
