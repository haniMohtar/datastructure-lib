CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SRC = dynamic_array/dynamic_array.c
OBJ = $(SRC:.c=.o)

libdatastructures.a: $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test_dynamic_array: dynamic_array/test_dynamic_array.c libdatastructures.a
	$(CC) $(CFLAGS) -Idynamic_array $< -L. -ldatastructures -o $@

test: test_dynamic_array
	./test_dynamic_array

clean:
	rm -f $(OBJ) *.a test_dynamic_array

.PHONY: test clean
