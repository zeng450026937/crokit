async function test(conference) {
  console.log('Conference test');

  const eventNames = [
    'prepare',
    'connecting',
    'connected',
    'connectFailed',
    'disconnected',
    'finished',
  ];

  eventNames.forEach((event) => {
    conference.on(event, () => console.log('conference event: ' + event));
  });

  conference.on('usersUpdated', (arg1, arg2) => {
    console.warn('start start start start start');
    console.warn('usersUpdated', conference);
    console.warn('usersUpdated users:', conference.users);
    console.warn('usersUpdated currentUser:', conference.users.currentUser);
    console.warn('usersUpdated userList:', conference.users.userList);
    console.warn('usersUpdated userList.length:', conference.users.userList.length);

    conference.users.userList.map((user) => {
      console.warn('this user entity = ', user.entity, 'isPresenter ', user.isPresenter());
      console.warn('isOrganizer ', user.isOrganizer());
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
    });

    console.warn('end end end end end');
   });

  conference.on('descriptionUpdated', (arg1, arg2) => {
    console.warn('descriptionUpdated desc:', conference.description);
    console.warn('descriptionUpdated startTime:', conference.description.startTime);
    console.warn('descriptionUpdated defaultRtmp:', conference.description.defaultRtmp);
    console.warn('descriptionUpdated lobbyCapable:', conference.description.lobbyCapable);

    console.warn('descriptionUpdated getLock:', conference.description.getLock());
    console.warn('descriptionUpdated getDefaultRtmp:', conference.description.getDefaultRtmp());
    console.warn('descriptionUpdated getShareInfo:', conference.description.getShareInfo('zh'));

    console.warn('descriptionUpdated setLock:', conference.description.setLock({
      'admissionPolicy' : 'openAuthenticated'
    }));
  });

  conference.on('viewUpdated', () => {
    console.warn('*******************************************');
    console.warn('viewUpdated view:', conference.view);

    console.warn('viewUpdated getLayout:', conference.view.getLayout());
    console.warn('viewUpdated GetInitialFilters:', conference.view.GetInitialFilters());
    console.warn('*******************************************');
  });

  conference.on('stateUpdated', () => {
    console.warn('stateUpdated state:', conference.state);
  });

  conference.on('shareInfoUpdated', (arg1, arg2, arg3) => {
    console.warn('shareInfoUpdated:', arg1, arg2, arg3);
  });
}

module.exports = test;
