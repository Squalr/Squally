#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Irmik : public PlatformerFriendly
{
public:
	static Irmik* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyIrmik;

private:
	typedef PlatformerFriendly super;
	Irmik(cocos2d::ValueMap& properties);
	~Irmik();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
