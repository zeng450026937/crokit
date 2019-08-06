/* eslint-disable no-bitwise */
export function rgbaToYuv(pixels: any, width: number, height: number)
  : {y: Array<number>, u: Array<number>, v: Array<number>} {

  const y = (r: number, g: number, b: number) => (((66 * r + 129 * g + 25 * b + 128) >> 8) + 16);
  const u = (r: number, g: number, b: number) => (((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128);
  const v = (r: number, g: number, b: number) => (((112 * r - 94 * g - 18 * b + 128) >> 8) + 128);
  const color = (x: number) => (((x < 0) ? 0 : ((x > 255) ? 255 : x)));

  let yIndex = 0;
  let uIndex = 0;
  let vIndex = 0;

  const dataY = [];
  const dataU = [];
  const dataV = [];

  for (let j = 0; j < height; j++) {
    for (let i = 0; i < width; i++) {
      const index = j * width + i;

      const R = pixels[index * 4] & 0xFF;
      const G = pixels[index * 4 + 1] & 0xFF;
      const B = pixels[index * 4 + 2] & 0xFF;

      let Y = y(R, G, B);
      let U = u(R, G, B);
      let V = v(R, G, B);

      Y = Y < 16 ? 16 : (Y > 255 ? 255 : Y);
      U = U < 0 ? 0 : (U > 255 ? 255 : U);
      V = V < 0 ? 0 : (V > 255 ? 255 : V);

      dataY[yIndex++] = color(Y);
      if (j % 2 === 0 && i % 2 === 0) {
        dataU[uIndex++] = color(U);
        dataV[vIndex++] = color(V);
      }
    }
  }


  return {
    y : dataY,
    u : dataU,
    v : dataV,
  };
}

export const suitableStride = (len : number) => {
  const alignment = 4;
  const remainder = len % alignment;

  return remainder === 0 ? len : len + (alignment - remainder);
};

const allocPlane = (width:number,
                    height: number,
                    source ?:Uint8Array,
                    stride ?: number,
                    offset ?: number) => {
  let bytes;

  offset = offset || 0;

  stride = stride || suitableStride(width);
  if (stride < width) {
    throw new Error('Invalid input stride for YUV plane; must be larger than width');
  }

  const size = stride * height;

  if (source) {
    if (source.length - offset < size) {
      throw new Error('Invalid input buffer for YUV plane; must be large enough for stride times height');
    }
    bytes = source.slice(offset, offset + size);
  }
  else {
    bytes = new Uint8Array(size);
    stride = stride || suitableStride(width);
  }

  return {
    bytes,
    stride,
  };
};

export const lumaPlane = (width : number,
                          height : number,
                          source ?:Uint8Array,
                          stride ?: number,
                          offset ?: number) => allocPlane(width, height, source, stride, offset);

export const chromaPlane = (chromaWidth:number,
                            chromaHeight: number,
                            source ?:Uint8Array,
                            stride ?: number,
                            offset ?: number) => allocPlane(chromaWidth, chromaHeight, source, stride, offset);
