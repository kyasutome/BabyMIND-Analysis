message(STATUS "Recon ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  #ADD_EXECUTABLE(TrackRecon		trackrecon.cpp)
  #TARGET_LINK_LIBRARIES(TrackRecon	${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
  #					${PROJECT_SOURCE_DIR}/lib/library/BMCluster.so		
  #					${PROJECT_SOURCE_DIR}/lib/library/BMHitCluster.so		
  #					${ROOT_LIBRARIES})
 					
  # TARGET_INCLUDE_DIRECTORIES(TrackRecon	PUBLIC	${PROJECT_SOURCE_DIR}/include/Recon
  #					${PROJECT_SOURCE_DIR}/include/EvtDisp
  #				${PROJECT_SOURCE_DIR}/lib/src)	

  ADD_EXECUTABLE(DetRecon		detrecon.cpp)
  TARGET_LINK_LIBRARIES(DetRecon	${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMCluster.so		
  					${PROJECT_SOURCE_DIR}/lib/library/BMHitCluster.so		
  					${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
					${PROJECT_SOURCE_DIR}/lib/library/DetHitCluster.so
					${PROJECT_SOURCE_DIR}/lib/library/Cell.so
					${PROJECT_SOURCE_DIR}/lib/library/DetCluster.so
					${PROJECT_SOURCE_DIR}/lib/library/DetHitClusters.so
					${PROJECT_SOURCE_DIR}/lib/library/DetClusters.so
					${PROJECT_SOURCE_DIR}/lib/library/DetRecon.so
					${PROJECT_SOURCE_DIR}/lib/library/MCTrue.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(DetRecon	PUBLIC	${PROJECT_SOURCE_DIR}/include/Recon
  					${PROJECT_SOURCE_DIR}/include/EvtDisp
  					${PROJECT_SOURCE_DIR}/lib/src)	

  ADD_EXECUTABLE(CheckRecon		checkrecon.cpp)
  TARGET_LINK_LIBRARIES(CheckRecon	${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMCluster.so		
  					${PROJECT_SOURCE_DIR}/lib/library/BMHitCluster.so		
  					${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
					${PROJECT_SOURCE_DIR}/lib/library/DetHitCluster.so
					${PROJECT_SOURCE_DIR}/lib/library/Cell.so
					${PROJECT_SOURCE_DIR}/lib/library/DetCluster.so
					${PROJECT_SOURCE_DIR}/lib/library/DetHitClusters.so
					${PROJECT_SOURCE_DIR}/lib/library/DetClusters.so
					${PROJECT_SOURCE_DIR}/lib/library/DetRecon.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(CheckRecon	PUBLIC	${PROJECT_SOURCE_DIR}/include/Recon
  					${PROJECT_SOURCE_DIR}/include/EvtDisp
  					${PROJECT_SOURCE_DIR}/lib/src)	

endif (ROOT_FOUND)
