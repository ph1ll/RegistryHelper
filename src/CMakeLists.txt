add_library(RegistryHelper
    RegistryHelper.cpp
    RegistryHelperInternal.cpp
    RegistryKeyHelper.cpp
)

target_include_directories(RegistryHelper
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(RegistryHelper
    PUBLIC
    PRIVATE
        ktmw32
)

target_compile_definitions(RegistryHelper
    PRIVATE
        UNICODE
)
