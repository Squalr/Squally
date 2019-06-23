#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class OrcGrunt : public PlatformerEnemy
{
public:
	static OrcGrunt* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyOrcGrunt;

private:
	typedef PlatformerEnemy super;
	OrcGrunt(cocos2d::ValueMap& initProperties);
	~OrcGrunt();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
