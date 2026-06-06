# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\KingSlayer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\KingSlayer_autogen.dir\\ParseCache.txt"
  "KingSlayer_autogen"
  )
endif()
