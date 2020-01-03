
async function test(binding, connector) {
  console.log('Schedule test');

  const { Schedule } = binding;

  console.log('constructor()');

  const schedule = new Schedule(connector);

  const start = new Date();
  const end = new Date();

  schedule.on('updated', (func, arg) => {
    console.warn('ScheduleUpdate');
  })

  start.setHours(start.getHours() - 10 * 24);
  end.setHours(start.getHours() + 7 * 24);

  console.log(new Date(), start, end);

  console.log('sync()');

  await schedule.sync(start.valueOf(), end.valueOf());

  console.log('fetch()');
  const list = await schedule.fetch(start.valueOf(), end.valueOf());

  console.log(list);

  const item = list[0];

  if (!item) return;

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

  const config = await schedule.getScheduleConfig().catch((e) => {console.warn(e)});
  console.warn('schedule config = ', config);

  const new_schedue = {
    profile: 'kDefault',
    subject: "lgd test",
    zoneId: "China_Standard_Time",
    startDate: "2020-01-02",
    startTime: "17:30",
    durationHour: 2,
    durationMinute: 0,
    recurrenceType: null,
    interval: 1,
    dayOfWeek: 5,
    rangeEndDate: "2020-01-03",
    remark: "",
    identifier: "31786f1b71c54aa9966562262ca4847b",
    memberType: 'kInternal',
    roleType: 'kOrganizer',
    extensionType: 'RTMP',
    rtmpLogoFileName: '',
    rtmpWatchLimitType: 'all',
    rtmpWatchPwd: '',
    enableAutoRecord: false,
  };

  const add_res = await schedule.addSchedulePlan(new_schedue).catch((e) => {console.warn(e)});

  console.warn('add result = ', add_res);

  setTimeout(() => {

  }, 100000);
}

module.exports = test;
