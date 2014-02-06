#!/usr/bin/env python

import sys, os, string, shutil, re

files = []
for f in range(len(sys.argv)):
	if f<2:
		continue
	files.append(sys.argv[f])

#first argument is type
type = sys.argv[1]

#fileNames = ["w","z","diboson"]
#fileNames = ["j","bb"]
#fileNames = ["tt","ttl","zee","zmumu","ztt","wenu","wmunu","wtaunu","jpyt"]


postFix = "COMB"
path = "/u1/phansson/jetmetbtag/FlatAna/trunk/utils"
for file in files:
	command = "python " + path + "/mergeRootFiles.py" + " " +file + " " + type + " " + file + postFix + "." + type + ".root"
	print "executing command: ", command, "\n"
	os.system(command)



