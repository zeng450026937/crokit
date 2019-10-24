#include "yealink/rtvc/lib/video_manager_impl.h"

#include "base/logging.h"

namespace rtvc {

VideoManagerImpl::VideoManagerImpl() {}
VideoManagerImpl::~VideoManagerImpl() = default;

std::vector<Device> VideoManagerImpl::videoInputDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
}

std::vector<Device> VideoManagerImpl::screenDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
}
std::vector<Device> VideoManagerImpl::windowDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
}

Device VideoManagerImpl::videoInputDevice() {
  LOG(INFO) << __FUNCTIONW__;
  return Device();
}
void VideoManagerImpl::setVideoInputDevice(Device device) {
  LOG(INFO) << __FUNCTIONW__;
  LOG(INFO) << __FUNCTIONW__;
}

Device VideoManagerImpl::secondaryVideoInputDevice() {
  LOG(INFO) << __FUNCTIONW__;
  return Device();
}
void VideoManagerImpl::setSecondaryVideoInputDevice(Device device) {
  LOG(INFO) << __FUNCTIONW__;
}

void VideoManagerImpl::SetRotation(int degree, bool is_secondary) {
  LOG(INFO) << __FUNCTIONW__;
}

void VideoManagerImpl::SetLocalVideoSink(VideoSink* sink) {
  LOG(INFO) << __FUNCTIONW__;
}
void VideoManagerImpl::SetLocalShareVideoSink(VideoSink* sink) {
  LOG(INFO) << __FUNCTIONW__;
}

// statc
VideoManager* VideoManager::Instance() {
  static VideoManagerImpl* video_manager = new VideoManagerImpl();
  return video_manager;
}

}  // namespace rtvc
