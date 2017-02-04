CXX = g++
CXXFLAGS = -Wall -std=c++0x

INCLUDES = -I./submodules/rapidjson/include -I./submodules/googletest/googletest/include -I./include

LXXFLAGS = -L./lib
LIBS = -lgmock_main

GMOCK_DIR = ./submodules/googletest/googlemock/make

TEST_MAIN = CacheSimulatorTest

all:

main:

googlemock:
	$(MAKE) -C $(GMOCK_DIR) gmock_main.a
	cp $(GMOCK_DIR)/gmock_main.a ./lib/libgmock_main.a
	$(MAKE) -C $(GMOCK_DIR) clean

test:
	$(MAKE) -C ./tests test.o
	$(MAKE) -C ./src cache_simulator.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) ./obj/test.o ./obj/cache_simulator.o -o \
		./bin/$(TEST_MAIN) $(LXXFLAGS) $(LIBS)
	cd ./bin && ./CacheSimulatorTest

clean:
	rm ./obj/*.o
	rm  bin/*
	rm ./lib/*
