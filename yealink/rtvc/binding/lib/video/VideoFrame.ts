/* eslint-disable lines-between-class-members */
import { VideoFrame, VideoFrameBuffer } from './type';

export class VideoFrameImpl implements VideoFrame {
  private readonly _buffer :VideoFrameBuffer;

  constructor(buffer :VideoFrameBuffer) {
    this._buffer = buffer;
  }

  buffer(): VideoFrameBuffer { return this._buffer; }

  height(): number { return this._buffer.height; }
  width(): number { return this._buffer.width; }
}
