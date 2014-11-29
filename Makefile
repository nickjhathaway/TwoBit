NO_R="true"
include makefile-common.mk
CPP = g++-mp-4.8
#CPP = clang++-mp-3.3
AR = ar
STRIP = strip

# main paths
EXT_PATH=$(realpath external)
COMMON_PATH=$(realpath ../../common)
SCRIPTS_PATH=$(realpath ./scripts)
VELDE_PATH=$(realpath ../../vandervelde)

LIB_EXCLUDE := src/main.cpp

HEADERS = $(call rwildcard, src/, *.h) \
	$(call rwildcard, src/, *.hpp)

OBJ_DIR := build
OBJ := $(addprefix $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(call rwildcard, src/, *.cpp)))
LIBOBJ := $(filter-out $(addprefix $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(LIB_EXCLUDE))), $(OBJ))

BIN := bin/twobit

.PHONY: all
all: $(OBJ_DIR) $(BIN)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p bin

$(OBJ_DIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)/$(shell dirname $<)
	$(CPP) -fpermissive $(COMMON_OPT) -c -o $@ $<

$(BIN): $(OBJ)
	$(CPP) -o $@ $^ $(LD_FLAGS)
	$(SCRIPTS_PATH)/fixDyLinking_mac.sh $@
	$(STRIP) $@

.PHONY : run
run:
	@echo "******************** running ********************"
	./a.out
	@echo "******************** done    ********************"

.PHONY: clean
clean:
	@rm -f $(BIN)
	@rm -rf $(OBJ_DIR)

.PHONY: redo
redo: clean all

.PHONY: test
test : all
	$(SCRIPTS_PATH)/test.sh


