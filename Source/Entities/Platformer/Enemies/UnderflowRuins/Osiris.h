#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Osiris : public PlatformerEnemy
{
public:
	static Osiris* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Osiris(cocos2d::ValueMap& properties);
	virtual ~Osiris();

private:
	typedef PlatformerEnemy super;
};
