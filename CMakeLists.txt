cmake_minimum_required(VERSION 3.12...3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(RegistryHelper 
            VERSION 1.0
            DESCRIPTION "Registry helpers for DllRegisterServer and DllUnregisterServer"
            LANGUAGES CXX)

# Add clang-tidy if available
find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
)
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*")
endif()

add_subdirectory(src)
