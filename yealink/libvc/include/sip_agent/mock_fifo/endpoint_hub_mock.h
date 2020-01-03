/*
 * @file endpoint_hub_mock.h
 * @date 2019-12-04
 *
 * @brief 
 */
#pragma once
#include <sip_agent/src/pjsip_helper/pjsip_endpoint.h>
#include <gmock/gmock.h>
#include "components/test_util/gtest_util.h"

namespace yealink
{
namespace mock
{
class EndpointHubMock
{
    DECLARE_SET_MOCK(EndpointHubMock)
public:
    MOCK_METHOD2(PostMsg, bool(pjsip_endpoint*, const MessageFIFO::Message&));
    MOCK_METHOD1(AddEndpoint, void(PJSIPEndpoint*));
    MOCK_METHOD1(RemoveEndpoint, void(PJSIPEndpoint*));
    MOCK_METHOD2(RegistGlobalHandler, void(const void*, MessageHandler*));
    MOCK_METHOD1(RemoveGlobalHandler, void(const void*));
};
} // namespace mock
} // namespace yealink
