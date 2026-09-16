# Modern C++ Deep Dives - code samples (one program per .cpp file)
#
#   make                 build every sample
#   make run             build and run every sample, one after the other
#   make 01_vector       build one sample (Windows: make 01_vector.exe)
#   make run-01_vector   build and run one sample
#   make clean           remove binaries and object files
#   make STD=c++20       pick the language standard (default c++26; MSVC always uses /std:c++latest)
#
# Compiler by operating system (override with make CXX=<compiler>, e.g. make CXX=g++ on Windows with MinGW):
#   Windows  -> cl (MSVC).  Run make from a "Developer Command Prompt" / after vcvars64.bat so cl is in PATH.
#   Linux    -> g++
#   macOS    -> clang++

STD ?= c++26

ifeq ($(OS),Windows_NT)
  PLATFORM    := windows
  DEFAULT_CXX := cl
  EXE         := .exe
  # GNU make on Windows may run recipes through cmd.exe or through an sh.exe found in PATH. Probe which one:
  # cmd expands %ComSpec% to its own path, sh leaves the text untouched.
  ifneq (,$(findstring cmd.exe,$(shell echo %ComSpec%)))
    RM  := del /q
    RUN :=
  else
    RM  := rm -f
    RUN := ./
  endif
else
  UNAME := $(shell uname -s)
  ifeq ($(UNAME),Darwin)
    PLATFORM    := macos
    DEFAULT_CXX := clang++
  else
    PLATFORM    := linux
    DEFAULT_CXX := g++
  endif
  EXE :=
  RUN := ./
  RM  := rm -f
endif

# make defines CXX=g++ on its own, so "?=" would never apply the platform default; only a user-given CXX wins
ifeq ($(origin CXX),default)
  CXX := $(DEFAULT_CXX)
endif

# flag syntax follows the compiler actually used
ifneq ($(filter cl cl.exe,$(notdir $(CXX))),)
  CXXFLAGS ?= /nologo /std:c++latest /W4 /EHsc /O2 /permissive-
  OUTFLAG   = /Fe:$@
else
  CXXFLAGS ?= -std=$(STD) -Wall -Wextra -pedantic -O2
  OUTFLAG   = -o $@
endif

SRCS  := $(sort $(wildcard *.cpp))
HDRS  := $(wildcard *.h)
BINS  := $(SRCS:.cpp=$(EXE))
JUNK  := $(sort $(wildcard $(BINS) $(SRCS:.cpp=) *.obj *.o *.pdb *.ilk))

all: $(BINS)
	@echo built $(words $(BINS)) samples on $(PLATFORM) with $(CXX)

%$(EXE): %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) $< $(OUTFLAG)

# run targets carry no extension (run-01_vector), otherwise "run-x.exe" would match the %.exe: %.cpp rule.
# "|| exit 1" is valid in sh and cmd alike and makes make hand the line to the shell instead of spawning it itself.
# (no ">" in the echo: sh would treat it as a redirect and overwrite the file named after it)
run: $(addprefix run-,$(SRCS:.cpp=))

run-%: %$(EXE)
	@echo == $< ==
	$(RUN)$< || exit 1

clean:
ifneq (,$(JUNK))
	$(RM) $(JUNK)
endif

.PHONY: all run clean
