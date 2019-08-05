#ifndef __SIMPLE_STRING_H__
#define __SIMPLE_STRING_H__
#include <cstdlib>
#include <cstring>

namespace yealink
{
template<typename T>
class SString
{
public:
    SString()
        : m_string(nullptr)
        , m_uLength(0)
    {
        Make(nullptr, 0);
    }
    explicit SString(const T* string)
        : m_string(nullptr)
        , m_uLength(0)
    {
        Make(string);
    }
    SString(const T* string, size_t uLength)
        : m_string(nullptr)
        , m_uLength(0)
    {
        Make(string, uLength);
    }
    SString(const SString& right)
        : m_string(nullptr)
        , m_uLength(0)
    {
        Make(right.m_string, right.m_uLength);
    }
    ~SString()
    {
        Release();
    }

public:
    const T* ConstData() const
    {
        return m_string;
    }
    size_t Length() const
    {
        return m_uLength;
    }
    size_t GetSize() const
    {
        if (m_string == nullptr)
        {
            return 0;
        }
        return (m_uLength + 1) * sizeof(T);
    }
    bool Empty() const
    {
        return Length() == 0;
    }

public:
    SString& operator=(const T* string)
    {
        Make(string);
        return *this;
    }
    SString& operator=(const SString& right)
    {
        Make(right.m_string, right.m_uLength);
        return *this;
    }

public:
    void Make(const T* string)
    {
        Release();
        size_t uLength = 0;
        while (string)
        {
            if (string[uLength] == 0)
            {
                break;
            }
            ++uLength;
        }
        Make(string, uLength);
    }
    void Make(const T* string, size_t uLength)
    {
        Release();
        if (uLength > 0)
        {
            m_string = new T[uLength + 1];
            if (m_string == nullptr)
            {
                m_uLength = 0;
            }
            else
            {
                memcpy(m_string, string, uLength * sizeof(T));
                m_uLength = uLength;
                m_string[m_uLength] = (T)0;
            }
        }
        else
        {
            m_string = new T[1];
            m_string[0] = (T)0;
            m_uLength = 0;
        }
    }
    void Release()
    {
        if (m_string != nullptr)
        {
            delete[] m_string;
            m_string = nullptr;
        }
        m_uLength = 0;
    }

private:
    T* m_string;
    size_t m_uLength;
};

typedef SString<char> SStringA;
typedef SString<wchar_t> SStringW;
} // namespace yealink

#endif //__SIMPLE_STRING_H__
