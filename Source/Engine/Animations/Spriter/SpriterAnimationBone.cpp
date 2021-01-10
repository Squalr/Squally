#include "SpriterAnimationBone.h"

#include "cocos/2d/CCDrawNode.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const std::vector<Color4F> SpriterAnimationBone::DebugColorHeirarchy = std::vector<Color4F>
{
	Color4F(Color4B(5, 18, 97, 255)),
	Color4F(Color4B(29, 41, 112, 255)),
	Color4F(Color4B(54, 65, 128, 255)),
	Color4F(Color4B(80, 89, 144, 255)),
	Color4F(Color4B(105, 112, 160, 255)),
	Color4F(Color4B(130, 136, 176, 255)),
	Color4F(Color4B(155, 160, 191, 255)),
	Color4F(Color4B(180, 183, 207, 255)),
	Color4F(Color4B(205, 207, 223, 255)),
	Color4F(Color4B(230, 231, 239, 255)),
	Color4F(Color4B(255, 255, 255, 255)),
};

SpriterAnimationBone* SpriterAnimationBone::create(Size boneSize)
{
	SpriterAnimationBone* instance = new SpriterAnimationBone(boneSize);

	instance->autorelease();

	return instance;
}

SpriterAnimationBone::SpriterAnimationBone(Size boneSize)
{
	this->boneSize = boneSize;
	this->debugDraw = nullptr;
	this->heirarchyDepth = 0;
}

SpriterAnimationBone::~SpriterAnimationBone()
{
}

void SpriterAnimationBone::setDebugDrawHeirarchyDepth(int heirarchyDepth)
{
	this->heirarchyDepth = MathUtils::clamp(heirarchyDepth, 0,  SpriterAnimationBone::DebugColorHeirarchy.size() - 1);

	if (DeveloperModeController::isDeveloperModeEnabled())
	{
		this->redrawDebugDraw();
	}
}

void SpriterAnimationBone::onDeveloperModeEnable(int debugLevel)
{
	if (this->debugDraw == nullptr)
	{
		this->debugDraw = DrawNode::create();

		this->addChild(this->debugDraw);
	}
	
	this->redrawDebugDraw();
	this->debugDraw->setVisible(true);
}

void SpriterAnimationBone::onDeveloperModeDisable()
{
	if (this->debugDraw != nullptr)
	{
		this->debugDraw->setVisible(false);
	}
}

void SpriterAnimationBone::redrawDebugDraw()
{
	if (this->debugDraw == nullptr)
	{
		return;
	}

	this->debugDraw->clear();

	// Applying scale on draw is preferred to scaling the draw node, as the w/h can be small values.
	// The alternative is to draw sub-pixel shapes and try to scale them up, which seems sketchy.
	this->debugDraw->drawTriangle(
		Vec2(0.0f, this->boneSize.height / 2.0f * this->_scaleY),
		Vec2(0.0f, -this->boneSize.height / 2.0f * this->_scaleY),
		Vec2(this->boneSize.width * this->_scaleX, 0.0f),
		SpriterAnimationBone::DebugColorHeirarchy[this->heirarchyDepth]
	);
}
