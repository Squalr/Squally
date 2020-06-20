#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Agnes : public PlatformerEnemy
{
public:
	static Agnes* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;

protected:
	Agnes(cocos2d::ValueMap& properties);
	virtual ~Agnes();

private:
	typedef PlatformerEnemy super;
};
