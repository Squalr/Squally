#pragma once

#include "Scenes/Platformer/AttachedBehavior/Npcs/Hexus/HexusBehaviorBase.h"

class HexusOpponentData;

class TutorialCHexusBehavior : public HexusBehaviorBase
{
public:
	static TutorialCHexusBehavior* create(GameObject* owner);

	HexusOpponentData* createOpponentData() override;

	static const std::string MapKeyAttachedBehavior;

protected:
	TutorialCHexusBehavior(GameObject* owner);
	~TutorialCHexusBehavior();

	void onLoad() override;

private:
	typedef HexusBehaviorBase super;
};
