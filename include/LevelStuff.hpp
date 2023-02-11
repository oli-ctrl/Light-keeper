#include "HMUI/ModalView.hpp"
#include "rapidjson-macros/shared/macros.hpp"




namespace LightKeeper::LevelStuff {

    DECLARE_JSON_CLASS(LevelData, 
        NAMED_VALUE_DEFAULT(int, lightsetting, 0, "Settings");
    );

    DECLARE_JSON_CLASS(Config,
        NAMED_MAP(LevelData, Levels, "Levels");
        NAMED_VALUE_DEFAULT(bool, chromaoveride, true, "ChromaOveride");
        NAMED_VALUE_DEFAULT(bool, enabled, true, "Enabled");
    );

    void SetLevel(HMUI::ModalView* modal, StringW levelID);
    void Init();
}

