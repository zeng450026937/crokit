async function test(binding, connector) {
  console.log('Contact test');

  const { CloudContact } = binding;

  console.log('constructor()');

  const cloud_contact = new CloudContact({connector});

  console.log('synced: ', cloud_contact.synced);
  console.log('loadMode: ', cloud_contact.loadMode);

  console.log('sync()');

  await cloud_contact.sync();

  console.log('synced: ', cloud_contact.synced);
  console.log('loadMode: ', cloud_contact.loadMode);
  console.log('rootId: ', cloud_contact.rootId);

  const rootId = cloud_contact.rootId;
  const rootNode = cloud_contact.getNode(rootId);

  console.log('rootNode: ', rootNode);
}

module.exports = test;
