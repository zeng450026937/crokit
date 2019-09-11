const path = require('path');

async function test(binding, userAgent) {
  console.log('Call test');

  const { Call, VideoManager, DesktopCapture } = binding;

  const videoManager = new VideoManager();

  console.log('-- enumerateDevices --');
  videoManager.enumerateDevices();

  console.log('-- videoInputDeviceList --');
  const videoInputDeviceList = videoManager.videoInputDeviceList();
  console.log(videoInputDeviceList);

  const sink = {
    onFrame(frame) {
    },
  };

  videoManager.videoInputDevice = videoInputDeviceList[0];
  // videoManager.setLocalVideoSink(sink);

  videoManager.acquireStream();

  const call = new Call(userAgent);

  // call.connect('sip:62061**040660@123456.onylyun.com;transport=tls');
  // call.connect('sip:1001@123456.onylyun.com;transport=tls');
  //call.connect('sip:1090@223504.onylyun.com;transport=tls');
  call.connect('sip:23524@223504.onylyun.com;transport=tls');
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

  eventNames.forEach((event) => {
    call.on(event, () => console.log(event));
  })

  let hangupTimmer;
  let shareTimer;

  // call.on('established', async() => {
  //   console.log('established');

  //   hangupTimmer = setTimeout(() => {
  //     call.hangup();
  //   }, 35000);
  // });

  // call.on('share:established', async() => {
  //   console.log('share:established');

  //   setTimeout(async() => {
  //     const desktopCapture = new DesktopCapture();
  //     const list = await desktopCapture.getSources({
  //       captureWindow: true,
  //       captureScreen: false,
  //     });

  //     console.log(list);

  //     const picture = path.resolve('./test-picture.png');

  //     console.log(picture);

  //     call.startShare({ screen: 0, window: 14747790, file: picture });
  //   }, 1000);

  //   shareTimer = setTimeout(() => {
  //     call.stopShare();
  //   }, 25000);
  // })

  // call.on('finished', () => {
  //   console.log('finished');
  //   clearTimeout(hangupTimmer);
  //   clearTimeout(shareTimer);
  //   videoManager.releaseStream();
  //   videoManager.videoInputDevice = null;
  //   userAgent.unregister();
  // });

  // if (global.window) {
  //   window.call = call;
  // }

  let user_test = true;
  call.conference.on('usersUpdated', (arg1, arg2) => {
    console.warn('start start start start start');
    console.warn('usersUpdated', call.conference);
    console.warn('usersUpdated users:', call.conference.users);
    console.warn('usersUpdated currentUser:', call.conference.users.currentUser);
    console.warn('usersUpdated userList:', call.conference.users.userList);
    console.warn('usersUpdated userList.length:', call.conference.users.userList.length);

    if(user_test == true)
    {
      user_test = false;

      call.conference.users.userList.map((user) => {
        console.warn('this user entity = ', user.entity, 'isPresenter ', user.isPresenter());
        console.warn('isOrganizer ', user.isOrganizer());
        console.warn('isCurrentUser ', user.isCurrentUser());
        console.warn('isPresenter ', user.isPresenter());
        console.warn('isAttendee ', user.isAttendee());
        console.warn('isCastViewer ', user.isCastViewer());
        console.warn('isAttendee ', user.isAttendee());
        console.warn('isDemonstrator ', user.isDemonstrator());
        console.warn('isPresenterDemonstrator ', user.isPresenterDemonstrator());
        console.warn('isOnHold ', user.isOnHold());
        console.warn('isSharing ', user.isSharing());
        console.warn('isFocus ', user.isFocus());
        console.warn('getAudioFilter = ', user.getAudioFilter());
        console.warn('getAudioFilter = ', user.getVideoFilter());

        setInterval(() => {
          console.warn('getAudioFilter = ', user.getStats());
        }, 5000);

        console.warn('SetAudioIngressFilter = ', user.setAudioIngressFilter(false));
        console.warn('SetAudioIngressFilter = ', user.setAudioIngressFilter(true));
        console.warn('SetAudioEgressFilter = ', user.setAudioEgressFilter(false));
        console.warn('SetAudioEgressFilter = ', user.setAudioEgressFilter(true));
        console.warn('SetVideoIngressFilter = ', user.setVideoIngressFilter(false));
        console.warn('SetVideoIngressFilter = ', user.setVideoIngressFilter(true));
        console.warn('SetDisplayName = ', user.setDisplayName('lalaal'));

        if(user.isCurrentUser() == false)
        {
          console.warn('setPermission = ', user.setPermission('attendee'));
          console.warn('hold = ', user.hold());

          console.warn('unHold = ', call.conference.users.allow([], true));

          //console.warn('unHold = ', user.unHold());
          console.warn('setPermission = ', user.setPermission('presenter'));
        }

        console.warn('SetVideoIngressFilter = ', user.setFocus(true));
        console.warn('SetVideoIngressFilter = ', user.setFocus(false));

        //console.warn('kick = ', user.kick());
      });
    }


    console.warn('end end end end end');
   });

  let desc_test = true;
  call.conference.on('descriptionUpdated', (arg1, arg2) => {
    console.warn('descriptionUpdated desc:', call.conference.description);
    console.warn('descriptionUpdated startTime:', call.conference.description.startTime);
    console.warn('descriptionUpdated defaultRtmp:', call.conference.description.defaultRtmp);
    console.warn('descriptionUpdated lobbyCapable:', call.conference.description.lobbyCapable);

    console.warn('descriptionUpdated getLock:', call.conference.description.getLock());
    console.warn('descriptionUpdated getDefaultRtmp:', call.conference.description.getDefaultRtmp());
    console.warn('descriptionUpdated getShareInfo:', call.conference.description.getShareInfo('zh'));

    if(desc_test == true)
    {
      desc_test = false;

      // lock
      console.warn('descriptionUpdated setLock:', call.conference.description.setLock({
        'admissionPolicy' : 'openAuthenticated'
      }));

      // unlock
      console.warn('descriptionUpdated setLock:', call.conference.description.setLock({
        'admissionPolicy' : 'anonymous'
      }));
    }
  });

  let view_test = true;
  call.conference.on('viewUpdated', () => {
    console.warn('*******************************************');
    console.warn('viewUpdated view:', call.conference.view);

    console.warn('viewUpdated getLayout:', call.conference.view.getLayout());
    console.warn('viewUpdated getInitialFilters:', call.conference.view.getInitialFilters());
    console.warn('*******************************************');

    if(view_test == true)
    {
      view_test = false;

      console.warn('viewUpdated GetInitialFilters:', call.conference.view.setLayout(
        {
          'videoLayout' : 'Equality' // SpeechExcitation | Equality | Exclusive
        }
      ));

      console.warn('viewUpdated SetInitialFilters:', call.conference.view.setInitialFilters(
        {
          'role' : 'default',
          'ingress' : 'block'
        }
      ));

      console.warn('viewUpdated SetInitialFilters:', call.conference.view.setInitialFilters(
        {
          'role' : 'default',
          'ingress' : 'unblock'
        }
      ));
    }
  });

  let state_test = true;
  call.conference.on('stateUpdated', () => {
    console.warn('stateUpdated state:', call.conference.state);

    if(state_test == true)
    {
      state_test = false;
    }
  });

  call.conference.on('shareInfoUpdated', (arg1, arg2, arg3) => {
    console.warn('#######################################');
    console.warn('shareInfoUpdated:', arg1, arg2, arg3);
    console.warn('#######################################');
  });

  call.conference.on('callStatsUpdated', (arg1, arg2, arg3) => {
    console.warn('#######################################');
    console.warn('callStatsUpdated:', arg1, arg2, arg3);
    console.warn('#######################################');
  });

  setTimeout(() => {

  }, 1000 * 1000);


}

module.exports = test;
