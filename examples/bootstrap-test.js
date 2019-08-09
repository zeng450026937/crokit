function test(binding) {
  console.log('bootstrap test');

  const { Bootstrap } = binding;

  console.log('-- constructor --');

  try {
    const bootstrap = new Bootstrap();
  } catch (error) {
    console.log(error);
  }

  const bootstrap = new Bootstrap('01234567890123456789012345678912');

  bootstrap.server = 'https://002018.onqa.yealinkops.com';
  bootstrap.username = '5555';
  bootstrap.password = 'a123456789';

  bootstrap.authenticate()
    .then((r) => {
      console.log('authenticated resolved', r)

    })
    .catch(() => {
      console.log('authenticated rejected')
    });

  // setTimeout(() => { console.log('time out') }, 3000)
}

module.exports = test;
