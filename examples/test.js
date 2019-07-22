const addon = require('../out/debug/hello_addon');

console.log(addon.hello);
addon.hello("world", "hell");
console.log(process.version);
