#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class SkeletalArcher : public PlatformerEnemy
{
public:
	static SkeletalArcher* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeySkeletalArcher;

private:
	typedef PlatformerEnemy super;
	SkeletalArcher(cocos2d::ValueMap& properties);
	~SkeletalArcher();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
