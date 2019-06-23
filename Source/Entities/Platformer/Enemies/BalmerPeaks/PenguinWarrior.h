#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class PenguinWarrior : public PlatformerEnemy
{
public:
	static PenguinWarrior* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPenguinWarrior;

private:
	typedef PlatformerEnemy super;
	PenguinWarrior(cocos2d::ValueMap& initProperties);
	~PenguinWarrior();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
