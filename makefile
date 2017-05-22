TARGET_EXEC ?= tau2_capture

# specify compilation directories
BUILD_DIR ?= ./build
SRC_DIR ?= ./src
LIB_DIR ?= ./lib ./lib/wic_sdk ./lib/pleora/
INC_DIR := ./include/wic_sdk ./include/pleora ./include

# identify source files and define objects
SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o) 
DEPS := $(OBJS:.o=.d)

# define the libraries to include
LIBS := -lWIC_SDK -ljpeg -lPvBase -lPvDevice -lPvBuffer -lPvGenICam -lPvTransmitter -lPvVirtualDevice -lPvAppUtils -lPvPersistence -lPvSerial -lPvStream -pthread

# define the flags required by the compiler
INC_FLAGS := $(addprefix -I,$(INC_DIR))
CPPFLAGS ?= -D_UNIX_ -D_LINUX_ -MMD -MP -std=c++0x -Wpedantic
LDFLAGS := $(addprefix -L,$(LIB_DIR)) 

# Tool invocations
# compile the target executable
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

# compile the c-code into object files
$(OBJS): $(SRCS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(INC_FLAGS) $(CPPFLAGS) -c $< -o $@

# define clean recipe
clean:
	$(RM) -r $(BUILD_DIR)

# miscellaneous definitions and inclusions
-include $(DEPS)
MKDIR_P ?= mkdir -p
.PHONY: clean

