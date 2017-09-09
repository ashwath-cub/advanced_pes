#!/usr/bin/env python
# Author: Ashwath Gundepally, CU, ECEE
#
# Name: find_sys_info.py
#
# Description: Finds some sys_info and writes to a file sys_info.txt
#              in the same directory.

import subprocess   #module helps execute shell commands in python



sys_info_file_name="sys_info.txt"
os_version_info="/proc/version"
os_distro_info_file="/etc/lsb-release"



file_to_write=open(sys_info_file_name, "w")

os_type_version_info=open(os_version_info, "r")

file_to_write.write("OS Type: ")
version_info_string=os_type_version_info.read()
version_info_list=version_info_string.split(" ")
file_to_write.write(version_info_list[0])   #OS type written


file_to_write.write("\nOS Distro: ")
os_distro_info_file_obj=open(os_distro_info_file, "r")
distro_info=os_distro_info_file_obj.read()
distro_info=distro_info.split("\n")
distro_name=distro_info[3].split("=")
file_to_write.write(distro_name[1])         #distro name written

#OS version info
file_to_write.write("\n"+version_info_list[1]+ ": "+ version_info_list[2]) 

#gcc build version info 
file_to_write.write("\nKernel GCC build version info: "+version_info_list[6]+" "+version_info_list[7])

file_to_write.write("\nKernel build time: ")

for x in range(13,19):
    file_to_write.write(version_info_list[x]+" ")

#sys arch info, calling lscpu using the subprocess module
lscpu_call=subprocess.check_output("lscpu")

lscpu_call_list=lscpu_call.split("\n")

file_to_write.write("\nSystem Architecture info:\n")
for x in range(0,4):
    file_to_write.write(lscpu_call_list[x]+"\n")

file_to_write.close()

