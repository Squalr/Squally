#include "CipherChest.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Input/Input.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/CipherEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Cipher/CipherPuzzleData.h"
#include "Scenes/Platformer/Level/Physics//PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CipherChest::MapKeyCipherChest = "cipher-chest";
const std::string CipherChest::MapKeyPropertyInputsEasy = "inputs-easy";
const std::string CipherChest::MapKeyPropertyInputsHard = "inputs-hard";
const std::string CipherChest::MapKeyPropertyRuleEasy = "rule-easy";
const std::string CipherChest::MapKeyPropertyRuleHard = "rule-hard";
const std::string CipherChest::MapKeyPropertyRewards = "rewards";
const std::string CipherChest::MapKeyPropertyBonusReward = "bonus-reward";
const std::string CipherChest::MapKeyPropertyTokensEasy = "tokens-easy";
const std::string CipherChest::MapKeyPropertyTokensHard = "tokens-hard";

CipherChest* CipherChest::create(cocos2d::ValueMap& properties)
{
	CipherChest* instance = new CipherChest(properties);

	instance->autorelease();

	return instance;
}

CipherChest::CipherChest(cocos2d::ValueMap& properties) : super(properties)
{
	this->cipherPuzzleData = this->buildPuzzleData();

	this->addChild(this->cipherPuzzleData);
}

CipherChest::~CipherChest()
{
}

void CipherChest::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CipherChest::initializePositions()
{
	super::initializePositions();
}

void CipherChest::initializeListeners()
{
	super::initializeListeners();
}

void CipherChest::onInteract()
{
	CipherEvents::TriggerOpenCipher(CipherEvents::CipherOpenArgs(this->cipherPuzzleData, [=]()
	{
		// On success
	}));
}

CipherPuzzleData* CipherChest::buildPuzzleData()
{
	auto getChar = [&](std::string input)
	{
		if (input.size() == 1)
		{
			return (unsigned char)(input[0]);
		}
		else if (MathUtils::isInteger(input))
		{
			int intVal = std::stoi(input);
			return (unsigned char)(intVal);
		}
		
		return (unsigned char)(0);
	};

	auto applyRule = [&](unsigned char input, std::string rule)
	{
		std::string expression = StrUtils::replaceAll(rule, "{i}", std::to_string(input));
		
		return (unsigned char)(MathUtils::resolveBinaryMathExpression(expression));
	};

	std::string easyRule = GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyRuleEasy, Value("")).asString();
	std::string hardRule = GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyRuleHard, Value("")).asString();
	std::vector<std::string> easyInputs = StrUtils::splitOn(
		GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyInputsEasy, Value("")).asString(), ", ", false
	);
	std::vector<std::string> hardInputs = StrUtils::splitOn(
		GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyInputsHard, Value("")).asString(), ", ", false
	);
	std::vector<std::string> easyTokens = StrUtils::splitOn(
		GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyTokensEasy, Value("")).asString(), ", ", false
	);
	std::vector<std::string> hardTokens = StrUtils::splitOn(
		GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyTokensHard, Value("")).asString(), ", ", false
	);
	std::vector<std::string> rewards = StrUtils::splitOn(
		GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyRewards, Value("")).asString(), ", ", false
	);
	std::string bonusRewards = GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyBonusReward, Value("")).asString();
	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy = std::vector<std::tuple<unsigned char, unsigned char>>();
	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard = std::vector<std::tuple<unsigned char, unsigned char>>();

	for (auto it = easyInputs.begin(); it != easyInputs.end(); it++)
	{
		unsigned char input = getChar(*it);
		unsigned char output = applyRule(input, easyRule);

		inputOutputMapEasy.push_back(std::tuple<unsigned char, unsigned char>(input, output));
	}

	for (auto it = hardInputs.begin(); it != hardInputs.end(); it++)
	{
		unsigned char input = getChar(*it);
		unsigned char output = applyRule(input, hardRule);

		inputOutputMapHard.push_back(std::tuple<unsigned char, unsigned char>(input, output));
	}

	return CipherPuzzleData::create(inputOutputMapEasy, inputOutputMapHard, easyTokens, hardTokens, rewards, bonusRewards);
}
