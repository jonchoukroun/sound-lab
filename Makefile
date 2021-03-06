CXX=clang++
CXXFLAGS=-std=c++20
CXXFLAGS+=-I.
CXXFLAGS+=-W
-CXXFLAGS+=Wall
CXXFLAGS+=-Wextra

LDFLAGS=-lSDL2

TARGET=sound_lab

SOURCE_DIR=src/
INCLUDE_DIR=include/
BUILD_DIR=build/

_OBJ=audio_engine.o dft.o instrument.o noise.o sawtooth.o settings.o sine.o timer.o wavetable_osc.o main.o
OBJ=$(patsubst %,$(BUILD_DIR)%,$(_OBJ))

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(CXXFLAGS) -I$(INCLUDE_DIR)

$(BUILD_DIR)%.o: $(SOURCE_DIR)%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) -I$(INCLUDE_DIR)

build: $(TARGET)

clean:
	rm -f $(BUILD_DIR)*.o
	rm -f $(TARGET)
	rm -f ./*.csv

all: clean build
