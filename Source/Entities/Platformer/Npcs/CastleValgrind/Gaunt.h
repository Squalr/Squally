#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Gaunt : public NpcBase
{
public:
	static Gaunt* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGaunt;

private:
	typedef NpcBase super;
	Gaunt(cocos2d::ValueMap& initProperties);
	~Gaunt();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
