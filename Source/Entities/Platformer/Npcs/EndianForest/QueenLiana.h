#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class QueenLiana : public PlatformerFriendly
{
public:
	static QueenLiana* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyQueenLiana;

private:
	typedef PlatformerFriendly super;
	QueenLiana(cocos2d::ValueMap& initProperties);
	~QueenLiana();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
