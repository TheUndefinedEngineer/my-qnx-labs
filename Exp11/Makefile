PLATFORM ?= x86_64
BUILD_PROFILE ?= debug

CONFIG_NAME ?= $(PLATFORM)-$(BUILD_PROFILE)
OUTPUT_DIR   = build/$(CONFIG_NAME)

SERVER = $(OUTPUT_DIR)/server
CLIENT = $(OUTPUT_DIR)/client

SERVER_SRC = src/server.c
CLIENT_SRC = src/client.c

SERVER_OBJ = $(OUTPUT_DIR)/src/server.o
CLIENT_OBJ = $(OUTPUT_DIR)/src/client.o

CC  = qcc -Vgcc_nto$(PLATFORM)
CXX = q++ -Vgcc_nto$(PLATFORM)_cxx
LD  = $(CC)

#INCLUDES += -I/path/to/my/lib/include
#LIBS     += -L/path/to/my/lib/$(PLATFORM)/usr/lib -lmylib

CCFLAGS_release  += -O2
CCFLAGS_debug    += -g -O0 -fno-builtin
CCFLAGS_coverage += -g -O0 -ftest-coverage -fprofile-arcs
LDFLAGS_coverage += -ftest-coverage -fprofile-arcs
CCFLAGS_profile  += -g -O0 -finstrument-functions
LIBS_profile     += -lprofilingS

CCFLAGS_all += -Wall -fmessage-length=0
CCFLAGS_all += $(CCFLAGS_$(BUILD_PROFILE))
LDFLAGS_all += $(LDFLAGS_$(BUILD_PROFILE))
LIBS_all    += $(LIBS_$(BUILD_PROFILE))

DEPS = -Wp,-MMD,$(@:%.o=%.d),-MT,$@

# Compile rule
$(OUTPUT_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(DEPS) -o $@ $(INCLUDES) $(CCFLAGS_all) $(CCFLAGS) $<

# Link rules
$(SERVER): $(SERVER_OBJ)
	$(LD) -o $@ $(LDFLAGS_all) $(LDFLAGS) $^ $(LIBS_all) $(LIBS)

$(CLIENT): $(CLIENT_OBJ)
	$(LD) -o $@ $(LDFLAGS_all) $(LDFLAGS) $^ $(LIBS_all) $(LIBS)

all: $(SERVER) $(CLIENT)

clean:
	rm -fr $(OUTPUT_DIR)

rebuild: clean all

.PHONY: all clean rebuild

-include $(SERVER_OBJ:.o=.d)
-include $(CLIENT_OBJ:.o=.d)