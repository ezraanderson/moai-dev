cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-voxel )    


  set ( MOAI_VOXEL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../moai-voxel" )  


  # Use all cpp files in directory as source code
  file ( GLOB MOAI_VOXEL_SRC "${MOAI_VOXEL_DIR}/*.cpp" "${MOAI_VOXEL_DIR}/*.h" )

  add_library ( moai-voxel STATIC ${MOAI_VOXEL_SRC} )

  target_include_directories (moai-voxel PUBLIC ${MOAI_VOXEL_DIR} "${MOAI_VOXEL_DIR}/../")

  target_link_libraries ( moai-voxel moai-sim moai-core moai-util zlcore )
  
  set_target_properties(moai-voxel PROPERTIES FOLDER Modules)


