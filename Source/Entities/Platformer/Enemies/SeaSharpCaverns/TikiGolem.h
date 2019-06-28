#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class TikiGolem : public PlatformerEnemy
{
public:
	static TikiGolem* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyTikiGolem;

private:
	typedef PlatformerEnemy super;
	TikiGolem(cocos2d::ValueMap& initProperties);
	~TikiGolem();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
