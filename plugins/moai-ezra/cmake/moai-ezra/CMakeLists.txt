cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-ezra )    


  set ( MOAI_EZRA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../moai-ezra" )  


  # Use all cpp files in directory as source code          
 # file ( GLOB MOAI_EZRA_SRC "${MOAI_EZRA_DIR}/*.cpp" "${MOAI_EZRA_DIR}/*.h" )
  
file ( GLOB_RECURSE MOAI_EZRA_SRC "${MOAI_EZRA_DIR}/*.cpp"
"${MOAI_EZRA_DIR}/layers/*.cpp"
"${MOAI_EZRA_DIR}/mesh/*.cpp"
"${MOAI_EZRA_DIR}/shell/*.cpp"
"${MOAI_EZRA_DIR}/tasks/*.cpp"
)  
  
  
  
file ( GLOB_RECURSE MOAI_EZRA_HEADERS "${MOAI_EZRA_DIR}/*.h"
"${MOAI_EZRA_DIR}/layers/*.h"
"${MOAI_EZRA_DIR}/mesh/*.h"
"${MOAI_EZRA_DIR}/shell/*.h"
"${MOAI_EZRA_DIR}/tasks/*.h"
)
  
  
  

  add_library ( moai-ezra STATIC ${MOAI_EZRA_SRC} ${MOAI_EZRA_HEADERS} )

  target_include_directories (moai-ezra PUBLIC ${MOAI_EZRA_DIR} "${MOAI_EZRA_DIR}/../")

  target_link_libraries ( moai-ezra moai-sim moai-core moai-util ez3rd zlcore )
  
  set_target_properties(moai-ezra PROPERTIES FOLDER Modules)


