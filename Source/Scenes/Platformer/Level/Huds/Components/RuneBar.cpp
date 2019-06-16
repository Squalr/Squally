#include "RuneBar.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Generics/XOverY.h"

using namespace cocos2d;

const int RuneBar::RuneCipher = 0x60351092;

RuneBar* RuneBar::create(bool isFrameOnLeft)
{
	RuneBar* instance = new RuneBar(isFrameOnLeft);

	instance->autorelease();

	return instance;
}

RuneBar::RuneBar(bool isFrameOnLeft)
{
	this->target = nullptr;
	this->emptyRunes = std::vector<Sprite*>();
	this->filledRunes = std::vector<Sprite*>();
	this->smokeFx = std::vector<SmartAnimationSequenceNode*>();
	this->smokeSound = std::vector<Sound*>();

	this->cachedRunes = 0 ^ RuneBar::RuneCipher;

	for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
	{
		this->emptyRunes.push_back(Sprite::create(UIResources::HUD_EyeSlot));
		this->filledRunes.push_back(Sprite::create(UIResources::HUD_Eye));
		this->smokeFx.push_back(SmartAnimationSequenceNode::create());
		this->smokeSound.push_back(Sound::create(SoundResources::Platformer_Abilities_HackerMode_Enable));
	}

	for (auto it = this->emptyRunes.begin(); it != this->emptyRunes.end(); it++)
	{
		this->addChild(*it);
	}

	for (auto it = this->filledRunes.begin(); it != this->filledRunes.end(); it++)
	{
		this->addChild(*it);
	}

	for (auto it = this->smokeFx.begin(); it != this->smokeFx.end(); it++)
	{
		this->addChild(*it);
	}

	for (auto it = this->smokeSound.begin(); it != this->smokeSound.end(); it++)
	{
		this->addChild(*it);
	}
}

RuneBar::~RuneBar()
{
}

void RuneBar::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void RuneBar::initializePositions()
{
	super::initializePositions();

	for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
	{
		this->emptyRunes[index]->setPosition(Vec2(0.0f, (float)index * -34.0f));
		this->filledRunes[index]->setPosition(Vec2(0.0f, (float)index * -34.0f));
		this->smokeFx[index]->setPosition(Vec2(0.0f, (float)index * -34.0f));
	}
}

void RuneBar::initializeListeners()
{
	super::initializeListeners();
}

void RuneBar::update(float dt)
{
	super::update(dt);

	if (this->target == nullptr)
	{
		return;
	}

	int currentRunes = MathUtils::clamp(target->getRunes(), 0, PlatformerEntity::MaxRunes);

	if (currentRunes != (this->cachedRunes ^ RuneBar::RuneCipher))
	{
		for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
		{
			if (index < currentRunes)
			{
				this->filledRunes[index]->setVisible(true);
				this->emptyRunes[index]->setVisible(false);
			}
			else
			{
				this->filledRunes[index]->setVisible(false);
				this->emptyRunes[index]->setVisible(true);
			}
		}

		if (currentRunes < (this->cachedRunes ^ RuneBar::RuneCipher) && currentRunes < PlatformerEntity::MaxRunes)
		{
			this->smokeFx[currentRunes]->playAnimation(FXResources::PurplePuffSmall_PurplePuff_0000, 0.05f, true);
			this->smokeSound[currentRunes]->play();
		}

		this->cachedRunes = currentRunes ^ RuneBar::RuneCipher;
	}
}

void RuneBar::setStatsTarget(PlatformerEntity* target)
{
	this->target = target;

	if (this->target != nullptr)
	{
		this->cachedRunes = PlatformerEntity::MaxRunes ^ RuneBar::RuneCipher;

		for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
		{
			this->filledRunes[index]->setVisible(true);
			this->emptyRunes[index]->setVisible(false);
		}
	}
	else
	{
		this->cachedRunes = target->getRunes() ^ RuneBar::RuneCipher;
	}
}
