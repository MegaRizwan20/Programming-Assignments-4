# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder actorconnections



# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: pathfinder.cpp ActorGraph.o ActorNode.o ActorEdge.o ActorPath.o MovieList.o MovieGraph.o MovieName.o

actorconnections: actorconnections.cpp ActorGraph.o ActorNode.o ActorEdge.o ActorPath.o MovieList.o MovieGraph.o MovieName.o

# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

ActorGraph.o: MovieName.h ActorNode.h ActorEdge.h ActorGraph.h ActorPath.h MovieList.h MovieGraph.h MovieName.h

ActorNode.o: ActorNode.h ActorEdge.h MovieName.h

ActorEdge.o: ActorEdge.h ActorNode.h MovieName.h

ActorPath.o: ActorPath.h ActorEdge.h ActorNode.h MovieName.h

MovieList.o: MovieList.h MovieGraph.h MovieName.h ActorNode.h ActorEdge.h

MovieGraph.o: MovieGraph.h MovieName.h ActorNode.h ActorEdge.h

MovieName.o: MovieName.h

clean:
	rm -f pathfinder *.o core*

