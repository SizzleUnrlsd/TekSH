CC=gcc
CFLAGS=-fPIC
LDFLAGS=-shared  -I./include/
PLUGIN_DIR=plugins
PLUGINS=$(patsubst %.c,%.so,$(wildcard $(PLUGIN_DIR)/*.c))

all: $(PLUGINS)

$(PLUGIN_DIR)/%.so: $(PLUGIN_DIR)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f $(PLUGINS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_BIN)