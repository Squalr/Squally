#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class LightningGolem : public PlatformerEnemy
{
public:
	static LightningGolem* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyLightningGolem;

private:
	typedef PlatformerEnemy super;
	LightningGolem(cocos2d::ValueMap& initProperties);
	~LightningGolem();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
