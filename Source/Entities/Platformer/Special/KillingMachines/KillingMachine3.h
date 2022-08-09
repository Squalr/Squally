#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class KillingMachine3 : public PlatformerEnemy
{
public:
	static KillingMachine3* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;
	
protected:
	KillingMachine3(cocos2d::ValueMap& properties);
	virtual ~KillingMachine3();

private:
	typedef PlatformerEnemy super;
};
