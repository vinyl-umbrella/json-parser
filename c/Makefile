CC=gcc
CFLAGS=-Wall -Wextra -std=c99
TARGET=test
MAIN_SOURCE=main.c

# Try to detect and link JSON libraries if available
LIBS=
INCLUDES=

# Check for cJSON
ifneq ($(shell pkg-config --exists libcjson 2>/dev/null; echo $$?), 0)
    # cJSON not found via pkg-config, try manual detection
    ifneq ($(wildcard /usr/include/cjson/cJSON.h),)
        LIBS += -lcjson
        INCLUDES += -DHAVE_CJSON
        HAVE_CJSON=1
    endif
else
    LIBS += $(shell pkg-config --libs libcjson)
    INCLUDES += $(shell pkg-config --cflags libcjson) -DHAVE_CJSON
    HAVE_CJSON=1
endif

# Check for jansson
ifneq ($(shell pkg-config --exists jansson 2>/dev/null; echo $$?), 0)
    # jansson not found via pkg-config, try manual detection
    ifneq ($(wildcard /usr/include/jansson.h),)
        LIBS += -ljansson
        INCLUDES += -DHAVE_JANSSON
        HAVE_JANSSON=1
    endif
else
    LIBS += $(shell pkg-config --libs jansson)
    INCLUDES += $(shell pkg-config --cflags jansson) -DHAVE_JANSSON
    HAVE_JANSSON=1
endif

# Check for json-c
ifneq ($(shell pkg-config --exists json-c 2>/dev/null; echo $$?), 0)
    # json-c not found via pkg-config, try manual detection
    ifneq ($(wildcard /usr/include/json-c/json.h),)
        LIBS += -ljson-c
        INCLUDES += -DHAVE_JSON_C
        HAVE_JSON_C=1
    endif
else
    LIBS += $(shell pkg-config --libs json-c)
    INCLUDES += $(shell pkg-config --cflags json-c) -DHAVE_JSON_C
    HAVE_JSON_C=1
endif

# Check for parson
ifneq ($(wildcard /usr/include/parson.h),)
    LIBS += -lparson
    INCLUDES += -DHAVE_PARSON
    HAVE_PARSON=1
endif

# Object files for each library
OBJS = main.o
ifdef HAVE_CJSON
OBJS += test_cjson.o
endif
ifdef HAVE_JANSSON
OBJS += test_jansson.o
endif
ifdef HAVE_JSON_C
OBJS += test_jsonc.o
endif
ifdef HAVE_PARSON
OBJS += test_parson.o
endif

# Default target
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

# Main object file
main.o: $(MAIN_SOURCE)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(MAIN_SOURCE)

# Individual library object files
test_cjson.o: test_cjson.c
	$(CC) $(CFLAGS) -DHAVE_CJSON -c test_cjson.c

test_jansson.o: test_jansson.c
	$(CC) $(CFLAGS) -DHAVE_JANSSON -c test_jansson.c

test_jsonc.o: test_jsonc.c
	$(CC) $(CFLAGS) -DHAVE_JSON_C -c test_jsonc.c

test_parson.o: test_parson.c
	$(CC) $(CFLAGS) -DHAVE_PARSON -c test_parson.c

clean:
	rm -f $(TARGET) *.o

.PHONY: clean
