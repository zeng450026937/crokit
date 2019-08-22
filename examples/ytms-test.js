async function test(binding) {
  console.warn('YTMS Test');

  const {YTMS} = binding;

  const ytmsHandler = new YTMS('01234567890123456789012345678912');

  ytmsHandler.server = 'http://10.5.200.199:8083';

  const isRegisted = await ytmsHandler.start();

  console.warn('### registe to ytms server', isRegisted);

  console.warn('### update to ytms server start');
  const isUpdated = await ytmsHandler.update(
    {
      'name' : '不要问我是谁',
      'type' : 'software',
      'category' : 'VCD',
      'model' : 'VCD-Native',
      'platform' : 'Windows',
      'version' : '1.30.28.1',
      'arch' : 'ia32',
      'updateChannel' : 'insiders',
      'customId' : '',
      'configId' : '',
      'remarks' : 'default,test',

      'deviceModel' : 'x1',
      'deviceResolution' : '2160*1080',
      'deviceOs' : 'Windows 10',
      'deviceIp' : '10.86.5.141',
      'deviceMac' : '1c:1b:0d:c0:2f:72',
      'deviceHostname' : 'YL1481-A01936PC',
      'deviceCpu' : 'Intel(R) Core(TM) i3-6100 CPU @ 3.70GHz',
      'deviceMemory' : '17088049152',

      'account' : '6666',
      'displayName' : '就是这么6',
      'serverType' : 'CLOUD',
      'serverAddress' : '10.200.112.165',
      'serverDomain' : 'academai.com',
      'serverOutbound' : '10.200.112.165',

      'enterpriseDomain' : 'Yealink',
      'enterpriseId' : '666666',
      'enterpriseName' : '宇宙行',
    }
  );

  console.warn('### update to ytms server end', isUpdated);

  // const isUploadAlarm = await ytmsHandler.uploadAlarm(
  //   {
  //     'filePath' : 'E:\\file\\alarm.zip',
  //     'code' : '480001',
  //     'name' : 'GPU_PROCESS_CRASH',
  //     'type' : 'PROCESS',
  //     'level' : '1',
  //     'desc' : 'This is alarm test'
  //   }
  // );

  // ytmsHandler.uploadAlarm(
  //   {
  //     'filePath' : 'E:\\file\\alarm.zip',
  //     'code' : '4800011',
  //     'name' : 'GPU_PROCESS_CRASH',
  //     'type' : 'PROCESS',
  //     'level' : '1',
  //     'desc' : 'This is alarm test'
  //   }
  // ).then((res) => {
  //   console.warn('### res = ', res);
  // }).
  // catch((e) => {
  //   console.warn('### e = ', e);
  // });

  // console.warn('### Upload Alarm to ytms server', isUploadAlarm);

  // const isUploadFeedback = await ytmsHandler.uploadFeedBack(
  //   {
  //     'filePath' : 'E:\\file\\feedback.zip',
  //     'imagePath' : '',
  //     'videoPath' : '',
  //     'title' : 'this is feedback test',
  //     'content' : 'there is nothing',
  //     'category' : 'nothing',
  //     'contact' : '18030127553',
  //   }
  // );

  // console.warn('### Upload Feedback to ytms server', isUploadFeedback);

  // const packageInfo = await ytmsHandler.getPackagesInfo();
  // console.warn('### Get Package Infos to ytms server ###');
  // console.warn('version = ', packageInfo.version);
  // console.warn('date = ', packageInfo.date);
  // console.warn('note = ', packageInfo.note);
  // console.warn('name = ', packageInfo.name);
  // console.warn('url = ', packageInfo.url);
  // console.warn('md5 = ', packageInfo.md5);
  // console.warn('size = ', packageInfo.size);
  // console.warn('forceUpdate = ', packageInfo.forceUpdate);

  // console.warn('### getConfigFileInfo test start');
  // const configInfo = await ytmsHandler.getConfigFileInfo();
  // console.warn('id = ', configInfo.id);
  // console.warn('name = ', configInfo.name);
  // console.warn('url = ', configInfo.url);
  // console.warn('md5 = ', configInfo.md5);
  // console.warn('### getConfigFileInfo test end');

  // console.warn('### downloadFile test start');
  // await ytmsHandler.downloadFile(
  //   {
  //     'url' : configInfo.url,
  //     'path' : 'E:\\file\\',
  //     'fileName' : 'download.json',
  //   }
  // );
  // console.warn('### downloadFile test end');

  // console.warn('### UploadConfig test start');
  // const config = {
  //   'testA' : 'aaa',
  //   'testB' : 'bbb',
  //   'fileName' : 'download.json',
  // };

  // await ytmsHandler.uploadConfig(JSON.stringify(config));
  // console.warn('### UploadConfig test end');
}

module.exports = test;
