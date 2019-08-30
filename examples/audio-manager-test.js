
async function test(binding) {
  console.log('AudioManager test')

  const { AudioManager } = binding;

  console.log('constructor()')
  const audioManager = new AudioManager();

  console.log(audioManager.ans);
  console.log(audioManager.aec);
  console.log(audioManager.agc);

  console.log(audioManager.volume)
  audioManager.volume = 1;
  console.log(audioManager.volume)

  console.log(audioManager.mute)

  console.log("enumerateDevices()")
  audioManager.enumerateDevices();

  console.log(audioManager.audioInputDevice)
  audioManager.audioInputDevice = { deviceId: 'testdeviceid', label: 'testdevice', type: 'kAudioOutput' };
  console.log(audioManager.audioInputDevice)
  try {
  audioManager.audioInputDevice = null;
  } catch (error) {
  console.error(error)
  }
  console.log(audioManager.audioInputDevice)
  console.log(audioManager.audioInputDeviceList)
  console.log(audioManager.audioInputDeviceList())

  // setTimeout(() => {
  //   videoManager.videoInputDevice = null;
  // }, 30 * 1000);
}

module.exports = test;
