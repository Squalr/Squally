#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class IceGolem : public PlatformerEnemy
{
public:
	static IceGolem* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;
	
protected:
	IceGolem(cocos2d::ValueMap& properties);
	virtual ~IceGolem();

private:
	typedef PlatformerEnemy super;
};
