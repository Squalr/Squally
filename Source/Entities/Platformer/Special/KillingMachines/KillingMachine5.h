#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class KillingMachine5 : public PlatformerEnemy
{
public:
	static KillingMachine5* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;
	
protected:
	KillingMachine5(cocos2d::ValueMap& properties);
	virtual ~KillingMachine5();

private:
	typedef PlatformerEnemy super;
};
