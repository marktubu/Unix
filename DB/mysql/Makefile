CXXFLAGS = -O0 -g -Wall -I ./ -pthread
LDFLAGS = -lpthread -lmysqlclient

LIB_SRC = test.cc mydb.cc

BINARIES = test

$(BINARIES):
	g++ $(CXXFLAGS) -o $@ $(LIB_SRC) $(filter %.cc,$^) $(LDFLAGS)

all: $(BINARIES)

clean:
	rm -f $(BINARIES) core

test = test.cc
