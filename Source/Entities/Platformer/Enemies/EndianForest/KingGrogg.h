#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class KingGrogg : public PlatformerEnemy
{
public:
	static KingGrogg* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyKingGrogg;

private:
	typedef PlatformerEnemy super;
	KingGrogg(cocos2d::ValueMap& properties);
	~KingGrogg();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
