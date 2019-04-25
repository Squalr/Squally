#include "CipherPuzzleMenuEndianForest.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

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
	this->buildOpponentList();
}

CipherPuzzleMenuEndianForest::~CipherPuzzleMenuEndianForest()
{
}
