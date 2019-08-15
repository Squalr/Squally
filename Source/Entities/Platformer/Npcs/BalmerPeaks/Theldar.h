#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Theldar : public PlatformerFriendly
{
public:
	static Theldar* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyTheldar;

private:
	typedef PlatformerFriendly super;
	Theldar(cocos2d::ValueMap& initProperties);
	~Theldar();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
