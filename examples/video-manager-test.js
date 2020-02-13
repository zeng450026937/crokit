let videoManager;

async function wait(duration = 1000) {
  return new Promise((resolve) => {
    setTimeout(resolve, duration);
  });
}

async function test(binding) {
  console.log('video manager test')

  const { VideoManager } = binding;

  videoManager = new VideoManager();

  console.log('-- enumerateDevices --');
  videoManager.enumerateDevices();

  console.log('-- videoInputDeviceList --');
  const videoInputDeviceList = videoManager.videoInputDeviceList();
  console.log(videoInputDeviceList);

  console.log('-- videoInputDevice --');
  const videoInputDevice = videoManager.videoInputDevice;
  console.log(videoInputDevice);

  console.log('-- secondaryVideoInputDevice --');
  const secondaryVideoInputDevice = videoManager.secondaryVideoInputDevice;
  console.log(secondaryVideoInputDevice);

  const sink = {
    onFrame(frame, id) {
      console.log('onFrame', frame.width, frame.height)
      return;
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

      // videoManager.videoInputDevice = null;
      // console.log('video manager test finished.')
    },
  };

  videoManager.videoInputDevice = videoInputDeviceList[0];
  console.log('setLocalVideoSink')
  videoManager.setLocalVideoSink(sink);
  await wait(1 * 1000);

  videoManager.acquireStream();

  await wait(1 * 1000);

  console.log('removeLocalVideoSink')
  videoManager.removeLocalVideoSink(sink)
  await wait(1 * 1000);

  console.log('addLocalVideoSink')
  videoManager.addLocalVideoSink(sink);
  await wait(1 * 1000);

  videoManager.releaseStream();

  const videoSource = {
    sinks: new Set(),
    addSink(sink) {
      console.log('add sink', sink);
      this.sinks.add(sink);
    },
    removeSink(sink) {
      console.log('remove sink', sink);
      this.sinks.delete(sink);
    },
    start() {
      console.log('start')
      this.timer = setInterval(() => {
        console.log('onframe')
        this.sinks.forEach(sink => sink.onFrame({
          width: 640,
          height: 480,
          buffer: new Uint8Array(),
        }));
      }, 1000);
    },
    stop() {
      console.log('stop')
      if (this.timer) {
        clearInterval(this.timer);
      }
    },
  };

  videoManager.setLocalVideoSource(videoSource);

  videoSource.start();

  await wait(3 * 1000);

  videoSource.stop();

  videoManager.destroy();
  videoManager = null;
}

module.exports = test;
