const useragent_test = require('./useragent-test');
const schedule_test = require('./schedule-test');
const contact_test = require('./contact-test');

async function test(binding) {
  console.log('Bootstrap test');

  const { Bootstrap, UserAgent, Call } = binding;

  console.log('constructor()');

  const bootstrap = new Bootstrap('01234567890123456789012345678912');

  bootstrap.server = 'https://onylyun.com';
  bootstrap.username = '223504.1066';
  bootstrap.password = 'v123456789';

  console.log('authenticate()');

  const accountList = await bootstrap.authenticate();

  console.log('authenticated', accountList)

  const [ account ] = accountList;
  const uid = account.uid;
  const username = account.number;
  const password = bootstrap.password;
  const domain = account.enterprise.domain;

  console.log('default username', username);
  console.log('default password', password);
  console.log('default domain', domain);

  console.log('getConnector()');

  const connector = bootstrap.getConnector(uid);

  useragent_test(binding, {username, password, domain});
  // schedule_test(binding, connector);
  // contact_test(binding, connector);
}

module.exports = test;
