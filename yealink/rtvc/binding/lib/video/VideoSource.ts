/* eslint-disable lines-between-class-members */
import { VideoSink, VideoSource } from './type';
import { PlanarYuv8BufferImpl } from './Buffer';
import { VideoFrameImpl } from './VideoFrame';
import { rgbaToYuv } from './utils';


export class VideoSourceBase implements VideoSource {
  protected sinks: Set<VideoSink>;

  constructor() {
    this.sinks = new Set();
  }

  public addSink(sink : VideoSink): void {
    this.sinks.add(sink);
  }

  public removeSink(sink: VideoSink) : void {
    this.sinks.delete(sink);
  }
}

export class CanvasVideoSource extends VideoSourceBase {
  private frameRate :number = 24; // per second frame
  private video !: HTMLVideoElement;
  private canvas !: HTMLCanvasElement;
  private renderTimer !: number;

  constructor(video ?: HTMLVideoElement) {
    super();
    if (video) this.video = video;
    this.canvas = document.createElement('canvas');
  }

  bindVideo(video : HTMLVideoElement) {
    this.video = video;
  }

  unbind() {
    this.stop();
    if (this.sinks) this.sinks.clear();
    delete this.video;
    delete this.canvas;
  }

  start() {
    this.stop();
    this.captureImageData();
  }

  stop() {
    if (this.renderTimer) clearInterval(this.renderTimer);
  }

  private setFrameRate(frameRate: number) {
    this.frameRate = frameRate;
  }

  private suitableStride(len: number) {
    const alignment = 4;
    const remainder = len % alignment;

    return remainder === 0 ? len : len + (alignment - remainder);
  }

  private captureImageData() {
    this.canvas.width = this.video.videoWidth;
    this.canvas.height = this.video.videoHeight;

    const context = this.canvas.getContext('2d');

    if (!context) throw new Error('Error get Context.');
    context.drawImage(this.video, 0, 0);

    const imageData = context.getImageData(0, 0, this.canvas.width, this.canvas.height);

    this.onCaptured(imageData);

    this.renderTimer = setTimeout(() => this.captureImageData(), 1000 / this.frameRate);
  }

  private onCaptured(imageData : ImageData) {
    const width = this.video.videoWidth;
    const height = this.video.videoHeight;

    // NOTICE NO PERFORMANCE PROBLEM
    const yuvData = rgbaToYuv(imageData.data, width, height);

    const buffer = new PlanarYuv8BufferImpl({
      dataU  : yuvData.u,
      dataV  : yuvData.v,
      dataY  : yuvData.y,
      width  : this.suitableStride(width),
      height : this.suitableStride(height),
    });

    const videoFrame = new VideoFrameImpl(buffer);

    this.sinks.forEach((sink) => sink.onFrame(videoFrame));
  }
}
