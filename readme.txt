                       Demonator
                          
                       Version 0.9

            Resource extraction tool for DemonStar by Popov Evgeniy Alekseyevich

System requirement

64 kilobytes free space on storage media. 

Description and usage

Demonstar is a cool scroll-shooter. This game store resources in GLB pseudo-archives.
Do you want to extract files from this pseudo-archives? You can use my software for doing it.
This program takes a target file name and output path as command line arguments.
Always add directory separator(\ or /) at an end of output path.

Exit codes

0 - Operation successfully complete.
1 - Can't open input file.
2 - Can't create output file.
3 - Can't jump to target offset.
4 - Can't allocate memory.
5 - Invalid format.

License

This program distributed under GNU GENERAL PUBLIC LICENSE.

Compatibility

This software successfully tested with follow games:

DemonStar
DemonStar Secret Missions 1
DemonStar Secret Missions 2

Source code

The source code compiled under Open Watcom.
But you can compile it under any modern C compiler.
Source code can be compiled for wide range of operating systems, but you need to create makefile or build script by yourself.
I provide only two things: compiled the binary file for Windows and makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1.Extract content of source code archive.
2.Open terminal and go to source code directory.
3.
Run as root for installation: make install
Run as root for uninstall: make uninstall

Contact

You can send me a letter to tuzik87@inbox.ru.

Version history

0.1 - Initial version.
0.2 - 0.4 - Small changes.
0.5 - Small bug fixed.
0.6 - 0.8.3 - Small changes.
0.8.3.1 - 0.8.3.2 - Makefile updated.
0.8.3.3 - Documentation updated.
0.8.4 - 0.8.9 - Small changes.
0.9 - Visual C++ support improved.