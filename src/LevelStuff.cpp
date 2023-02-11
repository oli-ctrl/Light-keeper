#include "LevelStuff.hpp"
#include "main.hpp"
#include <filesystem>
#include "questui/shared/BeatSaberUI.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/PlayerSpecificSettings.hpp"
#include "GlobalNamespace/EnvironmentEffectsFilterPreset.hpp"
#include "GlobalNamespace/PlayerSettingsPanelController.hpp"

LightKeeper::LevelStuff::Config config;
const std::string configPath = "/sdcard/ModData/com.beatgames.beatsaber/Mods/LightKeeper";
HMUI::SimpleTextDropdown* dropdown;
std::string levelIDstring;


void SetPlayerData(int value){
    auto playerdatamodal = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::PlayerDataModel*>().First();
    auto playerdata = playerdatamodal->playerData;    
    if (value == 2){value = 10;}
    playerdata->playerSpecificSettings->environmentEffectsFilterExpertPlusPreset = value;
    playerdata->playerSpecificSettings->environmentEffectsFilterDefaultPreset = value;
    getLogger().info("changing playerdata %i", value);

    auto playerSettingsPanelController = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::PlayerSettingsPanelController*>().First();
    playerdatamodal->Save();
    playerSettingsPanelController->Refresh();
}

void CreateUI(HMUI::ModalView* modal){
    std::vector <StringW> options = {"All Effects", "No Flickering", "No Effects"};
    auto transform = QuestUI::BeatSaberUI::CreateScrollableModalContainer(modal)->get_transform();
    dropdown = QuestUI::BeatSaberUI::CreateDropdown(transform, "", options[config.Levels[levelIDstring].lightsetting], options, [options](StringW value){
        config.Levels[levelIDstring].lightsetting = std::find(options.begin(), options.end(), static_cast<std::string>(value)) - options.begin();
        WriteToFile(configPath + "/config.json", config);
        SetPlayerData(config.Levels[levelIDstring].lightsetting);
    }
    );
}

void LightKeeper::LevelStuff::SetLevel(HMUI::ModalView* modal, StringW levelID)
{
    levelIDstring = static_cast<std::string>(levelID); 
    if (!dropdown)
        CreateUI(modal);
        int value = config.Levels[levelIDstring].lightsetting;
    dropdown->SelectCellWithIdx(value);
    getLogger().info("logging value: %i", value);
    SetPlayerData(value);
}

void LightKeeper::LevelStuff::Init()
{
    if (!std::filesystem::exists(configPath))
    {
        std::filesystem::create_directories(configPath);
        WriteToFile(configPath + "/config.json", config);
    }
}