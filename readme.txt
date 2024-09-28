                       Demonator
                          
                       Version 0.9.1

            Resource extraction tool for DemonStar by Popov Evgeniy Alekseyevich

System requirements

64 kilobytes of free space on storage media. 

Description and usage

Demonstar is a cool scroll shooter. This game stores resources in GLB pseudo–archives.
Do you want to extract files from this pseudo–archive? You can use my software for doing it.
This program takes a target file name and an output path as the command-line arguments.
Always add a directory separator (\ or /) at the end of the output path.

Exit codes

0 - Operation was successfully completed.
1 - Can't open the input file.
2 - Can't create the output file.
3 - Can't jump to the target offset.
4 - Can't allocate memory.
5 - Invalid format.

License

This program is distributed under GNU GENERAL PUBLIC LICENSE.

Compatibility

This software successfully tested with the following games:

DemonStar
DemonStar Secret Missions 1
DemonStar Secret Missions 2

Source code

The source code was compiled under Open Watcom.
But you can compile it under any modern C compiler.
The source code can be compiled for a wide range of operating systems, but you need to create a makefile or a build script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Contact

You can send me a letter at tuzik87@inbox.ru.

Version history

0.1 – Initial version.
0.2 – 0.4 – Small changes.
0.5 – Small bug fixed.
0.6 – 0.8.3 – Small changes.
0.8.3.1 – 0.8.3.2 – Makefile updated.
0.8.3.3 – Documentation updated.
0.8.4 – 0.8.9 – Small changes.
0.9 – Visual C++ support improved.
0.9.0.1 – Documentation updated.
0.9.1 – Small changes.