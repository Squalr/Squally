#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class HexusOpponentData;
class PlatformerEntity;

class SarudeTutorialBehavior : public HexusBehaviorBase
{
public:
	static SarudeTutorialBehavior* create(GameObject* owner);

	HexusOpponentData* createOpponentData() override;

protected:
	SarudeTutorialBehavior(GameObject* owner);
	~SarudeTutorialBehavior();

private:
	typedef HexusBehaviorBase super;

	static const std::string WinLossTrackIdentifier;
};
