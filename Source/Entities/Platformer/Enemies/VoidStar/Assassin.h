#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Assassin : public PlatformerEnemy
{
public:
	static Assassin* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyAssassin;

private:
	typedef PlatformerEnemy super;
	Assassin(cocos2d::ValueMap& initProperties);
	~Assassin();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
