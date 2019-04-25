#include "CipherPuzzleMenuEndianForest.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzlePreview.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleDeserializer.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherPuzzleMenuEndianForest* CipherPuzzleMenuEndianForest::instance = nullptr;
std::string CipherPuzzleMenuEndianForest::ChapterSavekey = "CIPHER_CHAPTER_ENDIAN_FOREST";

void CipherPuzzleMenuEndianForest::registerGlobalScene()
{
	if (CipherPuzzleMenuEndianForest::instance == nullptr)
	{
		CipherPuzzleMenuEndianForest::instance = new CipherPuzzleMenuEndianForest();

		CipherPuzzleMenuEndianForest::instance->autorelease();
		CipherPuzzleMenuEndianForest::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuEndianForest::instance);
}

CipherPuzzleMenuEndianForest::CipherPuzzleMenuEndianForest() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::EndianForest, CipherPuzzleMenuEndianForest::ChapterSavekey)
{
	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_EndianForest_Chest0,
		CipherResources::Menus_EndianForest_Chest0,
		CipherResources::Menus_EndianForest_Chest0
	));

	this->buildOpponentList();
}

CipherPuzzleMenuEndianForest::~CipherPuzzleMenuEndianForest()
{
}
