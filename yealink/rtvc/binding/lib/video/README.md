###USAGE

####WEBGL

```
import { CanvasVideoSource } from '@/video-renderer/VideoSource';
import { CanvasVideoRendererImpl } from '@/video-renderer/canvas/CanvasVideoRendererImpl';

  private videoSource : CanvasVideoSource = new CanvasVideoSource();
  private videoRenderer : CanvasVideoRendererImpl = new CanvasVideoRendererImpl();
 
  bindElement() {
    this.videoSource.bindVideo(this.sourceVideo);
    this.videoRenderer.attach(this.canvas);

    this.videoSource.addSink(this.videoRenderer);
  } 
  
  startRender() {
    this.videoSource.start();
  }
  
  
  bindElement();
  startRender();
```

####CANVAS

```
import { CanvasVideoSource } from '@/video-renderer/VideoSource';
import { WebGLRendererImpl } from '@/video-renderer/canvas/WebGLRendererImpl';

  private videoSource : CanvasVideoSource = new CanvasVideoSource();
  private videoRenderer : WebGLRendererImpl = new WebGLRendererImpl();
 
  bindElement() {
    this.videoSource.bindVideo(this.sourceVideo);
    this.videoRenderer.attach(this.canvas);

    this.videoSource.addSink(this.videoRenderer);
  } 
  
  startRender() {
    this.videoSource.start();
  }
  
  
  bindElement();
  startRender();
```
