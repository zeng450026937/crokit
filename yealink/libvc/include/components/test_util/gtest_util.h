/*
 * @file gtest_util.h
 * @date 2019-12-03
 *
 * @brief 
 */
#pragma once
#include <memory>

#define DECLARE_SET_MOCK(type) \
public: \
    static void SetMock(const std::shared_ptr<type>& mock);

#define DECLARE_MOCK_OBJECT(type, mockType) \
    DECLARE_SET_MOCK(mockType) \
    MOCK_METHOD1(Equal, bool(const type& other)); \
    MOCK_METHOD0(Available, bool());

#define GENERATE_MOCK_OBJECT_SET_MOCK(mockType) \
    namespace \
    { \
    std::weak_ptr<mockType> g_mockInstance; \
    std::shared_ptr<mockType> GetMock() \
    { \
        return g_mockInstance.lock(); \
    } \
    } \
    void mockType::SetMock(const std::shared_ptr<mockType>& mock) \
    { \
        g_mockInstance = mock; \
    }

#define GENERATE_MOCK_OBJECT_CONSTRUCTOR_DESTRUCTOR(type) \
    type::type() \
        : m_data(nullptr) \
    { \
    } \
    type::~type() = default; \
    type::type(const type& other) = default; \
    type& type::operator=(const type& other) \
    { \
        return *this; \
    } \
    type::type(void* data) \
    { \
    }

#define GENERATE_MOCK_OBJECT_AVAILABLE_FUNCTION(type) \
    bool type::Available() const \
    { \
        return GetMock()->Available(); \
    }

#define GENERATE_MOCK_OBJECT_OPERATOR_EQUAL(type) \
    bool type::operator==(const type& other) const \
    { \
        return GetMock()->Equal(other); \
    } \
    bool type::operator!=(const type& other) const \
    { \
        return !(*this == other); \
    }

#define GENERATE_MOCK_OBJECT_IMPL(type, mockType) \
    GENERATE_MOCK_OBJECT_SET_MOCK(mockType) \
    GENERATE_MOCK_OBJECT_CONSTRUCTOR_DESTRUCTOR(type) \
    GENERATE_MOCK_OBJECT_AVAILABLE_FUNCTION(type) \
    GENERATE_MOCK_OBJECT_OPERATOR_EQUAL(type)

#define SET_UP_MOCK(mockVariable, mockType) \
    mockVariable = std::make_shared<mockType>(); \
    mockType::SetMock(mockVariable);

#define TEAR_DOWN_MOCK(mockVariable, mockType) \
    mockVariable = nullptr; \
    mockType::SetMock(nullptr);

template<typename MockType>
void SetUpMock(std::shared_ptr<MockType>& mock)
{
    mock = std::make_shared<MockType>();
    MockType::SetMock(mock);
}

inline void SetUpMock()
{
}

template<typename MockType, typename... MockTypes>
void SetUpMock(MockType& mock, MockTypes&... mockTypes)
{
    SetUpMock(mock);
    SetUpMock(mockTypes...);
}
template<typename MockType>
void TearDownMock(std::shared_ptr<MockType>& mock)
{
    mock = nullptr;
    MockType::SetMock(nullptr);
}

inline void TearDownMock()
{
}

template<typename MockType, typename... MockTypes>
void TearDownMock(MockType& mock, MockTypes&... mockTypes)
{
    TearDownMock(mock);
    TearDownMock(mockTypes...);
}
