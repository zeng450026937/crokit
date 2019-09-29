const path = require('path');

async function test(binding, userAgent) {
  console.log('Call test');

  const {
    Call,
    VideoManager,
    DesktopCapture
  } = binding;

  const videoManager = new VideoManager();

  console.log('-- enumerateDevices --');
  videoManager.enumerateDevices();

  console.log('-- videoInputDeviceList --');
  const videoInputDeviceList = videoManager.videoInputDeviceList();
  console.log(videoInputDeviceList);

  const sink = {
    onFrame(frame) {},
  };

  videoManager.videoInputDevice = videoInputDeviceList[0];
  // videoManager.setLocalVideoSink(sink);

  videoManager.acquireStream();

  const call = new Call(userAgent);

  // call.connect('sip:62061**040660@123456.onylyun.com;transport=tls');
  // call.connect('sip:1001@123456.onylyun.com;transport=tls');
  //call.connect('sip:1090@223504.onylyun.com;transport=tls');
  call.connect('sip:8602@22014665.10.200.112.39.xip.io;transport=tls');
  //call.setRemoteVideoSink(sink);

  const eventNames = [
    'progress',
    'trying',
    'ringing',
    'redirect',
    'established',
    'focus:prepare',
    'focus:ready',
    'focus:established',
    'focus:finished',
    'share:ready',
    'share:established',
    'share:finished',
    'referFailed',
    'replaceFailed',
    'refered',
    'replaced',
    'finished',
    'rtc:audioStart',
    'rtc:audioStop',
    'rtc:audioBroken',
    'rtc:videoStart',
    'rtc:videoStop',
    'rtc:videoBroken',
    'rtc:shareRecvStart',
    'rtc:shareRecvStop',
    'rtc:shareSendStart',
    'rtc:shareSendStop',
    'rtc:shareBroken',
  ];

  // eventNames.forEach((event) => {
  //   call.on(event, () => console.log(event));
  // })

  let hangupTimmer;
  let shareTimer;

  // call.conference.on('user:added', (func, users) => {
  //   console.warn('user:added', users);
  // });

  // call.conference.on('user:updated', (func, users) => {
  //   console.warn('user:updated', users);
  // });

  // call.conference.on('user:removed', (func, users) => {
  //   console.warn('user:removed', users);
  // });

  call.conference.on('messageUpdated', (func, message) => {
    console.warn('chat messageUpdated:', message);
  });

  let user_test = true;
  call.conference.on('usersUpdated', (arg1, arg2) => {
    console.warn('chat dialogList:', call.conference, call.conference.chat.dialogList);
    console.warn('chat dialogList length:', call.conference.chat.dialogList.length);
    console.warn('chat publicDialog:', call.conference.chat.publicDialog);

    console.warn('chat:', call.conference.chat);

    console.warn('usersUpdated users:', call.conference.users);
    // console.warn('usersUpdated currentUser:', call.conference.users.currentUser);
    // console.warn('usersUpdated currentUser.entity:', call.conference.users.currentUser.entity);
    // console.warn('usersUpdated userList:', call.conference.users.userList);
    // console.warn('usersUpdated userList.length:', call.conference.users.userList.length);

    // console.warn('usersUpdated addedUser:', call.conference.users.addedUser, call.conference.users.addedUser.length);
    // console.warn('usersUpdated deletedUser:', call.conference.users.deletedUser, call.conference.users.deletedUser.length);
    // console.warn('usersUpdated updatedUser:', call.conference.users.updatedUser, call.conference.users.updatedUser.length);
    // console.warn('usersUpdated presenters:', call.conference.users.presenters, call.conference.users.presenters.length);
    // console.warn('usersUpdated attendees:', call.conference.users.attendees, call.conference.users.attendees.length);
    // console.warn('usersUpdated onHoldUsers:', call.conference.users.onHoldUsers, call.conference.users.onHoldUsers.length);
    // console.warn('usersUpdated demonstrators:', call.conference.users.demonstrators, call.conference.users.demonstrators.length);
    // console.warn('usersUpdated castviewers:', call.conference.users.castviewers, call.conference.users.castviewers.length);

    if (user_test == true) {
      user_test = true;

      setInterval(() => {
        console.warn('chat publicDialog:', call.conference.chat);
        call.conference.chat.sendChatMessage('私聊聊天测试', ['2'])
          .then((res) => {
            //console.warn(res, res.direction);
          })
          .catch(() => {});

        call.conference.chat.sendChatMessage('群聊聊天测试', [])
          .then((res) => {
            //console.warn(res, res.direction);
          })
          .catch(() => {});
      }, 10000);

      // setInterval(() => {
      //   //console.warn('usersUpdated setInterval currentUser.entity:', call.conference.users.currentUser.entity);
      // }, 500);

      //console.warn('usersUpdated invite', call.conference.users.invite('223504.1055'))

      // reject all handup users
      // call.conference.users.handUp(false)
      //   .then((res) => {
      //     console.warn(res);
      //   })
      //   .catch((e) => {
      //     console.warn(e);
      //   })

      call.conference.users.userList.map((user) => {

        // console.warn('this user entity = ', user.entity);

        // console.warn('this user isConnected = ', user.isConnected());
        // console.warn('isPresenter ', user.isPresenter());
        // console.warn('isOrganizer ', user.isOrganizer());
        // console.warn('isCurrentUser ', user.isCurrentUser());
        // console.warn('isPresenter ', user.isPresenter());
        // console.warn('isAttendee ', user.isAttendee());
        // console.warn('isCastViewer ', user.isCastViewer());
        // console.warn('isAttendee ', user.isAttendee());
        // console.warn('isDemonstrator ', user.isDemonstrator());
        // console.warn('isPresenterDemonstrator ', user.isPresenterDemonstrator());
        // console.warn('isOnHold ', user.isOnHold());
        // console.warn('isSharing ', user.isSharing());
        // console.warn('isFocus ', user.isFocus());
        // console.warn('getAudioFilter = ', user.getAudioFilter());
        // console.warn('getAudioFilter = ', user.getVideoFilter());

        // setInterval(() => {
        //   user.getStats()
        //     .then((result) => {
        //       console.warn('getStats success = ', result);
        //     })
        //     .catch((e) => {
        //       console.warn('getStats fail = ', e);
        //     });

        // }, 10000);

        // console.warn('SetAudioIngressFilter = ', user.setAudioIngressFilter(false));
        // console.warn('SetAudioIngressFilter = ', user.setAudioIngressFilter(true));
        // console.warn('SetAudioEgressFilter = ', user.setAudioEgressFilter(false));
        // console.warn('SetAudioEgressFilter = ', user.setAudioEgressFilter(true));
        // console.warn('SetVideoIngressFilter = ', user.setVideoIngressFilter(false));
        // console.warn('SetVideoIngressFilter = ', user.setVideoIngressFilter(true));
        // console.warn('SetDisplayName = ', user.setDisplayName('lalaal'));

        // if(user.isCurrentUser() == false)
        // {
        //   console.warn('setPermission = ', user.setPermission('attendee'));
        //   console.warn('hold = ', user.hold());

        //   console.warn('unHold = ', call.conference.users.allow([user.entity, '123'], true));

        //   //console.warn('unHold = ', user.unHold());
        //   console.warn('setPermission = ', user.setPermission('presenter'));
        // }

        // console.warn('SetVideoIngressFilter = ', user.setFocus(true));
        // console.warn('SetVideoIngressFilter = ', user.setFocus(false));

        //console.warn('kick = ', user.kick());
      });
    }
  });

  let desc_test = true;
  call.conference.on('descriptionUpdated', (arg1, arg2) => {
    // console.warn('descriptionUpdated desc:', call.conference.description);
    // console.warn('descriptionUpdated startTime:', call.conference.description.startTime);
    // console.warn('descriptionUpdated defaultRtmp:', call.conference.description.defaultRtmp);
    // console.warn('descriptionUpdated lobbyCapable:', call.conference.description.lobbyCapable);

    // console.warn('descriptionUpdated getLock:', call.conference.description.getLock());
    // console.warn('descriptionUpdated getDefaultRtmp:', call.conference.description.getDefaultRtmp());

    // console.warn('descriptionUpdated attendeeByPass:', call.conference.description.attendeeByPass);

    if (desc_test == true) {
      desc_test = false;

      // console.warn('descriptionUpdated getShareInfo:');
      // call.conference.description.getShareInfo('zh')
      // .then((result) => {
      //   console.warn('getShareInfo success', result);
      // })
      // .catch(() => {
      //   console.warn('getShareInfo fail');
      // })

      // console.warn('descriptionUpdated attendeeByPass:', call.conference.description.attendeeByPass);

      // lock
      // call.conference.description.setLock({
      //   'admissionPolicy' : 'closedAuthenticated', // closedAuthenticated | openAuthenticated
      //   'attendeeByPass'  : false
      // })
      // .then(() => {
      //   console.warn('descriptionUpdated setLock lock success');
      //   console.warn('descriptionUpdated attendeeByPass:', call.conference.description.attendeeByPass);
      // })
      // .catch((e) => {
      //   console.warn('descriptionUpdated setLock lock fail');
      // });



      // unlock
      // call.conference.description.setLock({
      //   'admissionPolicy' : 'anonymous'
      // })
      // .then(() => {
      //   console.warn('descriptionUpdated setLock unlock success');
      // })
      // .catch((e) => {
      //   console.warn('descriptionUpdated setLock unlock fail');
      // });
    }
  });

  let view_test = true;
  call.conference.on('viewUpdated', () => {
    // console.warn('*******************************************');
    // console.warn('viewUpdated view:', call.conference.view);

    // console.warn('viewUpdated getLayout:', call.conference.view.getLayout());
    // console.warn('viewUpdated getInitialFilters:', call.conference.view.getInitialFilters());
    // console.warn('*******************************************');

    if (view_test == true) {
      view_test = false;

      // call.conference.view.setSpeakMode('free') // handUp | free
      //   .then((res) => {
      //     console.warn(res);
      //   })
      //   .catch((e) =>{
      //     console.warn(e);
      //   })

      //   call.conference.view.setLayout({
      //       'videoLayout' : 'Equality' // SpeechExcitation | Equality | Exclusive
      //     })
      //   .then(() => {
      //     console.warn('viewUpdated GetInitialFilters success', );
      //   })
      //   .catch(() => {
      //     console.warn('viewUpdated GetInitialFilters fail', );
      //   })

      //   call.conference.view.setInitialFilters({
      //     'role' : 'default',
      //     'ingress' : 'block'
      //   })
      //   .then(() => {
      //     console.warn('viewUpdated setInitialFilters success', );
      //   })
      //   .catch(() => {
      //     console.warn('viewUpdated setInitialFilters fail', );
      //   })

      //   call.conference.view.setInitialFilters({
      //     'role' : 'default',
      //     'ingress' : 'unblock'
      //   })
      //   .then(() => {
      //     console.warn('viewUpdated setInitialFilters success', );
      //   })
      //   .catch(() => {
      //     console.warn('viewUpdated setInitialFilters fail', );
      //   })
    }
  });

  let state_test = true;
  call.conference.on('stateUpdated', () => {
    // console.warn('stateUpdated state:', call.conference.state);

    // if(state_test == true)
    // {
    //   state_test = false;
    // }
  });

  call.conference.on('recordUpdated', () => {
    // console.warn('recordUpdated ', call.conference.record);
    // console.warn('recordUpdated getRecordStatus', call.conference.record.getRecordStatus());

    // call.conference.record.setRecordStatus('start') // start / stop / pause / resume
    //   .then((result) => {
    //     console.warn(result);
    //   })
    //   .catch((e) => {
    //     console.warn(e);
    //   })
  });

  call.conference.on('rtmpUpdated', () => {
    // console.warn('rtmpUpdated ', call.conference.rtmp);

    // console.warn('rtmpUpdated getRtmpStatus', call.conference.rtmp.getRtmpStatus());

    // call.conference.rtmp.setRtmpStatus('start') // start / stop / pause / resume
    //   .then((result) => {
    //     console.warn(result);
    //   })
    //   .catch((e) => {
    //     console.warn(e);
    //   })

    // call.conference.rtmp.setRtmpStatus('start')
    //   .then((func, res) => {
    //     console.warn('setRtmpStatus = ', res);
    //   })
    //   .catch((e) => {
    //     console.warn(e);
    //   })
  });

  setTimeout(() => {

  }, 1000 * 1000);


}

module.exports = test;
