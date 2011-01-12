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
