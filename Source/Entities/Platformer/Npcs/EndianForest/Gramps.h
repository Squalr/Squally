#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Gramps : public PlatformerFriendly
{
public:
	static Gramps* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGramps;

private:
	typedef PlatformerFriendly super;
	Gramps(cocos2d::ValueMap& initProperties);
	~Gramps();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
