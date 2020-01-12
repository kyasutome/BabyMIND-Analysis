message(STATUS "YASUTracker ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
Message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  ADD_EXECUTABLE(BasicDist	basicdist.cpp)
  TARGET_LINK_LIBRARIES(BasicDist	${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so
					${PROJECT_SOURCE_DIR}/lib/library/BMCluster.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(BasicDist	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp
  						${PROJECT_SOURCE_DIR}/include/YASUTracker
  						${PROJECT_SOURCE_DIR}/lib/src)

endif (ROOT_FOUND)
