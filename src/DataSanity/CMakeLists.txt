message(STATUS "DataSanity ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  ADD_EXECUTABLE(WGDataSanity	wgdatasanity.cpp)
  TARGET_LINK_LIBRARIES(WGDataSanity	${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(WGDataSanity	PUBLIC	${PROJECT_SOURCE_DIR}/include/DataSanity
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(BMDataSanity	bmdatasanity.cpp)
  TARGET_LINK_LIBRARIES(BMDataSanity	${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(BMDataSanity	PUBLIC	${PROJECT_SOURCE_DIR}/include/DataSanity
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/lib/src)

endif (ROOT_FOUND)
