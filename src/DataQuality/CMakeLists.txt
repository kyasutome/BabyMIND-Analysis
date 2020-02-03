message(STATUS "DataQuality ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

      
  ADD_EXECUTABLE(WMDataQuality		WMDataQuality.cpp)
  TARGET_LINK_LIBRARIES(WMDataQuality	${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
					${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
					${PROJECT_SOURCE_DIR}/lib/library/WGRecon.so
					${PROJECT_SOURCE_DIR}/lib/library/WMDQData.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(WMDataQuality	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  							${PROJECT_SOURCE_DIR}/include/EvtDisp	
  							${PROJECT_SOURCE_DIR}/include/DataQuality	
  							${PROJECT_SOURCE_DIR}/lib/src)




endif (ROOT_FOUND)
