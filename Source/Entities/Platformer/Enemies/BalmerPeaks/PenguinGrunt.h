#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class PenguinGrunt : public PlatformerEnemy
{
public:
	static PenguinGrunt* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPenguinGrunt;

private:
	typedef PlatformerEnemy super;
	PenguinGrunt(cocos2d::ValueMap& initProperties);
	~PenguinGrunt();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
