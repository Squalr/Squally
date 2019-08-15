#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Ragnis : public PlatformerFriendly
{
public:
	static Ragnis* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyRagnis;

private:
	typedef PlatformerFriendly super;
	Ragnis(cocos2d::ValueMap& initProperties);
	~Ragnis();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
