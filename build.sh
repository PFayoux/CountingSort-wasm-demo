emcc -o counting.html counting.c -O3 -s WASM=1 -s NO_EXIT_RUNTIME=1 \
-s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'writeArrayToMemory', 'getValue']" \
-s EXPORTED_FUNCTIONS="['_malloc', '_free', '_max', '_countingSort']"
