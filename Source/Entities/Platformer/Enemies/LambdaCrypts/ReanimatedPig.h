#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class ReanimatedPig : public PlatformerEnemy
{
public:
	static ReanimatedPig* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyReanimatedPig;

private:
	typedef PlatformerEnemy super;
	ReanimatedPig(cocos2d::ValueMap& properties);
	~ReanimatedPig();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
