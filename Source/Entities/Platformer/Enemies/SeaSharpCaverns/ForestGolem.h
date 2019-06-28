#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class ForestGolem : public PlatformerEnemy
{
public:
	static ForestGolem* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyForestGolem;

private:
	typedef PlatformerEnemy super;
	ForestGolem(cocos2d::ValueMap& initProperties);
	~ForestGolem();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
