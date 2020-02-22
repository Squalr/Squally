#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class TrainingDummy : public PlatformerEnemy
{
public:
	static TrainingDummy* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyTrainingDummy;

protected:
	TrainingDummy(cocos2d::ValueMap& properties);
	virtual ~TrainingDummy();

private:
	typedef PlatformerEnemy super;
};
