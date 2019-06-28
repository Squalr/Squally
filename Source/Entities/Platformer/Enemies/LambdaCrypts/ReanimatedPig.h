#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class ReanimatedPig : public PlatformerEnemy
{
public:
	static ReanimatedPig* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyReanimatedPig;

private:
	typedef PlatformerEnemy super;
	ReanimatedPig(cocos2d::ValueMap& initProperties);
	~ReanimatedPig();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
