
export enum VideoFrameType {
  kNative = 0,
  kI420 = 1,
  kI420A = 2,
  kI444 = 3,
}

export interface VideoFrameBuffer {
  type: VideoFrameType;

  width: number;
  height : number;

  toI420(): I420Buffer;

  getI420(): I420Buffer;
  getI420A(): I420ABuffer;
  getI444(): I444Buffer;
}

export interface PlanarYuv8Buffer extends VideoFrameBuffer {
  chromaWidth(): number;
  chromaHeight(): number;

  strideY: number;
  strideU: number;
  strideV: number;

  dataY: ArrayBuffer;
  dataU: ArrayBuffer;
  dataV: ArrayBuffer;
}

export interface I420Buffer extends PlanarYuv8Buffer {
}

export interface I420ABuffer extends I420Buffer {
  strideA: number;

  dataA: ArrayBuffer;
}

export interface I444Buffer extends PlanarYuv8Buffer {
}

export interface VideoFrame {
  width(): number;
  height(): number;

  buffer(): VideoFrameBuffer;
}

export interface VideoSink {
  onFrame(frame: VideoFrame, id: number): void;
}

export interface VideoSource {
  addSink(sink: VideoSink): void;
  removeSink(sink: VideoSink): void;
}

export interface VideoProcessor {
  setSink(sink: VideoSink): void;
}

export interface VideoRenderer {
  drawFrame(frame: VideoFrame): void;
}

export interface CanvasVideoRenderer extends VideoRenderer {
  attach(element: Element): void;
  detach(): void;
}
