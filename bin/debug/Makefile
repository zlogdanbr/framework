cc=g++
VPATH = ../../src
FONTES= main.cpp log.cpp th.cpp util.cpp com.cpp db.cpp factory.cpp
INCLUDE = ../../include
LIBFLAGS = -lpthread -lsqlite3
CTAGS = -g -Wall -pedantic -O2 -D_DEBUG -std=c++11 
OUT = Tool
LIBDIR = ../lib


all:$(OUT)

$(OUT): $(FONTES:.cpp=.o)
	$(cc) -o $@ $^ $(LIBFLAGS)

%.o: %.cpp 
	$(cc) -c $(CTAGS) -I$(INCLUDE) -I$(LIBDIR) $< -o $@

clean:
	rm -f $(OUT) *.o


