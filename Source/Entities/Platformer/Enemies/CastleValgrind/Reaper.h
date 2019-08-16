#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Reaper : public PlatformerEnemy
{
public:
	static Reaper* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyReaper;

private:
	typedef PlatformerEnemy super;
	Reaper(cocos2d::ValueMap& properties);
	~Reaper();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
