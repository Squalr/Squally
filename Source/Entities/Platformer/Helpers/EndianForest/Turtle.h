#pragma once
#include <string>

#include "Entities/Platformer/PlatformerHelper.h"

class HexusOpponentData;
class LocalizedString;

class Turtle : public PlatformerHelper
{
public:
	static Turtle* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyTurtle;

private:
	typedef PlatformerHelper super;
	Turtle(cocos2d::ValueMap& properties);
	~Turtle();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
