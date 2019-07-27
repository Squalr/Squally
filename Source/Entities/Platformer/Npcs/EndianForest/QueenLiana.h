#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class QueenLiana : public NpcBase
{
public:
	static QueenLiana* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyQueenLiana;

private:
	typedef NpcBase super;
	QueenLiana(cocos2d::ValueMap& initProperties);
	~QueenLiana();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
