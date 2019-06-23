#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Centaur : public PlatformerEnemy
{
public:
	static Centaur* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCentaur;

private:
	typedef PlatformerEnemy super;
	Centaur(cocos2d::ValueMap& initProperties);
	~Centaur();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
