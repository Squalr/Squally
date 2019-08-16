#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class OrcBomber : public PlatformerEnemy
{
public:
	static OrcBomber* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyOrcBomber;

private:
	typedef PlatformerEnemy super;
	OrcBomber(cocos2d::ValueMap& properties);
	~OrcBomber();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
