#include "CipherPuzzleMenuBalmerPeaks.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

using namespace cocos2d;

CipherPuzzleMenuBalmerPeaks* CipherPuzzleMenuBalmerPeaks::instance = nullptr;
std::string CipherPuzzleMenuBalmerPeaks::ChapterSavekey = "CIPHER_CHAPTER_BALMER_PEAKS";

void CipherPuzzleMenuBalmerPeaks::registerGlobalScene()
{
	if (CipherPuzzleMenuBalmerPeaks::instance == nullptr)
	{
		CipherPuzzleMenuBalmerPeaks::instance = new CipherPuzzleMenuBalmerPeaks();

		CipherPuzzleMenuBalmerPeaks::instance->autorelease();
		CipherPuzzleMenuBalmerPeaks::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuBalmerPeaks::instance);
}

CipherPuzzleMenuBalmerPeaks::CipherPuzzleMenuBalmerPeaks() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::BalmerPeaks, CipherPuzzleMenuBalmerPeaks::ChapterSavekey)
{
	// this->opponents.push_back(CipherPuzzleData::create());

	this->buildOpponentList();
}

CipherPuzzleMenuBalmerPeaks::~CipherPuzzleMenuBalmerPeaks()
{
}
