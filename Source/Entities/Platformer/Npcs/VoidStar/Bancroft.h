#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Bancroft : public NpcBase
{
public:
	static Bancroft* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyBancroft;

private:
	typedef NpcBase super;
	Bancroft(cocos2d::ValueMap& initProperties);
	~Bancroft();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
