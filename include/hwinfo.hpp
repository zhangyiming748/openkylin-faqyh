/**
 * @file hwinfo.hpp
 * @brief 硬件信息头文件
 * @author DSOE1024
 */

#ifndef HWINFO_HPP
#define HWINFO_HPP

#include "iostream"
#include "cstdio"
#include "vector"
#include "fstream"
#include "filesystem"
#include "sys/stat.h"

/**
 * @namespace hwinfo_ns
 * @brief 硬件信息命名空间
 */
namespace hwinfo_ns
{
    /**
     * @brief 硬件信息结构体
     */
    enum ChassisType
    {
        /**
         * @brief 笔记本电脑
         */
        LAPTOP,
        /**
         * @brief 台式机
         */
        DESKTOP,
        /**
         * @brief 其他
         */
        OTHER
    };

    /**
     * @struct productinfo
     * @brief 产品信息结构体
     */
    struct Productinfo
    {
        /**
         * @enum ChassisType
         * @brief 产品类型枚举
         */
        ChassisType chassis_type;
        /**
         * @brief 产品型号名称
         */
        std::string product_name;

        /**
         * @brief 产品供应商名称
         */
        std::string product_vendor;

        /**
         * @brief 将产品信息转换为字符串
         */
        std::string get_str();
    };

    /**
     * @struct osinfo
     * @brief 操作系统信息结构体
     */
    struct Osinfo
    {
        /**
         * @brief 操作系统名称+版本
         */
        std::string os_name_version;

        /**
         * @brief 操作系统内核版本
         */
        std::string os_kernel_version;

        /**
         * @brief 将操作系统信息转换为字符串
         */
        std::string get_str();
    };

    /**
     * @struct cpuinfo
     * @brief CPU信息结构体
     */
    struct Cpuinfo
    {
        /**
         * @brief CPU核心数
         */
        std::string cpu_cores;
        /**
         * @brief CPU线程数
         */
        std::string cpu_threads;
        /**
         * @brief CPU型号
         */
        std::string cpu_model;
        /**
         * @brief 将CPU信息转换为字符串
         */
        std::string get_str();
    };

    /**
     * @struct gpuinfo
     * @brief GPU信息结构体
     */
    struct Gpuinfo
    {
        /**
         * @brief GPU型号
         */
        std::string gpu_name;

        /**
         * @brief 将GPU信息转换为字符串
         */
        std::string get_str();
    };

    /**
     * @struct raminfo
     * @brief 内存信息结构体
     */
    struct Raminfo
    {
        /**
         * 内存大小
         */
        std::string ram_size;

        /**
         * @brief 将内存信息转换为字符串
         */
        std::string get_str();
    };

    /**
     * @struct diskinfo
     * @brief 硬盘信息结构体
     */
    struct Diskinfo
    {
        /**
         * @brief 硬盘名称
         */
        std::string disk_name;

        /**
         * @brief 硬盘大小
         */
        std::string disk_size;

        /**
         * @brief 将硬盘信息转换为字符串
         */
        std::string get_str();
    };

    /**
     * @struct netinfo
     * @brief 网卡信息结构体
     */
    struct Netinfo
    {
        /**
         * @brief 网卡型号
         */
        std::string net_model;

        /**
         * @brief 网卡供应商
         */
        std::string net_vendor;

        /**
         * @brief 将网卡信息转换为字符串
         */
        std::string get_str();
    };

    /**
     * @struct audioinfo
     * @brief 声卡信息结构体
     */
    struct Audioinfo
    {
        /**
         * @brief 声卡型号
         */
        std::string audio_model;

        /**
         * @brief 声卡供应商
         */
        std::string audio_vendor;

        /**
         * @brief 将声卡信息转换为字符串
         */
        std::string get_str();
    };

    /**
     * @struct displayinfo
     * @brief 显示器信息结构体
     */
    struct Displayinfo
    {
        std::string display_size;

        std::string get_str();
    };

    /**
     * @class hwinfo
     * @brief 硬件信息类
     */
    class Hwinfo
    {
    private:
        std::unique_ptr<Productinfo> product_info;
        std::unique_ptr<Osinfo> os_info;
        std::unique_ptr<std::vector<Cpuinfo>> cpu_info;
        std::unique_ptr<std::vector<Gpuinfo>> gpu_info;
        std::unique_ptr<Raminfo> ram_info;
        std::unique_ptr<std::vector<Diskinfo>> disk_info;
        std::unique_ptr<std::vector<Netinfo>> net_info;
        std::unique_ptr<std::vector<Audioinfo>> audio_info;
        
        // TODO: display_info

        std::unique_ptr<std::string> source_report;
        std::unique_ptr<std::string> product_info_str;
        std::unique_ptr<std::string> os_info_str;
        std::unique_ptr<std::string> cpu_info_str;
        std::unique_ptr<std::string> gpu_info_str;
        std::unique_ptr<std::string> ram_info_str;
        std::unique_ptr<std::string> disk_info_str;
        std::unique_ptr<std::string> net_info_str;
        std::unique_ptr<std::string> audio_info_str;
        std::unique_ptr<std::string> display_info_str;

        /**
         * @brief 获取PCI设备ID对应的厂商信息和型号信息
         * @param id PCI设备ID
         * @return std::string 厂商信息和型号信息
         */
        std::string get_pciids(std::string id);
    public:
        Hwinfo();

        ~Hwinfo();

        /**
         * @brief 获取源报告
         * @return std::string 源报告文本
         */
        std::string get_source_report();

        /**
         * @brief 获取产品信息
         * @return productinfo 产品信息
         */
        Productinfo get_product_info();

        /**
         * @brief 获取操作系统信息
         * @return osinfo 操作系统信息
         */
        Osinfo get_os_info();

        /**
         * @brief 获取CPU信息
         * @return std::vector<cpuinfo> CPU信息列表
         */
        std::vector<Cpuinfo> get_cpu_info();

        /**
         * @brief 获取GPU信息
         * @return std::vector<gpuinfo> GPU信息列表
         */
        std::vector<Gpuinfo> get_gpu_info();

        /**
         * @brief 获取内存信息
         * @return std::vector<raminfo> 内存信息列表
         */
        Raminfo get_ram_info();

        /**
         * @brief 获取硬盘信息
         * @return std::vector<diskinfo> 硬盘信息列表
         */
        std::vector<Diskinfo> get_disk_info();

        /**
         * @brief 获取网卡信息
         * @return std::vector<netinfo> 网卡信息列表
         */
        std::vector<Netinfo> get_net_info();

        /**
         * @brief 获取声卡信息
         * @return std::vector<audioinfo> 声卡信息列表
         */
        std::vector<Audioinfo> get_audio_info();


        // TODO: display_info
    };

} // namespace hwinfo_ns

#endif