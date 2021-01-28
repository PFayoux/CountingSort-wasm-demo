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

You can try the module by serving those file with a web server and open `spaghetti.html` with a browser. Opening the file directly from the file system in a browser will cause the error `Cross-Origin Request Blocked`.

Then you can try the following code in the console : 

```javascript
var spaghetti = Module.cwrap(
            'spaghettiSort',    // name of C function
            'number',    // return type
            ['number', 'number']
        );
var max = Module.cwrap('max', 'number', ['number', 'number']);

// create a new typed array
var myTypedArray = new Int8Array([3,2,1])

// allocate the memory for the array
var ptr = Module._malloc(myTypedArray.length*myTypedArray.BYTES_PER_ELEMENT);

// set the array on the heap
Module.HEAP8.set(myTypedArray, ptr);

// call the C method "max" on the array
var res = max(3, ptr) // should return 3

// call the C method "spaghettiSort" on the array
var sortedArrayPtr = spaghetti(3, ptr) // return the sorted array's pointer address

// Read the value of the sorted array
Module.getValue(sortedArrayPtr, 'i8') // should return 1
Module.getValue(sortedArrayPtr+1, 'i8') // should return 2
Module.getValue(sortedArrayPtr+2, 'i8') // should return 3
```
