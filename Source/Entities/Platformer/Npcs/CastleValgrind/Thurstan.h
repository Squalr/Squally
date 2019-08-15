#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Thurstan : public PlatformerFriendly
{
public:
	static Thurstan* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyThurstan;

private:
	typedef PlatformerFriendly super;
	Thurstan(cocos2d::ValueMap& initProperties);
	~Thurstan();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
