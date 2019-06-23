#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class HexusOpponentData;

class Grim : public PlatformerEntity
{
public:
	static Grim* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGrim;

private:
	typedef PlatformerEntity super;
	Grim(cocos2d::ValueMap& initProperties);
	~Grim();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
