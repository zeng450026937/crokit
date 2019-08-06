/* eslint-disable lines-between-class-members */
import { VideoFrameBuffer, VideoFrameType, PlanarYuv8Buffer, I420Buffer, I444Buffer, I420ABuffer } from './type';

export class VideoFrameBufferBase implements VideoFrameBuffer {
  type : VideoFrameType = VideoFrameType.kNative;

  width : number;
  height : number;

  constructor(width: number, height: number) {
    this.width = width;
    this.height = height;
  }

  toI420() : any { return undefined; }

  getI420(): any { return undefined; }

  getI420A(): any { return undefined; }

  getI444(): any { return undefined; }
}

export class PlanarYuv8BufferImpl extends VideoFrameBufferBase implements PlanarYuv8Buffer {
  dataU !: Array<number>;
  dataV !: Array<number>;
  dataY !: Array<number>;

  strideU !: number;
  strideV !: number;
  strideY !: number;

  constructor(options : {
    dataU:Array<number>
    dataV:Array<number>
    dataY:Array<number>
    width : number
    height : number}) {
    super(options.width, options.height);
    this.dataU = options.dataU;
    this.dataV = options.dataV;
    this.dataY = options.dataY;
  }

  chromaHeight(): number {
    return this.height / 2;
  }

  chromaWidth(): number {
    return this.width / 2;
  }
}

export class I420BufferImpl extends PlanarYuv8BufferImpl implements I420Buffer {
  toI420(): any {
    return this;
  }

  getI420(): any {
    return this;
  }
}

export class I420ABufferImpl extends I420BufferImpl implements I420ABuffer {
  strideA !: number;
  dataA !: ArrayBuffer;

  toI420(): any {
    // TBD
    return super.toI420();
  }

  getI420A(): any {
    return this;
  }
}

export class I444BufferImpl extends PlanarYuv8BufferImpl implements I444Buffer {
  toI420(): any {
    // TBD
    return super.toI420();
  }

  getI444(): any {
    return this;
  }
}
