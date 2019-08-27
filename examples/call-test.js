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
      console.log('onFrame', frame.width, frame.height)

      console.log(frame);
      console.log(frame.width);
      console.log(frame.height);
      console.log(frame.size);
      console.log(frame.buffer);

      const i420Buffer = frame.buffer;
      const i420Buffer2 = frame.buffer;

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
    },
  };

  videoManager.videoInputDevice = videoInputDeviceList[0];
  // videoManager.setLocalVideoSink(sink);

  util.inherits(Call, events.EventEmitter);

  const call = new Call(userAgent);

  call.connect('sip:223504.1090@onylyun.com');
  call.setRemoteVideoSink(sink);

  setTimeout(() => {
    call.hangup();
    videoManager.videoInputDevice = null;
    userAgent.unregister();
  }, 10000);
}

module.exports = test;
