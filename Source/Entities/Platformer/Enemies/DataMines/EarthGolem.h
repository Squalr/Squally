#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class EarthGolem : public PlatformerEnemy
{
public:
	static EarthGolem* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	EarthGolem(cocos2d::ValueMap& properties);
	virtual ~EarthGolem();

private:
	typedef PlatformerEnemy super;
};
