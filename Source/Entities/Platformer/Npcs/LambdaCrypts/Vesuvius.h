#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Vesuvius : public PlatformerFriendly
{
public:
	static Vesuvius* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyVesuvius;

private:
	typedef PlatformerFriendly super;
	Vesuvius(cocos2d::ValueMap& initProperties);
	~Vesuvius();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
