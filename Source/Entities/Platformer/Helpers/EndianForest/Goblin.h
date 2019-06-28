#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class HexusOpponentData;

class Goblin : public PlatformerEntity
{
public:
	static Goblin* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGoblin;

private:
	typedef PlatformerEntity super;
	Goblin(cocos2d::ValueMap& initProperties);
	~Goblin();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
