#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class PrincessPepper : public NpcBase
{
public:
	static PrincessPepper* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPrincessPepper;

private:
	typedef NpcBase super;
	PrincessPepper(cocos2d::ValueMap& initProperties);
	~PrincessPepper();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
