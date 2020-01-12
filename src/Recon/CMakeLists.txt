message(STATUS "Recon ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  ADD_EXECUTABLE(TrackRecon		trackrecon.cpp)
  TARGET_LINK_LIBRARIES(TrackRecon	${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMCluster.so		
  					${PROJECT_SOURCE_DIR}/lib/library/BMHitCluster.so		
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(TrackRecon	PUBLIC	${PROJECT_SOURCE_DIR}/include/Recon
  					${PROJECT_SOURCE_DIR}/include/EvtDisp
  					${PROJECT_SOURCE_DIR}/lib/src)	

endif (ROOT_FOUND)
