message(STATUS "MakeCalib ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  ADD_EXECUTABLE(BMCalib		BMCalib.cpp)
  TARGET_LINK_LIBRARIES(BMCalib		${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(BMCalib	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(PMCalib    	        PMCalib.cpp)
  TARGET_LINK_LIBRARIES(PMCalib         ${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
                                        ${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
                                        ${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
                                        ${PROJECT_SOURCE_DIR}/lib/library/PMRecon.so
                                        ${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(PMCalib    PUBLIC  ${PROJECT_SOURCE_DIR}/include/MakeCalib
                                                        ${PROJECT_SOURCE_DIR}/include/EvtDisp
                                                        ${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(WGCalib  	        WGCalib.cpp)
  TARGET_LINK_LIBRARIES(WGCalib         ${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
                                        ${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
                                        ${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
                                        ${PROJECT_SOURCE_DIR}/lib/library/WGRecon.so
                                        ${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(WGCalib    PUBLIC  ${PROJECT_SOURCE_DIR}/include/MakeCalib
                                                        ${PROJECT_SOURCE_DIR}/include/EvtDisp
                                                        ${PROJECT_SOURCE_DIR}/lib/src)


endif (ROOT_FOUND)
