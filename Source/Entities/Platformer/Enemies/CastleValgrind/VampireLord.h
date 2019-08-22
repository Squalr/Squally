#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class VampireLord : public PlatformerEnemy
{
public:
	static VampireLord* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyVampireLord;

private:
	typedef PlatformerEnemy super;
	VampireLord(cocos2d::ValueMap& properties);
	~VampireLord();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
