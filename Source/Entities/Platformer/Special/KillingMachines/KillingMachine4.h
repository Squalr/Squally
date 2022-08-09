#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class KillingMachine4 : public PlatformerEnemy
{
public:
	static KillingMachine4* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;
	
protected:
	KillingMachine4(cocos2d::ValueMap& properties);
	virtual ~KillingMachine4();

private:
	typedef PlatformerEnemy super;
};
