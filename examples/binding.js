let binding
try {
  binding = require('D:\\workspace\\crokit\\src\\out\\debug\\rtvc_binding.node');
} catch (error) {
  console.log(error);
  return;
}

console.log(binding);
console.log(binding.version);

const user_agent = new binding.UserAgent({
  username: 'my username',
  password: 'my password',
  domain: 'my domain',
});

console.log(user_agent.username())
