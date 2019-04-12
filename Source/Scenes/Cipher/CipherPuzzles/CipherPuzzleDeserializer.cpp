#include "CipherPuzzleDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzles.h"

using namespace cocos2d;

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
		[=](EventCustom* args) { this->onDeserializationRequest(static_cast<CipherEvents::CipherLoadArgs*>(args->getUserData())); }
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void CipherPuzzleDeserializer::onDeserializationRequest(CipherEvents::CipherLoadArgs* args)
{
	CipherPuzzleData* puzzle = nullptr;

	if (args->cipherName == CipherPuzzleAtbash::MapKeyAtbash)
	{
		puzzle = CipherPuzzleAtbash::create();
	}
	else if (args->cipherName == CipherPuzzleRot13::MapKeyRot13)
	{
		puzzle = CipherPuzzleRot13::create();
	}
	else
	{
		CCLOG("Unknown cipher name in cipher event");
	}

	if (puzzle != nullptr)
	{
		CipherEvents::TriggerOpenCipher(CipherEvents::CipherOpenArgs(puzzle));
	}
}
