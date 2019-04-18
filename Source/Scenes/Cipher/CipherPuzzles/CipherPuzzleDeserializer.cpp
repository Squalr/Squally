#include "CipherPuzzleDeserializer.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
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

	if (!document.HasMember("hard") || !document["hard"].IsObject())
	{
		CCLOG("Missing or invalid key 'hard' on cipher json.");
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

	std::vector<std::tuple<std::string, std::string>> inputOutputMapEasy = std::vector<std::tuple<std::string, std::string>>();
	std::vector<std::tuple<std::string, std::string>> inputOutputMapHard = std::vector<std::tuple<std::string, std::string>>();
	std::vector<std::string> rewards = std::vector<std::string>();
	std::vector<std::string> bonusRewards = std::vector<std::string>();

	for (rapidjson::Value::ConstMemberIterator itr = document["easy"].MemberBegin(); itr != document["easy"].MemberEnd(); ++itr)
	{
		if (itr->value.IsString())
		{
			std::string key = itr->name.GetString();
			std::string value = itr->value.GetString();

			inputOutputMapEasy.push_back(std::tuple<std::string, std::string>(key, value));
		}
	}

	for (rapidjson::Value::ConstMemberIterator itr = document["hard"].MemberBegin(); itr != document["hard"].MemberEnd(); ++itr)
	{
		if (itr->value.IsString())
		{
			std::string key = itr->name.GetString();
			std::string value = itr->value.GetString();

			inputOutputMapHard.push_back(std::tuple<std::string, std::string>(key, value));
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
