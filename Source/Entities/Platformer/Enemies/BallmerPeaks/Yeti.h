#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Yeti : public PlatformerEnemy
{
public:
	static Yeti* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Yeti(cocos2d::ValueMap& properties);
	virtual ~Yeti();

private:
	typedef PlatformerEnemy super;
};
