#pragma once

#include <string>
#include <codecvt>
#include <locale>

namespace cks {
    
    using convert_t = std::codecvt_utf8<wchar_t>;
    static std::wstring_convert<convert_t, wchar_t> converter;

    class WStringUtil {
    public:
        static std::wstring toWString(std::string str) {
            return converter.from_bytes(str);
        }
    };
}