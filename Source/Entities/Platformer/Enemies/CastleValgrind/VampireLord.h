#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class VampireLord : public PlatformerEnemy
{
public:
	static VampireLord* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	VampireLord(cocos2d::ValueMap& properties);
	virtual ~VampireLord();

private:
	typedef PlatformerEnemy super;
};
