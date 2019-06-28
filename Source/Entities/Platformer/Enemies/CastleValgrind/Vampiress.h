#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class Vampiress : public PlatformerEnemy
{
public:
	static Vampiress* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyVampiress;

private:
	typedef PlatformerEnemy super;
	Vampiress(cocos2d::ValueMap& initProperties);
	~Vampiress();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
