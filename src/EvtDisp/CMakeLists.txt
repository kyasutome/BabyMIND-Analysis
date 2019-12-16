message(STATUS "EvtDisp ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  ADD_EXECUTABLE(MakeEvt	MakeEvt.cpp)
  TARGET_LINK_LIBRARIES(MakeEvt		${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
					${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so	
					${PROJECT_SOURCE_DIR}/lib/library/PMRecon.so	
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(MakeEvt	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(MakeDisp	MakeDisp.cpp)
  TARGET_LINK_LIBRARIES(MakeDisp	${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
					${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
					${PROJECT_SOURCE_DIR}/lib/library/PMRecon.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(MakeDisp	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(MakePMClass	MakePMClass.cpp)
  TARGET_LINK_LIBRARIES(MakePMClass	${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
					${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
					${PROJECT_SOURCE_DIR}/lib/library/PMRecon.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(MakePMClass	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  							${PROJECT_SOURCE_DIR}/include/EvtDisp	
  							${PROJECT_SOURCE_DIR}/lib/src)


endif (ROOT_FOUND)
