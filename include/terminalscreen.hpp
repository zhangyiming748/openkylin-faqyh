/**
 * @file terminalscreen.hpp
 * @brief 终端屏幕切换类
 * @author DSOE1024
 */
#ifndef TERMINALSCREEN_HPP
#define TERMINALSCREEN_HPP

#include <iostream>

/**
 * @class Terminalscreen
 * @brief 终端屏幕切换类
 */
class Terminalscreen
{
private:
public:

    Terminalscreen();

    ~Terminalscreen();

    /**
     * @brief 切换到备用屏幕
     * @return void
     */
    void switchToAlternateScreen();

    /**
     * @brief 切换到主屏幕
     * @return void
     */
    void switchToMainScreen();
};

#endif // TERMINALSCREEN_HPP