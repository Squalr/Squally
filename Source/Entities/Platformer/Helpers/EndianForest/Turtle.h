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

	static const std::string MapKey;
	
protected:
	Turtle(cocos2d::ValueMap& properties);
	virtual ~Turtle();

private:
	typedef PlatformerHelper super;
};
