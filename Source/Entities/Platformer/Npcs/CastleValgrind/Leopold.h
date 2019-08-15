#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Leopold : public PlatformerFriendly
{
public:
	static Leopold* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyLeopold;

private:
	typedef PlatformerFriendly super;
	Leopold(cocos2d::ValueMap& initProperties);
	~Leopold();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
