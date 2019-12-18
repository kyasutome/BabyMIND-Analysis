message(STATUS "YASUTracker ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  ADD_EXECUTABLE(YASUTracker	main.cpp)
  TARGET_LINK_LIBRARIES(YASUTracker	${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(YASUTracker	PUBLIC	${PROJECT_SOURCE_DIR}/include/YASUTracker
  						${PROJECT_SOURCE_DIR}/lib/src)

endif (ROOT_FOUND)
