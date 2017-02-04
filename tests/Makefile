CXX = g++
CXXFLAGS = -Wall -std=c++0x

INCLUDES = -I../submodules/rapidjson/include -I../submodules/googletest/googletest/include -I../include

OBJ_DIR = ../obj

SRCS = test_Cache.cpp test_CacheLine.cpp test_Set.cpp test_Simulator.cpp

OBJS = $(SRCS:.cpp=.o)
OBJS_PATH = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

MAIN = test.o

all: test.o

test.o: $(OBJS)
	$(LD) -r $(OBJS_PATH) -o ../obj/test.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o ../obj/$@
