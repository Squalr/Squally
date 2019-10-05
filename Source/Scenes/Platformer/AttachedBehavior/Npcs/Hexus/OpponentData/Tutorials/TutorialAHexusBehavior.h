#pragma once

#include "Scenes/Platformer/AttachedBehavior/Npcs/Hexus/HexusBehaviorBase.h"

class HexusOpponentData;

class TutorialAHexusBehavior : public HexusBehaviorBase
{
public:
	static TutorialAHexusBehavior* create(GameObject* owner);

	HexusOpponentData* createOpponentData() override;

	static const std::string MapKeyAttachedBehavior;

protected:
	TutorialAHexusBehavior(GameObject* owner);
	~TutorialAHexusBehavior();

	void onLoad() override;

private:
	typedef HexusBehaviorBase super;
};
