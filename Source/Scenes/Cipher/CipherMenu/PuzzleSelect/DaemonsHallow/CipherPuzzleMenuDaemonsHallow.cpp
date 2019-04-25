#include "CipherPuzzleMenuDaemonsHallow.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

using namespace cocos2d;

CipherPuzzleMenuDaemonsHallow* CipherPuzzleMenuDaemonsHallow::instance = nullptr;
std::string CipherPuzzleMenuDaemonsHallow::ChapterSavekey = "CIPHER_CHAPTER_DAEMONS_HALLOW";

void CipherPuzzleMenuDaemonsHallow::registerGlobalScene()
{
	if (CipherPuzzleMenuDaemonsHallow::instance == nullptr)
	{
		CipherPuzzleMenuDaemonsHallow::instance = new CipherPuzzleMenuDaemonsHallow();

		CipherPuzzleMenuDaemonsHallow::instance->autorelease();
		CipherPuzzleMenuDaemonsHallow::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuDaemonsHallow::instance);
}

CipherPuzzleMenuDaemonsHallow::CipherPuzzleMenuDaemonsHallow() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::DaemonsHallow, CipherPuzzleMenuDaemonsHallow::ChapterSavekey)
{
	this->buildCipherList();
}

CipherPuzzleMenuDaemonsHallow::~CipherPuzzleMenuDaemonsHallow()
{
}
