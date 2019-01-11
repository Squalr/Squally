#include "LightningSphere.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

LightningSphere* LightningSphere::create()
{
	LightningSphere* instance = new LightningSphere();

	instance->autorelease();

	return instance;
}

LightningSphere::LightningSphere()
{
	this->animations = SmartAnimationSequenceNode::create(UIResources::EmptyImage);

	static bool runOnce = true;

	if (runOnce)
	{
		runOnce = false;

		// Prime the cache with all of the animation sequence files used by lightning sphere
		this->animations->primeCache(UIResources::Menus_WorldMap_Lightning_LightningSphere1_Lightning_0000);
		this->animations->primeCache(UIResources::Menus_WorldMap_Lightning_LightningSphere2_Lightning_01);
		this->animations->primeCache(UIResources::Menus_WorldMap_Lightning_LightningSphere3_Lightning_01);
		this->animations->primeCache(UIResources::Menus_WorldMap_Lightning_LightningSphere4_Lightning_01);
		this->animations->primeCache(UIResources::Menus_WorldMap_Lightning_LightningSphere5_Lightning_01);
		this->animations->primeCache(UIResources::Menus_WorldMap_Lightning_LightningSphere6_Lightning_01);
		this->animations->primeCache(UIResources::Menus_WorldMap_Lightning_LightningSphere7_Lightning_01);
		this->animations->primeCache(UIResources::Menus_WorldMap_Lightning_LightningSphere8_Lightning_01);
	}

	this->addChild(this->animations);
}

LightningSphere::~LightningSphere()
{
}

void LightningSphere::onEnter()
{
	super::onEnter();

	this->playNextAnimation();
}

void LightningSphere::playNextAnimation()
{
	static int animationIndex = 0;
	const float animationSpeed = 0.035f;
	auto callback = CC_CALLBACK_0(LightningSphere::playNextAnimation, this);

	// Bound index from 1 to 8
	animationIndex = (animationIndex % 8) + 1;

	switch (animationIndex)
	{
		case 1:
		default:
			this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_LightningSphere1_Lightning_0000, animationSpeed, true, callback);
			break;
		case 2:
			this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_LightningSphere2_Lightning_01, animationSpeed, true, callback);
			break;
		case 3:
			this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_LightningSphere3_Lightning_01, animationSpeed, true, callback);
			break;
		case 4:
			this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_LightningSphere4_Lightning_01, animationSpeed, true, callback);
			break;
		case 5:
			this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_LightningSphere5_Lightning_01, animationSpeed, true, callback);
			break;
		case 6:
			this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_LightningSphere6_Lightning_01, animationSpeed, true, callback);
			break;
		case 7:
			this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_LightningSphere7_Lightning_01, animationSpeed, true, callback);
			break;
		case 8:
			this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_LightningSphere8_Lightning_01, animationSpeed, true, callback);
			break;
	}
}
