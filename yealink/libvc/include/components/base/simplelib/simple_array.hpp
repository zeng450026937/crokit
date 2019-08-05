#ifndef SIMPLE_ARRAY_HPP
#define SIMPLE_ARRAY_HPP

#include <cstdint>
#include <cstdio>
#include <new>

namespace yealink
{
/**
 * @brief 简单数组
 * @tparam ElementType 元素类型
 * @note 该简单数组未非线程安全类型，若需要多线程访问请加锁
 */
template<typename ElementType>
class Array
{
public:
    /**
     * @brief 初始化最大容量，内部元素均为空
     * @param maxSize 初始最大容量
     */
    Array(size_t maxSize = 0);

    /**
     * @brief 析构，析构时释放数组
     */
    ~Array();

    /**
     * @brief 拷贝构造函数
     * @param other 另一个数组
     */
    Array(const Array& other);

    /**
     * @brief 赋值拷贝函数
     * @param other 另一个数组
     * @return 本身
     */
    Array& operator=(const Array& other);

    /**
     * @brief 添加一个元素到数组尾
     * @param element
     * @return 数组本身，可以支持链式调用
     * @note 容量不足时会自动扩容，每次扩容为10个元素大小
     */
    Array& Append(const ElementType& element);

    /**
     * @brief 清空元素
     * @note 会释放所有内存和元素
     */
    void Clear();

    /**
     * @brief 根据下标访问成员
     * @param index 下标
     * @return 返回对应下标成员的引用
     * @note 越界将直接崩溃，使用时需要注意！
     */
    ElementType& operator[](size_t index);

    /**
     * @brief 根据下标访问成员（只读）
     * @param index 下标
     * @return 返回对应下标成员的常引用
     * @note 越界将直接崩溃，使用时需要注意！
     */
    const ElementType& operator[](size_t index) const;

    /**
     * @brief 获取当前数组元素个数
     * @return 元素个数
     */
    size_t Size() const;

    /**
     * @brief 获取当前数组最大容量
     * @return 最大容量
     */
    size_t MaxSize() const;

private:
    /**
     * @brief 数组的头位置
     */
    char* m_headerPtr;
    /**
     * @brief 数组的最大容量
     */
    size_t m_maxSize;
    /**
     * @brief 数组当前元素个数
     */
    size_t m_size;
};

template<typename ElementType>
Array<ElementType>::Array(size_t maxSize)
    : m_maxSize(maxSize)
    , m_size(0)
{
    if (m_maxSize != 0)
    {
        m_headerPtr = new char[sizeof(ElementType) * m_maxSize];
        memset(m_headerPtr, 0, sizeof(ElementType) * m_maxSize);
        if (m_headerPtr == nullptr)
        {
            m_maxSize = 0;
        }
    }
    else
    {
        m_headerPtr = nullptr;
    }
}

template<typename ElementType>
Array<ElementType>::~Array()
{
    for (size_t i = 0; i < m_size; ++i)
    {
        reinterpret_cast<ElementType*>(m_headerPtr + i * sizeof(ElementType))
            ->~ElementType();
    }
    delete[] m_headerPtr;
    m_headerPtr = nullptr;
    m_size = 0;
    m_maxSize = 0;
}

template<typename ElementType>
Array<ElementType>::Array(const Array& other)
    : m_maxSize(other.m_maxSize)
    , m_size(other.m_size)
{
    m_maxSize = other.m_maxSize;
    m_headerPtr = new char[sizeof(ElementType) * m_maxSize];
    memset(m_headerPtr, 0, sizeof(ElementType) * m_maxSize);
    if (m_headerPtr != nullptr)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            new (m_headerPtr + i * sizeof(ElementType)) ElementType(other[i]);
        }
    }
    else
    {
        m_size = 0;
        m_maxSize = 0;
    }
}

template<typename ElementType>
Array<ElementType>& Array<ElementType>::operator=(const Array& other)
{
    if (this == &other)
    {
        return *this;
    }
    Clear();
    m_maxSize = other.m_maxSize;
    m_size = other.m_size;
    m_headerPtr = new char[sizeof(ElementType) * m_maxSize];
    memset(m_headerPtr, 0, sizeof(ElementType) * m_maxSize);
    if (m_headerPtr != nullptr)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            new (m_headerPtr + i * sizeof(ElementType)) ElementType(other[i]);
        }
    }
    else
    {
        m_size = 0;
        m_maxSize = 0;
    }
    return *this;
}

template<typename ElementType>
Array<ElementType>& Array<ElementType>::Append(const ElementType& element)
{
    if (m_size >= m_maxSize)
    {
        size_t newCaptionSize = m_maxSize + 10;
        size_t currentSize = m_size;
        try
        {
            char* newPtr = new char[sizeof(ElementType) * newCaptionSize];
            memset(newPtr, 0, sizeof(ElementType) * newCaptionSize);

            for (size_t i = 0; i < m_size; ++i)
            {
                new (newPtr + i * sizeof(ElementType))
                    ElementType(*reinterpret_cast<ElementType*>(
                        m_headerPtr + i * sizeof(ElementType)));
            }
            Clear();
            m_headerPtr = newPtr;
            m_size = currentSize;
            m_maxSize = newCaptionSize;
        }
        catch (std::bad_alloc&)
        {
            /* 容错，申请新空间失败时不添加新元素 */
            return *this;
        }
    }
    new (m_headerPtr + m_size * sizeof(ElementType)) ElementType(element);
    m_size++;
    return *this;
}

template<typename ElementType>
void Array<ElementType>::Clear()
{
    for (size_t i = 0; i < m_size; ++i)
    {
        reinterpret_cast<ElementType*>(m_headerPtr + i * sizeof(ElementType))
            ->~ElementType();
    }
    delete[] m_headerPtr;
    m_headerPtr = nullptr;
    m_size = 0;
    m_maxSize = 0;
}

template<typename ElementType>
ElementType& Array<ElementType>::operator[](size_t index)
{
    if (index >= m_size)
    {
        std::abort();
    }
    return *reinterpret_cast<ElementType*>(m_headerPtr
                                           + index * sizeof(ElementType));
}

template<typename ElementType>
const ElementType& Array<ElementType>::operator[](size_t index) const
{
    if (index >= m_size)
    {
        std::abort();
    }
    return *reinterpret_cast<ElementType*>(m_headerPtr
                                           + index * sizeof(ElementType));
}

template<typename ElementType>
size_t Array<ElementType>::Size() const
{
    return m_size;
}

template<typename ElementType>
size_t Array<ElementType>::MaxSize() const
{
    return m_maxSize;
}
} // namespace yealink
#endif // SIMPLE_ARRAY_HPP
