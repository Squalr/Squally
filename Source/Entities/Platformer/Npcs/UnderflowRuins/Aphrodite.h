#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Aphrodite : public NpcBase
{
public:
	static Aphrodite* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyAphrodite;

private:
	typedef NpcBase super;
	Aphrodite(cocos2d::ValueMap& initProperties);
	~Aphrodite();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
