#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class PenguinWarrior : public PlatformerEnemy
{
public:
	static PenguinWarrior* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPenguinWarrior;

private:
	typedef PlatformerEnemy super;
	PenguinWarrior(cocos2d::ValueMap& properties);
	~PenguinWarrior();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
