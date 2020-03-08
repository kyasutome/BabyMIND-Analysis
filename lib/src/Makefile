CXX           = g++
CXXFLAGS      = -O2 -pipe -Wall -W -Woverloaded-virtual

ROOTCONFIG = root-config
ROOTCFLAGS:= $(shell $(ROOTCONFIG) --cflags)
ROOTLIBS  := $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS := $(shell $(ROOTCONFIG) --glibs)
MAKEDIR=${PWD}/../library

CXXFLAGS+= $(ROOTCFLAGS)
CXXFLAGS+= -g
LIBS     = $(ROOTLIBS)


BMBasicRecon:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

BMBeaminfo:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

BMDisp:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

BMCluster:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

BMHitCluster:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

PMRecon:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

BMBSD:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

WGRecon:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

WMDQData:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

EVTCluster:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

BasicRecon:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

MCRecon:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

DetRecon:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

MCTrue:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

DetHitCluster:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

Cell:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

DetCluster:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

DetHitClusters:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

DetClusters:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

move:
	mv ./*pcm ${MAKEDIR}/

clean:
	$(RM) -f *.o *~ *Dict.* *pcm ${OBJS} chkfort
