TARGET_EXEC ?= a.out

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src ./include/pugixml-1.9/src ./test
TEST_OUT_DIR ?= test/output
# ./include

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d) /usr/local/Cellar/boost/1.66.0
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) -I/usr/local/Cellar/boost/1.66.0/include

LDFLAGS := $(INC_FLAGS) -L/usr/local/Cellar/boost/1.66.0/lib -lboost_regex-mt

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++11

COMMON_DOC_FLAGS = --report --merge docs --output html $(SRCS)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# $(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
# 	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# # assembly
# $(BUILD_DIR)/%.s.o: %.s
# 	$(MKDIR_P) $(dir $@)
# 	$(AS) $(ASFLAGS) -c $< -o $@
#
# # c source
# $(BUILD_DIR)/%.c.o: %.c
# 	$(MKDIR_P) $(dir $@)
# 	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# FIXME: this does NOT work because if clang version and python binding issues :(
# doc:
# 	@echo "Generating documentation..."; \
# 	cldoc generate $(CPPFLAGS) -- $(COMMON_DOC_FLAGS)
#
# static-doc:
# 	@echo "Generating static documentation..."; \
# 	cldoc generate $(CPPFLAGS) -- --static $(COMMON_DOC_FLAGS)
#
# serve:
# 	cldoc serve html


.PHONY: clean all test

all: clean $(BUILD_DIR)/$(TARGET_EXEC) 
clean:
	$(RM) -r $(BUILD_DIR) test/output

-include $(DEPS)

test: clean $(BUILD_DIR)/$(TARGET_EXEC) 
	$(MKDIR_P)  $(TEST_OUT_DIR)

MKDIR_P ?= mkdir -p
