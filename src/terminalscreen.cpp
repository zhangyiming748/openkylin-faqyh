/**
 * @file terminalscreen.cpp
 * @brief 终端屏幕切换类实现
 * @author DSOE1024
 */
#include "../include/terminalscreen.hpp"

Terminalscreen::Terminalscreen()
{
    //switchToAlternateScreen();
}

Terminalscreen::~Terminalscreen()
{
    //switchToMainScreen();
}

void Terminalscreen::switchToAlternateScreen()
{
    std::cout << "\033[?47h" << std::flush;
}

void Terminalscreen::switchToMainScreen()
{
    std::cout << "\033[?47l" << std::flush;
}
