#
# Optional command line arguments:
# see http://stackoverflow.com/a/24264930/43839
#
# For an optimized, stripped build, use:
#
#   $ make OPTIMIZE=-O3 SYMBOLS=""
#
# For a C++14 build, use:
#
#   $ make COMPILER=g++-5 STDLIB=c++14
#

COMPILER ?= g++
OPTIMIZE ?= -O0
STDLIB ?= c++1y
SYMBOLS ?= -g

#
# Compilation variables.
#
CXX = $(COMPILER)
CODE_GENERATION = $(OPTIMIZE) $(SYMBOLS) -std=$(STDLIB) -pthread
DEPENDENCIES =  -MMD -MP -MF
INCLUDES = -Isrc -Isrc/jsoncpp/include
LIBRARIES = -lm -lstdc++
WARNINGS = -Wall -Wextra -Wno-strict-aliasing -Wpedantic

DEFINES = -DDEBUG

CXXFLAGS_BASE += \
  $(CODE_GENERATION) \
  $(DEFINES) \
  $(INCLUDES) \
  $(LIBRARIES) \
  $(WARNINGS) \
  $(DEPENDENCIES)

CXXFLAGS = $(CXXFLAGS_BASE) $(DEPENDENCIES)
CXXFLAGS_TEST = $(CXXFLAGS_BASE) $(GTEST_FLAGS)

BINARIES = bin/tests
OBJ = bin/obj
DIRECTORIES = bin $(OBJ) .deps

#
# Build rules
#

.PHONY: all binaries
.SUFFIXES:
.SECONDARY:

all: binaries

pre-build:
	mkdir -p $(DIRECTORIES)

binaries: pre-build
	@$(MAKE) --no-print-directory $(BINARIES)

bin/%: src/%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) .deps/$*.d

clean:
	rm -Rf $(DIRECTORIES)

-include .deps/*.d
