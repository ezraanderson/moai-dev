cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-bullet )


  set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/src/moai-bullet/" )
 

  set ( MOAI_BULLET_INCLUDES 
      "${MOAI_ROOT}/src/"
      "${MOAI_ROOT}/src/BulletCollision/"
      "${MOAI_ROOT}/src/BulletDynamics/"  
      "${MOAI_ROOT}/src/BulletSoftBody/"
      "${MOAI_ROOT}/src/LinearMath/"       
        
    )

  # Use all cpp files in directory as source code
  file ( GLOB MOAI_BULLET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

  include_directories ( ${MOAI_BULLET_INCLUDES} )

  add_library ( moai-bullet STATIC ${MOAI_BULLET_SRC} )

  get_target_property (BULLET_INCLUDES bullet INCLUDE_DIRECTORIES)
  target_include_directories (moai-bullet PUBLIC ${MOAI_BULLET_INCLUDES} ${BULLET_INCLUDES})

  target_link_libraries ( moai-bullet moai-sim moai-core moai-util bullet zlcore )
  set_target_properties(moai-bullet PROPERTIES FOLDER Modules)  



