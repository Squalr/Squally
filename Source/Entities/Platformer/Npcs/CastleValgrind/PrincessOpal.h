#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class PrincessOpal : public NpcBase
{
public:
	static PrincessOpal* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPrincessOpal;

private:
	typedef NpcBase super;
	PrincessOpal(cocos2d::ValueMap& initProperties);
	~PrincessOpal();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
