#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Drak : public NpcBase
{
public:
	static Drak* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDrak;

private:
	typedef NpcBase super;
	Drak(cocos2d::ValueMap& initProperties);
	~Drak();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
