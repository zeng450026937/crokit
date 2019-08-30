const events = require('events');
const util = require('util');

async function test(binding, connector) {
  console.log('DesktopCapture test');

  const { DesktopCapture } = binding;

  // util.inherits(DesktopCapture, events.EventEmitter);
  // Object.setPrototypeOf(DesktopCapture.prototype, events.EventEmitter.prototype);

  console.log('constructor()');

  const desktopCapture = new DesktopCapture();

  // desktopCapture.once('finished', (e) => console.log('finished', e));

  const list = await desktopCapture.getSources({
    captureWindow: true,
    captureScreen: true,
  });

  console.log(list);
  // desktopCapture must be destroy
  // setTimeout(() => desktopCapture.destroy(), 3000);
}

module.exports = test;
