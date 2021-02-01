# Counting Sort Web Assembly demo 

This is a Web Assembly demo using emscripten.

## Getting Started

First of all you will need to install emscripten and configure your environment, you can do it by following the official [documentation](https://emscripten.org/docs/getting_started/downloads.html).

When your installation is complete, you can run the following command to build our wasm module :

```bash
emcc -o counting.html counting.c -O3 -s WASM=1 -s NO_EXIT_RUNTIME=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'writeArrayToMemory', 'getValue']" -s EXPORTED_FUNCTIONS="['_malloc', '_free', '_max', '_countingSort']"
```

Or run the `build` script :

```bash
$ ./build
```

This will generate the files : 

 * counting.html
 * counting.js
 * counting.wasm

You can try the module by serving those file with a web server and open `counting.html` with a browser. Opening the file directly from the file system in a browser will cause the error `Cross-Origin Request Blocked`.

Then you can try the following code in the console : 

```javascript
var counting = Module.cwrap(
            'countingSort',    // name of C function
            'number',    // return type
            ['number', 'number']
        );
var max = Module.cwrap('max', 'number', ['number', 'number']);

// create a new typed array
var myTypedArray = new Uint8Array([3,2,1,5,19,4,7,6,9,10,11,14,12,13,16,17,15,18,20,21,8]);

// allocate the memory for the array
var ptr = Module._malloc(myTypedArray.length*myTypedArray.BYTES_PER_ELEMENT);

// set the array on the heap
Module.HEAPU8.set(myTypedArray, ptr);

// call the C method "max" on the array
var res = max(myTypedArray.length, ptr); // should return 21

// call the C method "countingSort" on the array
var sortedArrayPtr = counting(myTypedArray.length, ptr); // return the sorted array's pointer address

// Read the value of the sorted array
Module.getValue(sortedArrayPtr, 'i8'); // should return 1
Module.getValue(sortedArrayPtr+1, 'i8'); // should return 2
Module.getValue(sortedArrayPtr+2, 'i8'); // should return 3
// ...
```
