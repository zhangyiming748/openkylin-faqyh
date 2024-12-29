/**
 * @file formatter.hpp
 * @brief 格式化输出类头文件
 * @author DSOE1024
 */
#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <map>
#include <memory>

/**
 * @namespace formatter
 * @brief 格式化输出命名空间
 */
namespace formatter
{
    /**
     * @brief 格式化输出类型枚举
     */
    enum class FormatType
    {
        /**
         * @brief 文本格式，纯文本信息
         */
        Text,
        /**
         * @brief Markdown格式
         */
        Markdown,
        /**
         * @brief JSON格式
         */
        Json
    };

    /**
     * @class Formatter
     * @brief 格式化输出类，用于格式化输出配置信息为Markdown等格式
     */
    class Formatter
    {
    private:

        /**
         * @brief 格式化为普通文本
         */
        std::string format_text(const std::string &source);

        /**
         * @brief 格式化为Markdown
         */
        std::string format_markdown(const std::string &source);

        // TODO: JSON格式化

    public:
        Formatter();
        ~Formatter();

        /**
         * @brief 格式化输出为指定格式的字符串
         */
        std::string format_to_string(const std::string &source, FormatType type);
    };

}

#endif // FORMATTER_HPP