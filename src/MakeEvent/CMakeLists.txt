message(STATUS "MakeEvent ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  ADD_EXECUTABLE(MakeEvent	MakeEvent.cpp)
  TARGET_LINK_LIBRARIES(MakeEvent	${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
					${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so	
					${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
					${PROJECT_SOURCE_DIR}/lib/library/PMRecon.so
					${PROJECT_SOURCE_DIR}/lib/library/WGRecon.so		
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(MakeEvent	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(MakeMCEvent	MakeMCEvent.cpp)
  TARGET_LINK_LIBRARIES(MakeMCEvent	${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
  					${PROJECT_SOURCE_DIR}/lib/library/MCTrue.so
 					${PROJECT_SOURCE_DIR}/lib/library/MCRecon.so
					${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so	
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
					${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so
					${PROJECT_SOURCE_DIR}/lib/library/PMRecon.so	
					${PROJECT_SOURCE_DIR}/lib/library/WGRecon.so
					${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(MakeMCEvent	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/lib/src)




endif (ROOT_FOUND)
