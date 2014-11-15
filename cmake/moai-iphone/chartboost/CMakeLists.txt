message("************************************")
message("chartboost")
message("************************************")

cmake_minimum_required ( VERSION 2.8.11 )      
project ( moai-ios-chartboost )



set(CHARTBOOST_ROOT ${MOAI_ROOT}/3rdparty/chartboost-5.3/Chartboost.framework)
set(CHARTBOOST_LIB ${CHARTBOOST_ROOT}/Chartboost)
add_library(Chartboost SHARED IMPORTED)

set_property(TARGET Chartboost PROPERTY IMPORTED_LOCATION ${CHARTBOOST_LIB})
set_property(TARGET Chartboost PROPERTY FRAMEWORK 1)    

add_library(moai-ios-chartboost STATIC
  "${MOAI_ROOT}/src/moai-ios-chartboost/MOAIChartBoostIOS.h"
  "${MOAI_ROOT}/src/moai-ios-chartboost/MOAIChartBoostIOS.mm"
  

)

target_include_directories(moai-ios-chartboost PUBLIC
"$<BUILD_INTERFACE:${MOAI_ROOT}/src>"
"$<BUILD_INTERFACE:${CHARTBOOST_ROOT}>"
"$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
)

target_link_libraries(moai-ios-chartboost Chartboost moai-sim moai-util moai-core)    
set_target_properties( moai-ios-chartboost PROPERTIES FOLDER Modules)     
install(TARGETS moai-ios-chartboost EXPORT libmoai ARCHIVE DESTINATION lib)





## I DONT HAVE THIS FILE
##"${MOAI_ROOT}/src/moai-iphone/AKU-iphone.mm"
##THIS FILE DOESN'T WORK
##install(FILES ${MOAI_ROOT}/src/moai-ios-chartboost/host.h DESTINATION include/moai-ios-chartboost)
##install(DIRECTORY "${CHARTBOOST_ROOT}" DESTINATION lib)