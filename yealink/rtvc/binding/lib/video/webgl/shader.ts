
export type VERTEX_SHADER = string;
export type FRAGMENT_SHADER = string;

export const vertex = `
precision lowp float;

attribute vec2 aPosition;
attribute vec2 aLumaPosition;
attribute vec2 aChromaPosition;
varying vec2 vLumaPosition;
varying vec2 vChromaPosition;
void main() {
    gl_Position = vec4(aPosition, 0, 1);
    vLumaPosition = aLumaPosition;
    vChromaPosition = aChromaPosition;
}`;

export const fragment = `
precision lowp float;

uniform sampler2D uTextureY;
uniform sampler2D uTextureCb;
uniform sampler2D uTextureCr;
varying vec2 vLumaPosition;
varying vec2 vChromaPosition;
void main() {
   // Y, Cb, and Cr planes are uploaded as LUMINANCE textures.
   float fY = texture2D(uTextureY, vLumaPosition).x;
   float fCb = texture2D(uTextureCb, vChromaPosition).x;
   float fCr = texture2D(uTextureCr, vChromaPosition).x;

   // Premultipy the Y...
   float fYmul = fY * 1.1643828125;

   // And convert that to RGB!
   gl_FragColor = vec4(
     fYmul + 1.59602734375 * fCr - 0.87078515625,
     fYmul - 0.39176171875 * fCb - 0.81296875 * fCr + 0.52959375,
     fYmul + 2.017234375   * fCb - 1.081390625,
     1
   );
}`;

export const vertexStripe = `
precision lowp float;

attribute vec2 aPosition;
attribute vec2 aTexturePosition;
varying vec2 vTexturePosition;

void main() {
    gl_Position = vec4(aPosition, 0, 1);
    vTexturePosition = aTexturePosition;
}`;

export const fragmentStripe = `
precision lowp float;

uniform sampler2D uStripe;
uniform sampler2D uTexture;
varying vec2 vTexturePosition;
void main() {
   // Y, Cb, and Cr planes are mapped into a pseudo-RGBA texture
   // so we can upload them without expanding the bytes on IE 11
   // which doesn't allow LUMINANCE or ALPHA textures
   // The stripe textures mark which channel to keep for each pixel.
   // Each texture extraction will contain the relevant value in one
   // channel only.

   float fLuminance = dot(
      texture2D(uStripe, vTexturePosition),
      texture2D(uTexture, vTexturePosition)
   );

   gl_FragColor = vec4(fLuminance, fLuminance, fLuminance, 1);
}`;
