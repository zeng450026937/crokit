// import { CanvasVideoRenderer, VideoRenderer } from './VideoRenderer';
// import { VideoSource } from './VideoSource';
// import { VideoFrame } from './VideoFrame';
// import { VideoProcessor } from './VideoProcessor';
// import { VideoSink } from './VideoSink';
//
// const videoRenderer = new CanvasVideoRenderer();
//
// videoRenderer.attach(document.createElement('canvas'));
//
// const videoSource = new VideoSource();
// const videoSink = new VideoSink();
// const rederer = new CanvasVideoRenderer();
//
// rederer.attach(new HTMLCanvasElement());
//
// // const videoProcessor = new VideoProcessor(videoSource);
// //
// // videoProcessor.setSink(videoSink); // | videoSource.addSink(videoSink);
// videoSource.addSink(videoSink);
// videoSource.addSink(rederer);
//
// for (let i = 0; i < 100; i++) {
//   // videoSink.onFrame(new VideoFrame());// | videoRenderer.drawFrame(new VideoFrame());
// }
