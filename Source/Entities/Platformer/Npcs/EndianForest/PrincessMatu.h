#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class PrincessMatu : public NpcBase
{
public:
	static PrincessMatu* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPrincessMatu;

private:
	typedef NpcBase super;
	PrincessMatu(cocos2d::ValueMap& initProperties);
	~PrincessMatu();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
