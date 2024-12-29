/**
 * @file logger.hpp
 * @brief 日志类
 * @author DSOE1024
 */
#pragma once

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <map>

/** 日志等级 */
enum class log_level {
    INFO,
    WARNING,
    ERROR
};

/**
 * 日志类
 */
class Logger
{
private:
    std::map<log_level, std::string> levelColors;
    std::map<log_level, std::string> levelFontBold;
public:
    Logger();
    ~Logger();
    /**
     * @brief 日志输出
     * @param msg 日志信息
     * @return void
     */
    void log(std::string msg);

    /**
     * @brief 日志输出
     * @param msg 日志信息
     * @param level 日志等级
     * @return void
     */
    void log(std::string msg, log_level level);
};


#endif // LOGGER_HPP