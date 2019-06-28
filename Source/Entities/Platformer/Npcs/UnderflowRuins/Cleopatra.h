#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Cleopatra : public NpcBase
{
public:
	static Cleopatra* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCleopatra;

private:
	typedef NpcBase super;
	Cleopatra(cocos2d::ValueMap& initProperties);
	~Cleopatra();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
