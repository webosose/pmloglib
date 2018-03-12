# Copyright (c) 2015-2018 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

project(PmLogLibCpp CXX)

# We should unset these flags manually here, so that the visibility of the
# dynamic symbols exported by the library isn't affected by outer --version-script
# linker flag, also for preventing --std=c99 to be passed to c++ library.
unset(CMAKE_CXX_FLAGS)
unset(CMAKE_C_FLAGS)

# restore needed flags from outer library
webos_include_install_paths()
webos_add_linker_options(ALL --no-undefined)
webos_add_compiler_flags(ALL --std=c++11)

webos_build_pkgconfig(${CMAKE_SOURCE_DIR}/files/pkgconfig/PmLogLibCpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(PmLogLibCpp SHARED PmLog.cpp)
target_link_libraries(PmLogLibCpp ${CMAKE_PROJECT_NAME})
webos_build_library(NAME PmLogLibCpp NOHEADERS)
install(FILES PmLog.h DESTINATION @WEBOS_INSTALL_INCLUDEDIR@)
