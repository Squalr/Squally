#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Mermaid : public PlatformerEnemy
{
public:
	static Mermaid* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyMermaid;

private:
	typedef PlatformerEnemy super;
	Mermaid(cocos2d::ValueMap& properties);
	~Mermaid();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
