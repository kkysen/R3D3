type Runnable = () => void;

interface Module {
    
    // preamble.js
    
    buffer: ArrayBuffer;
    
    HEAP8: Int8Array;
    HEAP16: Int16Array;
    HEAP32: Int32Array;
    
    HEAPU8: Uint8Array;
    HEAPU16: Uint16Array;
    HEAPU32: Uint32Array;
    
    HEAPF32: Float32Array;
    HEAPF64: Float64Array;
    
    STACKTOP: number;
    
    ccall(ident: string, returnType: string, argTypes: string[], args: any[]): any;
    
    cwrap(ident: string, returnType: string, argTypes: string[]): (...args: any[]) => any;
    
    getValue(ptr: number, type: string): number;
    
    getValue(ptr: number, type: string, noSafe: boolean): number;
    
    setValue(ptr: number, value: number, type: string): void;
    
    setValue(ptr: number, value: number, type: string, noSafe: boolean): void;
    
    Pointer_stringify(ptr: number): string;
    
    Pointer_stringify(ptr: number, length: number): string;
    
    lengthBytesUTF16(str: string): number;
    
    UTF8ToString(ptr: number): string;
    
    stringToUTF8(str: string, outPtr: number, maxBytes: number): void;
    
    lengthBytesUTF32(str: string): number;
    
    UTF16ToString(ptr: number): string;
    
    stringToUTF16(str: number, outPtr: number, maxBytes: number): void;
    
    lengthBytesUTF8(str: string): number;
    
    UTF32ToString(ptr: number): string;
    
    stringToUTF32(str: number, outPtr: number, maxBytes: number): void;
    
    intArrayFromString(str: string, dontAddNull: boolean): number[];
    
    intArrayFromString(str: string, dontAddNull: boolean, length: number): number[];
    
    intArrayToString(array: number[]): string;
    
    writeArrayToMemory<T>(array: T[], buffer: number): void;
    
    writeAsciiToMemory(str: string, buffer: number, dontAddNull: boolean): void;
    
    addRunDependency(id: string): void;
    
    removeRunDependency(id: string): void;
    
    stackTrace(): void; // TODO FIXME
    
    preRun: Runnable[];
    
    postRun: Runnable[];
    
}

declare var Module: Module;