/**
 * @file: main.cpp
 * @description: 程序入口
 * @author: DSOE1024
 */
#include "../include/main.hpp"

using namespace hwinfo_ns;

int main(int argc, char **argv)
{
    /**
     * @description: 负责终端输出
     */
    Logger mainLogger;

    mainLogger.log("欢迎使用FAQYH！", log_level::INFO);

#pragma region 用户选择输出格式
    int formatChoice;
    while (true)
    {
        mainLogger.log("请选择输出格式（输入数字按回车）：");
        mainLogger.log("1. 适用于提交issue的Markdown格式");
        mainLogger.log("2. 适用于在聊天软件上分享的普通文本格式");

        if (!(std::cin >> formatChoice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mainLogger.log("输入错误，请重新输入", log_level::ERROR);
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (formatChoice == 1)
        {
            mainLogger.log("您选择了Markdown格式，将生成Markdown格式的硬件信息报告", log_level::WARNING);
            break;
        }
        else if (formatChoice == 2)
        {
            mainLogger.log("你选择了普通文本格式", log_level::WARNING);
            break;
        }
        else
        {
            mainLogger.log("输入错误，请重新输入", log_level::ERROR);
            continue;
        }
    }

#pragma endregion

    /**
     * @description: 获取硬件信息
     */
    Hwinfo hwinfo;

    std::vector<Netinfo> netinfo = hwinfo.get_net_info();

    for (auto &i : netinfo)
    {
        mainLogger.log(i.get_str(), log_level::INFO);
    }

    std::vector<Cpuinfo> info = hwinfo.get_cpu_info();
    std::vector<Diskinfo> diskinfo = hwinfo.get_disk_info();
    Osinfo osinfo = hwinfo.get_os_info();

    Raminfo raminfo = hwinfo.get_ram_info();
    mainLogger.log(raminfo.get_str(), log_level::INFO);

    mainLogger.log(osinfo.get_str(), log_level::INFO);

    Productinfo prod = hwinfo.get_product_info();

    for (auto &i : info)
    {
        mainLogger.log(i.get_str(), log_level::INFO);
    }
    for (auto &i : diskinfo)
    {
        mainLogger.log(i.get_str(), log_level::INFO);
    }

    mainLogger.log(prod.get_str(), log_level::INFO);

#pragma region 打开文件

    mainLogger.log("文件已生成，是否打开？也可以稍后手动打开：");
    mainLogger.log("1. 是", log_level::WARNING);
    mainLogger.log("2. 否", log_level::ERROR);

    int fileopenChoice;
    while (true)
    {
        if (!(std::cin >> fileopenChoice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mainLogger.log("输入错误，请重新输入", log_level::ERROR);
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (fileopenChoice == 1)
        {
            mainLogger.log("打开文件", log_level::INFO);
            // 调用Linux命令打开文件
            system("xdg-open");
        }
        else if (fileopenChoice == 2)
        {
            mainLogger.log("稍后可以手动打开文件");
        }
        else
        {
            mainLogger.log("输入错误，请重新输入", log_level::ERROR);
            continue;
        }
    }

#pragma endregion

    mainLogger.log("感谢使用FAQYH！");

    return 0;
}
