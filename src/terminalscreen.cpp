/**
 * @file terminalscreen.cpp
 * @brief 终端屏幕切换类实现
 * @author DSOE1024
 */
#include "../include/terminalscreen.hpp"

Terminalscreen::Terminalscreen()
{
    
}

Terminalscreen::~Terminalscreen()
{
    
}

void Terminalscreen::switchToAlternateScreen()
{
    // 切换到备用屏幕
    std::cout << "\033[?47h" << std::flush;
}

void Terminalscreen::switchToMainScreen()
{
    // 清理备用屏幕
    std::cout << "\033[2J" << std::flush;
    // 切换回主屏幕
    std::cout << "\033[?47l" << std::flush;
}

void Terminalscreen::enableEcho()
{
    // 启用回显
    system("stty echo");
}

void Terminalscreen::disableEcho()
{
    // 禁用回显
    system("stty -echo");
}
