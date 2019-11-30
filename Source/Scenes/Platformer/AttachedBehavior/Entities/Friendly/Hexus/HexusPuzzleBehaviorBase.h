#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class Squally;

class HexusPuzzleBehaviorBase : public HexusBehaviorBase
{
public:

protected:
	HexusPuzzleBehaviorBase(GameObject* owner, std::string voiceResource, LocalizedString* dialogueChoiceOverride = nullptr);
	~HexusPuzzleBehaviorBase();

	void onEnter() override;

private:
	typedef HexusBehaviorBase super;

	Squally* squally;
};
