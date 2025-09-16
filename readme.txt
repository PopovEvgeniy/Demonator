                       Demonator
                          
                       Version 0.9.4.1

            DemonStar resource extraction tool by Popov Evgeniy Alekseyevich

The program description.

Demonstar is a cool scroll shooter. This game stores resources in GLB pseudo-archives.
Do you want to extract the files from these pseudo-archives? You can use my software for doing it.
This program takes a target file name and an output path as the command-line arguments.
Always add a directory separator (\ or /) at the end of the output path.

Exit codes.

0: The operation was successfully completed.
1: Can't open the input file.
2: Can't create the output file.
3: Can't jump to the target offset.
4: Can't allocate memory.
5: The invalid format.

License.

This program is distributed under the GNU GENERAL PUBLIC LICENSE.

The source code.

The source code was compiled under Open Watcom.
But you can compile it with any modern C compiler.
The source code can be compiled for a wide range of operating systems, but you need to create a makefile or a build script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux.

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Version history.

0.1: The initial version.
0.2-0.4: The small changes.
0.5: The small bug has been fixed.
0.6-0.8.3: The small changes.
0.8.3.1-0.8.3.2: The makefile has been updated.
0.8.3.3: The documentation has been updated.
0.8.4-0.8.9: The small changes.
0.9: Visual C++ support has improved.
0.9.0.1: The documentation has been updated.
0.9.1: The small changes.
0.9.1.1-0.9.1.2: The documentation has been updated.
0.9.2: The source code was recompiled under Tiny C Compiler.
0.9.3: The small changes.
0.9.3.1: The documentation has been updated.
0.9.4: The small changes.
0.9.4.1: The documentation has been updated.