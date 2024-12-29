/**
 * @file: main.cpp
 * @description: 程序入口
 * @author: DSOE1024
 */
#include "../include/main.hpp"

using namespace hwinfo_ns;

Terminalscreen terminalscreen;

void exit_signal_handler(int signum)
{
    terminalscreen.enableEcho();
    terminalscreen.switchToMainScreen();
    exit(signum);
}

int main(int argc, char **argv)
{
    signal(SIGINT, exit_signal_handler);  // Ctrl+C
    signal(SIGTERM, exit_signal_handler); // 终止信号

    terminalscreen.switchToAlternateScreen();

    /**
     * @description: 负责终端输出
     */
    Logger logger;

    logger.log("欢迎使用FAQYH！", log_level::INFO);

#pragma region 用户选择输出格式
    int formatChoice;
    while (true)
    {
        logger.log("请选择输出格式（输入数字按回车）：");
        logger.log("1. 适用于提交issue的Markdown格式");
        logger.log("2. 适用于在聊天软件上分享的普通文本格式");

        if (!(std::cin >> formatChoice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            logger.log("输入错误，请重新输入", log_level::ERROR);
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');



        if (formatChoice == 1)
        {
            logger.log("您选择了Markdown格式，将生成Markdown格式的硬件信息报告", log_level::WARNING);
            break;
        }
        else if (formatChoice == 2)
        {
            logger.log("你选择了普通文本格式", log_level::WARNING);
            break;
        }
        else
        {
            logger.log("输入错误，请重新输入", log_level::ERROR);
            continue;
        }
    }

#pragma endregion

#pragma region 获取硬件信息
    /**
     * @description: 获取硬件信息
     */
    Hwinfo hwinfo;

    std::string report = hwinfo.get_source_report();
    logger.log(report, log_level::INFO);

    // logger.log(report, log_level::INFO);

#pragma endregion

#pragma region 格式化报告

    // Markdown格式
    if (formatChoice == 1)
    {
    }

#pragma endregion

#pragma region 打开文件（待实现）
    // TODO: 打开文件

    //     logger.log("报告文件已生成，是否打开？也可以稍后手动打开：");
    //     logger.log("1. 是", log_level::WARNING);
    //     logger.log("2. 否", log_level::ERROR);

    //     int fileopenChoice;
    //     while (true)
    //     {
    //         if (!(std::cin >> fileopenChoice))
    //         {
    //             std::cin.clear();
    //             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //             logger.log("输入错误，请重新输入", log_level::ERROR);
    //             continue;
    //         }

    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //         if (fileopenChoice == 1)
    //         {
    //             logger.log("打开文件", log_level::INFO);
    //             // 调用Linux命令打开文件
    //             system("xdg-open");
    //         }
    //         else if (fileopenChoice == 2)
    //         {
    //             logger.log("稍后可以手动打开文件");
    //         }
    //         else
    //         {
    //             logger.log("输入错误，请重新输入", log_level::ERROR);
    //             continue;
    //         }
    //     }

#pragma endregion

#pragma region 退出程序

    // 为了能上下滚动查看终端输出，禁用回显
    terminalscreen.disableEcho();

    logger.log("感谢使用FAQYH！");
    logger.log("再见！");
    logger.log("按回车退出程序...");
    while (true)
    {
        if (std::cin.get() == '\n')
        {
            break;
        }
    }
    terminalscreen.enableEcho();
    terminalscreen.switchToMainScreen();

#pragma endregion

    return 0;
}
