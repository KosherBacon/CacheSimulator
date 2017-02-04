CXX = g++
CXXFLAGS = -Wall -std=c++0x

INCLUDES = -I../submodules/rapidjson/include -I../submodules/googletest/googletest/include -I../include

OBJ_DIR = ../obj

SRCS = Cache.cpp Set.cpp Simulator.cpp
SRCS_MAIN = Cache.cpp main.cpp Set.cpp Simulator.cpp

OBJS = $(SRCS:.cpp=.o)
OBJS_PATH = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

OBJS_MAIN = $(SRCS_MAIN:.cpp=.o)
OBJS_MAIN_PATH = $(SRCS_MAIN:%.cpp=$(OBJ_DIR)/%.o)

MAIN = CacheSimulator
NO_MAIN = cache_sim_no_main.o

all: $(MAIN)

$(MAIN): $(OBJS_MAIN)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o ../bin/$(MAIN) $(OBJS_MAIN)

cache_simulator.o: $(OBJS)
	$(LD) -r $(OBJS_PATH) -o ../obj/cache_simulator.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o ../obj/$@
