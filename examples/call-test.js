const path = require('path');
const conference_test = require('./conference-test');

async function test(binding, userAgent) {
  console.log('Call test');

  const { Call, VideoManager, DesktopCapture } = binding;

  const videoManager = new VideoManager();

  console.log('-- enumerateDevices --');
  videoManager.enumerateDevices();

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

  videoManager.acquireStream();

  const call = new Call(userAgent);

  // call.connect('sip:62061**040660@123456.onylyun.com;transport=tls');
  // call.connect('sip:1001@123456.onylyun.com;transport=tls');
  call.connect('sip:1090@223504.onylyun.com;transport=tls');
  //call.connect('sip:90006@123456.onylyun.com;transport=tls');
  //call.setRemoteVideoSink(sink);

  const eventNames = [
    'progress',
    'trying',
    'ringing',
    'redirect',
    'established',
    'focus:prepare',
    'focus:ready',
    'focus:established',
    'focus:finished',
    'share:ready',
    'share:established',
    'share:finished',
    'referFailed',
    'replaceFailed',
    'refered',
    'replaced',
    'upgraded',
    'upgradeFailed',
    'finished',
    'rtc:audioStart',
    'rtc:audioStop',
    'rtc:audioBroken',
    'rtc:videoStart',
    'rtc:videoStop',
    'rtc:videoBroken',
    'rtc:shareRecvStart',
    'rtc:shareRecvStop',
    'rtc:shareSendStart',
    'rtc:shareSendStop',
    'rtc:shareBroken',
  ];

  eventNames.forEach((event) => {
    call.on(event, () => console.log('call event: ' + event));
  });

  // call.upgrade();

  let hangupTimmer;
  let shareTimer;

  call.on('established', async() => {
    console.log('established');

    // call.upgrade();

    hangupTimmer = setTimeout(() => {
      call.hangup();
    }, 15000);
  });

  // call.on('upgraded', async() => {
  call.on('share:established', async() => {
    console.log('share:established');

    setTimeout(async() => {
      const desktopCapture = new DesktopCapture();
      const list = await desktopCapture.getSources({
        captureWindow: true,
        captureScreen: false,
      });

      console.log(list);

      const picture = path.resolve('./test-picture.png');

      console.log(picture);

      call.startShare({ screen: 0, window: 14747790, file: picture });
    }, 1500);

    shareTimer = setTimeout(() => {
      call.stopShare();
    }, 10000);
  })

  call.on('finished', () => {
    console.log('finished');
    clearTimeout(hangupTimmer);
    clearTimeout(shareTimer);
    videoManager.releaseStream();
    videoManager.videoInputDevice = null;
    userAgent.unregister();
  });

  if (global.window) {
    window.call = call;
  }

  // await conference_test(call.conference);
}

module.exports = test;
