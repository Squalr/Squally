#include "CipherPuzzleDeserializer.h"

#include <limits>

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

using namespace cocos2d;
using namespace rapidjson;

CipherPuzzleDeserializer* CipherPuzzleDeserializer::instance = nullptr;

void CipherPuzzleDeserializer::registerGlobalNode()
{
	if (CipherPuzzleDeserializer::instance == nullptr)
	{
		CipherPuzzleDeserializer::instance = new CipherPuzzleDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(CipherPuzzleDeserializer::instance);
	}
}

void CipherPuzzleDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		CipherEvents::EventLoadCipher,
		[=](EventCustom* args) { this->onDeserializationRequest(static_cast<CipherEvents::CipherOpenArgs*>(args->getUserData())); }
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void CipherPuzzleDeserializer::onDeserializationRequest(CipherEvents::CipherOpenArgs* args)
{
	CipherPuzzleData* puzzle = nullptr;
	std::string json = args->cipherJson;

	Document document;
	document.Parse(json.c_str());

	if (!document.HasMember("easy") || !document["easy"].IsObject())
	{
		CCLOG("Missing or invalid key 'easy' on cipher json.");
		return;
	}

	if (!document["easy"].HasMember("rule") || !document["easy"]["rule"].IsString())
	{
		CCLOG("Missing or invalid key 'rule' for easy puzzle.");
		return;
	}

	if (!document["easy"].HasMember("inputs") || !document["easy"]["inputs"].IsArray())
	{
		CCLOG("Missing or invalid key 'inputs' for easy puzzle.");
		return;
	}

	if (!document.HasMember("hard") || !document["hard"].IsObject())
	{
		CCLOG("Missing or invalid key 'hard' on cipher json.");
		return;
	}

	if (!document["hard"].HasMember("rule") || !document["hard"]["rule"].IsString())
	{
		CCLOG("Missing or invalid key 'rule' for hard puzzle.");
		return;
	}

	if (!document["hard"].HasMember("inputs") || !document["hard"]["inputs"].IsArray())
	{
		CCLOG("Missing or invalid key 'inputs' for hard puzzle.");
		return;
	}

	if (!document.HasMember("rewards") || !document["rewards"].IsArray())
	{
		CCLOG("Missing or invalid key 'rewards' on cipher json.");
		return;
	}

	if (!document.HasMember("bonus-rewards") || !document["bonus-rewards"].IsArray())
	{
		CCLOG("Missing or invalid key 'bonus-rewards' on cipher json.");
		return;
	}

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

	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapEasy = std::vector<std::tuple<unsigned char, unsigned char>>();
	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMapHard = std::vector<std::tuple<unsigned char, unsigned char>>();
	std::vector<std::string> rewards = std::vector<std::string>();
	std::vector<std::string> bonusRewards = std::vector<std::string>();
	std::string easyRule = document["easy"]["rule"].GetString();
	std::string hardRule = document["hard"]["rule"].GetString();

	for (SizeType index = 0; index < document["easy"]["inputs"].Size(); index++)
	{
		if (document["easy"]["inputs"][index].IsString())
		{
			unsigned char input = getChar(document["easy"]["inputs"][index].GetString());
			unsigned char output = applyRule(input, easyRule);

			inputOutputMapEasy.push_back(std::tuple<unsigned char, unsigned char>(input, output));
		}
	}

	for (SizeType index = 0; index < document["hard"]["inputs"].Size(); index++)
	{
		if (document["hard"]["inputs"][index].IsString())
		{
			unsigned char input = getChar(document["hard"]["inputs"][index].GetString());
			unsigned char output = applyRule(input, hardRule);

			inputOutputMapHard.push_back(std::tuple<unsigned char, unsigned char>(input, output));
		}
	}

	for (SizeType index = 0; index < document["rewards"].Size(); index++)
	{
		if (document["rewards"][index].IsString())
		{
			rewards.push_back(document["rewards"][index].GetString());	
		}
	}

	for (SizeType index = 0; index < document["bonus-rewards"].Size(); index++)
	{
		if (document["bonus-rewards"][index].IsString())
		{
			rewards.push_back(document["bonus-rewards"][index].GetString());	
		}
	}

	puzzle = CipherPuzzleData::create(inputOutputMapEasy, inputOutputMapHard, rewards, bonusRewards, args->isHardMode);

	if (puzzle != nullptr)
	{
		CipherEvents::TriggerOpenCipher(CipherEvents::CipherLoadArgs(puzzle));
	}
}
