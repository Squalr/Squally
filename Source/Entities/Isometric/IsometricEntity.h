#pragma once
#include <math.h>

#include "cocos2d.h"
#include "cocos-ext.h"

#include "Engine/Hackables/HackableObject.h"
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
		float scale = 1.0f,
		Vec2 offset = Vec2(0.0f, 0.0f),
		Size size = Size(256.0f, 128.0f));
	~IsometricEntity();

	void onEnter() override;
	void update(float) override;

	AnimationNode* animationNode;
	SpriterEngine::EntityInstance* animationNodeEntity;

	Vec2 movement;
};

