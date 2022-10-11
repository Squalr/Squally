#pragma once
#include <string>

#include "Entities/Platformer/PlatformerHelper.h"

class LocalizedString;

class Knight : public PlatformerHelper
{
public:
	static Knight* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Knight(cocos2d::ValueMap& properties);
	virtual ~Knight();

private:
	typedef PlatformerHelper super;
};
