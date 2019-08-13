async function test(binding) {
  console.log('bootstrap test');

  const { Bootstrap, UserAgent, v8Util } = binding;

  console.log('-- constructor --');

  const bootstrap = new Bootstrap('01234567890123456789012345678912');

  bootstrap.server = 'https://002018.onqa.yealinkops.com';
  bootstrap.username = '5555';
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

  console.log('unregister()');

  userAgent.unregister();
  delete userAgent;
}

module.exports = test;
