const events = require('events');
const util = require('util');

async function test(binding, userAgent) {
  console.log('Call test');

  const { Call, VideoManager } = binding;

  const videoManager = new VideoManager();

  console.log('-- enumerateDevices --');
  videoManager.enumerateDevices();

  console.log('-- enumerateScreenDevices --');
  videoManager.enumerateScreenDevices();

  console.log('-- enumerateWindowDevices --');
  videoManager.enumerateWindowDevices();

  console.log('-- videoInputDeviceList --');
  const videoInputDeviceList = videoManager.videoInputDeviceList();
  console.log(videoInputDeviceList);

  const sink = {
    onFrame(frame) {
    },
  };

  videoManager.videoInputDevice = videoInputDeviceList[0];
  // videoManager.setLocalVideoSink(sink);

  util.inherits(Call, events.EventEmitter);

  const call = new Call(userAgent);

  //console.warn(call.descController);
  //console.warn(call.descController);
  //console.warn(call.descController);

  // console.warn(call.roomController);
  // console.warn(call.roomController);
  // console.warn(call.roomController);

  // console.warn(call.stateController.active);
  // console.warn(call.stateController.lock);

  // call.on('established', () => {
  //   console.warn('call state established');

  //   console.warn(call.stateController);
  //   console.warn(call.stateController);
  //   console.warn(call.stateController);

  //   //console.warn(call.stateController);
  //   //console.warn(call.roomController);
  // })

  //console.warn('node test log-1', call.roomController);
  //console.warn('node test log-2', call.descController);

  // call.on('established', () => {
  //   console.warn('node test log', call.descController);
  //   console.warn('node test log', call.descController.profile);

  //   console.warn('node test log', call.stateController);
  //   console.warn('node test log', call.stateController.active);
  //   console.warn('node test log', call.stateController.lock);
  // });

  call.connect('sip:58972@223504.onylyun.com;transport=tls');
  call.setRemoteVideoSink(sink);

  console.warn('node test log', call.roomController);

  while(1)
  {
    console.warn('node test log', call);
    console.warn('node test log', call.roomController);
  }

  setTimeout(() => {
    call.hangup();
    videoManager.videoInputDevice = null;
    userAgent.unregister();
  }, 60 * 1000);
}

module.exports = test;
