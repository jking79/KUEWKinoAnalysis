#!/usr/bin/python

import sys 
import os
#input arguments python.py arg1= bg2016, bg2017, sms   arg2= input file list, arg3= outputpath/name.root

bg2016 = False;
bg2017 = False;
sms = False;


print "input",  str(sys.argv)
args = sys.argv
print str(args[1])

if str(args[1]) == 'bg2016':
	bg2016 = True
if str(args[1]) == 'bg2017':
	bg2017 = True
if str(args[1]) == 'sms':
	sms = True

path = ''


# path to the ewkino skims
if bg2017 == True:
	path = '/home/t3-ku/janguian/stopNtuple_Skims/All_Bkg_2017/' 
elif bg2016 == True:
	path = '/home/t3-ku/janguian/stopNtuple_Skims/All_Bkg_2016/'
elif sms == True:
	path = '/home/t3-ku/janguian/stopNtuple_Skims/All_Sig/'


print "path selected: ", path

flist = open(str(args[2]),"r")
files = flist.readlines()

print "input files from: ", path+str(args[2])
#print files

cmd = "hadd -f "+str(args[3])
for fin in files:
	cmd = cmd +" "+path+fin.rstrip()

print cmd 
os.system(cmd)


