#include "CipherPuzzleMenuCastleValgrind.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

using namespace cocos2d;

CipherPuzzleMenuCastleValgrind* CipherPuzzleMenuCastleValgrind::instance = nullptr;
std::string CipherPuzzleMenuCastleValgrind::ChapterSavekey = "CIPHER_CHAPTER_CASTLE_VALGRIND";

void CipherPuzzleMenuCastleValgrind::registerGlobalScene()
{
	if (CipherPuzzleMenuCastleValgrind::instance == nullptr)
	{
		CipherPuzzleMenuCastleValgrind::instance = new CipherPuzzleMenuCastleValgrind();

		CipherPuzzleMenuCastleValgrind::instance->autorelease();
		CipherPuzzleMenuCastleValgrind::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuCastleValgrind::instance);
}

CipherPuzzleMenuCastleValgrind::CipherPuzzleMenuCastleValgrind() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::CastleValgrind, CipherPuzzleMenuCastleValgrind::ChapterSavekey)
{
	this->buildCipherList();
}

CipherPuzzleMenuCastleValgrind::~CipherPuzzleMenuCastleValgrind()
{
}
