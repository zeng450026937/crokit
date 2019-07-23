let binding
try {
  binding = require('../out/debug/rtvc_binding');
} catch (error) {
  console.error(error);
}

console.log(binding);
console.log(binding.version);

const user_agent = new binding.UserAgent({
  username: 'my username',
  password: 'my password',
  domain: 'my domain',
});

console.log(user_agent.username())
