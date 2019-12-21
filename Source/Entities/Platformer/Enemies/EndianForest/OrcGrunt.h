#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class OrcGrunt : public PlatformerEnemy
{
public:
	static OrcGrunt* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyOrcGrunt;

private:
	typedef PlatformerEnemy super;
	OrcGrunt(cocos2d::ValueMap& properties);
	~OrcGrunt();
};
