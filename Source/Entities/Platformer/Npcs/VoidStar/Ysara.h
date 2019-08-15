#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Ysara : public PlatformerFriendly
{
public:
	static Ysara* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyYsara;

private:
	typedef PlatformerFriendly super;
	Ysara(cocos2d::ValueMap& initProperties);
	~Ysara();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
