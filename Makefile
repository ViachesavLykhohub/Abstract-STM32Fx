PROFILE ?= release

DOC_DIR = doc
DOC_FORMAT = html

PREFIX		?= arm-none-eabi-

DEBUG_FLAGS ?= -ggdb3 -O1
STANDARD_FLAGS ?= -std=gnu17 -Os
BUILD_DIR := ./build
SRC_DIR := ./src
INC_DIRS := ./include
SOURCES := abstractSTM32.c
SOURCES += abstractLCD.c
SOURCES += abstractINIT.c
SOURCES += abst_libopencm3.c

CC		= $(PREFIX)gcc
AR		= $(PREFIX)ar

LIB_DIR ?= lib

TARGETS ?= stm32f1 stm32f4

MAKE_FILE_PREFIX = make_
# Do not print "Entering directory ...".
MAKEFLAGS = --no-print-directory

# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
Q := @
endif

LIB_MAKES:=$(addprefix $(MAKE_FILE_PREFIX),$(TARGETS))

# Platform specific variables
include $(LIB_MAKES)

# Compiling and linling library
include Makefile.include

all: | $(BUILD_DIR)/libopencm3.a $(BUILD_DIR)/liblist.a $(BUILD_DIR)/$(ABST_LIBNAME).a

shared:
	$(MAKE) -f $(LIB_MAKES) PREFIX="$(PREFIX)" PROFILE=$(PROFILE) shared

clean:
	$(Q)rm -fr $(BUILD_DIR)
	$(Q)cd $(DOC_DIR) && $(MAKE) clean

documentation:
	$(Q)cd $(DOC_DIR) && $(MAKE) $(DOC_FORMAT)
	$(Q)ln -sf build/html/index.html $(DOC_DIR)/abstractSTM32.html

.PHONY: clean build shared documentation
