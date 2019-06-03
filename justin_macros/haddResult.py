

import sys 
import os
import subprocess
#input arguments  arg1 = input path, arg 2 = output path
#notes for input path, this is the path to the directory the result root files are stored in
# this script will LS that directory to get the list of files, nothing else must be in the directory

def bash( bashCommand ):
	process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
	#process = subprocess.Popen(bashCommand.split())
	output, error = process.communicate()
	return output ,error

print "input",  str(sys.argv)
args = sys.argv
#print str(args[1])

cmd = "ls "+ str(args[1])
LS = bash(cmd)
LS = LS[0].split('\n')
LS = [f for f in LS if ".root" in f]

print "combining files: ", LS

cmd = "hadd -f "+str(args[2])
for fin in LS:
	cmd = cmd +" "+str(args[1])+fin.rstrip()
print cmd
os.system(cmd)
