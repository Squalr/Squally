#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class Squally;

class HexusPuzzleBehaviorBase : public HexusBehaviorBase
{
public:

protected:
	HexusPuzzleBehaviorBase(GameObject* owner, std::string voiceResource, LocalizedString* dialogueChoiceOverride = nullptr);
	virtual ~HexusPuzzleBehaviorBase();

	void onEnter() override;
	LocalizedString* getCustomWinDialogue() override;
	LocalizedString* getCustomDrawDialogue() override;
	LocalizedString* getCustomLossDialogue() override;

private:
	typedef HexusBehaviorBase super;

	Squally* squally;
};
