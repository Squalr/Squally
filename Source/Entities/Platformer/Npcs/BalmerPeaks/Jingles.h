#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Jingles : public PlatformerFriendly
{
public:
	static Jingles* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyJingles;

private:
	typedef PlatformerFriendly super;
	Jingles(cocos2d::ValueMap& initProperties);
	~Jingles();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
