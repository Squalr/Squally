#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class BoneKnight : public PlatformerEnemy
{
public:
	static BoneKnight* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyBoneKnight;

private:
	typedef PlatformerEnemy super;
	BoneKnight(cocos2d::ValueMap& properties);
	~BoneKnight();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
