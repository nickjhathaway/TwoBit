include makefile-common.mk
CPP = clang++
#CPP = g++-4.8
STRIP = strip
AR = ar

# main paths
EXT_PATH=$(realpath external)
SCRIPTS_PATH=$(realpath ./scripts)

LIB_EXCLUDE := src/main.cpp


HEADERS = $(call rwildcard, src/, *.h) \
	$(call rwildcard, src/, *.hpp)

OBJ_DIR := build
OBJ := $(addprefix $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(call rwildcard, src/, *.cpp)))
LIBOBJ := $(filter-out $(addprefix $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(LIB_EXCLUDE))), $(OBJ))

BIN := bin/twobit
STATIC := bin/twobit.a

.PHONY: all
all: $(OBJ_DIR) $(BIN) $(STATIC)

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

$(STATIC): $(LIBOBJ)
	$(AR) rcs $@ $^

.PHONY: clean
clean:
	@rm -f $(BIN)
	@rm -f $(STATIC)
	@rm -rf $(OBJ_DIR)

.PHONY: redo
redo: clean all

