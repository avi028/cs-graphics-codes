CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

MODEL_RIDER_BIN=./bin/a2-model-rider 
MODEL_RIDER_SRCS=gl_framework.cpp shader_util.cpp hierarchy_node.cpp human_model.cpp humanoid.cpp 
MODEL_RIDER_INCS=gl_framework.hpp shader_util.hpp hierarchy_node.hpp human_model.hpp humanoid.hpp globals.hpp

BIKE_MODEL_BIN=./bin/a2-model-bike
BIKE_MODEL_SRCS=bike_model.cpp gl_framework.cpp shader_util.cpp hierarchy_node.cpp cylinder.cpp frustum.cpp modelling_bike.cpp texture.cpp
BIKE_MODEL_INCS=gl_framework.hpp shader_util.hpp bike_model.hpp hierarchy_node.hpp cylinder.hpp frustum.hpp modelling_bike.hpp globals.hpp texture.hpp

TRACK_MODEL_BIN=./bin/a2-model-track
TRACK_MODEL_SRCS=track_model.cpp gl_framework.cpp shader_util.cpp hierarchy_node.cpp cylinder.cpp frustum.cpp modelling_track.cpp humanoid.cpp modelling_bike.cpp
TRACK_MODEL_INCS=gl_framework.hpp shader_util.hpp track_model.hpp hierarchy_node.hpp cylinder.hpp frustum.hpp modelling_track.hpp globals.hpp humanoid.cpp modelling_bike.hpp

SRCDIR= ./src/
BINDIR= ./bin/

_INC_B = $(patsubst %,$(SRCDIR)/%,$(BIKE_MODEL_INCS))
_SRC_B = $(patsubst %,$(SRCDIR)/%,$(BIKE_MODEL_SRCS))

_INC_R = $(patsubst %,$(SRCDIR)/%,$(MODEL_RIDER_INCS))
_SRC_R = $(patsubst %,$(SRCDIR)/%,$(MODEL_RIDER_SRCS))

_INC_T = $(patsubst %,$(SRCDIR)/%,$(TRACK_MODEL_INCS))
_SRC_T = $(patsubst %,$(SRCDIR)/%,$(TRACK_MODEL_SRCS))

all: $(BIKE_MODEL_BIN) 

$(MODEL_RIDER_BIN): $(_SRC_R) $(_INC_R)
	@if [ ! -d $(BINDIR) ]; then  mkdir bin; fi
	g++ $(CPPFLAGS) $(_SRC_R) -o $(MODEL_RIDER_BIN) $(LDFLAGS) $(LIBS)

$(BIKE_MODEL_BIN): $(_SRC_B) $(_INC_B)
	@if [ ! -d $(BINDIR) ]; then  mkdir bin; fi
	g++ $(CPPFLAGS) $(_SRC_B) -o $(BIKE_MODEL_BIN) $(LDFLAGS) $(LIBS)

$(TRACK_MODEL_BIN): $(_SRC_T) $(_INC_T)
	@if [ ! -d $(BINDIR) ]; then  mkdir bin; fi
	g++ $(CPPFLAGS) $(_SRC_T) -o $(TRACK_MODEL_BIN) $(LDFLAGS) $(LIBS)


clean:
	@rm -rf *~ *.o $(BINDIR)