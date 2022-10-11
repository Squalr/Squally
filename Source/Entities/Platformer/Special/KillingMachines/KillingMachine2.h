#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class KillingMachine2 : public PlatformerEnemy
{
public:
	static KillingMachine2* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;
	
protected:
	KillingMachine2(cocos2d::ValueMap& properties);
	virtual ~KillingMachine2();

private:
	typedef PlatformerEnemy super;
};
