#pragma once

#include "Scenes/Platformer/AttachedBehavior/Npcs/Hexus/HexusBehaviorBase.h"

class HexusOpponentData;

class TutorialFHexusBehavior : public HexusBehaviorBase
{
public:
	static TutorialFHexusBehavior* create(GameObject* owner);

	HexusOpponentData* createOpponentData() override;

	static const std::string MapKeyAttachedBehavior;

protected:
	TutorialFHexusBehavior(GameObject* owner);
	~TutorialFHexusBehavior();

	void onLoad() override;

private:
	typedef HexusBehaviorBase super;
};
