#include "HexusOpponentMenuTrainingPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Training/HexusChapterPreviewTrainingPuzzle.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/PuzzleTutorials/TutorialHexusPuzzleOpponents.h"

using namespace cocos2d;

HexusOpponentMenuTrainingPuzzle* HexusOpponentMenuTrainingPuzzle::instance = nullptr;

void HexusOpponentMenuTrainingPuzzle::registerGlobalScene()
{
	if (HexusOpponentMenuTrainingPuzzle::instance == nullptr)
	{
		HexusOpponentMenuTrainingPuzzle::instance = new HexusOpponentMenuTrainingPuzzle();

		HexusOpponentMenuTrainingPuzzle::instance->autorelease();
		HexusOpponentMenuTrainingPuzzle::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuTrainingPuzzle::instance);
}

HexusOpponentMenuTrainingPuzzle::HexusOpponentMenuTrainingPuzzle() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleTraining, HexusChapterPreviewTrainingPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPuzzleTutorialA::getInstance()));

	this->buildOpponentList();
}

HexusOpponentMenuTrainingPuzzle::~HexusOpponentMenuTrainingPuzzle()
{
}
