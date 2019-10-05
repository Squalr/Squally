#pragma once

#include "Scenes/Platformer/AttachedBehavior/Npcs/Hexus/HexusBehaviorBase.h"

class HexusOpponentData;

class TutorialDHexusBehavior : public HexusBehaviorBase
{
public:
	static TutorialDHexusBehavior* create(GameObject* owner);

	HexusOpponentData* createOpponentData() override;

	static const std::string MapKeyAttachedBehavior;

protected:
	TutorialDHexusBehavior(GameObject* owner);
	~TutorialDHexusBehavior();

	void onLoad() override;

private:
	typedef HexusBehaviorBase super;
};
