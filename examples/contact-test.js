async function test(binding, connector) {
  console.log('Contact test');

  const { CloudContact, LocalContact } = binding;

  console.log('constructor()');

  const cloud_contact = new CloudContact({connector});

  console.log('synced: ', cloud_contact.synced);
  console.log('loadMode: ', cloud_contact.loadMode);

  console.log('sync()');

  await cloud_contact.sync().then(() => console.log('synced'));

  console.log('synced: ', cloud_contact.synced);
  console.log('loadMode: ', cloud_contact.loadMode);
  console.log('rootId: ', cloud_contact.rootId);

  const rootId = cloud_contact.rootId;
  const rootNode = cloud_contact.getNode(rootId);

  console.log('rootNode: ', rootNode, rootNode.toString());

  if (global.window) {
    window.node = rootNode;
  }

  for (const key in rootNode) {
    console.log(key, rootNode[key]);
  }

  rootNode.xx = 'xx';

  // contact node is cached by uid
  const reRootNode = cloud_contact.getNode(rootId);

  console.log('reRootNode: ', reRootNode);

  for (const key in rootNode) {
    console.log(key, rootNode[key]);
  }

  console.log('constructor()');

  const local_contact = new LocalContact({connector});

  const data = {
    name: '1',
    phone: '13131313131',
    email: '131@131.com',
  };

  const update_data = {
    name: '2',
    phone: '13232323232',
    email: '132@132.com',
  };

  console.log('create()');

  const uid = local_contact.create(data);

  console.log('uid: ', uid);

  console.log('getNode()');

  let node = local_contact.getNode(uid);

  console.log('node:', node);

  console.log('findById()', uid);

  node = local_contact.findById(uid);

  console.log('node:', node);

  console.log('findByName(1)');

  node = local_contact.findByName('1');

  console.log('node:', node);

  console.log('update()');

  local_contact.update(uid, update_data);

  node = local_contact.getNode(uid);

  console.log('node:', node);

  console.log('findById()', uid);

  node = local_contact.findById(uid);

  console.log('node:', node);

  console.log('findByName(1)');

  node = local_contact.findByName('1');

  console.log('node:', node);

  console.log('findByName(2)');

  node = local_contact.findByName('2');

  console.log('node:', node);

  console.log('find(email, 132@132.com)');

  node = local_contact.find('email', '132@132.com');

  console.log('node:', node);

  console.log('search(132@132.com)');

  node = local_contact.search('132@132.com');

  console.log('node:', node);

  console.log('search(13)');

  node = local_contact.search('13');

  console.log('node:', node);

  console.log('searchWith(email, 13)');

  node = local_contact.searchWith('email', '13');

  console.log('node:', node);

  console.log('remove()', uid);

  local_contact.remove(uid);

  console.log('findById()', uid);

  node = local_contact.findById(uid);

  console.log('node:', node);


  // cloud_contact.destroy();
  // local_contact.destroy();
}

module.exports = test;
