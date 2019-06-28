#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class IceGolem : public PlatformerEnemy
{
public:
	static IceGolem* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyIceGolem;

private:
	typedef PlatformerEnemy super;
	IceGolem(cocos2d::ValueMap& initProperties);
	~IceGolem();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
