
# g++ -std=c++0x read.cpp -o read.out -L./ -lreadworld -lboost_serialization -lboost_program_options
# for a static build
#g++ -static -static-libgcc -static-libstdc++ -std=c++0x -o darwin.out Commons.cpp Food.cpp Chromo.cpp DNA.cpp Being.cpp World.cpp  Constants_wrapper.cpp Darwin.cpp -lboost_serialization -lpthread -lboost_program_options

CXX=g++
LD=g++
CXXFLAGS=-std=c++0x
CXXFLAGS_SHARED=-c -W -fpic -std=c++0x
LDFLAGS=-L.
LDLIBS=-lboost_serialization -lboost_program_options

SRCS=Commons.cpp Food.cpp Chromo.cpp DNA.cpp Being.cpp World.cpp  Constants_wrapper.cpp Darwin.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

RM=rm -f
TARGET=darwin.out
READ=read.out

SHARED_READ=libreadworld.so.1.0
SHARED_READ_SO=libreadworld.so
SHARED_READ_SONAME=libreadworld.so.1

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


clean:
	$(RM) *.o
	$(RM) $(TARGET)
	$(RM) $(READ)
	$(RM) $(SHARED_READ)
	$(RM) $(SHARED_READ_SO)
	$(RM) $(SHARED_READ_SONAME)

clean_shared_read:
	$(RM) $(SHARED_READ)
	$(RM) $(SHARED_READ_SO)
	$(RM) $(SHARED_READ_SONAME)
