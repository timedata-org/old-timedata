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

OPTIMIZE ?= -O0
STDLIB ?= c++11
SYMBOLS ?= -g

#
# Compilation variables.
#
CODE_GENERATION = $(OPTIMIZE) $(SYMBOLS) -std=$(STDLIB) -pthread
DEPENDENCIES = -MMD -MP -MF
INCLUDES = -Isrc -Isrc/jsoncpp/include
LIBRARIES = -lm -lstdc++
WARNINGS = -Wall -Wextra -Wno-strict-aliasing -Wpedantic

DEFINES = -DDEBUG -DCATCH_CONFIG_COLOUR_NONE

CXXFLAGS_BASE +=     \
  $(CODE_GENERATION) \
  $(DEFINES)         \
  $(INCLUDES)        \
  $(LIBRARIES)       \
  $(WARNINGS)        \
  $(DEPENDENCIES)

CXXFLAGS = $(CXXFLAGS_BASE) $(DEPENDENCIES)
CXXFLAGS_TEST = $(CXXFLAGS_BASE)

BINARIES = build/tests
OBJ = build/obj
DIRECTORIES = build $(OBJ) build/.deps

# Full build and test commands on my machine:
#
# $ source /development/env/cython/bin/activate && \
#    rm -Rf build *.so && \
#    python setup.py clean && \
#    python setup.py build_ext && \
#    make && \
#    build/tests
#

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

build/%: src/%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) build/.deps/$*.d

clean:
	rm -Rf $(DIRECTORIES)

-include build/.deps/*.d
