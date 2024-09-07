# Find all module interface files
file(GLOB_RECURSE MODULE_FILES "${CMAKE_SOURCE_DIR}/src/*.ixx")

# Create a custom target to build the modules
add_custom_target(build_modules)

foreach(MODULE_FILE ${MODULE_FILES})
    get_filename_component(MODULE_NAME ${MODULE_FILE} NAME_WE)
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/gcm.cache/${MODULE_NAME}.gcm
        COMMAND ${CMAKE_CXX_COMPILER} -std=c++20 -fmodules-ts -x c++ -c ${MODULE_FILE} -o ${CMAKE_BINARY_DIR}/gcm.cache/${MODULE_NAME}.gcm
        DEPENDS ${MODULE_FILE}
        COMMENT "Building module ${MODULE_NAME}"
    )
    add_custom_target(${MODULE_NAME}_module DEPENDS ${CMAKE_BINARY_DIR}/gcm.cache/${MODULE_NAME}.gcm)
    add_dependencies(build_modules ${MODULE_NAME}_module)
endforeach()

# Make MODULE_FILES available to the parent scope
set(MODULE_FILES ${MODULE_FILES} PARENT_SCOPE)