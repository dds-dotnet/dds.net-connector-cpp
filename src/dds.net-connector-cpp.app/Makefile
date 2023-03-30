# Building DDS.Net Connected C++ App
################################################################################
# Edited
# -------------------------------------------------------------------------
# On                  | By                    | Remarks
# -------------------------------------------------------------------------
#                     |                       |
#                     |                       |
#                     |                       |
#                     |                       |
#                     |                       |
#                     |                       |
#                     |                       |
################################################################################

GCC    = gcc
GXX    = g++
LDGCC  = g++
LD     = $(LDGCC)


# 
# Paths' setting
# 
THIS_DIR           = $(PWD)
CONNECTOR_DIR      = $(THIS_DIR)/../dds.net-connector-cpp.lib/
CONNECTOR_INC_DIR  = $(CONNECTOR_DIR)/connector/inc
CONNECTOR_LIB_DIR  = $(CONNECTOR_DIR)/build
CONNECTOR_LIB_FILE = $(CONNECTOR_LIB_DIR)/dds.net.connector.cpplib


# 
# Building the application
# 
application: 
	@if [ ! -f $(CONNECTOR_LIB_FILE) ]; then cd $(CONNECTOR_DIR); make; cd $(THIS_DIR); fi
	@$(GXX) -c test-app.cpp -I$(CONNECTOR_INC_DIR) -o app.o
	@$(GXX) app.o $(CONNECTOR_LIB_FILE) -o app
	@rm app.o
	@echo Build completed


# 
# Cleaning-up
# 
clean:
	@rm -f app.o
	@rm -f app
	@echo Project cleaned


################################################################################
#                            ----------------------                            #
################################################################################

