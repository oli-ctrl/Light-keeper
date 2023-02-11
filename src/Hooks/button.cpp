#include "main.hpp"
#include "Hooks/button.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "UnityEngine/Vector3.hpp"
#include "questui/shared/beatsaberui.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "sprites.hpp"
#include "LevelStuff.hpp"

HMUI::ModalView* modal;


MAKE_HOOK_MATCH(StandardLevelDetailView_Awake, &GlobalNamespace::StandardLevelDetailView::Awake, void, GlobalNamespace::StandardLevelDetailView* self)
{
    StandardLevelDetailView_Awake(self);
    modal = QuestUI::BeatSaberUI::CreateModal(self->get_transform(), {50, 30}, nullptr);

    QuestUI::ClickableImage* image = QuestUI::BeatSaberUI::CreateClickableImage(self->get_transform(), QuestUI::BeatSaberUI::Base64ToSprite(light), {0, 0}, {5, 5});
    image->get_onPointerClickEvent() += [self](auto _)
    {
        modal->Show(false, false, nullptr);
        LightKeeper::LevelStuff::SetLevel(modal, self->level->i_IPreviewBeatmapLevel()->get_levelID());
    };
    auto imagetransform = (UnityEngine::RectTransform*)image->get_transform();
    imagetransform->set_anchoredPosition({20, 22});
}

MAKE_HOOK_MATCH(StandardLevelDetailView_RefreshContent, &GlobalNamespace::StandardLevelDetailView::RefreshContent, void, GlobalNamespace::StandardLevelDetailView* self){
    StandardLevelDetailView_RefreshContent(self);
    auto levelid = self->level->i_IPreviewBeatmapLevel()->get_levelID();
    LightKeeper::LevelStuff::SetLevel(modal, levelid);
    
}

void LightKeeper::Hooks::InstallButton()
{
    INSTALL_HOOK(getLogger(), StandardLevelDetailView_Awake);
}