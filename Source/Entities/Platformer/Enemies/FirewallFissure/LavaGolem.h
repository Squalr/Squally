#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class LavaGolem : public PlatformerEnemy
{
public:
	static LavaGolem* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;
	
protected:
	LavaGolem(cocos2d::ValueMap& properties);
	virtual ~LavaGolem();

private:
	typedef PlatformerEnemy super;
};
