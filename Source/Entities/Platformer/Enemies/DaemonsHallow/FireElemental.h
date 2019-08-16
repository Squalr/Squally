#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class FireElemental : public PlatformerEnemy
{
public:
	static FireElemental* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyFireElemental;

private:
	typedef PlatformerEnemy super;
	FireElemental(cocos2d::ValueMap& properties);
	~FireElemental();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
