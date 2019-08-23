#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class OrcSwordsman : public PlatformerEnemy
{
public:
	static OrcSwordsman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyOrcSwordsman;

private:
	typedef PlatformerEnemy super;
	OrcSwordsman(cocos2d::ValueMap& properties);
	~OrcSwordsman();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
