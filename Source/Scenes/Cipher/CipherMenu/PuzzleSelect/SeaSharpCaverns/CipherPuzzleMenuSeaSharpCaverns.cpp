#include "CipherPuzzleMenuSeaSharpCaverns.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

using namespace cocos2d;

CipherPuzzleMenuSeaSharpCaverns* CipherPuzzleMenuSeaSharpCaverns::instance = nullptr;
std::string CipherPuzzleMenuSeaSharpCaverns::ChapterSavekey = "CIPHER_CHAPTER_SEA_SHARP_CAVERNS";

void CipherPuzzleMenuSeaSharpCaverns::registerGlobalScene()
{
	if (CipherPuzzleMenuSeaSharpCaverns::instance == nullptr)
	{
		CipherPuzzleMenuSeaSharpCaverns::instance = new CipherPuzzleMenuSeaSharpCaverns();

		CipherPuzzleMenuSeaSharpCaverns::instance->autorelease();
		CipherPuzzleMenuSeaSharpCaverns::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuSeaSharpCaverns::instance);
}

CipherPuzzleMenuSeaSharpCaverns::CipherPuzzleMenuSeaSharpCaverns() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::SeaSharpCaverns, CipherPuzzleMenuSeaSharpCaverns::ChapterSavekey)
{
	this->buildOpponentList();
}

CipherPuzzleMenuSeaSharpCaverns::~CipherPuzzleMenuSeaSharpCaverns()
{
}
