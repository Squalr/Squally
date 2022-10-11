#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class KillingMachine1 : public PlatformerEnemy
{
public:
	static KillingMachine1* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;
	
protected:
	KillingMachine1(cocos2d::ValueMap& properties);
	virtual ~KillingMachine1();

private:
	typedef PlatformerEnemy super;
};
