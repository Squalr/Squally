#include "PuzzleDoorBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Sound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Doors/PuzzleDoor/PuzzleDoorGenericPreview.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const int PuzzleDoorBase::RuneCount = 4;
const Color4B PuzzleDoorBase::PassColor = Color4B(70, 144, 75, 255);
const Color4B PuzzleDoorBase::FailColor = Color4B(144, 70, 70, 255);
const Vec2 PuzzleDoorBase::Offset = Vec2(0.0f, -160.0f);
const Vec2 PuzzleDoorBase::DoorOffset = Vec2(0.0f, 64.0f);
const Vec2 PuzzleDoorBase::DoorOpenOffset = Vec2(0.0f, 356.0f);
const std::string PuzzleDoorBase::UnlockedSaveKey = "PUZZLE_DOOR_UNLOCKED";

PuzzleDoorBase::PuzzleDoorBase(ValueMap& initProperties) : super(initProperties, Size(256.0f, 512.0f), PuzzleDoorBase::Offset + Vec2(0.0f, 48.0f))
{
	this->back = Sprite::create(ObjectResources::Doors_PuzzleDoor_Back);
	this->lightLeft = Sprite::create(ObjectResources::Doors_PuzzleDoor_Light);
	this->lightRight = Sprite::create(ObjectResources::Doors_PuzzleDoor_Light);
	this->door = Sprite::create(ObjectResources::Doors_PuzzleDoor_Door);
	this->front = Sprite::create(ObjectResources::Doors_PuzzleDoor_Front);
	this->runes = std::vector<cocos2d::Sprite*>();
	this->runesPassed = std::vector<cocos2d::Sprite*>();
	this->runesFailed = std::vector<cocos2d::Sprite*>();
	this->indexString = ConstantString::create(std::to_string(0));
	this->truthString = ConstantString::create(std::to_string(0));
	this->hackableString = ConstantString::create(std::to_string(0));
	this->indexLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, this->indexString);
	this->truthLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, this->truthString);
	this->hackableLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, this->hackableString);
	this->lockButton = ClickableNode::create(UIResources::Menus_Icons_Lock, UIResources::Menus_Icons_Lock);
	this->unlockButton = ClickableNode::create(UIResources::Menus_Icons_LockUnlocked, UIResources::Menus_Icons_LockUnlocked);
	this->doorOpenSound = Sound::create(SoundResources::Platformer_Doors_StoneWall1, true);
	this->isUnlocked = false;

	this->setRequiresInteraction(true);

	for (int index = 0; index < PuzzleDoorBase::RuneCount; index++)
	{
		this->runes.push_back(Sprite::create(ObjectResources::Doors_PuzzleDoor_Rune));
		this->runesPassed.push_back(Sprite::create(ObjectResources::Doors_PuzzleDoor_RuneGreen));
		this->runesFailed.push_back(Sprite::create(ObjectResources::Doors_PuzzleDoor_RuneRed));
	}

	DrawNode* doorStencil = DrawNode::create();

	doorStencil->drawSolidRect(Vec2(-312.0f / 2.0f, -540.0f / 2.0f - 112.0f), Vec2(312.0f / 2.0f, 540.0f / 2.0f - 112.0f), Color4F::GREEN);

	this->doorClip = SmartClippingNode::create(this->door, doorStencil);

	this->indexLabel->enableOutline(Color4B::BLACK, 4);
	this->truthLabel->enableOutline(Color4B::BLACK, 4);
	this->hackableLabel->enableOutline(Color4B::BLACK, 4);

	this->indexLabel->enableShadow(Color4B(0, 0, 0, 128), Size(2.0f, -2.0f));
	this->truthLabel->enableShadow(Color4B(0, 0, 0, 128), Size(2.0f, -2.0f));
	this->hackableLabel->enableShadow(Color4B(0, 0, 0, 128), Size(2.0f, -2.0f));

	this->indexLabel->setTextColor(PuzzleDoorBase::PassColor);
	this->truthLabel->setTextColor(PuzzleDoorBase::PassColor);
	this->hackableLabel->setTextColor(PuzzleDoorBase::FailColor);

	this->firstRun = true;
	this->puzzleIndex = 0;
	this->realValue = 0;
	this->hackValue = 0;

	for (int index = 0; index < PuzzleDoorBase::RuneCount; index++)
	{
		this->runesPassed[index]->setOpacity(0);
		this->runesFailed[index]->setOpacity(0);
	}

	this->lightLeft->setOpacity(0);
	this->lightRight->setOpacity(0);

	this->addChild(this->back);
	this->addChild(this->lightLeft);
	this->addChild(this->lightRight);
	this->addChild(this->doorClip);
	this->addChild(this->front);
	this->addChild(this->indexLabel);
	this->addChild(this->truthLabel);
	this->addChild(this->hackableLabel);

	for (int index = 0; index < PuzzleDoorBase::RuneCount; index++)
	{
		this->addChild(this->runes[index]);
		this->addChild(this->runesFailed[index]);
		this->addChild(this->runesPassed[index]);
	}

	this->addChild(this->lockButton);
	this->addChild(this->unlockButton);
	this->addChild(this->doorOpenSound);
}

PuzzleDoorBase::~PuzzleDoorBase()
{
}

void PuzzleDoorBase::onEnter()
{
	super::onEnter();

	this->runAction(RepeatForever::create(
		Sequence::create(
			CallFunc::create([=]()
			{
				if (!this->isUnlocked)
				{
					// Increment counter (not on first run tho)
					if (firstRun)
					{
						firstRun = false;
					}
					else
					{
						this->puzzleIndex = MathUtils::wrappingNormalize(this->puzzleIndex + 1, 0, 3);
					}
						
					if (this->puzzleIndex == 0)
					{
						this->passedCount = 0;

						for (int index = 0; index < PuzzleDoorBase::RuneCount; index++)
						{
							this->runesPassed[index]->runAction(FadeTo::create(0.25f, 0));
							this->runesFailed[index]->runAction(FadeTo::create(0.25f, 0));
						}
					}

					this->indexString->setString(std::to_string(this->puzzleIndex));
				}
				else
				{
				}
			}),
			CallFunc::create([=]()
			{
				// Run light effect
				if (!this->isUnlocked)
				{
					this->lightLeft->setPosition(Vec2(-4.0f, 296.0f));
					this->lightRight->setPosition(Vec2(-8.0f, 296.0f));

					this->lightLeft->runAction(Sequence::create(
						FadeTo::create(0.0f, 255),
						MoveBy::create(0.4f, Vec2(-286.0f, 0.0f)),
						MoveBy::create(1.0f, Vec2(0.0f, -360.0f)),
						FadeTo::create(0.0f, 0),
						nullptr
					));

					this->lightRight->runAction(Sequence::create(
						FadeTo::create(0.0f, 255),
						MoveBy::create(0.4f, Vec2(286.0f, 0.0f)),
						MoveBy::create(1.0f, Vec2(0.0f, -360.0f)),
						FadeTo::create(0.0f, 0),
						nullptr
					));
				}
			}),
			DelayTime::create(1.5f),
			CallFunc::create([=]()
			{
				if (!this->isUnlocked)
				{
					this->runOperation(this->puzzleIndex);

					if (this->realValue == this->hackValue)
					{
						this->passedCount++;
						this->hackableLabel->setTextColor(PuzzleDoorBase::PassColor);
						this->runesPassed[this->puzzleIndex]->runAction(FadeTo::create(0.25f, 255));
					}
					else
					{
						this->hackableLabel->setTextColor(PuzzleDoorBase::FailColor);
						this->runesFailed[this->puzzleIndex]->runAction(FadeTo::create(0.25f, 255));
					}
				}
			}),
			DelayTime::create(1.5f),
			CallFunc::create([=]()
			{
				if (!this->isUnlocked && this->passedCount == PuzzleDoorBase::RuneCount)
				{
					this->unlock();
				}
			}),
			nullptr
		)
	));

	this->lockButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->lock(true);
	});

	this->unlockButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->unlock(true);
	});
}

void PuzzleDoorBase::initializePositions()
{
	super::initializePositions();

	this->back->setPosition(Vec2(-4.0f, 128.0f) + PuzzleDoorBase::Offset);
	this->door->setPosition(Vec2(0.0f, 64.0f) + PuzzleDoorBase::Offset);
	this->front->setPosition(Vec2(0.0f, 144.0f) + PuzzleDoorBase::Offset);
	this->indexLabel->setPosition(Vec2(0.0f, 464.0f) + PuzzleDoorBase::Offset);
	this->truthLabel->setPosition(Vec2(284.0f, 104.0f) + PuzzleDoorBase::Offset);
	this->hackableLabel->setPosition(Vec2(-288.0f, 104.0f) + PuzzleDoorBase::Offset);
	this->lockButton->setPosition(Vec2(-64.0f, 212.0f) + PuzzleDoorBase::Offset);
	this->unlockButton->setPosition(Vec2(64.0f, 212.0f) + PuzzleDoorBase::Offset);
	this->doorOpenSound->setPosition(PuzzleDoorBase::Offset);

	for (int index = 0; index < PuzzleDoorBase::RuneCount; index++)
	{
		const Vec2 basePosition = Vec2(-208.0f, 354.0f);

		this->runes[index]->setPosition(basePosition + Vec2(float(index) * 136.0f, 0.0f) + PuzzleDoorBase::Offset);
		this->runesPassed[index]->setPosition(basePosition + Vec2(float(index) * 136.0f, 0.0f) + PuzzleDoorBase::Offset);
		this->runesFailed[index]->setPosition(basePosition + Vec2(float(index) * 136.0f, 0.0f) + PuzzleDoorBase::Offset);
	}
}

void PuzzleDoorBase::initializeListeners()
{
	super::initializeListeners();
}

void PuzzleDoorBase::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();
	
	this->lockButton->setVisible(true);
	this->unlockButton->setVisible(true);
}

void PuzzleDoorBase::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->lockButton->setVisible(false);
	this->unlockButton->setVisible(false);
}

void PuzzleDoorBase::onObjectStateLoaded()
{
	super::onObjectStateLoaded();

	if (this->getObjectStateOrDefault(PuzzleDoorBase::UnlockedSaveKey, Value(false)).asBool())
	{
		this->unlock(false);
	}
	else
	{
		this->lock(false);
	}
}

Vec2 PuzzleDoorBase::getButtonOffset()
{
	return Vec2(-286.0f, -128.0f);
}

HackablePreview* PuzzleDoorBase::createDefaultPreview()
{
	return PuzzleDoorGenericPreview::create();
}

void PuzzleDoorBase::setRealValue(int value)
{
	this->realValue = value;

	this->truthString->setString(std::to_string(value));
}

void PuzzleDoorBase::setHackValue(int value)
{
	this->hackValue = value;

	this->hackableString->setString(std::to_string(value));
}

void PuzzleDoorBase::lock(bool animate)
{
	// Update parent door class lock
	this->setLocked(true);

	this->saveObjectState(PuzzleDoorBase::UnlockedSaveKey, Value(false));

	this->isUnlocked = false;

	this->indexLabel->runAction(FadeTo::create(0.25f, 255));
	this->hackableLabel->runAction(FadeTo::create(0.25f, 255));
	this->truthLabel->runAction(FadeTo::create(0.25f, 255));

	for (int index = 0; index < PuzzleDoorBase::RuneCount; index++)
	{
		this->runes[index]->runAction(FadeTo::create(0.25f, 255));
	}

	Vec2 closedPosition = PuzzleDoorBase::Offset + PuzzleDoorBase::DoorOffset;
	Vec2 openedPosition = PuzzleDoorBase::Offset + PuzzleDoorBase::DoorOffset + PuzzleDoorBase::DoorOpenOffset;
	float currentProgress = (this->door->getPositionY() - closedPosition.y) / (openedPosition.y - closedPosition.y);

	if (animate)
	{
		this->door->stopAllActions();
		this->door->runAction(MoveTo::create(5.0f * currentProgress, closedPosition));
		this->doorOpenSound->play();
	}
	else
	{
		this->door->setPosition(closedPosition);
	}
}

void PuzzleDoorBase::unlock(bool animate)
{
	// Update parent door class lock
	this->setLocked(false);

	this->saveObjectState(PuzzleDoorBase::UnlockedSaveKey, Value(true));

	this->isUnlocked = true;
	this->indexLabel->runAction(FadeTo::create(0.25f, 0));
	this->hackableLabel->runAction(FadeTo::create(0.25f, 0));
	this->truthLabel->runAction(FadeTo::create(0.25f, 0));

	for (int index = 0; index < PuzzleDoorBase::RuneCount; index++)
	{
		this->runes[index]->runAction(FadeTo::create(0.25f, 0));
		this->runesPassed[index]->runAction(FadeTo::create(0.25f, 0));
		this->runesFailed[index]->runAction(FadeTo::create(0.25f, 0));
	}

	Vec2 closedPosition = PuzzleDoorBase::Offset + PuzzleDoorBase::DoorOffset;
	Vec2 openedPosition = PuzzleDoorBase::Offset + PuzzleDoorBase::DoorOffset + PuzzleDoorBase::DoorOpenOffset;
	float currentProgress = 1.0f - (this->door->getPositionY() - closedPosition.y) / (openedPosition.y - closedPosition.y);

	if (animate)
	{
		this->door->stopAllActions();
		this->door->runAction(MoveTo::create(5.0f * currentProgress, openedPosition));
		this->doorOpenSound->play();
	}
	else
	{
		this->door->setPosition(openedPosition);
	}
}
