const useragent_test = require('./useragent-test');
const schedule_test = require('./schedule-test');
const contact_test = require('./contact-test');

let g_bootstrp = null;

async function test(binding) {
  console.log('Bootstrap test');

  const { Bootstrap, UserAgent, Call } = binding;

  console.log('constructor()');

  const bootstrap = g_bootstrp = new Bootstrap('01234567890123456789012345678912');

  bootstrap.server = 'https://onylyun.com';
  bootstrap.username = '223504.1091';
  bootstrap.password = 'v123456789';
  bootstrap.debug = false;

  console.log('authenticate()');

  const accountList = await bootstrap.authenticate();

  console.log('authenticated', accountList)

  const [ account ] = accountList;
  const id = account.id;
  const username = account.number;
  const password = bootstrap.password;
  const domain = account.enterprise.domain;

  console.log('default username', username);
  console.log('default password', password);
  console.log('default domain', domain);

  console.log('getConnector()');

  const connector = bootstrap.getConnector(id);

  useragent_test(binding, connector, {username, password, domain});
  //schedule_test(binding, connector);
  //contact_test(binding, connector);
}

module.exports = test;
