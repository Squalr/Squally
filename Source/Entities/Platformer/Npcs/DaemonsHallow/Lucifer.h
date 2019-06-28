#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Lucifer : public NpcBase
{
public:
	static Lucifer* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyLucifer;

private:
	typedef NpcBase super;
	Lucifer(cocos2d::ValueMap& initProperties);
	~Lucifer();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
