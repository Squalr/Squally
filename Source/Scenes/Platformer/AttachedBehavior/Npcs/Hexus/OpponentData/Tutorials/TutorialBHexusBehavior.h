#pragma once

#include "Scenes/Platformer/AttachedBehavior/Npcs/Hexus/HexusBehaviorBase.h"

class HexusOpponentData;

class TutorialBHexusBehavior : public HexusBehaviorBase
{
public:
	static TutorialBHexusBehavior* create(GameObject* owner);

	HexusOpponentData* createOpponentData() override;

	static const std::string MapKeyAttachedBehavior;

protected:
	TutorialBHexusBehavior(GameObject* owner);
	~TutorialBHexusBehavior();

	void onLoad() override;

private:
	typedef HexusBehaviorBase super;
};
