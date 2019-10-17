
async function test(binding) {
  console.log('AudioManager test')

  const { AudioManager } = binding;

  console.log('constructor()')
  const audioManager = new AudioManager();

  console.log('ans:', audioManager.ans);
  console.log('aec:', audioManager.aec);
  console.log('agc:', audioManager.agc);

  audioManager.volume = 1;
  console.log('volume:', audioManager.volume);
  audioManager.volume = 80;
  console.log('volume:', audioManager.volume);

  console.log('mute:', audioManager.mute)

  console.log("enumerateDevices()")
  audioManager.enumerateDevices();

  console.log('-- audioOutputDeviceList --');
  const audioOutputDeviceList = audioManager.audioOutputDeviceList();
  console.log(audioOutputDeviceList);

  audioManager.audioOutputDevice = audioOutputDeviceList[0];

  console.log('-- audioOutputDevice --');
  const audioOutputDevice = audioManager.audioOutputDevice;
  console.log(audioOutputDevice)

  console.log('-- audioInputDeviceList --');
  const audioInputDeviceList = audioManager.audioInputDeviceList();
  console.log(audioInputDeviceList);

  audioManager.audioInputDevice = audioInputDeviceList[0];

  console.log('-- audioInputDevice --');
  const audioInputDevice = audioManager.audioInputDevice;
  console.log(audioInputDevice)

  audioManager.recording = true;
  console.log('recording:', audioManager.recording);

  audioManager.playback = true;
  console.log('playback:', audioManager.playback);

  setInterval(() => {
    console.log(audioManager.requestAudioVolume());
  }, 300);

  setInterval(() => {
    const tone = '1';
    console.log('playTone:', tone)
    audioManager.playTone(tone);
  }, 3000);
}

module.exports = test;
