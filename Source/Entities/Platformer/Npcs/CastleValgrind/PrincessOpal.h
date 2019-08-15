#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class PrincessOpal : public PlatformerFriendly
{
public:
	static PrincessOpal* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPrincessOpal;

private:
	typedef PlatformerFriendly super;
	PrincessOpal(cocos2d::ValueMap& initProperties);
	~PrincessOpal();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
