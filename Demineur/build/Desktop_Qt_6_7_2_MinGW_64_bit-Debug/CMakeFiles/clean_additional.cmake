# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DemineurConsole_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DemineurConsole_autogen.dir\\ParseCache.txt"
  "DemineurConsole_autogen"
  )
endif()
