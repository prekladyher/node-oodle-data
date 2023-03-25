import { createRequire } from "module";

let variant = null;

if (process.platform === 'win32') {
    variant = 'win32';
} else if (process.arch === 'x64') {
    variant = 'amd64';
} else if (process.arch === 'arm64') {
    variant = 'arm64';
}

const noodle = createRequire(import.meta.url)(`./lib/${variant}/noodle.node`);

export default noodle;
