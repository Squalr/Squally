#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Bonnie : public NpcBase
{
public:
	static Bonnie* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyBonnie;

private:
	typedef NpcBase super;
	Bonnie(cocos2d::ValueMap& initProperties);
	~Bonnie();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
