import { createRequire } from "module";

const noodle = createRequire(import.meta.url)(`./lib/${process.platform}/noodle.node`);

export default noodle;
