#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class ZombieElric : public PlatformerEnemy
{
public:
	static ZombieElric* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyZombieElric;

private:
	typedef PlatformerEnemy super;
	ZombieElric(cocos2d::ValueMap& properties);
	~ZombieElric();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
