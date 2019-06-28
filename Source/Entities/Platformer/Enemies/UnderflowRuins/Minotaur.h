#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Minotaur : public PlatformerEnemy
{
public:
	static Minotaur* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyMinotaur;

private:
	typedef PlatformerEnemy super;
	Minotaur(cocos2d::ValueMap& initProperties);
	~Minotaur();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
