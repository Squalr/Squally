#include "Lightning.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/ccRandom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/Sound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

Lightning* Lightning::create()
{
	Lightning* instance = new Lightning();

	instance->autorelease();

	return instance;
}

Lightning::Lightning()
{
	this->animations = SmartAnimationSequenceNode::create(UIResources::EmptyImage);
	this->sound = Sound::create(SoundResources::Hexus_Attacks_Energy);
	this->manualDelay = -1.0f;

	static bool runOnce = true;

	if (runOnce)
	{
		runOnce = false;

		// Prime the cache with all of the animation sequence files used by lightning
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning1_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning2_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning3_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning4_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning5_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning6_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning7_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning8_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning9_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning10_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning11_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning12_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning13_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning14_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning15_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning16_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning17_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning18_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning19_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning20_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning21_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning22_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning23_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning24_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning25_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning26_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning27_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning28_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning29_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning30_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning31_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning32_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning33_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning34_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning35_Lightning_01);
		SmartAnimationSequenceNode::primeCache(UIResources::Menus_WorldMap_Lightning_Lightning36_Lightning_01);
	}

	this->addChild(this->animations);
}

Lightning::~Lightning()
{
}

void Lightning::onEnter()
{
	super::onEnter();
}

void Lightning::setManualDelay(float manualDelay)
{
	this->manualDelay = manualDelay;
}

void Lightning::playAnimations(bool repeat)
{
	this->playAnimationsInternal(repeat, true);
}

void Lightning::playAnimationsInternal(bool repeat, bool isFirstRun)
{
	const float animationSpeed = 0.035f;

	auto callback = [=]()
	{
		if (repeat)
		{
			this->playAnimationsInternal(repeat);
		}
	};

	int animationIndex = RandomHelper::random_int(1, 36);
	float delay = this->manualDelay >= 0.0f ? this->manualDelay : (isFirstRun ? RandomHelper::random_real(0.1f, 5.0f) : RandomHelper::random_real(1.0f, 5.0f));

	this->runAction(Sequence::create(DelayTime::create(delay), CallFunc::create([=]()
	{
		float cameraDistance = GameCamera::getInstance()->getCameraPosition().distance(this->getPosition());
		float soundIntensity = (GameCamera::getInstance()->getBounds().size.width / 2.0f) / (4 * float(M_PI) * cameraDistance);

		this->sound->setVolumeMultiplier(soundIntensity);
		this->sound->play();

		switch (animationIndex)
		{
			case 1:
			default:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning1_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 2:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning2_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 3:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning3_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 4:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning4_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 5:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning5_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 6:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning6_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 7:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning7_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 8:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning8_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 9:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning9_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 10:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning10_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 11:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning11_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 12:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning12_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 13:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning13_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 14:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning14_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 15:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning15_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 16:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning16_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 17:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning17_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 18:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning18_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 19:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning19_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 20:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning20_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 21:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning21_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 22:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning22_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 23:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning23_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 24:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning24_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 25:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning25_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 26:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning26_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 27:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning27_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 28:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning28_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 29:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning29_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 30:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning30_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 31:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning31_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 32:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning32_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 33:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning33_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 34:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning34_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 35:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning35_Lightning_01, animationSpeed, true, callback);
				break;
			}
			case 36:
			{
				this->animations->playAnimation(UIResources::Menus_WorldMap_Lightning_Lightning36_Lightning_01, animationSpeed, true, callback);
				break;
			}
		}
	}), nullptr));
}
