#pragma once
#include <string>

#include "Entities/Platformer/PlatformerHelper.h"

class HexusOpponentData;
class LocalizedString;

class Guano : public PlatformerHelper
{
public:
	static Guano* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Guano(cocos2d::ValueMap& properties);
	virtual ~Guano();

private:
	typedef PlatformerHelper super;
};
