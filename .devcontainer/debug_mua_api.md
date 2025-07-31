- This is the start of how our mua_api.wasm is found
- In this case `path` is `"mua_api.wasm"` as noted by line 50
- Left off at `instantiateAsync` bc need to verify that it's returns are similar or the same, leading to a consistency in ln 697
- TODO: what does `fetch(mua_api.wasm)` in ln 697 resolve to?

ln 34
```javascript
Module["locateFile"] = (path, scriptDirectory_unused) => {
  return path;
}
```

- I'm not sure what import.meta.url is?
ln 46
```javascript
var _scriptName = import.meta.url
```

- Only instance where _scriptName is used
ln 72
```javascript
scriptDirectory = new URL('.', _scriptName).href; // includes trailing slash
```
ln 72 traced
```javascript
scriptDirectory = new URL('.', import.meta.url).href;
```

- Only instance where scriptDirectory is used
ln 50
```javascript
function locateFile(path) {
    if (Module['locateFile']) {
        return Module['locateFile'](path, scriptDirectory);
    }
    ...
}
```
- In other words
ln 50 traced
```javascript
function locateFile(path) {
    return path;
}
```

- Instance usage of `locateFile(path)`
ln 556
```javascript
function findWasmBinary() {
    if (Module['locateFile']) {
        return locateFile('mua_api.wasm');
    }
    ...
}
```
ln 556 traced
```javascript 
function findWasmBinary() {
    return "mua_api.wasm"
}
```

- Instance of `findWasmBinary`
ln 696
```javascript
wasmBinaryFile ??= findWasmBinary();
```
ln 696 traced
```javascript
wasmBinaryFile = "mua_api.wasm"
```

- Definition of `wasmBinary`
- Where is `Module['wasmBinary']` coming from, and what is it?
ln 5533
```javascript
if (Module['wasmBinary']) wasmBinary = Module['wasmBinary'];
```

- Instance of `getWasmImports()`
ln 624
```javascript
function getWasmImports() {
    return {
        'env': wasmImports,
        'wasi_snapshot_preview1': wasmImports
    }
}
```

- Definition of `info`
ln 675
```javascript
var info = getWasmImports();
```
ln 675 traced
```javascript
var info = {
    'env': wasmImports,
    'wasi_snapshot_preview1': wasmImports
}
```
- wasmImports can be found on ln 6101

- Defintion of `readAsync`
ln 82
```javascript
readAsync = async (url) => {
    var response = await fetch(url, {credentials: 'same-origin'});
    if (response.ok) {
        return response.arrayBuffer();
    }
}
```

- Defintion `async function getWasmBinary(binaryFile)`
ln 574
```javascript
async function getWasmBinary(binaryFile) {
    if (!wasmBinary) {
        try {
            var response = await readAsync(binaryFile);
            return new Uint8Array(response);
        }
    }
    return getBinarySync(binaryFile);
}
```

- Defintion of `async function instantiateArrayBuffer(binaryFile, imports)`
ln 590
```javascript
async function instantiateArrayBuffer(binaryFile, imports) {
    try {
        var binary = await getWasmBinary(binaryFile);
        var instance = await WebAssembly.instantiate(binary, imports);
        return instance;
    } ...
}
```
ln 590 traced
```javascript
async function instantiateAsyncBuffer("mua_api.wasm", info) {
    var binary = new Uint8Array((await fetch("mua_api.wasm", {credentials: 'same-origin'})).arrayBuffer());
    var instance = await WebAssembly.instantiate(binary, info);
    return instance;
}

```

- Definition of `async function instantiateAsync(binary, binaryFile, imports)`
ln 606
```javascript
async function instantiateAsync(binary, binaryFile, imports) {
    if (!binary && typeof WebAssembly.instantiateStreaming == 'function') {
        try {
            var response = fetch(binaryFile, {credentials: 'same-origin'});
            var instantiationResult = await WebAssembly.instantiateStreaming(response, imports);
            return instantiationResult;
        }...
    }
    return instantiateArrayBuffer(binaryFile, imports);
}
```

- Defintion of `function receiveInstantiationResult(result)`
ln 665
```javascript
function receiveInstantiationResult(result) {
    return receiveInstance(result['instance']);
}
```

- Instances of `wasmBinaryFile`
ln 697 the end of `async function createWasm()`
```javascript
var result = await instantiateAsync(wasmBinary, wasmBinaryFile, info);
var exports = receiveInstantiationResult(result);
return exports;
```
ln 697 traced
```javascript
var result = await WebAssembly.instantiateStreaming(fetch("mua_api.wasm", {credentials:'same-origin'}), info);
var exports = receiveInstance(result['instance']);
```
ln 564
```javascript
function getBinarySync(file) {
    if (file == wasmBinaryFile && wasmBinary) {
        return new Uint8Array(wasmBinary);
    }
    if (readBinary) {
        return readBinary(file);
    }
}
```

