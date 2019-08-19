
async function test(binding, connector) {
  console.log('Schedule test');

  const { Schedule } = binding;

  console.log('constructor()');

  const schedule = new Schedule(connector);

  const start = new Date();
  const end = new Date();

  start.setHours(start.getHours() - 7 * 24);
  end.setHours(start.getHours() + 7 * 24);

  console.log(new Date(), start, end);

  console.log('sync()');

  await schedule.sync(start.valueOf(), end.valueOf());

  console.log('fetch()');
  const list = schedule.fetch(start.valueOf(), end.valueOf());

  console.log(list);

  const item = list[0];

  console.log('\nItem:');
  for (const key in item) {
    console.log(key, item[key]);
  }

  console.log('detail()');
  const detail = await item.getDetail();

  console.log('\nDetail:');
  for (const key in detail) {
    if (key === 'participants') {
      console.log(detail[key][0]);
    }
  }

  console.log('end');
}

module.exports = test;
