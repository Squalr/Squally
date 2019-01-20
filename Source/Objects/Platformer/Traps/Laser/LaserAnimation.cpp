#include "LaserAnimation.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

LaserAnimation* LaserAnimation::create(float height)
{
	LaserAnimation* instance = new LaserAnimation(height);

	instance->autorelease();

	return instance;
}

LaserAnimation::LaserAnimation(float height)
{
	this->laserHeadTop = Sprite::create(ObjectResources::Traps_Laser_LaserHead);
	this->laserHeadBottom = Sprite::create(ObjectResources::Traps_Laser_LaserHead);
	this->laserWeak = Sprite::create(ObjectResources::Traps_Laser_LaserWeak);
	this->laserStrong = Sprite::create(ObjectResources::Traps_Laser_LaserMid);

	this->height = height;

	this->laserHeadBottom->setFlippedY(true);

	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapT = GL_REPEAT;

	this->laserWeak->getTexture()->setTexParameters(params);
	this->laserWeak->setTextureRect(Rect(0.0f, 0.0f, this->laserWeak->getContentSize().width, this->height));

	this->laserStrong->getTexture()->setTexParameters(params);
	this->laserStrong->setTextureRect(Rect(0.0f, 0.0f, this->laserStrong->getContentSize().width, this->height));

	this->addChild(this->laserWeak);
	this->addChild(this->laserStrong);
	this->addChild(this->laserHeadTop);
	this->addChild(this->laserHeadBottom);
}

LaserAnimation::~LaserAnimation()
{
}

void LaserAnimation::onEnter()
{
	super::onEnter();
}

void LaserAnimation::initializePositions()
{
	super::initializePositions();

	this->laserHeadTop->setPositionY(this->height / 2.0f);
	this->laserHeadBottom->setPositionY(-this->height / 2.0f);
}

void LaserAnimation::runAnimation(std::function<void()> onBeamActiveCallback, std::function<void()> onBeamDeactiveCallback)
{
	const float stayActiveDuration = 1.5f;
	
	// Move collision box
	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->laserWeak->setVisible(true);
		}),
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			this->laserWeak->setVisible(false);
		}),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			this->laserWeak->setVisible(true);
		}),
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			this->laserWeak->setVisible(false);
		}),
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			this->laserWeak->setVisible(true);
		}),
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			this->laserWeak->setVisible(false);
		}),
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			this->laserStrong->setVisible(true);

			if (onBeamActiveCallback != nullptr)
			{
				onBeamActiveCallback();
			}
		}),
		DelayTime::create(stayActiveDuration),
		CallFunc::create([=]()
		{
			this->laserStrong->setVisible(false);

			if (onBeamDeactiveCallback != nullptr)
			{
				onBeamDeactiveCallback();
			}
		}),
		nullptr
	));
}
