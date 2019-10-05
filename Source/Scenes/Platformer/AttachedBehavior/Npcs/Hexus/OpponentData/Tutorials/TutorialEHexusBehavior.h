#pragma once

#include "Scenes/Platformer/AttachedBehavior/Npcs/Hexus/HexusBehaviorBase.h"

class HexusOpponentData;

class TutorialEHexusBehavior : public HexusBehaviorBase
{
public:
	static TutorialEHexusBehavior* create(GameObject* owner);

	HexusOpponentData* createOpponentData() override;

	static const std::string MapKeyAttachedBehavior;

protected:
	TutorialEHexusBehavior(GameObject* owner);
	~TutorialEHexusBehavior();

	void onLoad() override;

private:
	typedef HexusBehaviorBase super;
};
