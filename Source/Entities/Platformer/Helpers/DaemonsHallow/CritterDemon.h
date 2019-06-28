#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class HexusOpponentData;

class CritterDemon : public PlatformerEntity
{
public:
	static CritterDemon* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCritterDemon;

private:
	typedef PlatformerEntity super;
	CritterDemon(cocos2d::ValueMap& initProperties);
	~CritterDemon();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
