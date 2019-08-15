#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class QueenElise : public PlatformerFriendly
{
public:
	static QueenElise* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyQueenElise;

private:
	typedef PlatformerFriendly super;
	QueenElise(cocos2d::ValueMap& initProperties);
	~QueenElise();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
