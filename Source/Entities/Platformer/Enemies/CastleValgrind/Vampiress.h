#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Vampiress : public PlatformerEnemy
{
public:
	static Vampiress* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Vampiress(cocos2d::ValueMap& properties);
	virtual ~Vampiress();

private:
	typedef PlatformerEnemy super;
};
