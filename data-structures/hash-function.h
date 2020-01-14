#pragma once

template <class T>
struct HashFunction   // hash function type overrides
{
    static size_t Hash(const T& k) { static_assert(false, "Unsupported key type!"); };
};

template <>
size_t HashFunction<const char*>::Hash(const char* const& k)
{
    int hash = 401;
    const char* ch = k;

    while (*ch != '\0')
    {
        hash = hash << 4;
        hash = hash + (int)(*ch);
        ch++;
    }
    return hash;
}

template <>
size_t HashFunction<int>::Hash(const int& k)
{
    int hash = 401;
    hash = hash << 4;
    hash = hash + k;
    return hash;
}