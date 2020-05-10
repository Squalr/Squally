#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class MummyPriest : public PlatformerEnemy
{
public:
	static MummyPriest* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	MummyPriest(cocos2d::ValueMap& properties);
	virtual ~MummyPriest();

private:
	typedef PlatformerEnemy super;
};
