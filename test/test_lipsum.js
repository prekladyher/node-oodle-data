import noodle from "@prekladyher/node-oodle-data";

const lipsum = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum";

const input = Buffer.from(lipsum, 'utf-8');
const compressed = Buffer.alloc(input.length + 16);

console.log(`Encoding data of length: ${input.length}`);

const compressedLength = noodle.Compress(9 /* Mermaid */, input, input.length, compressed);

console.log(`Compressed to length: ${compressedLength}`)

const decompressed = Buffer.alloc(input.length);
const decompressedLength = noodle.Decompress(compressed, decompressed, input.length);

console.log(`Decompressed to length: ${decompressedLength}`);

const target = Buffer.from(decompressed, 0, decompressedLength).toString('utf-8');
if (target === lipsum) {
    console.log('Source and target strings match.');
} else {
    console.error(`Unexpected target: ${target}`);
    console.error(decompressed);
}
