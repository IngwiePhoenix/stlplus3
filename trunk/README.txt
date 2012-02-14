STLplus
-------

STLplus was originally intended as a library to extend the STL by
providing missing container data structures such as smart-pointers,
matrices, trees and graphs.

On the way it became a collection point for other general-purpose
code. The most significant of these is the data persistance functions
which allow any C++ data structure to be made serialisable.

Since v3.0 the library has been split into a collection of 5
libraries. The idea is that some of these can be used stand-alone. For
example, the extension data structures can be used without the rest of
STLplus by just using the containers library.

Changes and Versions
--------------------

For details of the different versions and the changes between them,
see http://stlplus.sourceforge.net/stlplus3/docs/changes.html.

You can also access the STLplus library using CVS.

Directory Structure
-------------------

This directory is for implementing STLplus as a library collection. The
libraries are to be found in the directories:

          containers
          persistence
          portability
          strings
          subsystems

The documentation is in the 'docs' directory and starts with index.html.

Build files for IDEs are found in the 'ide' directory, but the gcc
command-line tools use make.

Gcc Build
---------

The Makefile requires the makefiles project, which is available from
the same SourceForge site that you downloaded the STLplus library
from. Follow the "View all Files" link - sadly SourceForge don't give
a way of providing two download buttons.

Multi-Library Build
-------------------

To build the STLplus3 library collection as 5 separate libraries, use
either make at the top level for gcc, or the project files in the
'ide/' directory for Borland or Microsoft compilers.

Monolithic Build
----------------

The 'source' directory is provided with script files that allow the library
collection to be merged into one large library - termed the monolithic build.

Run the make_monolithic script from within the source directory
(i.e. from a command shell).

To build the monolithic STLplus3 library, use either make in the
source directory for gcc, or the project files ending in '_monolithic'
in the 'ide/' directory for Borland or Microsoft compilers.
