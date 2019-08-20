
async function test(binding, userAgent) {
  console.log('Call test');

  const { Call } = binding;

  const call = new Call(userAgent);

  call.connect('sip:223504.1090@onylyun.com');
}

module.exports = test;