#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Tyracius : public NpcBase
{
public:
	static Tyracius* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyTyracius;

private:
	typedef NpcBase super;
	Tyracius(cocos2d::ValueMap& initProperties);
	~Tyracius();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
