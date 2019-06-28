#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class HexusOpponentData;

class Polyphemus : public NpcBase
{
public:
	static Polyphemus* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPolyphemus;

private:
	typedef NpcBase super;
	Polyphemus(cocos2d::ValueMap& initProperties);
	~Polyphemus();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
