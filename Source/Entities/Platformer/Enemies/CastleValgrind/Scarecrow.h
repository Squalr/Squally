#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class Scarecrow : public PlatformerEnemy
{
public:
	static Scarecrow* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyScarecrow;

private:
	typedef PlatformerEnemy super;
	Scarecrow(cocos2d::ValueMap& properties);
	~Scarecrow();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
