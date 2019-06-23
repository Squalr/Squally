#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class HexusOpponentData;

class Turtle : public PlatformerEntity
{
public:
	static Turtle* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyTurtle;

private:
	typedef PlatformerEntity super;
	Turtle(cocos2d::ValueMap& initProperties);
	~Turtle();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
