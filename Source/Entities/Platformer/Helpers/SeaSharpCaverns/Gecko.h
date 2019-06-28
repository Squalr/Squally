#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class HexusOpponentData;

class Gecko : public PlatformerEntity
{
public:
	static Gecko* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGecko;

private:
	typedef PlatformerEntity super;
	Gecko(cocos2d::ValueMap& initProperties);
	~Gecko();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
