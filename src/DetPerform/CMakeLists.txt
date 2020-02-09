message(STATUS "DetPerform ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  ADD_EXECUTABLE(wmcoincheck	wm_coin.cpp)
  TARGET_LINK_LIBRARIES(wmcoincheck		${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
						${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so
						${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
						${PROJECT_SOURCE_DIR}/lib/library/PMRecon.so
						${PROJECT_SOURCE_DIR}/lib/library/WGRecon.so		
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(wmcoincheck	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(wm_matchingtest	wm_matchingtest.cpp)
  TARGET_LINK_LIBRARIES(wm_matchingtest		${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
						${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so
						${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
						${PROJECT_SOURCE_DIR}/lib/library/PMRecon.so
						${PROJECT_SOURCE_DIR}/lib/library/WGRecon.so		
						${PROJECT_SOURCE_DIR}/lib/library/BasicRecon.so		
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(wm_matchingtest	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)




endif (ROOT_FOUND)
