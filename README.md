# Installation Guide

## Minimum Requirements
### Processor
Recommended: Any member of the Intel Core, Xeon, or Xeon Phi processor family

Supported: Any member of the Intel Pentium 4 processor family, or any non-Intel processor architecture

### RAM
Please use at least 4GB of RAM to ensure a good runtime speed. The user’s mileage may vary.

### Operating System
Arch Linux
MacOS 10.12, 10.13

### Compiler
For Linux-based operating systems, please use one of the following compilers:

- Standard GCC version provided by your operating system, preferably versions 4.1-7.1
- GLIBC versions 2.4-2.19

### Available HDD space

20gb of space should be available for this program to run optimally.

## Installation
NOTE: You may have to enable audio on the VirtualBox Image if using one; if so, follow the steps after the installation steps:

Download the compressed application archive.

Move the archive to where you’d like to install the application; replacing “some/path/” with the desired installation path:

` > mv TeamA.tgz some/path/ `

Navigate to the directory containing the compressed application file; replacing “some/path/” with the path to the directory containing the TeamA.tgz file:

` > cd some/path/ `

Decompress the archive using tar:

` tar -xvzf TeamA.tgz `

Navigate into the application directory:

` > cd project2/ `

Run the precompiled executable:
	
` > ./ImagesToWavetables `

## Enabling Audio in Arch Guest (CIS Image)
Install the ALSA Utilities package to get alsactl and alsamixer:

` > sudo pacman -S alsa-utils `

Configure ALSA for the guest’s virtual audio devices:

` > sudo alsactl init `
` > sudo alsactl store `

Enable audio on the master chanel, open alsamixer and raise the volume of “master” using the arrow keys:
	
` > alsamixer `

Test the guest’s audio:
		
` > speaker-test `

-----

Disclaimer:
This project was done for CIS 422 in Winter 2018 at the University of Oregon, and was completed by a team of six of which I was a member. 

Due to hardware failure and no longer being able to access the BitBucket repository we originally used, the code hosted here was copied from a backup of the final verison another team member had.

All files here were copied from this repository with the owner's permission: 
https://github.com/Touchette/Images-to-Wavetables
