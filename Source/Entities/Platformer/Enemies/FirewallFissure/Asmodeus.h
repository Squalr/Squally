#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Asmodeus : public PlatformerEnemy
{
public:
	static Asmodeus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Asmodeus(cocos2d::ValueMap& properties);
	virtual ~Asmodeus();

private:
	typedef PlatformerEnemy super;
};
