CC       = gcc
CFLAGS   = -Wall -Wextra -std=c11 -g -fsanitize=address,undefined -MMD -MP
BUILD    = build

INCLUDES = $(addprefix -I,$(sort $(dir $(wildcard */*.h))))

LIB_SRC  = $(filter-out $(wildcard */test_*.c),$(wildcard */*.c))
LIB_OBJ  = $(LIB_SRC:%.c=$(BUILD)/%.o)
LIB      = $(BUILD)/libdatastructures.a

TEST_SRC = $(wildcard */test_*.c)
TEST_BIN = $(TEST_SRC:%.c=$(BUILD)/%)

all: $(LIB)

$(LIB): $(LIB_OBJ)
	ar rcs $@ $^

$(BUILD)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_BIN): $(BUILD)/%: %.c $(LIB)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) $< -L$(BUILD) -ldatastructures -o $@

test: $(TEST_BIN)
	@for t in $(TEST_BIN); do echo "== $$t"; ./$$t || exit 1; done

clean:
	rm -rf $(BUILD)

-include $(LIB_OBJ:.o=.d)

.PHONY: all test clean