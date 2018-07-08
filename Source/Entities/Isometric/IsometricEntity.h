#pragma once
#include "cocos2d.h"

#include "Engine/Objects/Hackables/HackableObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerCollisionMapping.h"
#include "Resources.h"

using namespace cocos2d;

class IsometricEntity : public HackableObject
{
protected:
	IsometricEntity(
		ValueMap* initProperties,
		std::string scmlResource,
		float scale = 1.0f);
	~IsometricEntity();

	void onEnter() override;
	void update(float) override;

	AnimationNode* animationNode;
	SpriterEngine::EntityInstance* animationNodeEntity;

	Vec2 movement;
};

