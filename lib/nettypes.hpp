#pragma once 

#include <arpa/inet.h> 

#include <string>
#include <cstring>
#include <iostream>

#include "endian.hpp"
#include "show.hpp"


inline namespace inline_more
{
    ///////////////////////////////////////
    // ipv4_t 

    struct ipv4_t
    {
        uint32be_t value;    

        explicit operator bool() const
        {
            return static_cast<bool>(value);
        }

        bool 
        operator==(const ipv4_t &other) const
        {
            return value == other.value;
        }
        bool 
        operator!=(const ipv4_t &other) const
        {
            return !(value == other.value);
        }

        bool operator<(const ipv4_t &other) const
        {
            return value < other.value;
        }
        bool operator>(const ipv4_t &other) const
        {
            return value > other.value;
        }
        
        bool operator<=(const ipv4_t &other) const
        {
            return value <= other.value;
        }
        bool operator>=(const ipv4_t &other) const
        {
            return value >= other.value;
        }
    };

    template <typename CharT, typename Traits>
    inline typename std::basic_ostream<CharT, Traits> &
    operator<<(std::basic_ostream<CharT,Traits> &out, const ipv4_t & instance)
    {
        std::ios::fmtflags f = out.flags(); // store flags

        out << std::hex << instance.value;

        out.flags(f);
        return out;
    }

    template <typename CharT, typename Traits>
    typename std::basic_istream<CharT, Traits> &
    operator>>(std::basic_istream<CharT,Traits>& in, ipv4_t & instance)
    {
        std::ios::fmtflags f = in.flags(); // store flags

        uint32be_t val;

        if(in >> std::hex >> val)
        {
            instance.value = val;
        }

        in.flags(f);
        return in;
    }

    inline std::string
    show(const ipv4_t &addr, const char * n = nullptr)
    {
        std::string s;
        if (n) {
            s += std::string(n) + ' ';
        }
        char buf[16] = { '\0' };
        inet_ntop(AF_INET, &addr, buf, sizeof(buf));
        return s + std::string(buf);
    }

    ///////////////////////////////////////
    // ipv6_t 

    struct ipv6_t
    {
        char value[16];

        explicit operator bool() const
        {
            auto addr = reinterpret_cast<uint64_t const *>(value);
            return addr[0] || addr[1];
        }

        bool 
        operator==(const ipv6_t &other) const
        {
            return memcmp(value, other.value, 16) == 0;
        }

        bool 
        operator!=(const ipv6_t &other) const
        {
            return !(value == other.value);
        }
    };


    template <typename CharT, typename Traits>
    inline typename std::basic_ostream<CharT, Traits> &
    operator<<(std::basic_ostream<CharT,Traits> &out, const ipv6_t & instance)
    {
        std::ios::fmtflags f = out.flags(); // store flags

        out << std::hex;

        auto addr = reinterpret_cast<uint64_t const *>(instance.value);

        out << addr[0] << ' '<< addr[1];

        out.flags(f);
        return out;
    }

    template <typename CharT, typename Traits>
    typename std::basic_istream<CharT, Traits> &
    operator>>(std::basic_istream<CharT,Traits>& in, ipv6_t & instance)
    {
        std::ios::fmtflags f = in.flags(); // store flags
        uint64_t addr[2];

        if (in >> std::hex >> addr[0] >> addr[1])
        {
            auto ptr = reinterpret_cast<char *>(addr);
            for(int i = 0; i < 16; ++i)
            {
                instance.value[i] = ptr[i];
            }    
        }

        in.flags(f);
        return in;
    }

    inline std::string
    show(const ipv6_t &addr, const char * n = nullptr)
    {
        std::string s;
        if (n) {
            s += std::string(n) + ' ';
        }
        char buf[INET6_ADDRSTRLEN] = { '\0' };
        inet_ntop(AF_INET6, &addr, buf, sizeof(buf));
        return s + std::string(buf);
    }

} // inline_more
