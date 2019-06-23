#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Thatcher : public NpcBase
{
public:
	static Thatcher* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyThatcher;

private:
	typedef NpcBase super;
	Thatcher(cocos2d::ValueMap& initProperties);
	~Thatcher();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
