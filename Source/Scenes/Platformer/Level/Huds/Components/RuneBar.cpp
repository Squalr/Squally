#include "RuneBar.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCDrawNode.h"
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
	this->cooldownClips = std::vector<ClippingNode*>();
	this->cooldownCircles = std::vector<DrawNode*>();
	this->cooldownStencils = std::vector<DrawNode*>();
	this->filledRunes = std::vector<Sprite*>();
	this->smokeFx = std::vector<SmartAnimationSequenceNode*>();
	this->smokeSound = std::vector<Sound*>();

	this->cachedRunes = 0 ^ RuneBar::RuneCipher;

	for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
	{
		DrawNode* cooldownStencil = DrawNode::create();
		DrawNode* cooldownCircle = DrawNode::create();

		cooldownCircle->drawSolidCircle(Vec2::ZERO, 12.0f, 0.0f, 24, Color4F(Color4B(0, 0, 0, 196)));

		// Enable to debug clipping:
		// this->addChild(cooldownStencil);

		ClippingNode* cooldownClip = ClippingNode::create(cooldownStencil);

		cooldownClip->addChild(cooldownCircle);

		this->cooldownStencils.push_back(cooldownStencil);
		this->cooldownCircles.push_back(cooldownCircle);
		this->cooldownClips.push_back(cooldownClip);
		this->emptyRunes.push_back(Sprite::create(UIResources::HUD_EyeSlot));
		this->filledRunes.push_back(Sprite::create(UIResources::HUD_Eye));
		this->smokeFx.push_back(SmartAnimationSequenceNode::create());
		this->smokeSound.push_back(Sound::create(SoundResources::Platformer_Abilities_HackerMode_Enable));
	}

	for (auto it = this->emptyRunes.begin(); it != this->emptyRunes.end(); it++)
	{
		this->addChild(*it);
	}

	for (auto it = this->cooldownClips.begin(); it != this->cooldownClips.end(); it++)
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
		this->cooldownClips[index]->setPosition(Vec2(0.0f, (float)index * -34.0f));
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

	int currentRunes = MathUtils::clamp(target->getAvailableRunes(), 0, PlatformerEntity::MaxRunes);

	for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
	{
		this->cooldownStencils[index]->clear();

		float progress = (PlatformerEntity::RuneCooldown - target->getRuneCooldown(index)) / PlatformerEntity::RuneCooldown;

		if (progress < 0.25f)
		{
			static std::vector<Vec2> quadrant = std::vector<Vec2>
			{
				Vec2(0.0f, 0.0f),
				Vec2(24.0f, 0.0f),
				Vec2(0.0f, 0.0f),
			};

			float quadrantProgress = 1.0f - MathUtils::clamp(progress, 0.0f, 0.25f) / 0.25f;

			quadrant[2] = Vec2(24.0f * std::cos(quadrantProgress * M_PI / 2.0f), 24.0f * std::sin(quadrantProgress * M_PI / 2.0f));

			this->cooldownStencils[index]->drawSolidPoly(quadrant.data(), quadrant.size(), Color4F(Color4B(0, 0, 0, 196)));
		}

		if (progress < 0.5f)
		{
			static std::vector<Vec2> quadrant = std::vector<Vec2>
			{
				Vec2(0.0f, 0.0f),
				Vec2(0.0f, -24.0f),
				Vec2(0.0f, 0.0f),
			};

			float quadrantProgress = progress < 0.25f ? 1.0f : (1.0f - MathUtils::clamp(std::fmod(progress, 0.25f), 0.0f, 0.25f) / 0.25f);

			quadrant[2] = Vec2(24.0f * std::cos((quadrantProgress - 1.0f) * M_PI / 2.0f), 24.0f * std::sin((quadrantProgress - 1.0f) * M_PI / 2.0f));

			this->cooldownStencils[index]->drawSolidPoly(quadrant.data(), quadrant.size(), Color4F(Color4B(0, 0, 0, 196)));
		}

		if (progress < 0.75f)
		{
			static std::vector<Vec2> quadrant = std::vector<Vec2>
			{
				Vec2(0.0f, 0.0f),
				Vec2(-24.0f, 0.0f),
				Vec2(0.0f, 0.0f),
			};

			float quadrantProgress = progress < 0.5f ? 1.0f : (1.0f - MathUtils::clamp(std::fmod(progress, 0.25f), 0.0f, 0.25f) / 0.25f);

			quadrant[2] = Vec2(24.0f * std::cos((quadrantProgress - 2.0f) * M_PI / 2.0f), 24.0f * std::sin((quadrantProgress - 2.0f) * M_PI / 2.0f));

			this->cooldownStencils[index]->drawSolidPoly(quadrant.data(), quadrant.size(), Color4F(Color4B(0, 0, 0, 196)));
		}

		if (progress < 1.0f)
		{
			static std::vector<Vec2> quadrant = std::vector<Vec2>
			{
				Vec2(0.0f, 0.0f),
				Vec2(0.0f, 24.0f),
				Vec2(0.0f, 0.0f),
			};

			float quadrantProgress = progress < 0.75f ? 1.0f : (1.0f - MathUtils::clamp(std::fmod(progress, 0.25f), 0.0f, 0.25f) / 0.25f);

			quadrant[2] = Vec2(24.0f * std::cos((quadrantProgress - 3.0f) * M_PI / 2.0f), 24.0f * std::sin((quadrantProgress - 3.0f) * M_PI / 2.0f));

			this->cooldownStencils[index]->drawSolidPoly(quadrant.data(), quadrant.size(), Color4F(Color4B(0, 0, 0, 196)));
		}
	}

	if (currentRunes != (this->cachedRunes ^ RuneBar::RuneCipher))
	{
		int mostRecentIndex = 0;
		float mostRecentCooldown = 0.0f;

		for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
		{
			float cooldown = target->getRuneCooldown(index);

			if (cooldown > mostRecentCooldown)
			{
				mostRecentIndex = index;
				mostRecentCooldown = cooldown;
			}

			if (cooldown <= 0.0f)
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
			this->smokeFx[mostRecentIndex]->playAnimation(FXResources::PurplePuffSmall_PurplePuff_0000, 0.05f, true);
			this->smokeSound[mostRecentIndex]->play();
		}

		this->cachedRunes = currentRunes ^ RuneBar::RuneCipher;
	}
}

void RuneBar::setStatsTarget(PlatformerEntity* target)
{
	this->target = target;

	if (this->target == nullptr)
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
		this->cachedRunes = target->getAvailableRunes() ^ RuneBar::RuneCipher;
	}
}
