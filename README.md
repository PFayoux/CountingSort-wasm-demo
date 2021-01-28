# Spaghetti Sort Web Assembly demo 

This is a Web Assembly demo using emscripten.

## Getting Started

First of all you will need to install emscripten and configure your environment, you can do it by following the official [documentation](https://emscripten.org/docs/getting_started/downloads.html).

When your installation is complete, you can run the following command to build our wasm module :

```bash
emcc -o spaghetti.html spaghetti.c -O3 -s WASM=1 -s NO_EXIT_RUNTIME=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'writeArrayToMemory', 'getValue']" -s EXPORTED_FUNCTIONS="['_malloc', '_free', '_max', '_spaghettiSort']"
```

Or run the `build` script :

```bash
$ ./build
```

This will generate the files : 

 * spaghetti.html
 * spaghetti.js
 * spaghetti.wasm

You can try the module by serving those file with a web server and open `spaghetti.html`.


