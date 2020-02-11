/*
 * @file gtest_util.h
 * @date 2019-12-03
 *
 * @brief 
 */
#pragma once
#include <memory>
#include <type_traits>

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
    type& type::operator=(const type& other) = default; \
    type::type(void* data) \
        : m_data(nullptr) \
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

class StaticMockType
{
public:
    virtual ~StaticMockType() = default;
};

/**
 * @brief 初始化mock（不继承与StaticMockType）
 * @tparam MockType Mock的类型
 * @param mock mock的智能指针
 */
template<typename MockType, typename std::enable_if<!std::is_base_of<StaticMockType, MockType>::value, int>::type = 0>
void SetUpMock(std::shared_ptr<MockType>& mock)
{
    mock = std::make_shared<MockType>();
}

/**
 * @brief 初始化mock（继承与StaticMockType），并调用SetMock方法
 * @tparam MockType Mock的类型
 * @param mock mock的智能指针
 */
template<typename MockType, typename std::enable_if<std::is_base_of<StaticMockType, MockType>::value, int>::type = 0>
void SetUpMock(std::shared_ptr<MockType>& mock)
{
    mock = std::make_shared<MockType>();
    MockType::SetMock(mock);
}

/**
 * @brief 变长模板展开收尾
 */
inline void SetUpMock()
{
}

/**
 * @brief 初始化所有mock
 * @tparam MockType 第一个mock类型
 * @tparam MockTypes 后续的mock类型
 * @param mock 第一个mock
 * @param mockTypes 后续的mock
 */
template<typename MockType, typename... MockTypes>
void SetUpMock(MockType& mock, MockTypes&... mockTypes)
{
    SetUpMock(mock);
    SetUpMock(mockTypes...);
}

/**
 * @brief 释放mock
 * @tparam MockType Mock的类型
 * @param mock mock的智能指针
 */
template<typename MockType>
void TearDownMock(std::shared_ptr<MockType>& mock)
{
    mock = nullptr;
}

/**
 * @brief 变长模板展开收尾
 */
inline void TearDownMock()
{
}

/**
 * @brief 释放所有mock
 * @tparam MockType 第一个mock类型
 * @tparam MockTypes 后续的mock类型
 * @param mock 第一个mock
 * @param mockTypes 后续的mock
 */
template<typename MockType, typename... MockTypes>
void TearDownMock(MockType& mock, MockTypes&... mockTypes)
{
    TearDownMock(mock);
    TearDownMock(mockTypes...);
}
