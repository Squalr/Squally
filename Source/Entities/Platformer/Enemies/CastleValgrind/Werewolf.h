#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Werewolf : public PlatformerEnemy
{
public:
	static Werewolf* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyWerewolf;

private:
	typedef PlatformerEnemy super;
	Werewolf(cocos2d::ValueMap& initProperties);
	~Werewolf();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
