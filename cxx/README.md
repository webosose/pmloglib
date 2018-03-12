PmLogLib
========

Summary
-------
C++ wrapper for the Open webOS logging library

Dependencies
==============

Below is the component required to build PmLogLibCpp:

- PmLogLib

Linking against library
========================
To link against PmLogLibCpp library it's possible to use standart cmake procedure:

include(FindPkgConfig)
pkg_check_modules(PMLOGLIB++ REQUIRED PmLogLibCpp)
include_directories(${PMLOGLIB++_INCLUDE_DIRS})
add_executable(main ${SOURCES})
target_link_libraries(main ${PMLOGLIB++_LDFLAGS})

For more information about library usage look at the
https://wiki.lgsvl.com/display/webOSDocs/pmlogcpp+v1.0

# Copyright and License Information

Unless otherwise specified, all content, including all source code files and
documentation files in this repository are:

Copyright (c) 2015 LG Electronics, Inc.

Unless otherwise specified or set forth in the NOTICE file, all content,
including all source code files and documentation files in this repository are:
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this content except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
