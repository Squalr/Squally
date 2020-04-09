#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Gorgon : public PlatformerEnemy
{
public:
	static Gorgon* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Gorgon(cocos2d::ValueMap& properties);
	virtual ~Gorgon();

private:
	typedef PlatformerEnemy super;
};
