#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class HexusOpponentData;

class Snowman : public PlatformerEntity
{
public:
	static Snowman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeySnowman;

private:
	typedef PlatformerEntity super;
	Snowman(cocos2d::ValueMap& properties);
	~Snowman();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
