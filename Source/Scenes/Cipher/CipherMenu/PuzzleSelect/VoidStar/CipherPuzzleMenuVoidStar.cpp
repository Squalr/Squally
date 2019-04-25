#include "CipherPuzzleMenuVoidStar.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

using namespace cocos2d;

CipherPuzzleMenuVoidStar* CipherPuzzleMenuVoidStar::instance = nullptr;
std::string CipherPuzzleMenuVoidStar::ChapterSavekey = "CIPHER_CHAPTER_VOID_STAR";

void CipherPuzzleMenuVoidStar::registerGlobalScene()
{
	if (CipherPuzzleMenuVoidStar::instance == nullptr)
	{
		CipherPuzzleMenuVoidStar::instance = new CipherPuzzleMenuVoidStar();

		CipherPuzzleMenuVoidStar::instance->autorelease();
		CipherPuzzleMenuVoidStar::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuVoidStar::instance);
}

CipherPuzzleMenuVoidStar::CipherPuzzleMenuVoidStar() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::VoidStar, CipherPuzzleMenuVoidStar::ChapterSavekey)
{
	this->buildOpponentList();
}

CipherPuzzleMenuVoidStar::~CipherPuzzleMenuVoidStar()
{
}
