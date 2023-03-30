# ********************************************************************
# Project: DDS.Net C++ Connector
# 
# Remarks:
#     Building the main library as a linkable binary.
#     
#     Author:     usama
#     Created On: 30 March, 2023
# 
# 
# Edited
# --------------------------------------------------------------------
# On                  | By                    | Remarks
# --------------------------------------------------------------------
#                     |                       |
#                     |                       |
#                     |                       |
#                     |                       |
#                     |                       |
#                     |                       |
# ********************************************************************

GCC    = gcc
GXX    = g++
LDGCC  = g++
LD     = $(LDGCC)





# 
# Paths settings
# 
OUTPUT_LIB_NAME = dds.net.connector.cpplib

ROOT_DIR                             = $(PWD)/connector
INC_DIR                              = $(ROOT_DIR)/inc
INC_INTERNAL_DIR                     = $(ROOT_DIR)/src/internal/inc
INC_INTERNAL_VARIABLES_DIR           = $(ROOT_DIR)/src/internal/inc/variables
SRC_ROOT_DIR                         = $(ROOT_DIR)
BUILD_ROOT_DIR                       = $(PWD)/build

CONN_BASE_DIR                        = .
CONN_SRC_DIR                         = src
CONN_SRC_INTERNAL_DIR                = src/internal
CONN_SRC_INTERNAL_SRC_DIR            = $(CONN_SRC_INTERNAL_DIR)/src
CONN_SRC_INTERNAL_SRC_VARIABLES_DIR  = $(CONN_SRC_INTERNAL_DIR)/src/variables


CONN_SRCS_DIRS =                              \
    $(CONN_BASE_DIR)                          \
    $(CONN_SRC_DIR)                           \
    $(CONN_SRC_INTERNAL_DIR)                  \
    $(CONN_SRC_INTERNAL_SRC_DIR)              \
    $(CONN_SRC_INTERNAL_SRC_VARIABLES_DIR)


INCLUDE_DIRS :=                                                  \
    $(foreach dir, $(CONN_SRCS_DIRS), -I$(SRC_ROOT_DIR)/$(dir))  \
    -I$(ROOT_DIR)                                                \
    -I$(INC_DIR)                                                 \
	-I$(INC_INTERNAL_DIR)                                        \
	-I$(INC_INTERNAL_VARIABLES_DIR)





# 
# Creating output directories
# 
$(shell [ -d $(BUILD_ROOT_DIR) ] || mkdir -p $(BUILD_ROOT_DIR))
$(foreach dir, $(CONN_SRCS_DIRS), $(shell [ -d $(BUILD_ROOT_DIR)/$(dir) ] || mkdir -p $(BUILD_ROOT_DIR)/$(dir)))





# 
# Enlisting the object files
# 
SRCS_C   = $(foreach dir, $(CONN_SRCS_DIRS), $(shell ls $(SRC_ROOT_DIR)/$(dir)/*.c   2>/dev/null | sed s,.*/,$(dir)/,))
SRCS_CPP = $(foreach dir, $(CONN_SRCS_DIRS), $(shell ls $(SRC_ROOT_DIR)/$(dir)/*.cpp 2>/dev/null | sed s,.*/,$(dir)/,))

OBJS_C   := $(foreach file, $(SRCS_C:c=o),     $(BUILD_ROOT_DIR)/$(file))
OBJS_CPP := $(foreach file, $(SRCS_CPP:cpp=O), $(BUILD_ROOT_DIR)/$(file))

CONN_OBJECTS = $(OBJS_C) $(OBJS_CPP)





# 
# Setting compilation flags
# 
COMPILATION_C_FLAGS          = -fPIC                                      \
                               -Wall                                      \
                               -DTARGET_PLATFORM=PLATFORM_GNU_LINUX       \
                               $(INCLUDE_DIRS)
COMPILATION_CPP_FLAGS        = -fPIC                                      \
                               -Wall                                      \
                               -DTARGET_PLATFORM=PLATFORM_GNU_LINUX       \
                               -std=c++11                                 \
                               $(INCLUDE_DIRS)                            \
                               -lpthread


default: library





# ************************************************
# Defining compilation rules
#
# ***************************************

# 
# - ROOT/base Directory
# 
$(BUILD_ROOT_DIR)/$(CONN_BASE_DIR)/%.o: $(SRC_ROOT_DIR)/$(CONN_BASE_DIR)/%.c
	@echo [Compiling] $<
	@$(GCC) -c $(COMPILATION_C_FLAGS) $< -o $@

$(BUILD_ROOT_DIR)/$(CONN_BASE_DIR)/%.O: $(SRC_ROOT_DIR)/$(CONN_BASE_DIR)/%.cpp
	@echo [Compiling] $<
	@$(GXX) -c $(COMPILATION_CPP_FLAGS) $< -o $@

# 
# - ROOT/src Directory
# 
$(BUILD_ROOT_DIR)/$(CONN_SRC_DIR)/%.o: $(SRC_ROOT_DIR)/$(CONN_SRC_DIR)/%.c
	@echo [Compiling] $<
	@$(GCC) -c $(COMPILATION_C_FLAGS) $< -o $@

$(BUILD_ROOT_DIR)/$(CONN_SRC_DIR)/%.O: $(SRC_ROOT_DIR)/$(CONN_SRC_DIR)/%.cpp
	@echo [Compiling] $<
	@$(GXX) -c $(COMPILATION_CPP_FLAGS) $< -o $@

# 
# - ROOT/src/internal Directory
# 
$(BUILD_ROOT_DIR)/$(CONN_SRC_INTERNAL_DIR)/%.o: $(SRC_ROOT_DIR)/$(CONN_SRC_INTERNAL_DIR)/%.c
	@echo [Compiling] $<
	@$(GCC) -c $(COMPILATION_C_FLAGS) $< -o $@

$(BUILD_ROOT_DIR)/$(CONN_SRC_INTERNAL_DIR)/%.O: $(SRC_ROOT_DIR)/$(CONN_SRC_INTERNAL_DIR)/%.cpp
	@echo [Compiling] $<
	@$(GXX) -c $(COMPILATION_CPP_FLAGS) $< -o $@

# 
# - ROOT/src/internal/src Directory
# 
$(BUILD_ROOT_DIR)/$(CONN_SRC_INTERNAL_SRC_DIR)/%.o: $(SRC_ROOT_DIR)/$(CONN_SRC_INTERNAL_SRC_DIR)/%.c
	@echo [Compiling] $<
	@$(GCC) -c $(COMPILATION_C_FLAGS) $< -o $@

$(BUILD_ROOT_DIR)/$(CONN_SRC_INTERNAL_SRC_DIR)/%.O: $(SRC_ROOT_DIR)/$(CONN_SRC_INTERNAL_SRC_DIR)/%.cpp
	@echo [Compiling] $<
	@$(GXX) -c $(COMPILATION_CPP_FLAGS) $< -o $@

# 
# - ROOT/src/internal/src/variables Directory
# 
$(BUILD_ROOT_DIR)/$(CONN_SRC_INTERNAL_SRC_VARIABLES_DIR)/%.o: $(SRC_ROOT_DIR)/$(CONN_SRC_INTERNAL_SRC_VARIABLES_DIR)/%.c
	@echo [Compiling] $<
	@$(GCC) -c $(COMPILATION_C_FLAGS) $< -o $@

$(BUILD_ROOT_DIR)/$(CONN_SRC_INTERNAL_SRC_VARIABLES_DIR)/%.O: $(SRC_ROOT_DIR)/$(CONN_SRC_INTERNAL_SRC_VARIABLES_DIR)/%.cpp
	@echo [Compiling] $<
	@$(GXX) -c $(COMPILATION_CPP_FLAGS) $< -o $@





# ************************************************
# Building the library
# 
# ***************************************
library: $(CONN_OBJECTS)
	@$(GXX) -shared -o $(BUILD_ROOT_DIR)/$(OUTPUT_LIB_NAME) $(CONN_OBJECTS) $(COMPILATION_CPP_FLAGS)
	@echo ""
	@echo ""
	@echo "DDS.Net C++ Connector built successfully"





# ************************************************
# Cleaning-up
# 
# ***************************************
clean:
	$(foreach dir, $(CONN_SRCS_DIRS), $(shell rm -f $(BUILD_ROOT_DIR)/$(dir)/*.o 2> /dev/null))
	$(foreach dir, $(CONN_SRCS_DIRS), $(shell rm -f $(BUILD_ROOT_DIR)/$(dir)/*.O 2> /dev/null))
	@rm -f $(BUILD_ROOT_DIR)/$(OUTPUT_LIB_NAME)
	@echo Done cleaning-up the project.





################################################################################
#                            ----------------------                            #
################################################################################

