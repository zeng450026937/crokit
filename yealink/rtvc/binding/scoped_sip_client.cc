#include "yealink/rtvc/binding/scoped_sip_client.h"

#include "yealink/libvc/include/sip_agent/sip_agent_api.h"

namespace yealink {

namespace rtvc {

ScopedSIPClient::ScopedSIPClient() : client_(yealink::CreateSIPClient()) {}
ScopedSIPClient::~ScopedSIPClient() {
  yealink::RealseSIPClient(client_);
}

}  // namespace rtvc

}  // namespace yealink
