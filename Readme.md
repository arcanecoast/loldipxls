DIP <=> XLS for Lands of Lore: The Throne of Chaos
==================================================

Author: metamaker

This application enables user to write .DIP files content from game's STARTUP.PAK to 
.XLS file and write changes back from .XLS to that .DIP files.

How to use the application
--------------------------

This is console application. The syntax is next:

Usage: loldipxls <<command>> <<filename.xls>>

Available commands:
- toxls -- extract all .DIPs' strings to <<filename.xls>>
- fromxls -- update all .DIPs with strings from <<filename.xls>>

Building the application
------------------------

You need CMake (<http://www.cmake.org/>) to build this application. The below example of how to build it is for
Visual Studio's nmake but you can use pretty same sequence for any other generator. Building steps are next:

1. Open command line and change current directory with **cd** command to the directory where you unpacked loldipxls source code.
2. Create new empty directory **build** and change your working directory to it by running **mkdir build**, **cd build**.
3. Run **cmake -G "NMake Makefiles" ..** to create Makefile.
4. Run **nmake** to build the library.

Dependencies
------------

The application depends on:
- lollibs (<https://github.com/metamaker/lollibs>)
- ExcelFormat (<http://www.codeproject.com/Articles/42504/ExcelFormat-Library>)

License agreement
-----------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as published
by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
 
Release history
---------------

03.03.2015:
- Initial release
