let binding

try {
  binding = require('D:\\workspace\\crokit\\src\\out\\debug\\rtvc_binding.node');
} catch (error) {
  console.log(error);
  return;
}

console.log(binding.version);

const tests = {
  videoManger : require('./video-manager-test'),
  bootstrap : require('./bootstrap-test'),
};

console.log('simple binding test');

//tests.videoManger(binding);
tests.bootstrap(binding).catch((e) => console.log(e));

// const user_agent = new UserAgent({
//   username: 'my username',
//   password: 'my password',
//   domain: 'my domain',
// });

// console.log(user_agent.username)

// console.log(audioManager.volume)
// audioManager.volume = 1;
// console.log(audioManager.volume)

// console.log(audioManager.mute)

// audioManager.enumerateDevices();

// console.log("enumerateDevices")
// console.log(audioManager.audioInputDevice)
// audioManager.audioInputDevice = { deviceId: 'testdeviceid', label: 'testdevice', type: 'kAudioOutput' };
// console.log(audioManager.audioInputDevice)
// try {
// audioManager.audioInputDevice = null;
// } catch (error) {
// console.error(error)
// }
// console.log(audioManager.audioInputDevice)
// console.log(audioManager.audioInputDeviceList)
// console.log(audioManager.audioInputDeviceList())

// videoManager.enumerateDevices();

// console.log(videoManager.videoInputDeviceList)
// console.log(videoManager.videoInputDeviceList())

// let video_sink = {}

// videoManager.setLocalVideoSink(video_sink)

// video_sink.onFrame = function() { console.log('onFrame'); }

// videoManager.setLocalVideoSink(video_sink)

// video_sink = {}

// videoManager.setLocalVideoSink(video_sink)


// console.log(videoManager.videoInputDeviceList())
