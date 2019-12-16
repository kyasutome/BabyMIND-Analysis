message(STATUS "MakeCalib ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  ADD_EXECUTABLE(MakeCalib	main.cpp)
  TARGET_LINK_LIBRARIES(MakeCalib	${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  					${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
					${ROOT_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(MakeCalib	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/lib/src)


endif (ROOT_FOUND)
