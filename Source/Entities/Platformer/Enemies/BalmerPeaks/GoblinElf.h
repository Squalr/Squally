#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class GoblinElf : public PlatformerEnemy
{
public:
	static GoblinElf* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGoblinElf;

private:
	typedef PlatformerEnemy super;
	GoblinElf(cocos2d::ValueMap& properties);
	~GoblinElf();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
