
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

  // console.log('unregister()');

  // userAgent.unregister();
  // userAgent.destroy();
  // delete call;
  // delete userAgent;
}

module.exports = test;
