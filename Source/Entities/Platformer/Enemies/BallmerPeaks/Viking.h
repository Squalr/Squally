#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Viking : public PlatformerEnemy
{
public:
	static Viking* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Viking(cocos2d::ValueMap& properties);
	virtual ~Viking();

private:
	typedef PlatformerEnemy super;
};
