PACKAGE = anipp
VERSION = 0.1.0

TARGET_EXEC  ?= libAnipp.a
BUILD_DIR    ?= ./build
TEST_EXEC    ?= $(BUILD_DIR)/test-driver
SRC_DIRS     ?= ./src ./include/pugixml-1.9/src
TEST_SRC_DIR ?= test/src
TEST_OUT_DIR ?= test/output
TEST_OUT_DIR ?= test/output

dist_files := $(shell find $(SRC_DIRS) -name *.hpp) $(BUILD_DIR)/$(TARGET_EXEC)

SRCS      := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS      := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS      := $(OBJS:.o=.d)
INC_DIRS  := $(shell find $(SRC_DIRS) -type d) /usr/local/Cellar/boost/1.66.0
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) -I/usr/local/Cellar/boost/1.66.0/include

LDFLAGS   := $(INC_FLAGS) -L/usr/local/Cellar/boost/1.66.0/lib -lboost_regex-mt
CPPFLAGS  ?= $(INC_FLAGS) -MMD -MP -std=c++1z

TEST_INC_FLAGS  := -I./src -I$(TEST_SRC_DIR)
TEST_LD_FLAGS   := $(TEST_INC_FLAGS) $(LDFLAGS) -L./build -lAnipp
TEST_CPPFLAGS   ?= $(TEST_INC_FLAGS) -MMD -MP -std=c++1z
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	ar crv $(BUILD_DIR)/$(TARGET_EXEC) $(OBJS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean all test release

release: $(BUILD_DIR)/$(TARGET_EXEC)
	mkdir -p $(PACKAGE)-$(VERSION)
	cp -p $(dist_files) $(PACKAGE)-$(VERSION)
	tar -czvf $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)
	rm -rf $(PACKAGE)-$(VERSION)

all: clean $(BUILD_DIR)/$(TARGET_EXEC)
clean:
	$(RM) -r $(BUILD_DIR) test/output release
	rm -rf $(PACKAGE)-$(VERSION)
	rm -rf $(PACKAGE)-$(VERSION).tar.gz

-include $(DEPS)

test: $(BUILD_DIR)/test-driver
	$(MKDIR_P)  $(TEST_OUT_DIR)

$(BUILD_DIR)/test-driver: $(BUILD_DIR)/test.o
	$(CXX) $< -o $@ $(TEST_LD_FLAGS) -L./build -lAnipp

$(BUILD_DIR)/test.o: $(TEST_SRC_DIR)/test.cpp $(TEST_SRC_DIR)/test.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $(BUILD_DIR)/test.o

MKDIR_P ?= mkdir -p
