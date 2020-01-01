CFLAGS = -std=c99 $(shell cat build/cflags)

DEPS := $(wildcard vm/*.h)
TEST_OBJS = test vm

.PHONY: all test debug clean

all: test

debug: | build
	@echo "Enabling debug flags"
	@echo "-g -Wall -Wextra -Werror -Wfatal-errors -Wno-unused-variable -Wno-unused-parameter -fsanitize=undefined -fsanitize=address" > build/cflags

build/cflags: | build
	@echo > $@

build:
	@mkdir -p $@

build/%.o: vm/%.c $(DEPS) build/cflags | build
	@echo "CC  $<"
	@$(CC) $(CFLAGS) $< -c -o $@

build/test: $(foreach name,$(TEST_OBJS),build/$(name).o)
	@echo "EXE $@"
	@$(CC) $(CFLAGS) $^ -o $@

test: build/test
	@./build/test

clean:
	rm -f woop
	rm -rf build

