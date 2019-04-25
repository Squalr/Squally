#include "CipherPuzzleMenuUnderflowRuins.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

using namespace cocos2d;

CipherPuzzleMenuUnderflowRuins* CipherPuzzleMenuUnderflowRuins::instance = nullptr;
std::string CipherPuzzleMenuUnderflowRuins::ChapterSavekey = "CIPHER_CHAPTER_UNDERFLOW_RUINS";

void CipherPuzzleMenuUnderflowRuins::registerGlobalScene()
{
	if (CipherPuzzleMenuUnderflowRuins::instance == nullptr)
	{
		CipherPuzzleMenuUnderflowRuins::instance = new CipherPuzzleMenuUnderflowRuins();

		CipherPuzzleMenuUnderflowRuins::instance->autorelease();
		CipherPuzzleMenuUnderflowRuins::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuUnderflowRuins::instance);
}

CipherPuzzleMenuUnderflowRuins::CipherPuzzleMenuUnderflowRuins() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::UnderflowRuins, CipherPuzzleMenuUnderflowRuins::ChapterSavekey)
{
	this->buildCipherList();
}

CipherPuzzleMenuUnderflowRuins::~CipherPuzzleMenuUnderflowRuins()
{
}
