#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class HexusOpponentData;

class YetiBaby : public PlatformerEntity
{
public:
	static YetiBaby* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyYetiBaby;

private:
	typedef PlatformerEntity super;
	YetiBaby(cocos2d::ValueMap& initProperties);
	~YetiBaby();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
