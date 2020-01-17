#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class Lazarus : public PlatformerEnemy
{
public:
	static Lazarus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyLazarus;

private:
	typedef PlatformerEnemy super;
	Lazarus(cocos2d::ValueMap& properties);
	~Lazarus();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
