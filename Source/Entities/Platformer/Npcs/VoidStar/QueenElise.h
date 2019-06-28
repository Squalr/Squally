#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class QueenElise : public NpcBase
{
public:
	static QueenElise* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyQueenElise;

private:
	typedef NpcBase super;
	QueenElise(cocos2d::ValueMap& initProperties);
	~QueenElise();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
