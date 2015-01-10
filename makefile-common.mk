UNAME_S := $(shell uname -s)
CPP = clang++
LOCAL_PATH = $(EXT_PATH)/local
MAKE_FILES=$(realpath Makefile makefile-common.mk)

# clang++
CXXFLAGS = -std=c++11 -stdlib=libc++ -Wall
CXXOPT = -O2 -march=native -mtune=native -funroll-loops -fstack-protector -ffast-math

# g++
#CXXFLAGS = -std=c++11 -Wall
#ifeq ($(UNAME_S),Darwin)
#    CXXOPT = -O2 -funroll-loops --fast-math
#else
#    CXXOPT = -O2 -march=native -mtune=native -funroll-loops --fast-math
#endif

CXXDEBUG = -g -gstabs+
LOCALTOOLS = -I$(LOCAL_PATH)
EXTTOOLS = -I$(EXT_PATH)
SRC = -I./src/

COMLIBS = $(LOCALTOOLS) $(EXTTOOLS) $(SRC)
COMMON_OPT = $(CXXFLAGS) $(CXXOPT) $(COMLIBS)
COMMON_DEBUG = $(CXXFLAGS) $(CXXDEBUG) $(COMLIBS)

# from http://stackoverflow.com/a/18258352
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

