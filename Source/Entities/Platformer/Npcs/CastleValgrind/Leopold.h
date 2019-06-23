#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Leopold : public NpcBase
{
public:
	static Leopold* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyLeopold;

private:
	typedef NpcBase super;
	Leopold(cocos2d::ValueMap& initProperties);
	~Leopold();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
