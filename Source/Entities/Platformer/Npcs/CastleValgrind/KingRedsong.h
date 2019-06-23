#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class KingRedsong : public NpcBase
{
public:
	static KingRedsong* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyKingRedsong;

private:
	typedef NpcBase super;
	KingRedsong(cocos2d::ValueMap& initProperties);
	~KingRedsong();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
