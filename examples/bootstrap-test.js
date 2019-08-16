async function test(binding) {
  console.log('bootstrap test');

  const { Bootstrap, UserAgent, Call } = binding;

  console.log('-- constructor --');

  const bootstrap = new Bootstrap('01234567890123456789012345678912');

  bootstrap.server = 'https://onylyun.com';
  bootstrap.username = '223504.1090';
  bootstrap.password = 'v123456789';

  const accountList = await bootstrap.authenticate();

  console.log('authenticated', accountList)

  const [ account ] = accountList;
  const username = account.number;
  const password = bootstrap.password;
  const domain = account.enterprise.domain;

  console.log('default username', username);
  console.log('default password', password);
  console.log('default domain', domain);

  const userAgent = new UserAgent({
    username,
    password,
    domain,
  });

  console.log('register()')

  await userAgent.register().then((r) => console.log(r));

  console.log('account registerd');

  console.log('username', userAgent.username);
  console.log('password', userAgent.password);
  console.log('domain', userAgent.domain);

  const call = new Call(userAgent);

  call.connect('sip:223504.1091@onylyun.com');

  // console.log('unregister()');

  // userAgent.unregister();
  // userAgent.destroy();
  // delete call;
  // delete userAgent;
}

module.exports = test;
