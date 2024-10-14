# 	Copyright (c) 2024, Signaloid.
#
# 	Permission is hereby granted, free of charge, to any person obtaining a copy
# 	of this software and associated documentation files (the "Software"), to
# 	deal in the Software without restriction, including without limitation the
# 	rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# 	sell copies of the Software, and to permit persons to whom the Software is
# 	furnished to do so, subject to the following conditions:
#
# 	The above copyright notice and this permission notice shall be included in
# 	all copies or substantial portions of the Software.
#
# 	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# 	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# 	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# 	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# 	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# 	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# 	DEALINGS IN THE SOFTWARE.


MAKEFILE_PATH 	:= $(abspath $(firstword $(MAKEFILE_LIST)))
MAKEFILE_DIR 	:= $(dir $(MAKEFILE_PATH))
ROOT_DIR 	:= $(abspath $(MAKEFILE_DIR)/..)


include $(ROOT_DIR)/config.mk
include $(ROOT_DIR)/build/signaloid_c0_microsd/software/include/generated/variables.mak


.PHONY: flash clean print-vars


# 	File paths configuration
SRC_DIR		:= $(FIRMWARE_ROOT_PATH)/src

LD_DIR		:= $(SOFTWARE_BUILD_PATH)/include/generated
LDSCRIPT	:= $(FIRMWARE_ROOT_PATH)/ld/linker.ld
LDSCRIPTS	:= $(LDSCRIPT) $(LD_DIR)/output_format.ld $(LD_DIR)/regions.ld

CSOURCES	:= $(wildcard $(SRC_DIR)/*.c)
CPPSOURCES	:= $(wildcard $(SRC_DIR)/*.cpp)
ASOURCES	:= $(wildcard $(SRC_DIR)/*.S)
ASOURCES	+= $(wildcard $(CPU_DIRECTORY)/*.S)

OBJ_DIR		:= $(SOFTWARE_BUILD_PATH)/.obj

COBJS		:= $(addprefix $(OBJ_DIR)/, $(notdir $(CSOURCES:.c=.o)))
CXXOBJS		:= $(addprefix $(OBJ_DIR)/, $(notdir $(CPPSOURCES:.cpp=.o)))
AOBJS		:= $(addprefix $(OBJ_DIR)/, $(notdir $(ASOURCES:.S=.o)))


# 	Compiler flags configuration
CFLAGS		:= -I$(FIRMWARE_ROOT_PATH)/include
CFLAGS		+= -I$(SOFTWARE_BUILD_PATH)/include
CFLAGS		+= -I$(CPU_DIRECTORY)
CFLAGS		+= -I$(SOC_DIRECTORY)/software/include
CFLAGS		+= $(CPUFLAGS)
CFLAGS		+= -Wall -Wextra
CFLAGS		+= -ffunction-sections
CFLAGS		+= -fdata-sections
CFLAGS		+= -fno-common
CFLAGS		+= -fomit-frame-pointer
CFLAGS		+= -std=gnu17
CFLAGS		+= -Os

CXXFLAGS	:= $(CFLAGS)
CXXFLAGS	+= -std=gnu++20
CXXFLAGS	+= -fno-rtti
CXXFLAGS	+= -fno-exceptions

LFLAGS		:= $(CFLAGS)
LFLAGS		+= -L$(LD_DIR)
LFLAGS		+= -nostartfiles
LFLAGS		+= -Wl,--gc-sections
LFLAGS		+= -Wl,--no-warn-mismatch
LFLAGS		+= -Wl,--script=$(LDSCRIPT)
LFLAGS		+= -Wl,--build-id=none
LFLAGS		+= -Wl,--fatal-warnings


# 	Targets
VPATH      := $(SRC_DIR):$(CPU_DIRECTORY)


all: $(FIRMWARE_BINARY_PATH)

$(FIRMWARE_BINARY_PATH): $(FIRMWARE_ELF_PATH)
	$(QUIET) echo "  OBJCOPY  $@"
	$(QUIET) $(OBJCOPY) -O binary $(FIRMWARE_ELF_PATH) $@

$(FIRMWARE_ELF_PATH): $(COBJS) $(CXXOBJS) $(AOBJS) $(LDSCRIPTS)
	$(QUIET) echo "  LD       $@"
	$(QUIET) $(CC) $(COBJS) $(CXXOBJS) $(AOBJS) $(LFLAGS) -o $@

$(COBJS): $(OBJ_DIR)/%.o : %.c
	$(QUIET) mkdir -p $(OBJ_DIR)
	$(QUIET) echo "  CC       $<	$(notdir $@)"
	$(QUIET) $(CC) -c $< $(CFLAGS) -o $@ -MMD

$(CXXOBJS): $(OBJ_DIR)/%.o: %.cpp
	$(QUIET) mkdir -p $(OBJ_DIR)
	$(QUIET) echo "  CXX      $<	$(notdir $@)"
	$(QUIET) $(CXX) -c $< $(CXXFLAGS) -o $@ -MMD

$(AOBJS): $(OBJ_DIR)/%.o: %.S
	$(QUIET) mkdir -p $(OBJ_DIR)
	$(QUIET) echo "  AS       $<	$(notdir $@)"
	$(QUIET) $(CC) -x assembler-with-cpp -c $< $(CFLAGS) -o $@ -MMD


flash: $(FIRMWARE_BINARY_PATH)
	sudo $(PYTHON) $(TOOLKIT) -t $(DEVICE) -b $(FIRMWARE_BINARY_PATH) -u

clean:
	$(QUIET) rm -rf $(OBJ_DIR)
	$(QUIET) echo "  RM       $(OBJ_DIR)"
	$(QUIET) rm -rf $(FIRMWARE_ELF_PATH)
	$(QUIET) echo "  RM       $(FIRMWARE_ELF_PATH)"
	$(QUIET) rm -rf $(FIRMWARE_BINARY_PATH)
	$(QUIET) echo "  RM       $(FIRMWARE_BINARY_PATH)"


print-vars:
	$(foreach v, $(.VARIABLES), $(if $(filter file,$(origin $(v))), $(info $"    - $(v):    $($(v))$")))
