#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class EvilEye : public PlatformerEnemy
{
public:
	static EvilEye* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyEvilEye;

private:
	typedef PlatformerEnemy super;
	EvilEye(cocos2d::ValueMap& properties);
	~EvilEye();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
