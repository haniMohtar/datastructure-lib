# datastructure-lib

Data structures and algorithms implemented from scratch in C.

## Requirements

- `gcc`
- `make`
- AddressSanitizer and UBSan runtime libraries

On Fedora:

```bash
sudo dnf install gcc make libasan libubsan
```

## Build

```bash
git clone git@github.com:haniMohtar/datastructure-lib.git
cd datastructure-lib
make
```

This builds `build/libdatastructures.a`.

## Run the tests

Run every module's tests:

```bash
make test
```

Run a single module's tests:

```bash
./build/dynamic_array/test_dynamic_array
```

## Clean

```bash
make clean
```

## Use in your own project

The library is built with sanitizers, so link with the same flags. Add an `-I` for each module whose header you include (some modules depend on others, e.g. `stack` needs `dynamic_array`):

```bash
gcc main.c -Idynamic_array -Lbuild -ldatastructures -fsanitize=address,undefined -o main
```

Alternatively, copy a module's `.h` and `.c` files (and any modules it depends on) into your project.

## License

MIT