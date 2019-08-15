#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Poseidon : public PlatformerFriendly
{
public:
	static Poseidon* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPoseidon;

private:
	typedef PlatformerFriendly super;
	Poseidon(cocos2d::ValueMap& initProperties);
	~Poseidon();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
