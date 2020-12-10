# CMakeList.txt : Top-level CMake project file, do global configuration and include sub-projects here
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(N4S)

# Find Geant4 package
option(WITH_GEANT4_UIVIS "Add Geant4 UI" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

# Locate sources and headers for this project
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Add the executable, and link it to the Geant4 libraries
add_executable(N4S N4S.cc ${sources} ${headers})
target_link_libraries(N4S ${Geant4_LIBRARIES} )

# Copy all scripts to the build directory
set(n4s_SCRIPTS
  )

foreach(_script ${n4s_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()