#pragma once

#include "Scenes/Platformer/AttachedBehavior/Npcs/Hexus/HexusBehaviorBase.h"

class HexusOpponentData;

class TobenHexusBehavior : public HexusBehaviorBase
{
public:
	static TobenHexusBehavior* create(GameObject* owner);

	HexusOpponentData* createOpponentData() override;

	static const std::string MapKeyAttachedBehavior;

protected:
	TobenHexusBehavior(GameObject* owner);
	~TobenHexusBehavior();

	void onLoad() override;

private:
	typedef HexusBehaviorBase super;
};
