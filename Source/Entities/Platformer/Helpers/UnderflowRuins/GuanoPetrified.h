#pragma once
#include <string>

#include "Entities/Platformer/PlatformerHelper.h"

class HexusOpponentData;
class LocalizedString;

class GuanoPetrified : public PlatformerHelper
{
public:
	static GuanoPetrified* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	GuanoPetrified(cocos2d::ValueMap& properties);
	virtual ~GuanoPetrified();

private:
	typedef PlatformerHelper super;
};
