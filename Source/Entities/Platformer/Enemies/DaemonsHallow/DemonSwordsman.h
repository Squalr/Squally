#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DemonSwordsman : public PlatformerEnemy
{
public:
	static DemonSwordsman* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonSwordsman;

private:
	typedef PlatformerEnemy super;
	DemonSwordsman(cocos2d::ValueMap& initProperties);
	~DemonSwordsman();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
