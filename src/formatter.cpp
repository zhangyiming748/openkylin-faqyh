/**
 * @file formatter.cpp
 * @brief 格式化器类实现
 * @author DSOE1024
 */
#include "../include/formatter.hpp"

namespace formatter
{
    Formatter::Formatter()
    {
    }

    Formatter::~Formatter()
    {
    }

    std::string Formatter::format_text(const std::string &source)
    {
        return source;
    }

    std::string Formatter::format_markdown(const std::string &source)
    {
        return source;
    }

    std::string Formatter::format_to_string(const std::string &source, FormatType type)
    {
        switch (type)
        {
        case FormatType::Text:
            return format_text(source);
            break;
        case FormatType::Markdown:
            return format_markdown(source);
            break;
        default:
            return source;
            break;
        }

        // return source;
    }
}