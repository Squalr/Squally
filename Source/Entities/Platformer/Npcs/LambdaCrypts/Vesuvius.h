#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Vesuvius : public NpcBase
{
public:
	static Vesuvius* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyVesuvius;

private:
	typedef NpcBase super;
	Vesuvius(cocos2d::ValueMap& initProperties);
	~Vesuvius();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
