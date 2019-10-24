const call_test = require('./call-test');
const control_test = require('./controll-test');

async function test(binding, connector, account) {
  console.log('UserAgent test');

  const { UserAgent } = binding;
  const { username, password, domain, ha1 } = account;

  const userAgent = new UserAgent({
    username,
    password,
    domain,
    ha1,
    //'userAgent' : 'Yealink Meeting(Windows) 1.0.0',
    //'clientInfo' : 'Apollo_VCD_Windows'
  });

  userAgent.setConnector(connector);
  userAgent.start();

  console.log('register()')

  await userAgent.register().then((r) => console.log(r));

  console.log('registerd');

  console.log('username', userAgent.username);
  console.log('password', userAgent.password);
  console.log('domain', userAgent.domain);

  userAgent.on('incoming', (event, call) => {
    console.log(event, call);

    const eventNames = [
      'progress',
      'trying',
      'ringing',
      'redirect',
      'established',
      'focus:prepare',
      'focus:ready',
      'focus:established',
      'focus:finished',
      'share:ready',
      'share:established',
      'share:finished',
      'referFailed',
      'replaceFailed',
      'refered',
      'replaced',
      'finished',
      'rtc:audioStart',
      'rtc:audioStop',
      'rtc:audioBroken',
      'rtc:videoStart',
      'rtc:videoStop',
      'rtc:videoBroken',
      'rtc:shareRecvStart',
      'rtc:shareRecvStop',
      'rtc:shareSendStart',
      'rtc:shareSendStop',
      'rtc:shareBroken',
    ];

    eventNames.forEach((event) => {
      call.on(event, () => console.log(event));
    })

    setTimeout(() => call.hangup(), 3000);
    //call.answer({video:false});
  });

  userAgent.on('reconnectNeeded', (event, code) => {
    console.warn('reconnectNeeded code = ', code);
  });

  // console.log('unregister()');

  // userAgent.unregister();
  // userAgent.destroy();
  // delete call;
  // delete userAgent;

  await call_test(binding, userAgent);

  console.log('stop')
  userAgent.stop();
}

module.exports = test;
