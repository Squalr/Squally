#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class OrcBomber : public PlatformerEnemy
{
public:
	static OrcBomber* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	OrcBomber(cocos2d::ValueMap& properties);
	virtual ~OrcBomber();

private:
	typedef PlatformerEnemy super;
};
