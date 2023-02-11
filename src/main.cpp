#include "main.hpp"
#include "Hooks/button.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/GameplaySetupViewController.hpp"
#include "GlobalNamespace/SinglePlayerLevelSelectionFlowCoordinator.hpp"
#include "GlobalNamespace/LevelSelectionNavigationController.hpp"
#include "LevelStuff.hpp"

using namespace GlobalNamespace;

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be removed if those are in use
Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

ModInfo& getModInfo() {
    return modInfo;
}


// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load();
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    getLogger().info("Installing hooks...");
    LightKeeper::Hooks::InstallButton();
    LightKeeper::LevelStuff::Init();
    getLogger().info("Installed all hooks!");
}