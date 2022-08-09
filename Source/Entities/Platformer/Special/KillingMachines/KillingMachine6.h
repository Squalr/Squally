#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class KillingMachine6 : public PlatformerEnemy
{
public:
	static KillingMachine6* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;
	
protected:
	KillingMachine6(cocos2d::ValueMap& properties);
	virtual ~KillingMachine6();

private:
	typedef PlatformerEnemy super;
};
