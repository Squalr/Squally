#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class OrcSwordsman : public PlatformerEnemy
{
public:
	static OrcSwordsman* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyOrcSwordsman;

private:
	typedef PlatformerEnemy super;
	OrcSwordsman(cocos2d::ValueMap& initProperties);
	~OrcSwordsman();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
