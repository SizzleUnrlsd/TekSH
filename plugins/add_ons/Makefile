CC=gcc
CXX=g++
CFLAGS=-fPIC
CXXFLAGS=$(CFLAGS)
LDFLAGS=-shared  -I./include/
PLUGIN_DIR=plugins
C_PLUGINS=$(patsubst %.c,%.so,$(wildcard $(PLUGIN_DIR)/*.c))
CPP_PLUGINS=$(patsubst %.cpp,%.so,$(wildcard $(PLUGIN_DIR)/*.cpp))

all: $(C_PLUGINS) $(CPP_PLUGINS)

$(PLUGIN_DIR)/%.so: $(PLUGIN_DIR)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

$(PLUGIN_DIR)/%.so: $(PLUGIN_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f $(C_PLUGINS) $(CPP_PLUGINS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_BIN)
