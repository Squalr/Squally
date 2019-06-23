#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Thor : public NpcBase
{
public:
	static Thor* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyThor;

private:
	typedef NpcBase super;
	Thor(cocos2d::ValueMap& initProperties);
	~Thor();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
