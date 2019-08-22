#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class SkeletalPriestess : public PlatformerEnemy
{
public:
	static SkeletalPriestess* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeySkeletalPriestess;

private:
	typedef PlatformerEnemy super;
	SkeletalPriestess(cocos2d::ValueMap& properties);
	~SkeletalPriestess();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
