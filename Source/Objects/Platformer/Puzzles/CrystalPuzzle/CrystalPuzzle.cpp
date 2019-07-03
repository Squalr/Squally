#include "CrystalPuzzle.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Puzzles/CrystalPuzzle/CrystalPuzzleGenericPreview.h"
#include "Objects/Platformer/Puzzles/CrystalPuzzle/CrystalPuzzleIncrementPreview.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/DecorResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/Puzzles/Crystal/PuzzleIncrement/PuzzleIncrement.h"
#include "Strings/Hacking/Objects/Puzzles/Crystal/PuzzleIncrement/RegisterEcx.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string CrystalPuzzle::MapKeyCrystalPuzzle = "crystal-puzzle";

CrystalPuzzle* CrystalPuzzle::create(ValueMap& initProperties)
{
	CrystalPuzzle* instance = new CrystalPuzzle(initProperties);

	instance->autorelease();

	return instance;
}

CrystalPuzzle::CrystalPuzzle(ValueMap& initProperties) : super(initProperties)
{
	this->truthCrystal = SmartAnimationSequenceNode::create(ObjectResources::Puzzles_CrystalPuzzle_CrystalBlack);
	this->hackableCrystalNode = Node::create();
	this->hackableCrystalSprites = std::vector<Sprite*>();
	this->gateLeft = Sprite::create(ObjectResources::Doors_Gate_GateLeft);
	this->gateRight = Sprite::create(ObjectResources::Doors_Gate_GateRight);
	this->postLeft = Sprite::create(DecorResources::Crypts_Post1);
	this->postRight = Sprite::create(DecorResources::Crypts_Post2);
	this->isUnlocked = false;

	this->hackableCrystalSprites.push_back(Sprite::create(ObjectResources::Puzzles_CrystalPuzzle_OrbBlack));
	this->hackableCrystalSprites.push_back(Sprite::create(ObjectResources::Puzzles_CrystalPuzzle_OrbBlue));
	this->hackableCrystalSprites.push_back(Sprite::create(ObjectResources::Puzzles_CrystalPuzzle_OrbCyan));
	this->hackableCrystalSprites.push_back(Sprite::create(ObjectResources::Puzzles_CrystalPuzzle_OrbGreen));
	this->hackableCrystalSprites.push_back(Sprite::create(ObjectResources::Puzzles_CrystalPuzzle_OrbOrange));
	this->hackableCrystalSprites.push_back(Sprite::create(ObjectResources::Puzzles_CrystalPuzzle_OrbPink));
	this->hackableCrystalSprites.push_back(Sprite::create(ObjectResources::Puzzles_CrystalPuzzle_OrbPurple));
	this->hackableCrystalSprites.push_back(Sprite::create(ObjectResources::Puzzles_CrystalPuzzle_OrbRed));

	this->hackableIndex = 0;
	this->nextHackableIndex = 0;

	this->showActiveHackableCrystal();

	for (auto it = this->hackableCrystalSprites.begin(); it != this->hackableCrystalSprites.end(); it++)
	{
		this->hackableCrystalNode->addChild(*it);
	}

	this->addChild(this->gateLeft);
	this->addChild(this->gateRight);
	this->addChild(this->postLeft);
	this->addChild(this->postRight);
	this->addChild(this->truthCrystal);
	this->addChild(this->hackableCrystalNode);
}

CrystalPuzzle::~CrystalPuzzle()
{
}

void CrystalPuzzle::onEnter()
{
	super::onEnter();

	this->truthCrystal->playAnimationRepeat(
		{
			ObjectResources::Puzzles_CrystalPuzzle_CrystalBlack,
			ObjectResources::Puzzles_CrystalPuzzle_CrystalBlue,
			ObjectResources::Puzzles_CrystalPuzzle_CrystalCyan,
			ObjectResources::Puzzles_CrystalPuzzle_CrystalGreen,
			ObjectResources::Puzzles_CrystalPuzzle_CrystalOrange,
			ObjectResources::Puzzles_CrystalPuzzle_CrystalPink,
			ObjectResources::Puzzles_CrystalPuzzle_CrystalPurple,
			ObjectResources::Puzzles_CrystalPuzzle_CrystalRed
		}, 1.0f, 0.0f);
	this->truthCrystal->getForwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		if (isUnlocked)
		{
			this->hackableIndex = 0;
			this->showActiveHackableCrystal();

			return 0;
		}
		else
		{
			int nextCount = current + 1;
			this->hackableIndex = this->nextHackableIndex;
			
			this->incrementCrystalPuzzleAnimation();
			this->showActiveHackableCrystal();

			if (current == this->hackableIndex)
			{
				// Match!
			}

			return nextCount;
		}
	};

	for (auto it = this->hackableCrystalSprites.begin(); it != this->hackableCrystalSprites.end(); it++)
	{
		(*it)->setVisible(false);
	}
}

void CrystalPuzzle::initializePositions()
{
	super::initializePositions();

	const Vec2 offset = Vec2(0.0f, 72.0f);

	this->hackableCrystalNode->setPosition(Vec2(-212.0f, 144.0f) + offset);
	this->gateLeft->setPosition(Vec2(-136.0f, 0.0f) + offset);
	this->postLeft->setPosition(Vec2(-212.0f, -80.0f) + offset);
	this->truthCrystal->setPosition(Vec2(212.0f, 144.0f) + offset);
	this->gateRight->setPosition(Vec2(136.0f, 0.0f) + offset);
	this->postRight->setPosition(Vec2(212.0f, -80.0f) + offset);
}

Vec2 CrystalPuzzle::getButtonOffset()
{
	return Vec2(-128.0f, 128.0f);
}

void CrystalPuzzle::registerHackables()
{
	super::registerHackables();

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::LateBindData(
				CrystalPuzzle::MapKeyCrystalPuzzle,
				Strings::Hacking_Objects_Puzzles_Crystal_PuzzleIncrement_PuzzleIncrement::create(),
				UIResources::Menus_Icons_BleedingLimb,
				CrystalPuzzleIncrementPreview::create(),
				{
					{ HackableCode::Register::zcx, Strings::Hacking_Objects_Puzzles_Crystal_PuzzleIncrement_RegisterEcx::create() },
				},
				1,
				20.0f
			)
		},
	};

	auto incrementAnimationFunc = &CrystalPuzzle::incrementCrystalPuzzleAnimation;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)incrementAnimationFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

HackablePreview* CrystalPuzzle::createDefaultPreview()
{
	return CrystalPuzzleGenericPreview::create();
}

void CrystalPuzzle::showActiveHackableCrystal()
{
	for (auto it = this->hackableCrystalSprites.begin(); it != this->hackableCrystalSprites.end(); it++)
	{
		(*it)->setVisible(false);
	}

	if (!this->hackableCrystalSprites.empty())
	{
		int index = MathUtils::wrappingNormalize(this->hackableIndex, 0, this->hackableCrystalSprites.size() - 1);

		this->hackableCrystalSprites[index]->setVisible(true);
	}
}

NO_OPTIMIZE void CrystalPuzzle::incrementCrystalPuzzleAnimation()
{
	int countLocal = this->hackableIndex;

	ASM(push ZCX)
	ASM_MOV_REG_VAR(ZCX, countLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME);
	ASM(inc ZCX)
	ASM_NOP6();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(countLocal, ZCX);
	ASM(pop ZCX);

	this->nextHackableIndex = MathUtils::wrappingNormalize(countLocal, 0, this->hackableCrystalSprites.size() - 1);

	HACKABLES_STOP_SEARCH();
}
