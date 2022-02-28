# Configuration
CC := gcc
FILE_TYPE := .c
DEBUG_FLAGS := -g -O0 -Wall -Wextra
RELEASE_FLAGS := -O3 -DNDEBUG
SRC_DIR := src/
OBJ_DIR := bin/obj/
EXEC_DIR := bin/
EXEC_NAME := flum
BUILD_TARGET := out
RUNTIME_ARGS := examples/hello_world.flum

#### DO NOT EDIT BELOW THIS LINE ####

# General names
EXEC := $(EXEC_NAME).$(BUILD_TARGET)
BUILD := $(EXEC_DIR)$(EXEC)

# Loading in file locations
SRCS := $(wildcard $(SRC_DIR)**/**$(FILE_TYPE)) $(wildcard $(SRC_DIR)*$(FILE_TYPE))
OBJS := $(patsubst $(SRC_DIR)%$(FILE_TYPE), $(OBJ_DIR)%.o, $(SRCS))

# Handles automatic dependency tracking
DEPS := $(patsubst %.o, %.d, $(OBJS))
-include $(DEPS)
DEP_FLAGS = -MMD -MF $(@:.o=.d) 

build_debug: $(OBJS)
	@echo "D" > .tmp_data
	@echo [INFO] Creating Static Library [$(BUILD_TARGET)] with Debug Flags ...
	@$(CC) -o $(BUILD) $^
	@echo [INFO] [$(EXEC)] Created with Debug Flags!
	
build_release: $(OBJS)
	@echo "" > .tmp_data
	@echo [INFO] Creating Static Library [$(BUILD_TARGET)] ...
	@$(CC) -o $(BUILD) $^
	@echo [INFO] [$(EXEC)] Created!

$(OBJ_DIR)%.o: $(SRC_DIR)%$(FILE_TYPE)
	@echo [CC] $<
	@mkdir -p $(@D)
ifeq ($(shell cat bin/.tmp_data),D)
	@$(CC) $(DEBUG_FLAGS) $< -c -o $@ -I headers $(DEP_FLAGS)
else
	@$(CC) $(RELEASE_FLAGS) $< -c -o $@ -I headers $(DEP_FLAGS) 
endif

run:
	@./$(BUILD) $(RUNTIME_ARGS)

.PHONY: clean
clean:
	@echo [INFO] Removing Pre-Compiled Object Files ...
	@rm -rf $(OBJ_DIR)
	@echo [INFO] Remvoing Prerequisite Files ...
	@rm -rf $(DEPS)
	@echo [INFO] Removing Compiled Libraries ...
	@rm -rf $(EXEC_DIR)