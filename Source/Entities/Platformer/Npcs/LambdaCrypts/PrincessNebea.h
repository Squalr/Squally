#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class PrincessNebea : public NpcBase
{
public:
	static PrincessNebea* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPrincessNebea;

private:
	typedef NpcBase super;
	PrincessNebea(cocos2d::ValueMap& initProperties);
	~PrincessNebea();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
