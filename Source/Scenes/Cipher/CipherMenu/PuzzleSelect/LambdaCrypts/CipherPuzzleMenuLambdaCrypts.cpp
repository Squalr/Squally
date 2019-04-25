#include "CipherPuzzleMenuLambdaCrypts.h"

#include "Engine/GlobalDirector.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

using namespace cocos2d;

CipherPuzzleMenuLambdaCrypts* CipherPuzzleMenuLambdaCrypts::instance = nullptr;
std::string CipherPuzzleMenuLambdaCrypts::ChapterSavekey = "CIPHER_CHAPTER_LAMBDA_CRYPTS";

void CipherPuzzleMenuLambdaCrypts::registerGlobalScene()
{
	if (CipherPuzzleMenuLambdaCrypts::instance == nullptr)
	{
		CipherPuzzleMenuLambdaCrypts::instance = new CipherPuzzleMenuLambdaCrypts();

		CipherPuzzleMenuLambdaCrypts::instance->autorelease();
		CipherPuzzleMenuLambdaCrypts::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherPuzzleMenuLambdaCrypts::instance);
}

CipherPuzzleMenuLambdaCrypts::CipherPuzzleMenuLambdaCrypts() : super(NavigationEvents::NavigateCipherPuzzleSelectArgs::Chapter::LambdaCrypts, CipherPuzzleMenuLambdaCrypts::ChapterSavekey)
{
	this->buildOpponentList();
}

CipherPuzzleMenuLambdaCrypts::~CipherPuzzleMenuLambdaCrypts()
{
}
