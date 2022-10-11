#pragma once
#include <string>

#include "Entities/Platformer/PlatformerHelper.h"

class LocalizedString;

class CritterDemon : public PlatformerHelper
{
public:
	static CritterDemon* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	CritterDemon(cocos2d::ValueMap& properties);
	virtual ~CritterDemon();

private:
	typedef PlatformerHelper super;
};
