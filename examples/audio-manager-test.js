
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
  audioManager.volume = 100;

  console.log(audioManager.mute)

  console.log("enumerateDevices()")
  audioManager.enumerateDevices();

  console.log('-- audioInputDeviceList --');
  const audioInputDeviceList = audioManager.audioInputDeviceList();
  console.log(audioInputDeviceList);

  audioManager.audioInputDevice = audioInputDeviceList[0];

  console.log('-- audioInputDevice --');
  const audioInputDevice = audioManager.audioInputDevice;
  console.log(audioInputDevice)

  audioManager.recording = true;
  console.log(audioManager.recording);

  setInterval(() => {
    console.log(audioManager.requestAudioVolume());
  }, 300);
}

module.exports = test;
