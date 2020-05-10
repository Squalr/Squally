#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class VoidDemon : public PlatformerEnemy
{
public:
	static VoidDemon* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	VoidDemon(cocos2d::ValueMap& properties);
	virtual ~VoidDemon();

private:
	typedef PlatformerEnemy super;
};
