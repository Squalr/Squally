////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuVoidStar.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Npcs/VoidStar/Atreus.h"
#include "Entities/Platformer/Npcs/VoidStar/Elriel.h"
#include "Entities/Platformer/Npcs/VoidStar/Illia.h"
#include "Entities/Platformer/Npcs/VoidStar/Leon.h"
#include "Entities/Platformer/Npcs/VoidStar/Mara.h"
#include "Entities/Platformer/Npcs/VoidStar/Marcel.h"
#include "Entities/Platformer/Npcs/VoidStar/Piper.h"
#include "Entities/Platformer/Npcs/VoidStar/QueenElise.h"
#include "Entities/Platformer/Npcs/VoidStar/Radon.h"
#include "Entities/Platformer/Npcs/VoidStar/Thor.h"
#include "Entities/Platformer/Npcs/VoidStar/Xenon.h"
#include "Entities/Platformer/Npcs/VoidStar/Ysara.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Entities/Platformer/Npcs/VoidStar/Atreus.h"
#include "Entities/Platformer/Npcs/VoidStar/Elriel.h"
#include "Entities/Platformer/Npcs/VoidStar/Illia.h"
#include "Entities/Platformer/Npcs/VoidStar/Leon.h"
#include "Entities/Platformer/Npcs/VoidStar/Mara.h"
#include "Entities/Platformer/Npcs/VoidStar/Marcel.h"
#include "Entities/Platformer/Npcs/VoidStar/Piper.h"
#include "Entities/Platformer/Npcs/VoidStar/QueenElise.h"
#include "Entities/Platformer/Npcs/VoidStar/Radon.h"
#include "Entities/Platformer/Npcs/VoidStar/Thor.h"
#include "Entities/Platformer/Npcs/VoidStar/Xenon.h"
#include "Entities/Platformer/Npcs/VoidStar/Ysara.h"
#include "Scenes/Hexus/Menus/ChapterSelect/VoidStar/HexusChapterPreviewVoidStar.h"

using namespace cocos2d;

HexusOpponentMenuVoidStar* HexusOpponentMenuVoidStar::instance = nullptr;

void HexusOpponentMenuVoidStar::registerGlobalScene()
{
	if (HexusOpponentMenuVoidStar::instance == nullptr)
	{
		HexusOpponentMenuVoidStar::instance = new HexusOpponentMenuVoidStar();

		HexusOpponentMenuVoidStar::instance->autorelease();
		HexusOpponentMenuVoidStar::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuVoidStar::instance);
}

HexusOpponentMenuVoidStar::HexusOpponentMenuVoidStar() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::VoidStar, HexusChapterPreviewVoidStar::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Atreus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Elriel::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Illia::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Leon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mara::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Marcel::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Piper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(QueenElise::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Radon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Thor::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Xenon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ysara::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuVoidStar::~HexusOpponentMenuVoidStar()
{
}
