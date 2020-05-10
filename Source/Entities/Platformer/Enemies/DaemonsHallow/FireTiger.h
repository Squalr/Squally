#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class FireTiger : public PlatformerEnemy
{
public:
	static FireTiger* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;
	
protected:
	FireTiger(cocos2d::ValueMap& properties);
	virtual ~FireTiger();

private:
	typedef PlatformerEnemy super;
};
