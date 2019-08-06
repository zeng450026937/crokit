let binding
try {
  binding = require('D:\\workspace\\crokit\\src\\out\\debug\\rtvc_binding.node');
} catch (error) {
  console.log(error);
  return;
}

console.log(binding);

const { version, UserAgent, audioManager, videoManager, videoFrame } = binding;

console.log(version);

console.log(videoFrame);
console.log(videoFrame.width);
console.log(videoFrame.height);
console.log(videoFrame.size);
console.log(videoFrame.buffer);

const i420Buffer = videoFrame.buffer;
const i420Buffer2 = videoFrame.buffer;

console.log(i420Buffer == i420Buffer2);
console.log(i420Buffer === i420Buffer2);

console.log(i420Buffer);
console.log(i420Buffer.type);
console.log(i420Buffer.width);
console.log(i420Buffer.height);
console.log(i420Buffer.chromaWidth);
console.log(i420Buffer.chromaHeight);
console.log(i420Buffer.strideY);
console.log(i420Buffer.strideU);
console.log(i420Buffer.strideV);
console.log(i420Buffer.dataY);
console.log(i420Buffer.dataU);
console.log(i420Buffer.dataV);
console.log(i420Buffer.toI420());
console.log(i420Buffer.getI420());
console.log(i420Buffer.getI420A());
console.log(i420Buffer.getI444());


console.log(i420Buffer == i420Buffer.toI420());
console.log(i420Buffer === i420Buffer.getI420());
console.log(i420Buffer == i420Buffer.getI420());
console.log(i420Buffer === i420Buffer.getI420());

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

// console.log(audioManager.audioInputDevice)
// audioManager.audioInputDevice = { deviceId: 'testdeviceid', label: 'testdevice', type: 'kAudioOutput' };
// console.log(audioManager.audioInputDevice)

// console.log(videoManager.videoInputDeviceList)
// console.log(videoManager.videoInputDeviceList())

// let video_sink = {}

// videoManager.setLocalVideoSink(video_sink)

// video_sink.onFrame = function() { console.log('onFrame'); }

// videoManager.setLocalVideoSink(video_sink)

// video_sink = {}

// videoManager.setLocalVideoSink(video_sink)


// console.log(videoManager.videoInputDeviceList())
