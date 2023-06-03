#
# SRND application makefile
# Copyright (c) 2011 Eray Ozturk <erayozturk1@gmail.com>
#
CC := gcc
STRIP := strip

TARGET_EXEC := srnd_test

SRC_DIRS := .
DEPLOY_DIR := .

SRCS := $(shell find $(SRC_DIRS) -not -name 'SRND_test.c' -name '*.c')

INC_DIRS := $(shell find $(SRC_DIRS) -type d)

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

#debug
#CFLAGS := $(INC_FLAGS) -g3 -o0 -ggdb

#release
CFLAGS := $(INC_FLAGS) -g0 -o2

all: $(TARGET_EXEC)

$(TARGET_EXEC):
	$(CC) $(SRCS) $(CFLAGS) $(EXTRA) -o $(DEPLOY_DIR)/$(TARGET_EXEC) $(SRC_DIRS)/SRND_test.c $(LIBS)

.PHONY: clean
clean:
	rm $(TARGET_EXEC)
