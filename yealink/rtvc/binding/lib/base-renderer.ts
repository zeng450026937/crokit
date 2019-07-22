import { CanvasVideoRenderer, VideoSink, VideoFrame } from '@/api/video';

export default abstract class BaseRenderer implements CanvasVideoRenderer, VideoSink {
  abstract attach(element: Element): void;

  abstract detach(): void;

  abstract drawFrame(frame: VideoFrame): void;

  onFrame(frame: VideoFrame): void {
    this.drawFrame(frame);
  }
}
