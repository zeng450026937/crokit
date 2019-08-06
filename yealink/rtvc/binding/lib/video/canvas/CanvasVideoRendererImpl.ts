/* eslint-disable lines-between-class-members */
import { VideoFrame, VideoRenderer, CanvasVideoRenderer } from '../type';
import { PlanarYuv8BufferImpl } from '../Buffer';

const YUVBuffer = require('yuv-buffer');
const YUVCanvas = require('yuv-canvas');

export class CanvasVideoRendererImpl implements CanvasVideoRenderer {
  private yuvContext !:any;
  private canvas !: HTMLCanvasElement;

  public attach(canvas: HTMLCanvasElement) : void {
    this.canvas = canvas;
    this.yuvContext = YUVCanvas.attach(canvas, { webGL: false });
  }

  public detach() : void {
    this.yuvContext = null;
  }

  public onFrame(frame : VideoFrame) :void {
    requestAnimationFrame(() => this.drawFrame(frame));
  }

  public drawFrame(videoFrame : VideoFrame) : void {
    if (!this.yuvContext) throw new Error('Haven\'t bind Canvas');

    const width = videoFrame.width();
    const height = videoFrame.height();

    this.refreshCanvas(width, height);

    const format = YUVBuffer.format({
      width,
      height,
      chromaWidth  : width / 2,
      chromaHeight : height / 2,
    });
    const frame = {
      format,
      y : YUVBuffer.lumaPlane(format),
      u : YUVBuffer.chromaPlane(format),
      v : YUVBuffer.chromaPlane(format),
    };

    const { dataY, dataU, dataV } = <PlanarYuv8BufferImpl> videoFrame.buffer();

    this.loadBrightness(dataY, frame.y.bytes, frame.y.stride, format.width, format.height);
    this.loadBrightness(dataU, frame.u.bytes, frame.u.stride, format.chromaWidth, format.chromaHeight);
    this.loadBrightness(dataV, frame.v.bytes, frame.v.stride, format.chromaWidth, format.chromaHeight);

    this.yuvContext.drawFrame(frame);
  }

  public refreshCanvas(width: number, height: number) : void {
    this.canvas.width = width;
    this.canvas.height = height;
  }

  private loadBrightness(imageData: Array<number>,
                         bytes: Uint8Array, stride: number,
                         width: number, height: number): VideoRenderer {
    const clampedBytes = new Uint8ClampedArray(bytes.buffer, bytes.byteOffset, bytes.byteLength);

    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        clampedBytes[y * stride + x] = imageData[y * width + x];
      }
    }

    return this;
  }
}
