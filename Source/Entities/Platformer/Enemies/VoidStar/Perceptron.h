#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Perceptron : public PlatformerEnemy
{
public:
	static Perceptron* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Perceptron(cocos2d::ValueMap& properties);
	virtual ~Perceptron();

private:
	typedef PlatformerEnemy super;
};
