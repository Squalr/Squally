////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuLambdaCrypts.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Amelia.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Azmus.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Garrick.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Johann.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Necron.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/PrincessNebea.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Roger.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Thion.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Ursula.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Viper.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Zana.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Zelina.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Amelia.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Azmus.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Garrick.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Johann.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Necron.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/PrincessNebea.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Roger.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Thion.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Ursula.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Viper.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Zana.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Zelina.h"
#include "Scenes/Hexus/Menus/ChapterSelect/LambdaCrypts/HexusChapterPreviewLambdaCrypts.h"

using namespace cocos2d;

HexusOpponentMenuLambdaCrypts* HexusOpponentMenuLambdaCrypts::instance = nullptr;

void HexusOpponentMenuLambdaCrypts::registerGlobalScene()
{
	if (HexusOpponentMenuLambdaCrypts::instance == nullptr)
	{
		HexusOpponentMenuLambdaCrypts::instance = new HexusOpponentMenuLambdaCrypts();

		HexusOpponentMenuLambdaCrypts::instance->autorelease();
		HexusOpponentMenuLambdaCrypts::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuLambdaCrypts::instance);
}

HexusOpponentMenuLambdaCrypts::HexusOpponentMenuLambdaCrypts() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::LambdaCrypts, HexusChapterPreviewLambdaCrypts::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Amelia::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Azmus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Garrick::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Johann::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Necron::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PrincessNebea::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Roger::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Thion::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ursula::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Viper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Zana::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Zelina::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuLambdaCrypts::~HexusOpponentMenuLambdaCrypts()
{
}
