let binding

try {
  binding = require('d:\\workspace\\crokit\\src\\out\\debug\\rtvc_binding.node');
} catch (error) {
  console.log(error);
}

if (global.window) {
  window.binding = binding;
}

console.log(binding);
console.log(binding.version);

const tests = {
  audioManager : require('./audio-manager-test'),
  videoManger : require('./video-manager-test'),
  bootstrap : require('./bootstrap-test'),
  desktopCapture : require('./desktop-capture-test'),
  ytms : require('./ytms-test')
};

console.log('simple binding test');

//tests.audioManager(binding);
//tests.videoManger(binding);
//tests.desktopCapture(binding).catch((e) => console.log(e));
tests.bootstrap(binding).catch((e) => console.log(e));
//tests.ytms(binding).catch((e) => console.log(e));
