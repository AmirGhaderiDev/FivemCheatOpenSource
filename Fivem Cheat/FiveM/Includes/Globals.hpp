#pragma once

#include "SDK.hpp"
#include "../Managers/FMemoryManager.hpp"
#include "../Renderer/Renderer.h"

#include <fstream>
#include <string>
#include <filesystem>



namespace Globals
{
    const char* GameProcessName = "";
    uintptr_t BonePosPtr = sigscan("FiveM_GTAProcess.exe", "48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 48 83 EC 60 48 8B 01 41 8B E8 48 8B F2 48 8B F9 33 DB");
    uintptr_t w2s = sigscan("FiveM_GTAProcess.exe", "48 89 5C 24 ?? 55 56 57 48 83 EC 70 65 4C 8B 0C 25");
    uintptr_t PlayerListPattern = sigscan("FiveM_GTAProcess.exe", "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 8B CF");
    uintptr_t ReplayInterfacePattern = sigscan("FiveM_GTAProcess.exe", "48 8D 0D ?? ?? ?? ?? 89 44 24 30 E8 ?? ?? ?? ?? 48 83 C4 28 C3 48 8B 05");
    uintptr_t pGameCamManager_pattern = sigscan("FiveM_GTAProcess.exe", "48 8B 05 ? ? ? ? 4A 8B 1C F0");
    uintptr_t oGetTPSCamera_pattern = sigscan("FiveM_GTAProcess.exe", "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D3 48 8B F8 E8 ? ? ? ? 8B 8B ? ? ? ? ? ? ? ?");
    uintptr_t GetNamePattern = sigscan("FiveM_GTAProcess.exe", "E9 ? ? ? ? 48 8D 64 24 F8 48 8D 2D 9B 7B E4 03");
    Renderer* renderer = new Renderer;

    int maxpeds = 0;
    uintptr_t BaseAddress, WorldPointer, LocalPlayer;
    

    namespace Colors
    {
        ImColor ESPCorner = ImColor(255, 255, 255, 255);
        ImColor ESPBox = ImColor(255, 255, 255, 255);
        ImColor ESPName = ImColor(247, 94, 112, 155);
        ImColor ESPSkeleton = ImColor(255, 189, 74, 255);
        ImColor ESPDistance = ImColor(74, 207, 255, 255);
        ImColor ESPHealthbar = ImColor(74, 207, 255, 255);
        ImColor NPCESPCorner = ImColor(255, 255, 255, 255);
        ImColor NPCESPBox = ImColor(255, 255, 255, 255);
        ImColor NPCESPName = ImColor(247, 94, 112, 155);
        ImColor NPCESPSkeleton = ImColor(255, 189, 74, 255);
        ImColor NPCESPDistance = ImColor(74, 207, 255, 255);
        ImColor NPCESPHealthbar = ImColor(74, 207, 255, 255);
        ImColor CrosshairColor = ImColor(247, 94, 112, 155);
        ImColor AimbotFovColor = ImColor(255,255,255, 255);
        ImColor PrimaryVehicleColor = ImColor(255, 255, 255, 255);
        ImColor ObjectDistance = ImColor(255, 255, 255, 255);

        ImColor LocalPlayerRadarColor = ImColor(0, 0, 255, 255);
        ImColor NPCRadarColor = ImColor(0, 0, 255, 255);
        ImColor PlayerRadarColor = ImColor(255, 0, 255, 255);
    }

    namespace Settings
    {
        bool ScripthookVBypass = false;
        bool Crosshair = false;
        int CrosshairSize = 10;
        bool fovenabled = false;
        float fov = 90.f;
    }

    namespace AimbotOptions
    {
        std::vector<uintptr_t> FriendsList[30] = {};
        bool npclockon = false;
        bool ignoredead = true;
        bool FovCircle = false;
        bool FilledFovCircle = false;
        float radius = 100;
        int smoothing = 1;
        int aimbotbone = 0;
        static const char* AimbotBones[]{ "head", "body", "left leg", "right leg", "right arm", "left arm" };
    }

    namespace ESPOptions
    {
        bool Enabled = false;
        int espmaxdist = 1000;
        const char* boxoptions[] = { "2D box", "corner" };
        bool Skeleton, Box, Name, Distance, Snaplines, Health, Armor, HealthBarBasedOnHealth, LocalPlayer, DarkBackground, Weapon, Corner;
    }

    namespace NPCESPOptions
    {
        bool Enabled = false;
        int espmaxdist = 1000;
        bool Skeleton, Box, Name, Distance, Snaplines, Health, Armor, HealthBarBasedOnHealth, LocalPlayer, DarkBackground, Weapon, Corner;
    }

    namespace ObjectESPOptions {
        bool Distance = false;
        int espmaxdist = 1000;
    }

    namespace VehicleInfo
    {
        CColor PrimaryColor;
    }

    namespace FOVOptions {
        bool aimfovenabled = false;
        float aimfov = 35;
    }

    namespace Radar
    {
        float zoomfactor = 1;
        float size = 5;
        float dotsizes = 3;
        bool npc, player = false;
    }

    namespace MenuOptions
    {
        bool Invisible, NoRecoil, NoSpread,NPCESP, ESP, Aimbot, Triggerbot, reloadspeedenabled, runspeedenabled, sneakwalkenabled, radar, primcarcolorenabled, secondarycarcolorenabled, objectesp = false;
        float spread = 1.0;
        float recoil = 0.3;
        float sneakwalkspeed, reloadspeed, runspeed = 1;
    }
}

class Config_Manager {
public:
    struct ConfigToggle
    {
        std::string identifier;
        float floatval = -1;
        bool value;
    };
    struct Slider
    {
        std::string identifier;
        bool value;
    };
    struct ConfigColor {
        std::string identifier;
        ImColor color;
    };
    class ESPConfig {
    public:
        ConfigToggle toggles[18];
    };
    class AimbotConfig {
    public:
        ConfigToggle toggles[5];
    };
    Config_Manager();
    ESPConfig GetConfigFormat();
    AimbotConfig GetAimbotCfg();
    void Load(std::string name);
    std::vector<std::string> GetConfigs();
    void Save(std::string name);
    void SetOptions(ConfigToggle cfg);
private:

    int DoesCfgDirExist(const char* path);
    inline bool DoesFileExist(const std::string& name);
    bool IsNumber(std::string s);
    ConfigToggle SplitLine(std::string s);
};

Config_Manager::Config_Manager()
{
    if (!this->DoesCfgDirExist("C:\\InfantryCheats"))
    {
        _wmkdir(L"C:\\InfantryCheats\\");
    }
    else
    {
        if (!this->DoesCfgDirExist("C:\\InfantryCheats\\cfg"))
        {
            _wmkdir(L"C:\\InfantryCheats\\cfg\\");
        }

        std::ifstream input("C:\\InfantryCheats\\cfg\\default.ini");
        for (std::string line; std::getline(input, line);)
        {
            ConfigToggle cfg = SplitLine(line);

            this->SetOptions(cfg);
        }
    }
}

inline bool Config_Manager::IsNumber(std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

inline void Config_Manager::Load(std::string name)
{
    if (!this->DoesCfgDirExist("C:\\InfantryCheats"))
    {
        _wmkdir(L"C:\\InfantryCheats\\");
    }
    else
    {
        if (!this->DoesCfgDirExist("C:\\InfantryCheats\\cfg"))
        {
            _wmkdir(L"C:\\InfantryCheats\\cfg\\");
        }

        std::ifstream input("C:\\InfantryCheats\\cfg\\" + name );
        for (std::string line; std::getline(input, line);)
        {
            ConfigToggle cfg = SplitLine(line);

            this->SetOptions(cfg);
        }
        input.close();
    }
}

inline std::vector<std::string> Config_Manager::GetConfigs()
{
    std::string folder = "C:\\InfantryCheats\\cfg";
    std::vector<std::string> names;
    std::string search_path = folder + "/*.*";
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                names.push_back(fd.cFileName);
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
}


inline void Config_Manager::Save(std::string name)
{
    
    if (!this->DoesCfgDirExist("C:\\InfantryCheats"))
    {
        _wmkdir(L"C:\\InfantryCheats\\");
    }
    else
    {
        if (!this->DoesCfgDirExist("C:\\InfantryCheats\\cfg"))
        {
            _wmkdir(L"C:\\InfantryCheats\\cfg\\");
        }

        std::ofstream output;   
        output.open("C:\\InfantryCheats\\cfg\\" + name);
        Config_Manager::ESPConfig espcfg = this->GetConfigFormat();
        Config_Manager::AimbotConfig aimbotcfg = this->GetAimbotCfg();
        for (int i = 0; i < IM_ARRAYSIZE(espcfg.toggles); i++) {
            if (output.is_open()) {
                ConfigToggle esp = espcfg.toggles[i];
                if (esp.floatval == -1) {
                std::string espval = esp.value ? "true" : "false";
                output << esp.identifier + "->" + espval << std::endl;
                }
                else {
                    output << esp.identifier + "->" + std::to_string(esp.floatval) << std::endl;
                }
            }
        }
        for (int i = 0; i < IM_ARRAYSIZE(aimbotcfg.toggles); i++) {
            if (output.is_open()) {
                ConfigToggle aimbot = aimbotcfg.toggles[i];
                std::string aimbotval = aimbot.value ? "true" : "false";
                output << aimbot.identifier + "->" + aimbotval << std::endl;
            }
        }
        output.close();
    }
}

inline void Config_Manager::SetOptions(ConfigToggle cfg)
{
   /* std::string valstr = cfg.value ? "true" : "false";
    MessageBoxA(0, (cfg.identifier + ":" + valstr).c_str(), 0, 0);*/
    if (cfg.identifier == "esp") {
        Globals::MenuOptions::ESP = cfg.value;
    }
    if (cfg.identifier == "esp_box") {
        Globals::ESPOptions::Box = cfg.value;
    }
    if (cfg.identifier == "esp_skel") {
        Globals::ESPOptions::Skeleton = cfg.value;
    }
    if (cfg.identifier == "esp_health") {
        Globals::ESPOptions::Health = cfg.value;
    }
    if (cfg.identifier == "esp_health_colbase") {
        Globals::ESPOptions::HealthBarBasedOnHealth = cfg.value;
    }
    if (cfg.identifier == "esp_armor") {
        Globals::ESPOptions::Armor = cfg.value;
    }
    if (cfg.identifier == "esp_weaponname") {
        Globals::ESPOptions::Weapon = cfg.value;
    }
    if (cfg.identifier == "esp_distance") {
        Globals::ESPOptions::Distance = cfg.value;
    } 
    if (cfg.identifier == "esp_maxdist") {
        Globals::ESPOptions::espmaxdist = cfg.floatval;
    }
    if (cfg.identifier == "npc_esp") {
        Globals::MenuOptions::NPCESP = cfg.value;
    }
    if (cfg.identifier == "npc_box") {
        Globals::NPCESPOptions::Box = cfg.value;
    }
    if (cfg.identifier == "npc_skel") {
        Globals::NPCESPOptions::Skeleton = cfg.value;
    }
    if (cfg.identifier == "npc_health") {
        Globals::NPCESPOptions::Health = cfg.value;
    }
    if (cfg.identifier == "npc_health_colbase") {
        Globals::NPCESPOptions::HealthBarBasedOnHealth = cfg.value;
    }
    if (cfg.identifier == "npc_armor") {
        Globals::NPCESPOptions::Armor = cfg.value;
    }
    if (cfg.identifier == "npc_weaponname") {
        Globals::NPCESPOptions::Weapon = cfg.value;
    }
    if (cfg.identifier == "npc_distance") {
        Globals::NPCESPOptions::Distance = cfg.value;
    }
    if (cfg.identifier == "npc_maxdist") {
        Globals::NPCESPOptions::espmaxdist = cfg.floatval;
    }
    if (cfg.identifier == "aimbot") {
        Globals::MenuOptions::Aimbot = cfg.value;
    }
    if (cfg.identifier == "aimbot_fov_circle") {
        Globals::AimbotOptions::FovCircle = cfg.value;
    }
    if (cfg.identifier == "aimbot_ignore_dead") {
        Globals::AimbotOptions::ignoredead = cfg.value;
    }
    if (cfg.identifier == "aimbot_lockon_npcs") {
        Globals::AimbotOptions::npclockon = cfg.value;
    }
    if (cfg.identifier == "aimbot_filled_fov") {
        Globals::AimbotOptions::FilledFovCircle = cfg.value;
    }
}

inline Config_Manager::AimbotConfig Config_Manager::GetAimbotCfg()
{
    AimbotConfig cfg;

    cfg.toggles[0].identifier = "aimbot";
    cfg.toggles[0].value = Globals::MenuOptions::Aimbot;

    cfg.toggles[1].identifier = "aimbot_fov_circle";
    cfg.toggles[1].value = Globals::AimbotOptions::FovCircle;

    cfg.toggles[2].identifier = "aimbot_ignore_dead";
    cfg.toggles[2].value = Globals::AimbotOptions::ignoredead;

    cfg.toggles[3].identifier = "aimbot_lockon_npcs";
    cfg.toggles[3].value = Globals::AimbotOptions::npclockon;

    cfg.toggles[4].identifier = "aimbot_filled_fov";
    cfg.toggles[4].value = Globals::AimbotOptions::FilledFovCircle;
    return cfg;
}

inline Config_Manager::ESPConfig Config_Manager::GetConfigFormat()
{
    ESPConfig cfg;

    cfg.toggles[0].identifier = "esp";
    cfg.toggles[0].value = Globals::MenuOptions::ESP;

    cfg.toggles[1].identifier = "esp_skel";
    cfg.toggles[1].value = Globals::ESPOptions::Skeleton;

    cfg.toggles[2].identifier = "esp_box";
    cfg.toggles[2].value = Globals::ESPOptions::Box;

    cfg.toggles[3].identifier = "esp_health";
    cfg.toggles[3].value = Globals::ESPOptions::Health;

    cfg.toggles[4].identifier = "esp_health_colbase";
    cfg.toggles[4].value = Globals::ESPOptions::HealthBarBasedOnHealth;

    cfg.toggles[5].identifier = "esp_armor";
    cfg.toggles[5].value = Globals::ESPOptions::Armor;

    cfg.toggles[6].identifier = "esp_weaponname";
    cfg.toggles[6].value = Globals::ESPOptions::Weapon;

    cfg.toggles[7].identifier = "esp_distance";
    cfg.toggles[7].value = Globals::ESPOptions::Distance;


    cfg.toggles[8].identifier = "npc_esp";
    cfg.toggles[8].value = Globals::MenuOptions::NPCESP;

    cfg.toggles[9].identifier = "npc_skel";
    cfg.toggles[9].value = Globals::NPCESPOptions::Skeleton;

    cfg.toggles[10].identifier = "npc_box";
    cfg.toggles[10].value = Globals::NPCESPOptions::Box;

    cfg.toggles[11].identifier = "npc_health";
    cfg.toggles[11].value = Globals::NPCESPOptions::Health;

    cfg.toggles[12].identifier = "npc_health_colbase";
    cfg.toggles[12].value = Globals::NPCESPOptions::HealthBarBasedOnHealth;

    cfg.toggles[13].identifier = "npc_armor";
    cfg.toggles[13].value = Globals::NPCESPOptions::Armor;

    cfg.toggles[14].identifier = "npc_weaponname";
    cfg.toggles[14].value = Globals::NPCESPOptions::Weapon;

    cfg.toggles[15].identifier = "npc_distance";
    cfg.toggles[15].value = Globals::NPCESPOptions::Distance;

    cfg.toggles[16].identifier = "esp_maxdist";
    cfg.toggles[16].floatval = Globals::ESPOptions::espmaxdist;

    cfg.toggles[16].identifier = "npc_maxdist";
    cfg.toggles[16].floatval = Globals::NPCESPOptions::espmaxdist;
    
    return cfg;
}

int Config_Manager::DoesCfgDirExist(const char* path)
{
    struct stat info;
    if (stat(path, &info) != 0)
        return 0;
    else if (info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

inline bool Config_Manager::DoesFileExist(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}


Config_Manager::ConfigToggle Config_Manager::SplitLine(std::string s)
{
    ConfigToggle cfg;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '-' && s[i + 1] == '>') {
            cfg.identifier = s.substr(0, i);
            std::string val = s.substr(i + 2, s.length());
            if (this->IsNumber(val)) {
                cfg.floatval = std::stof(val);
            }
            if (val == "true") {
                cfg.value = true;
            }
            else if (val == "false") {
                cfg.value = false;
            }
        }
    }
    return cfg;
}