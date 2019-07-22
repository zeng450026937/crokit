import { VideoFrame } from '../api/video';
import BaseRenderer from './base-renderer';

export default class YuvRenderer extends BaseRenderer {
  element: Element | null = null;

  frame: VideoFrame | null = null;

  attach(element: Element): void {
    this.element = element;
  }

  detach(): void {
    this.element = null;
  }

  drawFrame(frame: VideoFrame): void {
    this.frame = frame;
  }
}
