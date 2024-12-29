/**
 * @file hwinfo.cpp
 * @brief 硬件信息获取类实现
 * @author DSOE1024
 */

#include "../include/hwinfo.hpp"

namespace hwinfo_ns
{
    Hwinfo::Hwinfo()
        : product_info(std::make_unique<Productinfo>(get_product_info())),
          os_info(std::make_unique<Osinfo>(get_os_info())),
          cpu_info(std::make_unique<std::vector<Cpuinfo>>(get_cpu_info())),
          gpu_info(std::make_unique<std::vector<Gpuinfo>>(get_gpu_info())),
          ram_info(std::make_unique<Raminfo>(get_ram_info())),
          disk_info(std::make_unique<std::vector<Diskinfo>>(get_disk_info())),
          net_info(std::make_unique<std::vector<Netinfo>>(get_net_info()))
    // TODO: audio_info, display_info

    {
        product_info_str = std::make_unique<std::string>(product_info->get_str());
        os_info_str = std::make_unique<std::string>(os_info->get_str());

        std::vector<Cpuinfo> cpu_info_vec = get_cpu_info();
        std::string cputmpstr;
        for (auto &cpu : cpu_info_vec)
        {
            cputmpstr += cpu.get_str();
        }
        cpu_info_str.reset(new std::string(cputmpstr));

        std::vector<Gpuinfo> gpu_info_vec = get_gpu_info();
        std::string gputmpstr;
        for (auto &gpu : gpu_info_vec)
        {
            gputmpstr += gpu.get_str();
        }
        gpu_info_str.reset(new std::string(gputmpstr));

        std::vector<Diskinfo> disk_info_vec = get_disk_info();
        std::string disktmpstr;
        for (auto &disk : disk_info_vec)
        {
            disktmpstr += disk.get_str();
        }
        disk_info_str.reset(new std::string(disktmpstr));

        ram_info_str.reset(new std::string(ram_info->get_str()));

        std::vector<Netinfo> net_info_vec = get_net_info();
        std::string nettmpstr;
        for (auto &net : net_info_vec)
        {
            nettmpstr += net.get_str();
        }
        net_info_str.reset(new std::string(nettmpstr));

        // source_report = std::make_unique<std::string>(get_source_report());
    }

    Hwinfo::~Hwinfo()
    {
    }

    std::string Hwinfo::get_pciids(std::string id)
    {
        std::string command = "grep -i '" + id + "' /usr/share/hwdata/pci.ids"; // 获取网卡厂商信息

        std::FILE *pipe = popen(command.c_str(), "r");
        if (!pipe)
            throw std::runtime_error("popen() failed!");
        try
        {
            char buffer[128];
            std::string result = "";
            while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
            {
                result += buffer;
            }
            return result;
        }
        catch (...)
        {
            pclose(pipe);
            throw;
        }
        pclose(pipe);
    }

    std::string Hwinfo::get_source_report()
    {
        std::string tmp_product_info_str = *product_info_str;
        std::string tmp_os_info_str = *os_info_str;
        std::string tmp_cpu_info_str = *cpu_info_str;
        std::string tmp_gpu_info_str = *gpu_info_str;
        std::string tmp_ram_info_str = *ram_info_str;
        std::string tmp_disk_info_str = *disk_info_str;
        std::string tmp_net_info_str = *net_info_str;
        // std::string tmp_audio_info_str;
        // std::string tmp_display_info_str;

        std::string str = tmp_product_info_str;
        str += tmp_os_info_str + "\n";
        str += tmp_cpu_info_str + "\n";
        str += tmp_gpu_info_str + "\n";
        str += tmp_ram_info_str + "\n";
        str += tmp_disk_info_str + "\n";
        str += tmp_net_info_str + "\n";

        return str;
    }

    std::string Productinfo::get_str()
    {
        std::string chassis_str;
        switch (chassis_type)
        {
        case ChassisType::DESKTOP:
            chassis_str = "台式机";
            break;
        case ChassisType::LAPTOP:
            chassis_str = "笔记本电脑";
            break;
        case ChassisType::OTHER:
            chassis_str = "";
            break;
        default:
            chassis_str = "";
            break;
        }
        std::string str = product_vendor + " " + product_name + " " + chassis_str;
        return str;
    }

#pragma region 产品信息
    Productinfo Hwinfo::get_product_info()
    {
        Productinfo productInfo;

        // 通过hostnamectl判断是否为笔记本
        if (std::system("hostnamectl | grep -q 'Chassis: laptop'") == 0)
        {
            productInfo.chassis_type = ChassisType::LAPTOP;
        }
        else if (std::system("hostnamectl | grep -q 'Chassis: desktop'") == 0)
        {
            productInfo.chassis_type = ChassisType::DESKTOP;
        }
        else
        {
            productInfo.chassis_type = ChassisType::OTHER;
        }

        std::ifstream infile1("/sys/devices/virtual/dmi/id/sys_vendor");
        if (infile1.is_open())
        {
            std::string line;
            getline(infile1, line);
            productInfo.product_vendor = line;
            infile1.close();
        }
        else
        {
            productInfo.product_vendor = "未知供应商";
        }

        std::ifstream infile2("/sys/devices/virtual/dmi/id/product_name");
        if (infile2.is_open())
        {
            std::string line;
            getline(infile2, line);
            productInfo.product_name = line;
            infile2.close();
        }
        else
        {
            productInfo.product_name = "未知型号";
        }

        return productInfo;
    }
#pragma endregion

    std::string Osinfo::get_str()
    {
        std::string str = os_name_version;
        return str;
    }

    Osinfo Hwinfo::get_os_info()
    {
        // 从 /etc/os-release 读取 PRETTY_NAME
        Osinfo osInfo;
        std::ifstream infile("/etc/os-release");
        if (infile.is_open())
        {
            std::string line;
            while (std::getline(infile, line))
            {
                if (line.find("PRETTY_NAME") != std::string::npos)
                {
                    osInfo.os_name_version = line.substr(line.find("=") + 1);
                    osInfo.os_name_version = osInfo.os_name_version.substr(1, osInfo.os_name_version.length() - 2);
                }
                else
                {
                    continue;
                }
            }
            infile.close();
        }
        return osInfo;
    }

    std::string Cpuinfo::get_str()
    {
        std::string str = cpu_model + " " + cpu_cores + " 核心 " + cpu_threads + " 线程";
        return str;
    }

    std::vector<Cpuinfo> Hwinfo::get_cpu_info()
    {
        std::vector<Cpuinfo> cpuInfos;

        std::ifstream file("/proc/cpuinfo");
        if (!file.is_open())
        {
            std::cerr << "Failed to open /proc/cpuinfo" << std::endl;
            return cpuInfos;
        }

        std::string line;
        Cpuinfo cpuInfo;

        // TODO: 民用一台电脑一般只有一个cpu，只考虑一个CPU的情况，未来修改

        while (std::getline(file, line))
        {
            // 型号
            if (line.find("model") != std::string::npos)
            {
                cpuInfo.cpu_model = line.substr(line.find(":") + 2);
            }
            // 线程数
            else if (line.find("siblings") != std::string::npos)
            {
                cpuInfo.cpu_threads = line.substr(line.find(":") + 2);
            }
            // 核心数
            else if (line.find("cpu cores") != std::string::npos)
            {
                cpuInfo.cpu_cores = line.substr(line.find(":") + 2);
            }
            else
            {
                continue;
            }
        }
        cpuInfos.push_back(cpuInfo);

        return cpuInfos;
    }

    std::string Gpuinfo::get_str()
    {
        return gpu_name;
    }

    std::vector<Gpuinfo> Hwinfo::get_gpu_info()
    {
        // TODO: 获取显卡信息
        std::vector<Gpuinfo> gpuInfos;

        for (const auto &entry : std::filesystem::directory_iterator("/sys/class/drm"))
        {
            if (entry.path().filename().string().find("card") != std::string::npos)
            {
                // 排除DP 和 HDMI
                if (entry.path().filename().string().find("DP") != std::string::npos || entry.path().filename().string().find("HDMI") != std::string::npos)
                {
                    continue;
                }
                else
                {
                    // /sys/class/drm/card0/device/vendor获取厂商信息
                    // /sys/class/drm/card0/device/device获取显卡型号
                    std::ifstream infile1((entry.path() / "device" / "vendor").string());
                    std::ifstream infile2((entry.path() / "device" / "device").string());

                    if (infile1.is_open() && infile2.is_open())
                    {
                        std::string line1, line2;
                        std::getline(infile1, line1);
                        std::getline(infile2, line2);

                        Gpuinfo gpuInfo;

                        std::string vtmp = line1;
                        // 去掉0x
                        if (vtmp[0] == '0' && vtmp[1] == 'x')
                        {
                            vtmp = vtmp.substr(2);
                        }
                        // 加上^
                        vtmp = "^" + vtmp;
                        std::string v_result = get_pciids(vtmp);

                        v_result = v_result.substr(6);
                        v_result = v_result.substr(0, v_result.find('\n'));


                        infile1.close();

                        std::string dtmp = line2;

                        
                        // 去掉0x
                        if (dtmp[0] == '0' && dtmp[1] == 'x')
                        {
                            dtmp = dtmp.substr(2);
                        }

                        std::string m_result = get_pciids(dtmp);

                        // 在m_result中找到带有GeForce或者 Radeon 或者 Iris的字符串
                        if (m_result.find("GeForce") != std::string::npos)
                        {
                            m_result = m_result.substr(m_result.find("GeForce") - 6, m_result.find('\n'));
                        }
                        // TODO: 没测试过AMD显卡
                        else if (m_result.find("Radeon") != std::string::npos)
                        {
                            m_result = m_result.substr(m_result.find("Radeon"));
                        }
                        // TODO: 没测试过Intel显卡
                        else if (m_result.find("Iris") != std::string::npos)
                        {
                            m_result = m_result.substr(m_result.find("Iris"));
                        }

                        // TODO: 更多显卡型号

                        // 只保留第一行
                        m_result = m_result.substr(0, m_result.find('\n'));

                        // 去掉前面的空格
                        m_result = m_result.substr(m_result.find_first_not_of(" \t\n\r\f\v"));


                        // 去掉ID，如果显示不全提issue
                        m_result = m_result.substr(6);

                        infile2.close();

                        gpuInfo.gpu_name = v_result + " " + m_result;

                        gpuInfos.push_back(gpuInfo);
                    }
                }
            }
        }

        return gpuInfos;
    }

    std::string Raminfo::get_str()
    {
        return ram_size + " GB";
    }

    Raminfo Hwinfo::get_ram_info()
    {
        std::vector<Raminfo> ramInfos;

        std::ifstream file("/proc/meminfo");
        if (!file.is_open())
        {
            std::cerr << "Failed to open /proc/meminfo" << std::endl;
            return Raminfo();
        }

        std::string line;
        Raminfo ramInfo;

        while (std::getline(file, line))
        {
            if (line.find("MemTotal") != std::string::npos)
            {
                // 获取内存大小，单位换算为GB
                ramInfo.ram_size = std::to_string(std::stoll(line.substr(line.find(":") + 2)) / 1000 / 1000);
            }
            else
            {
                continue;
            }
        }
        return ramInfo;
    }

    std::string Diskinfo::get_str()
    {
        return disk_name + " " + disk_size + " GB";
    }

    std::vector<Diskinfo> Hwinfo::get_disk_info()
    {
        std::vector<Diskinfo> diskInfos;

        // 遍历/sys/block目录下的所有文件，获取磁盘容量
        for (const auto &entry : std::filesystem::directory_iterator("/sys/block"))
        {
            // 忽略loop设备
            if (entry.path().filename().string().find("loop") != std::string::npos)
            {
                continue;
            }

            Diskinfo diskInfo;
            diskInfo.disk_name = entry.path().filename().string();

            std::ifstream sizeFile((entry.path() / "size").string());
            if (sizeFile.is_open())
            {
                uint64_t sectors;
                sizeFile >> sectors;
                diskInfo.disk_size = std::to_string(sectors * 512 / 1024 / 1024 / 1024); // 转换为GB
            }
            else
            {
                diskInfo.disk_size = "未知大小";
            }

            diskInfos.push_back(diskInfo);
        }

        return diskInfos;
    }

#pragma region 网卡信息

    std::string Netinfo::get_str()
    {
        return net_vendor + " " + net_model;
    }

    std::vector<Netinfo> Hwinfo::get_net_info()
    {
        // 遍历/sys/class/net/ 目录下的所有文件，获取网卡信息
        std::vector<Netinfo> netInfos;
        for (const auto &entry : std::filesystem::directory_iterator("/sys/class/net/"))
        {
            // 如果device目录下有vendor文件，读取vendor和device信息
            if (std::filesystem::exists(entry.path() / "device" / "vendor") || std::filesystem::exists(entry.path() / "device" / "device"))
            {
                Netinfo netInfo;

                // 获取网卡供应商
                std::ifstream vendorFile((entry.path() / "device" / "vendor").string());
                if (vendorFile.is_open())
                {
                    std::string tmp;
                    vendorFile >> tmp;
                    // 去掉0x
                    if (tmp[0] == '0' && tmp[1] == 'x')
                    {
                        tmp = tmp.substr(2);
                    }
                    // 加上^
                    tmp = "^" + tmp;
                    std::string result = get_pciids(tmp);
                    result = result.substr(6);
                    result = result.substr(0, result.find('\n'));

                    netInfo.net_vendor = result;
                    vendorFile.close();
                }
                else
                {
                    netInfo.net_vendor = "未知供应商";
                }

                // 获取网卡型号
                std::ifstream modelFile((entry.path() / "device" / "device").string());
                if (modelFile.is_open())
                {
                    std::string modtmp;
                    modelFile >> modtmp;
                    // 去掉0x
                    if (modtmp[0] == '0' && modtmp[1] == 'x')
                    {
                        modtmp = modtmp.substr(2);
                    }

                    std::string result = get_pciids(modtmp);

                    // 只保留第一行
                    result = result.substr(0, result.find('\n'));

                    // 去掉前面的空格
                    result = result.substr(result.find_first_not_of(" \t\n\r\f\v"));

                    // 去掉ID，如果显示不全提issue
                    result = result.substr(6);

                    netInfo.net_model = result;
                }
                else
                {
                    netInfo.net_model = "未知型号";
                }

                modelFile.close();

                netInfos.push_back(netInfo);
            }
        }
        return netInfos;
    }

#pragma endregion

} // namespace hwinfo
