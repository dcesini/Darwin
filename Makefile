CXX=g++
LD=g++
CXXFLAGS=-std=c++0x
CXXFLAGS_SHARED=-c -W -fpic -std=c++0x
#LDFLAGS=-L.
LDLIBS=-lboost_serialization -lboost_program_options

SRCS=Commons.cpp Food.cpp Chromo.cpp DNA.cpp Being.cpp World.cpp  Constants_wrapper.cpp Darwin.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

RM=rm -f
TARGET=darwin.out

SHARED_READ=libctest.so.1.0
SHARED_READ_SO=libctest.so
SHARED_READ_SONAME=libctest.so.1

all: $(TARGET)

darwin.out: $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS) 

Constants_wrapper.o: Constants_wrapper.cpp

Commons.o: Commons.cpp

Food.o: Food.cpp

Chromo.o: Chromo.cpp

DNA.o: DNA.cpp

Being.o: Being.cpp

World.o: World.cpp

Darwin.o: Darwin.cpp


#shared_read: $(SHARED_READ)

#libctest.so.1.0: read_world.o Commons.o Food.o Chromo.o DNA.o Being.o World.o
#	$(LD) -shared -shared -Wl,-soname,$(SHARED_READ_SONAME) -o $(SHARED_READ) read_world.o Commons.o Food.o Chromo.o DNA.o Being.o World.o
#	ln -sf $(SHARED_READ) $(SHARED_READ_SO)
#	ln -sf $(SHARED_READ) $(SHARED_READ_SONAME)
#
#Commons.o: Commons.cpp
#	$(CXX) $(CXXFLAGS_SHARED) -o Commons.o Commons.cpp

#Food.o: Food.cpp
#	$(CXX) $(CXXFLAGS_SHARED) -o Food.o Food.cpp

#Chromo.o: Chromo.cpp
#	$(CXX) $(CXXFLAGS_SHARED) -o Chromo.o Chromo.cpp

#DNA.o: DNA.cpp
#	$(CXX) $(CXXFLAGS_SHARED) -o DNA.o DNA.cpp

#Being.o: Being.cpp
#	$(CXX) $(CXXFLAGS_SHARED) -o Being.o Being.cpp

#World.o: World.cpp
#	$(CXX) $(CXXFLAGS_SHARED) -o World.o World.cpp

#read_world.o: read_world.cpp
#	$(CXX) $(CXXFLAGS_SHARED) -o read_world.o read_world.cpp

clean:
	$(RM) *.o
	$(RM) $(TARGET)

clean_shared_read:
	$(RM) $(SHARED_READ)
	$(RM) $(SHARED_READ_SO)
	$(RM) $(SHARED_READ_SONAME)
