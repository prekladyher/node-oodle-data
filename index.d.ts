/**
 * Basic Oodle Data compression support.
 */
declare const Noodle: {

    /**
     * Compress raw input byte array and write compressed data to the output byte array.
     * @param input Input raw data array.
     * @param length Input data byte length.
     * @param output Output compressed byte array.
     * @return Compressed data length or zero when compression failed.
     */
    Compress: (input: Uint8Array, length: number, output: Uint8Array) => number;

    /**
     * Decompress input byte array and write raw data to the output byte array.
     * @param input Input compressed data array.
     * @param output Output raw data array.
     * @param length Output data byte length (has to be known).
     * @return Raw output data length or zero if unable to decompress 
     */
    Decompress: (input: Uint8Array, output: Uint8Array, length: number) => number;

};

export default Noodle;