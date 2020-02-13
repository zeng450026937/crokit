const useragent_test = require('./useragent-test');
const schedule_test = require('./schedule-test');
const contact_test = require('./contact-test');

let g_bootstrp = null;

async function test(binding) {
  console.log('Bootstrap test');

  const {
    Bootstrap,
    UserAgent,
    Call
  } = binding;

  console.log('constructor()');

  const bootstrap = g_bootstrp = new Bootstrap('01234567890123456789012345678912');

  bootstrap.server = 'https://onylyun.com';
  bootstrap.username = '18030127553';
  bootstrap.password = 'v123456789';
  bootstrap.debug = false;
  bootstrap.smsVerify = false;
  bootstrap.ha1 = '';

  //await bootstrap.pushVerifyCode();

  console.log('authenticate()');

  const accountInfo = await bootstrap.authenticate().catch((e) => {
    console.warn(e)
  });

  const accountList = accountInfo.accountList;
  console.log('authenticated', accountList)

  const [account] = accountList;
  const id = account.id;
  const username = account.number;
  const password = bootstrap.password;
  const domain = account.enterprise.domain;
  const ha1 = account.ha1;

  console.log('default username', username);
  console.log('default password', password);
  console.log('default domain', domain);

  console.log('getConnector()');

  const connector = bootstrap.getConnector(id);

  const token = bootstrap.getToken(id);

  // const inviteInfo = await bootstrap.getPartyInviteInfo();

  const inviteInfo = await bootstrap.getPartyInviteInfo().catch((e) => {
    console.warn(e)
  });

  const serverInfo = await bootstrap.getServiceInfo('https://onylyun.com').catch((e) => {
    console.warn(e)
  });

  const metaInfo = await bootstrap.getMetaInfo('https://onylyun.com').catch((e) => {
    console.warn(e)
  });

  useragent_test(binding, connector, {
    username,
    password,
    domain,
    ha1
  });
  //schedule_test(binding, connector);
  //contact_test(binding, connector);
}

module.exports = test;
