/* eslint-disable lines-between-class-members */
import { VideoFrame, VideoRenderer, CanvasVideoRenderer } from '../type';
import { PlanarYuv8BufferImpl } from '../Buffer';
import {
  VERTEX_SHADER, FRAGMENT_SHADER,
  vertex, fragment, vertexStripe, fragmentStripe,
} from './shader';
import { lumaPlane, chromaPlane } from '../utils';

const rectangle = new Float32Array([
  // First triangle (top left, clockwise)
  -1.0, -1.0,
  +1.0, -1.0,
  -1.0, +1.0,

  // Second triangle (bottom right, clockwise)
  -1.0, +1.0,
  +1.0, -1.0,
  +1.0, +1.0,
]);


export class WebGLRendererImpl implements CanvasVideoRenderer {
  private gl !: WebGLRenderingContext;
  private canvas !: HTMLCanvasElement;
  // unpack
  private unpackProgram !: WebGLProgram;
  private unpackPositionLocation !: GLint;
  private unpackTexturePositionLocation !: GLint;
  private stripeLocation !: WebGLUniformLocation;
  private unpackTextureLocation !: WebGLUniformLocation;
  private unpackTexturePositionBuffer !: WebGLBuffer;
  // program
  private program !: WebGLProgram;
  private buffer !: WebGLBuffer;
  private positionLocation !: GLint;
  private lumaPositionLocation !: GLint;
  private chromaPositionLocation !: GLint;
  private lumaPositionBuffer !: WebGLBuffer;
  private chromaPositionBuffer !: WebGLBuffer;
  // textures
  private textures : Map<string, WebGLTexture> = new Map<string, WebGLTexture>();
  // stripes
  private stripes : Map<number, Uint8Array> = new Map<number, Uint8Array>();
  private frameBuffers : Map<string, WebGLFramebuffer> = new Map<string, WebGLFramebuffer>();

  private readonly stripe : boolean;

  constructor() {
    this.stripe = navigator.userAgent.indexOf('Windows') !== -1;
  }


  public attach(canvas: HTMLCanvasElement) : void {
    this.canvas = canvas;

    const context = this.canvas.getContext('webgl',
      {
        powerPreference              : 'low-power',
        failIfMajorPerformanceCaveat : true,
        preserveDrawingBuffer        : true,
      })
      || this.canvas.getContext('experimental-webgl');

    if (!context) throw new Error('Error Creating WebGL Context');
    this.gl = context;
    this.clear();
  }

  public detach() : void {
    const context = this.gl.getExtension('WEBGL_lose_context');

    if (context) context.loseContext();

    this.textures.forEach(this.gl.deleteTexture);
    this.frameBuffers.forEach(this.gl.deleteFramebuffer);

    this.stripes.clear();
    this.textures.clear();
    this.frameBuffers.clear();
    this.gl.deleteProgram(this.unpackProgram);
    this.gl.deleteProgram(this.program);
    this.gl.deleteBuffer(this.buffer);
    this.gl.deleteBuffer(this.unpackTexturePositionBuffer);
    this.gl.deleteBuffer(this.lumaPositionBuffer);
    this.gl.deleteBuffer(this.chromaPositionBuffer);
    //

    // unpack
    delete this.unpackProgram;
    delete this.unpackPositionLocation;
    delete this.unpackTexturePositionLocation;
    delete this.stripeLocation;
    delete this.unpackTextureLocation;
    delete this.unpackTexturePositionBuffer;
    // program
    delete this.program;
    delete this.buffer;
    delete this.positionLocation;
    delete this.lumaPositionLocation;
    delete this.chromaPositionLocation;
    delete this.lumaPositionBuffer;
    delete this.chromaPositionBuffer;

    delete this.gl;
    delete this.canvas;
  }

  public onFrame(frame : VideoFrame) :void {
    requestAnimationFrame(() => this.drawFrame(frame));
  }

  public drawFrame(videoFrame : VideoFrame) : void {
    if (!this.canvas) throw new Error('Haven\'t bind Canvas');

    const width = videoFrame.width();
    const height = videoFrame.height();

    this.refreshCanvas(width, height);

    const _format = (fields : any) => {
      const chromaWidth = fields.chromaWidth || width;
      const chromaHeight = fields.chromaHeight || height;
      const cropLeft = fields.cropLeft || 0;
      const cropTop = fields.cropTop || 0;
      const cropWidth = fields.cropWidth || width - cropLeft;
      const cropHeight = fields.cropHeight || height - cropTop;
      const displayWidth = fields.displayWidth || cropWidth;
      const displayHeight = fields.displayHeight || cropHeight;


      return {
        width  : fields.width,
        height : fields.height,
        chromaWidth,
        chromaHeight,
        cropLeft,
        cropTop,
        cropWidth,
        cropHeight,
        displayWidth,
        displayHeight,
      };
    };

    const format = _format({ // TODO add format params
      width,
      height,
      chromaWidth  : width / 2,
      chromaHeight : height / 2,
    });
    const frame = {
      format,
      y : lumaPlane(format.width, format.height),
      u : chromaPlane(format.chromaWidth, format.chromaHeight),
      v : chromaPlane(format.chromaWidth, format.chromaHeight),
    };

    const { dataY, dataU, dataV } = <PlanarYuv8BufferImpl> videoFrame.buffer();

    this.loadBrightness(dataY, frame.y.bytes, frame.y.stride, format.width, format.height);
    this.loadBrightness(dataU, frame.u.bytes, frame.u.stride, format.chromaWidth, format.chromaHeight);
    this.loadBrightness(dataV, frame.v.bytes, frame.v.stride, format.chromaWidth, format.chromaHeight);


    this.renderFrame(frame);
  }

  public renderFrame(buffer: any) : WebGLRendererImpl {
    const { gl } = this;

    const { format } = buffer;
    const formatUpdate = (!this.program
      || this.canvas.width !== format.displayWidth
      || this.canvas.height !== format.displayHeight);

    if (formatUpdate) {
      // Keep the canvas at the right size...
      this.canvas.width = format.displayWidth;
      this.canvas.height = format.displayHeight;
      this.clear();
    }

    if (!this.program) {
      this.initRender();
    }

    //
    // this.initRender();
    if (formatUpdate) {
      const setupTexturePosition = (_buffer:WebGLBuffer, location:WebGLUniformLocation, texWidth:number) => {
        const textureX0 = format.cropLeft / texWidth;
        const textureX1 = (format.cropLeft + format.cropWidth) / texWidth;
        const textureY0 = (format.cropTop + format.cropHeight) / format.height;
        const textureY1 = format.cropTop / format.height;
        const textureRectangle = new Float32Array([
          textureX0, textureY0,
          textureX1, textureY0,
          textureX0, textureY1,
          textureX0, textureY1,
          textureX1, textureY0,
          textureX1, textureY1,
        ]);

        this.gl.bindBuffer(this.gl.ARRAY_BUFFER, _buffer);
        this.gl.bufferData(this.gl.ARRAY_BUFFER, textureRectangle, this.gl.STATIC_DRAW);
      };

      setupTexturePosition(
        this.lumaPositionBuffer,
        this.lumaPositionLocation,
        buffer.y.stride
      );
      setupTexturePosition(
        this.chromaPositionBuffer,
        this.chromaPositionLocation,
        buffer.u.stride * format.width / format.chromaWidth
      );
    }

    // Create or update the textures...
    this.uploadTexture('uTextureY', buffer.y.stride, format.height, buffer.y.bytes);
    this.uploadTexture('uTextureCb', buffer.u.stride, format.chromaHeight, buffer.u.bytes);
    this.uploadTexture('uTextureCr', buffer.v.stride, format.chromaHeight, buffer.v.bytes);

    if (this.stripe) {
      // Unpack the textures after upload to avoid blocking on GPU
      this.unpackTexture('uTextureY', buffer.y.stride, format.height);
      this.unpackTexture('uTextureCb', buffer.u.stride, format.chromaHeight);
      this.unpackTexture('uTextureCr', buffer.v.stride, format.chromaHeight);
    }

    // Set up the rectangle and draw it
    gl.useProgram(this.program);
    gl.viewport(0, 0, this.canvas.width, this.canvas.height);

    this.attachTexture('uTextureY', gl.TEXTURE0, 0);
    this.attachTexture('uTextureCb', gl.TEXTURE1, 1);
    this.attachTexture('uTextureCr', gl.TEXTURE2, 2);

    // Set up geometry
    gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer);
    gl.enableVertexAttribArray(this.positionLocation);
    gl.vertexAttribPointer(this.positionLocation, 2, gl.FLOAT, false, 0, 0);

    // Set up the texture geometry...
    gl.bindBuffer(gl.ARRAY_BUFFER, this.lumaPositionBuffer);
    gl.enableVertexAttribArray(this.lumaPositionLocation);
    gl.vertexAttribPointer(this.lumaPositionLocation, 2, gl.FLOAT, false, 0, 0);

    gl.bindBuffer(gl.ARRAY_BUFFER, this.chromaPositionBuffer);
    gl.enableVertexAttribArray(this.chromaPositionLocation);
    gl.vertexAttribPointer(this.chromaPositionLocation, 2, gl.FLOAT, false, 0, 0);

    // Aaaaand draw stuff.
    gl.drawArrays(gl.TRIANGLES, 0, rectangle.length / 2);

    return this;
  }

  private initRender() : WebGLRendererImpl {
    if (this.stripe) {
      const unpackProgram = this.initProgram(vertexStripe, fragmentStripe);
      const unpackPositionLocation = this.gl.getAttribLocation(unpackProgram, 'aPosition');
      const unpackTexturePositionBuffer = this.gl.createBuffer();

      if (!unpackTexturePositionBuffer) throw new Error('Error Creating Buffer');

      const textureRectangle = new Float32Array([
        0, 0, 1, 0, 0, 1,
        0, 1, 1, 0, 1, 1,
      ]);

      this.gl.bindBuffer(this.gl.ARRAY_BUFFER, unpackTexturePositionBuffer);
      this.gl.bufferData(this.gl.ARRAY_BUFFER, textureRectangle, this.gl.STATIC_DRAW); // STATIC_DRAW

      const unpackTexturePositionLocation = this.gl.getAttribLocation(unpackProgram, 'aTexturePosition');
      const stripeLocation = this.gl.getUniformLocation(unpackProgram, 'uStripe');
      const unpackTextureLocation = this.gl.getUniformLocation(unpackProgram, 'uTexture');

      if (!stripeLocation || !unpackTextureLocation) throw new Error('Error Get Uniform Location');

      this.unpackProgram = unpackProgram;
      this.unpackPositionLocation = unpackPositionLocation;
      this.unpackTexturePositionBuffer = unpackTexturePositionBuffer;
      this.unpackTexturePositionLocation = unpackTexturePositionLocation;
      this.stripeLocation = stripeLocation;
      this.unpackTextureLocation = unpackTextureLocation;
    }

    const program = this.initProgram(vertex, fragment);

    const buffer = this.gl.createBuffer();

    if (!buffer) throw new Error('Error Creating Buffer');
    this.gl.bindBuffer(this.gl.ARRAY_BUFFER, buffer);
    this.gl.bufferData(this.gl.ARRAY_BUFFER, rectangle, this.gl.STATIC_DRAW); // STATIC_DRAW

    const positionLocation = this.gl.getAttribLocation(program, 'aPosition');
    const lumaPositionBuffer = this.gl.createBuffer();
    const lumaPositionLocation = this.gl.getAttribLocation(program, 'aLumaPosition');
    const chromaPositionBuffer = this.gl.createBuffer();
    const chromaPositionLocation = this.gl.getAttribLocation(program, 'aChromaPosition');

    if (!lumaPositionBuffer || !chromaPositionBuffer) throw new Error('Error Get Uniform Location');

    this.positionLocation = positionLocation;
    this.lumaPositionBuffer = lumaPositionBuffer;
    this.lumaPositionLocation = lumaPositionLocation;
    this.chromaPositionBuffer = chromaPositionBuffer;
    this.chromaPositionLocation = chromaPositionLocation;

    this.program = program;
    this.buffer = buffer;


    return this;
  }

  private createOrReuseTexture(name : string) : WebGLTexture {
    let temTexture :any = this.textures.get(name);

    if (!temTexture) {
      temTexture = this.gl.createTexture();

      if (!temTexture) throw new Error('Error Creating Texture');
      this.textures.set(name, temTexture);
    }

    return temTexture;
  }

  private initProgram(vertexShaderSource : VERTEX_SHADER,
                      fragmentShaderSource : FRAGMENT_SHADER) : WebGLProgram {
    const { gl } = this;

    const compileShader = (type : number, source : string) => {
      const shader = gl.createShader(type);

      if (!shader) throw new Error('Error creating Shader.');
      gl.shaderSource(shader, source);
      gl.compileShader(shader);

      if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        const err = gl.getShaderInfoLog(shader);

        gl.deleteShader(shader);
        throw new Error(`GL shader compilation for ${type} failed: ${err}`);
      }

      return shader;
    };

    const vertexShader = compileShader(gl.VERTEX_SHADER, vertexShaderSource);
    const fragmentShader = compileShader(gl.FRAGMENT_SHADER, fragmentShaderSource);

    const program = gl.createProgram();

    if (!program) throw new Error('Error creating Program.');

    gl.attachShader(program, vertexShader);
    gl.attachShader(program, fragmentShader);

    gl.linkProgram(program);
    if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
      const err = gl.getProgramInfoLog(program);

      gl.deleteProgram(program);
      throw new Error(`GL program linking failed: ${err}`);
    }

    return program;
  }

  private uploadTexture(name : string,
                        width : number,
                        height: number,
                        data: ArrayBufferView) : WebGLRendererImpl {
    const texture = this.createOrReuseTexture(name);
    const { gl } = this;

    gl.activeTexture(gl.TEXTURE0);

    if (this.stripe) {
      const uploadTemp = !this.textures.get(`${name}_temp`);
      const tempTexture = this.createOrReuseTexture(`${name}_temp`);

      gl.bindTexture(gl.TEXTURE_2D, tempTexture);
      if (uploadTemp) {
        // new texture
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texImage2D(
          gl.TEXTURE_2D,
          0, // mip level
          gl.RGBA, // internal format
          width / 4,
          height,
          0, // border
          gl.RGBA, // format
          gl.UNSIGNED_BYTE, // type
          data // data!
        );
      }
      else {
        // update texture
        gl.texSubImage2D(
          gl.TEXTURE_2D,
          0, // mip level
          0, // x offset
          0, // y offset
          width / 4,
          height,
          gl.RGBA, // format
          gl.UNSIGNED_BYTE, // type
          data // data!
        );
      }

      let stripeTexture = this.textures.get(`${name}_stripe`);
      const uploadStripe = !stripeTexture;

      if (!stripeTexture) {
        stripeTexture = this.createOrReuseTexture(`${name}_stripe`);
      }
      gl.bindTexture(gl.TEXTURE_2D, stripeTexture);
      if (uploadStripe) {
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texImage2D(
          gl.TEXTURE_2D,
          0, // mip level
          gl.RGBA, // internal format
          width,
          1,
          0, // border
          gl.RGBA, // format
          gl.UNSIGNED_BYTE, // type
          this.buildStripe(width) // data!
        );
      }
    }
    else {
      gl.bindTexture(gl.TEXTURE_2D, texture);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
      gl.texImage2D(
        gl.TEXTURE_2D,
        0, // mip level
        gl.LUMINANCE, // internal format
        width,
        height,
        0, // border
        gl.LUMINANCE, // format
        gl.UNSIGNED_BYTE, // type
        data // data!
      );
    }

    return this;
  }

  private unpackTexture(name : string,
                        width: number,
                        height: number) : WebGLRendererImpl {
    const { gl } = this;

    const texture = this.textures.get(name);

    if (!texture) throw new Error('Upload Texture First');

    // Upload to a temporary RGBA texture, then unpack it.
    // This is faster than CPU-side swizzling in ANGLE on Windows.
    gl.useProgram(this.unpackProgram);

    let fb :any = this.frameBuffers.get(name);

    if (!fb) {
      // Create a framebuffer and an empty target size
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, texture);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
      gl.texImage2D(
        gl.TEXTURE_2D,
        0, // mip level
        gl.RGBA, // internal format
        width,
        height,
        0, // border
        gl.RGBA, // format
        gl.UNSIGNED_BYTE, // type
        null // data!
      );

      fb = gl.createFramebuffer();
      if (!fb) throw new Error('Error Create Frame Buffer');

      this.frameBuffers.set(name, fb);
    }

    gl.bindFramebuffer(gl.FRAMEBUFFER, fb);
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, texture, 0);

    const tempTexture = this.textures.get(`${name}_temp`);

    if (!tempTexture) throw new Error('Upload Texture First');

    gl.activeTexture(gl.TEXTURE1);
    gl.bindTexture(gl.TEXTURE_2D, tempTexture);
    gl.uniform1i(this.unpackTextureLocation, 1);

    const stripeTexture = this.textures.get(`${name}_stripe`);

    if (!stripeTexture) throw new Error('Upload Texture First');

    gl.activeTexture(gl.TEXTURE2);
    gl.bindTexture(gl.TEXTURE_2D, stripeTexture);
    gl.uniform1i(this.stripeLocation, 2);

    // Rectangle geometry
    gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer);
    gl.enableVertexAttribArray(this.positionLocation);
    gl.vertexAttribPointer(this.positionLocation, 2, gl.FLOAT, false, 0, 0);

    // Set up the texture geometry...
    gl.bindBuffer(gl.ARRAY_BUFFER, this.unpackTexturePositionBuffer);
    gl.enableVertexAttribArray(this.unpackTexturePositionLocation);
    gl.vertexAttribPointer(this.unpackTexturePositionLocation, 2, gl.FLOAT, false, 0, 0);

    // Draw into the target texture...
    gl.viewport(0, 0, width, height);

    gl.drawArrays(gl.TRIANGLES, 0, rectangle.length / 2);

    gl.bindFramebuffer(gl.FRAMEBUFFER, null);

    return this;
  }
  private attachTexture(name : string,
                        register : GLenum,
                        index : number) {
    const { gl } = this;

    gl.activeTexture(register);
    gl.bindTexture(gl.TEXTURE_2D, this.textures.get(name) || null);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);

    gl.uniform1i(gl.getUniformLocation(this.program, name), index);
  }

  public buildStripe(width: number) : Uint8Array {
    let tmpData : any = this.stripes.get(width);

    if (tmpData) return tmpData;

    const len = width;
    const out = new Uint32Array(len);

    for (let i = 0; i < len; i += 4) {
      out[i] = 0x000000ff;
      out[i + 1] = 0x0000ff00;
      out[i + 2] = 0x00ff0000;
      out[i + 3] = 0xff000000;
    }

    tmpData = new Uint8Array(out.buffer);
    this.stripes.set(width, tmpData);

    return tmpData;
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

  private clear() : WebGLRendererImpl {
    this.gl.viewport(0, 0, this.canvas.width, this.canvas.height);
    this.gl.clearColor(0.0, 0.0, 0.0, 0.0);
    this.gl.clear(this.gl.COLOR_BUFFER_BIT);

    return this;
  }
}
