#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class VoidArcher : public PlatformerEnemy
{
public:
	static VoidArcher* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	VoidArcher(cocos2d::ValueMap& properties);
	virtual ~VoidArcher();

private:
	typedef PlatformerEnemy super;
};
