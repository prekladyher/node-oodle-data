import { createRequire } from "module";

export default createRequire(import.meta.url)(`./lib/${process.platform}/noodle.node`);
