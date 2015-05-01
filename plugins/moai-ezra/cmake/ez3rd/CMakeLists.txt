cmake_minimum_required ( VERSION 2.8.11 )

project ( ez3rd )
set ( EZ3RD_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../ez3rd/" )
set ( EZ3RD_INCLUDES "${EZ3RD_SOURCE_DIR}" )    

file ( GLOB_RECURSE EZ3RD_SOURCES "${EZ3RD_SOURCE_DIR}/*.cpp")
file ( GLOB_RECURSE EZ3RD_HEADERS  "${EZ3RD_INCLUDES}/*.h")


add_library( ez3rd STATIC ${EZ3RD_SOURCES} ${EZ3RD_HEADERS} "${EZ3RD_SOURCE_DIR}/../.." ) 
target_include_directories ( ez3rd PUBLIC ${EZ3RD_INCLUDES})
set_target_properties( ez3rd PROPERTIES FOLDER Third-Party )



