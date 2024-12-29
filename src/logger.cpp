#include "logger.hpp"

Logger::Logger(){
    levelColors[log_level::INFO] = "\033[32m"; // 绿色
    levelColors[log_level::WARNING] = "\033[33m"; // 黄色
    levelColors[log_level::ERROR] = "\033[31m"; // 红色
}

Logger::~Logger(){
    
}

void Logger::log(std::string msg) {
    std::cout << msg << std::endl;
}

void Logger::log(std::string msg, log_level level) {
    std::cout << levelColors[level] << msg << "\033[0m" << std::endl;
}
