#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Garin : public NpcBase
{
public:
	static Garin* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGarin;

private:
	typedef NpcBase super;
	Garin(cocos2d::ValueMap& initProperties);
	~Garin();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
