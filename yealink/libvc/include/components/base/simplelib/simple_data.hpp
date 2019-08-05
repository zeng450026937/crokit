#ifndef __SIMPLE_DATA_H__
#define __SIMPLE_DATA_H__
#include <cstdlib>
#include <cstring>

namespace yealink
{
template<typename T>
class SData
{
public:
    SData()
        : m_pData(nullptr)
        , m_uLength(0)
    {
    }
    SData(const T* pData, size_t uLength)
        : m_pData(nullptr)
        , m_uLength(0)
    {
        Make(pData, uLength);
    }
    SData(const SData& right)
        : m_pData(nullptr)
        , m_uLength(0)
    {
        Make(right.m_pData, right.m_uLength);
    }
    ~SData()
    {
        Release();
    }

public:
    T* Data()
    {
        return m_pData;
    }
    unsigned int Length()
    {
        return m_uLength;
    }
    size_t GetSize()
    {
        return sizeof(T) * m_uLength;
    }

public:
    SData& operator=(const SData& right)
    {
        Release();
        Make(right.m_pData, right.m_uLength);
        return *this;
    }
    T& operator[](size_t index)
    {
        return m_pData[index];
    }
    const T& operator[](size_t index) const
    {
        return m_pData[index];
    }

public:
    void Alloc(size_t uLength)
    {
        if (uLength == m_uLength)
        {
            return;
        }
        Release();
        m_pData = new T[uLength];
        m_uLength = uLength;
    }
    void Make(const T* pData, size_t uLength)
    {
        Release();
        if (pData == nullptr)
        {
            m_pData = nullptr;
            m_uLength = 0;
            return;
        }
        size_t sizeByte = uLength * sizeof(T);
        m_pData = new T[uLength];
        if (m_pData == nullptr)
        {
            m_uLength = 0;
        }
        else
        {
            memcpy(m_pData, pData, sizeByte);
            m_uLength = uLength;
        }
    }
    void Release()
    {
        if (m_pData != nullptr)
        {
            delete[] m_pData;
            m_pData = nullptr;
        }
        m_uLength = 0;
    }

private:
    T* m_pData;
    size_t m_uLength;
};

typedef SData<unsigned char> SByteData;
} // namespace yealink

#endif //__SIMPLE_DATA_H__
