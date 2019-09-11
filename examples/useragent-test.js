const call_test = require('./call-test');

async function test(binding, account) {
  console.log('UserAgent test');

  const { UserAgent } = binding;
  const { username, password, domain } = account;

  const userAgent = new UserAgent({
    username,
    password,
    domain,
  });

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

  // console.log('unregister()');

  // userAgent.unregister();
  // userAgent.destroy();
  // delete call;
  // delete userAgent;

  call_test(binding, userAgent);
}

module.exports = test;
