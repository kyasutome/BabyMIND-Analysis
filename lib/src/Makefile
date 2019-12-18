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

PMRecon:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

BMBSD:
	rootcint -f $(@)Dict.cc -c $(@).hpp $(@)LinkDef.hh
	$(CXX) `root-config --cflags --libs` -shared $(@)Dict.cc $(@).cpp -o ${MAKEDIR}/$(@).so

move:
	mv ./*pcm ${MAKEDIR}/

clean:
	$(RM) -f *.o *~ *Dict.* *pcm ${OBJS} chkfort
