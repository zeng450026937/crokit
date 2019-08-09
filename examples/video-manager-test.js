function test(binding) {
  console.log('video manager test')

  const { VideoManager } = binding;

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

  console.log('-- screenDeviceList --');
  const screenDeviceList = videoManager.screenDeviceList();
  console.log(screenDeviceList);

  console.log('-- windowDeviceList --');
  const windowDeviceList = videoManager.windowDeviceList();
  console.log(windowDeviceList);

  console.log('-- videoInputDevice --');
  const videoInputDevice = videoManager.videoInputDevice;
  console.log(videoInputDevice);

  console.log('-- secondaryVideoInputDevice --');
  const secondaryVideoInputDevice = videoManager.secondaryVideoInputDevice;
  console.log(secondaryVideoInputDevice);

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
  videoManager.setLocalVideoSink(sink);

  setTimeout(() => {
    videoManager.videoInputDevice = null;
    console.log('video manager test finished.')
  }, 3000);
}

module.exports = test;
