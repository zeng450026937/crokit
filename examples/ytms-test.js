const util = require('util');
const EventEmitter = require('events');

async function test(binding) {
  console.warn('YTMS Test');

  const {YTMS} = binding;

  util.inherits(YTMS, EventEmitter);

  const ytmsHandler = new YTMS('01234567890123456789012345678912');

  ytmsHandler.server = 'http://10.5.200.199:8083';

	// YTMS 服务器还不支持推送下来
  ytmsHandler.on('pushPacket', (func) => {
    console.warn('### 测试 YTMS 推送安装包', func);

    console.warn('### 测试 YTMS 获取安装包信息开始');
    ytmsHandler.getPackagesInfo()
      .then((packageInfo) => {
        console.warn('### 测试 YTMS 获取安装包信息结束');
        console.warn('version = ', packageInfo.version);
        console.warn('date = ', packageInfo.date);
        console.warn('note = ', packageInfo.note);
        console.warn('name = ', packageInfo.name);
        console.warn('url = ', packageInfo.url);
        console.warn('md5 = ', packageInfo.md5);
        console.warn('size = ', packageInfo.size);
        console.warn('forceUpdate = ', packageInfo.forceUpdate);
      })
      .catch((e) => {
        console.warn('### 测试 YTMS 获取安装包信息失败', e);
      });
  });

  ytmsHandler.on('pushConfig', (func, configId) => {
    console.warn('### 测试 YTMS 推送配置', func, configId);

    console.warn('### 测试 YTMS 获取配置开始');
    ytmsHandler.getConfigFileInfo()
      .then((configInfo) => {
        console.warn('### 测试 YTMS 获取配置文件信息结果');
        console.warn('id = ', configInfo.id);
        console.warn('name = ', configInfo.name);
        console.warn('url = ', configInfo.url);
        console.warn('md5 = ', configInfo.md5);
        console.warn('##################################');

        console.warn('### 测试 YTMS 下载配置文件开始');
        return ytmsHandler.downloadFile(
            {
              'url' : configInfo.url,
              'path' : 'E:\\file\\',
              'fileName' : configInfo.name + '.json',
            }
        );
      })
      .then((res) => {
        console.warn('### 测试 下载配置文件结果 code = ', res);
      })
      .catch((e) => {
        console.warn('### 测试 YTMS 获取配置失败', e);
      })
  });

  ytmsHandler.on('message', (func, msg) => {
    console.warn('### 测试 YTMS 推送消息', func, msg);
  });

  ytmsHandler.on('uploadLog', (func, sessionId) => {
    console.warn('### 测试 YTMS 推送上报日志', func, sessionId);

    console.warn('### 测试 上报日志开始');
    ytmsHandler.uploadLog(
      {
        'sessionId' : sessionId,
        'filePath' : 'E:\\file\\log.zip',
      }
    )
    .then((res) => {
      console.warn('### 测试 上报日志结束 code = ', res);
    })
    .catch((e) => {
      console.warn('### 测试 上报日志出错 ', e);
    });
  });

  ytmsHandler.on('uploadConfig', (func, sessionId) => {
    console.warn('### 测试 YTMS 推送上报配置', func, sessionId);

    console.warn('### 测试 上传配置开始');

    const config = {
      'testA' : 'aaa',
      'testB' : 'bbb',
      'fileName' : 'download.json',
    };

    ytmsHandler.uploadConfig(JSON.stringify(config))
      .then((res) => {
        console.warn('### 测试 上传配置结束 code = ', res);
      })
      .catch((e) => {
        console.warn('### 测试 上传配置出错 ', e);
      });
  });

  ytmsHandler.on('startCapture', (func, sessionId) => {
    console.warn('### 测试 YTMS 推送开始抓包', func, sessionId);

    const id = sessionId;

    const config = {
      'path' : 'E:\\file\\',
      'deviceId' : '{801CE636-BEFB-4BC1-97B2-AB8EC6F9C4DE}',
      'sessionId' : id,
    };

    console.warn(config);

    console.warn('### 测试 抓包开始');

    ytmsHandler.startCapture(config)
      .then((res) => {
        console.warn('### 测试 抓包开始 code = ', res);
      })
      .catch((e) => {
        console.warn('### 测试 抓包开始 出错 ', e);
      });
  });

  ytmsHandler.on('stopCapture', (func, sessionId) => {
    console.warn('### 测试 YTMS 推送结束抓包', func, sessionId);

    ytmsHandler.stopCapture(sessionId)
      .then((res) => {
        console.warn('### 测试  抓包结束 code = ', res);
      })
      .catch((e) => {
        console.warn('### 测试 抓包结束 出错 ', e);
      });
  });

  ytmsHandler.on('reregiste', (func, sessionId) => {
    console.warn('### 测试 YTMS 推送重新注册', func, sessionId);

    ytmsHandler.start()
      .then((res) => {
        console.warn('### 测试 重新注册结束 code = ', res);
      })
      .catch((e) => {
        console.warn('### 测试 重新注册出错 ', e);
      })
  });

  ytmsHandler.on('reboot', (func, sessionId) => {
    console.warn('### 测试 YTMS 推送重新重启', func, sessionId);
  });

  const isRegisted = await ytmsHandler.start();
  console.warn('### 注册ytms code = ', isRegisted);

  console.warn('### update to ytms server start');
  const isUpdated = await ytmsHandler.update(
    {
      'name' : '不要问我是谁',
      'type' : 'software',
      'category' : 'VCD',
      'model' : 'VCD-Native',
      'platform' : 'Windows',
      'version' : '1.30.254-beta',
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
      'registerStatus' : 'registered',

      'enterpriseDomain' : 'Yealink',
      'enterpriseId' : '666666',
      'enterpriseName' : '宇宙行',
    }
  );

  console.warn('### update to ytms server end', isUpdated);


  console.warn('### 测试 YTMS 上报告警开始');
  const isUploadAlarm = await ytmsHandler.uploadAlarm(
    {
      'filePath' : 'E:\\file\\alarm.zip',
      'code' : '480001',
      'name' : 'GPU_PROCESS_CRASH',
      'type' : 'PROCESS',
      'level' : '1',
      'desc' : 'This is alarm test'
    }
  );
  console.warn('### 测试 YTMS 上报告警结束 code = ', isUploadAlarm);

  console.warn('### 测试 YTMS 上报反馈开始');
  const isUploadFeedback = await ytmsHandler.uploadFeedBack(
    {
      'filePath' : 'E:\\file\\feedback.zip',
      'imagePath' : '',
      'videoPath' : '',
      'title' : 'this is feedback test',
      'content' : 'there is nothing',
      'category' : 'nothing',
      'contact' : '18030127553',
    }
  );
  console.warn('### 测试 YTMS 上报反馈结束 code = ', isUploadFeedback);

  console.warn('### 测试 YTMS 上报事件开始');
  const isUploadEvent= await ytmsHandler.uploadEvent(
    {
      'code' : '01',
      'name' : 'CLIENT_START_UP',
    }
  );
  console.warn('### 测试 YTMS 上报时间结束 code = ', isUploadEvent);

  console.warn('### 测试 YTMS 获取安装包信息开始');
  const packageInfo = await ytmsHandler.getPackagesInfo();
  console.warn('### Get Package Infos to ytms server ###');
  console.warn('version = ', packageInfo.version);
  console.warn('date = ', packageInfo.date);
  console.warn('note = ', packageInfo.note);
  console.warn('name = ', packageInfo.name);
  console.warn('url = ', packageInfo.url);
  console.warn('md5 = ', packageInfo.md5);
  console.warn('size = ', packageInfo.size);
  console.warn('forceUpdate = ', packageInfo.forceUpdate);
  console.warn('### 测试 YTMS 获取安装包信息结束');

  if(packageInfo.url != null && packageInfo.url != undefined)
  {
    console.warn('### 测试 YTMS 开始下载安装包');
    // ytmsHandler.downloadFile(
    //   {
    //     'url' : packageInfo.url,
    //     'path' : 'E:\\file\\',
    //     'fileName' : packageInfo.name,
    //   }
    // )
    // .then((res) => {
    //   console.warn('### 测试 YTMS 下载安装包结束 code = ', res);
    // })
    // .catch((e) => {
    //   console.warn('### 测试 YTMS 下载安装包失败', e);
    // });
  }

  setTimeout(() => {
    console.warn('close test func');
    ytmsHandler.removeAllListeners();
  }, 6000000);
}

module.exports = test;
