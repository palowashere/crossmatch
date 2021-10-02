cmake_minimum_required(VERSION 3.6)
project(crossmatch)

find_package(retdec 4.0 REQUIRED 
   COMPONENTS 
      retdec 
      llvm
)

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Werror)
endif()

set(CROSSMATCH_SRC 
    src/Main.cpp
    src/Crossmatch.cpp
    src/Function.cpp
    src/Log.cpp
    src/Program.cpp
    src/StructuralAnalysis.cpp
    src/Config.cpp
    src/Utility.cpp
    src/Graph.cpp
    src/Dominator.cpp
)

include_directories(include/)
add_executable(crossmatch ${CROSSMATCH_SRC})
target_link_libraries(crossmatch 
   retdec::retdec
   retdec::deps::llvm
)