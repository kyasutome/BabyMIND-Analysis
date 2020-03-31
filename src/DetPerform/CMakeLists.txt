message(STATUS "DetPerform ... ")

AUX_SOURCE_DIRECTORY(.	SOURCE_FILES)
message(STATUS "${SOURCE_FILES}")

if    (ROOT_FOUND)

  ADD_EXECUTABLE(wmcoincheck			wm_coin.cpp)
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

  ADD_EXECUTABLE(wm_matchingtest		wm_matchingtest.cpp)
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

  ADD_EXECUTABLE(det_eventrate		        det_eventrate.cpp)
  TARGET_LINK_LIBRARIES(det_eventrate		${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
						${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so
						${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
						${PROJECT_SOURCE_DIR}/lib/library/PMRecon.so
						${PROJECT_SOURCE_DIR}/lib/library/WGRecon.so		
						${PROJECT_SOURCE_DIR}/lib/library/BasicRecon.so		
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(det_eventrate	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(eventrate_detail		eventrate_detail.cpp)
  TARGET_LINK_LIBRARIES(eventrate_detail	${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
						${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so
						${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
						${PROJECT_SOURCE_DIR}/lib/library/PMRecon.so
						${PROJECT_SOURCE_DIR}/lib/library/WGRecon.so		
						${PROJECT_SOURCE_DIR}/lib/library/BasicRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/DetRecon.so		
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(eventrate_detail	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(detect_eff		        detect_eff.cpp)
  TARGET_LINK_LIBRARIES(detect_eff		${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
  						${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
  						${PROJECT_SOURCE_DIR}/lib/library/DetRecon.so
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(detect_eff		PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(pedist				pedist.cpp)
  TARGET_LINK_LIBRARIES(pedist			${PROJECT_SOURCE_DIR}/lib/library/BMBasicRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/BMBeaminfo.so
						${PROJECT_SOURCE_DIR}/lib/library/BMBSD.so		
						${PROJECT_SOURCE_DIR}/lib/library/BasicRecon.so		
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(pedist		PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(find_neutrino		        find_neutrino.cpp)
  TARGET_LINK_LIBRARIES(find_neutrino		${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
  						${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
						${PROJECT_SOURCE_DIR}/lib/library/BasicRecon.so
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(find_neutrino	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(matching_eff		        matching_eff.cpp)
  TARGET_LINK_LIBRARIES(matching_eff		${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
  						${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
  						${PROJECT_SOURCE_DIR}/lib/library/DetRecon.so
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(matching_eff	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(tracking_eff		        tracking_eff.cpp)
  TARGET_LINK_LIBRARIES(tracking_eff		${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
  						${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
  						${PROJECT_SOURCE_DIR}/lib/library/DetRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/MCRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/MCTrue.so
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(tracking_eff	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(find_nuvertex		        find_nuvertex.cpp)
  TARGET_LINK_LIBRARIES(find_nuvertex		${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
  						${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
  						${PROJECT_SOURCE_DIR}/lib/library/DetRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/MCRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/MCTrue.so
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(find_nuvertex	PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(charge_eff		        charge_eff.cpp)
  TARGET_LINK_LIBRARIES(charge_eff		${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
  						${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
  						${PROJECT_SOURCE_DIR}/lib/library/DetRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/MCRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/MCTrue.so
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(charge_eff		PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)

  ADD_EXECUTABLE(lightyield_dist		lightyield_dist.cpp)
  TARGET_LINK_LIBRARIES(lightyield_dist		${PROJECT_SOURCE_DIR}/lib/library/EVTCluster.so	
  						${PROJECT_SOURCE_DIR}/lib/library/BMDisp.so
  						${PROJECT_SOURCE_DIR}/lib/library/DetRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/MCRecon.so
  						${PROJECT_SOURCE_DIR}/lib/library/MCTrue.so
						${ROOT_LIBRARIES})

  TARGET_INCLUDE_DIRECTORIES(lightyield_dist    PUBLIC	${PROJECT_SOURCE_DIR}/include/MakeCalib
  						${PROJECT_SOURCE_DIR}/include/EvtDisp	
  						${PROJECT_SOURCE_DIR}/include/MakeEvent	
  						${PROJECT_SOURCE_DIR}/include/BSDApply	
  						${PROJECT_SOURCE_DIR}/include/DetPerform	
  						${PROJECT_SOURCE_DIR}/lib/src)





endif (ROOT_FOUND)
