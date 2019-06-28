#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class HexusOpponentData;

class Ghost : public PlatformerEntity
{
public:
	static Ghost* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGhost;

private:
	typedef PlatformerEntity super;
	Ghost(cocos2d::ValueMap& initProperties);
	~Ghost();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
