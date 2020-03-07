#include "CipherChest.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Input/Input.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/CipherEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Cipher/CipherPuzzleData.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItemDeserializer.h"
#include "Scenes/Platformer/Level/Physics//PlatformerCollisionType.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CipherChest::MapKeyCipherChest = "cipher-chest";
const std::string CipherChest::MapKeyPropertyInputs = "inputs";
const std::string CipherChest::MapKeyPropertyRule = "rule";
const std::string CipherChest::MapKeyPropertyDataType = "data-type";
const std::string CipherChest::MapKeyPropertyTokens = "tokens";
const std::string CipherChest::MapKeyPropertyTutorial = "tutorial";

CipherChest* CipherChest::create(ValueMap& properties)
{
	CipherChest* instance = new CipherChest(properties);

	instance->autorelease();

	return instance;
}

CipherChest::CipherChest(ValueMap& properties) : super(properties, Size(128.0f, 96.0f))
{
	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::Interactive_Chests_CipherChestOpened);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::Interactive_Chests_CipherChestClosed);
	this->cipherPuzzleData = this->buildPuzzleData();

	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);
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
	// Intentionally do not call super here. Overriding default behavior of giving items.

	CipherEvents::TriggerOpenCipher(CipherEvents::CipherOpenArgs(this->cipherPuzzleData));
}

CipherPuzzleData* CipherChest::buildPuzzleData()
{
	auto getChar = [&](std::string input, std::string dataType)
	{
		if (dataType == "decimal" || dataType == "dec")
		{
			if (MathUtils::isInteger(input))
			{
				return (unsigned char)(std::stoi(input));
			}
		}
		else if (dataType == "binary" || dataType == "bin")
		{
			/*
			if (StrUtils::isBinaryNumber(input))
			{
				return (unsigned char)StrUtils::BinToInt(input);
			}*/
		}
		else if (dataType == "hexadecimal" || dataType == "hex")
		{
			if (StrUtils::isHexNumber(input))
			{
				return (unsigned char)StrUtils::HexToInt(input);
			}
		}

		if (input.size() == 1)
		{
			return (unsigned char)(input[0]);
		}
		
		return (unsigned char)(0);
	};

	auto applyRule = [&](unsigned char input, std::string rule)
	{
		std::string expression = StrUtils::replaceAll(rule, "{i}", std::to_string(input));

		// The math library we use expects single character operators, so we map our operators to theirs
		expression = StrUtils::replaceAll(expression, "<<<", "q");
		expression = StrUtils::replaceAll(expression, ">>>", "p");
		expression = StrUtils::replaceAll(expression, "<<", "<");
		expression = StrUtils::replaceAll(expression, ">>", ">");
		
		return (unsigned char)(MathUtils::resolveBinaryMathExpression(expression));
	};

	std::string rule = GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyRule, Value("")).asString();
	std::string dataType = StrUtils::toLower(GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyDataType, Value("ascii")).asString());
	std::vector<std::string> inputs = StrUtils::splitOn(
		GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyInputs, Value("")).asString(), ", ", false
	);
	std::vector<std::string> tokens = StrUtils::splitOn(
		GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyTokens, Value("")).asString(), ", ", false
	);

	std::string tutorial = GameUtils::getKeyOrDefault(this->properties, CipherChest::MapKeyPropertyTutorial, Value("")).asString();
	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMap = std::vector<std::tuple<unsigned char, unsigned char>>();

	for (auto it = inputs.begin(); it != inputs.end(); it++)
	{
		unsigned char input = getChar(*it, dataType);
		unsigned char output = applyRule(input, rule);

		inputOutputMap.push_back(std::tuple<unsigned char, unsigned char>(input, output));
	}

	return CipherPuzzleData::create(inputOutputMap, tokens, dataType, tutorial, [=](CipherPuzzleData* puzzleData)
	{
		this->performUnlockAndGiveItems();
	});
}
