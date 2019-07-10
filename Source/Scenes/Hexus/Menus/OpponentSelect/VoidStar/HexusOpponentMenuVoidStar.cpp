#include "HexusOpponentMenuVoidStar.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Npcs/VoidStar/Atreus.h"
#include "Entities/Platformer/Npcs/VoidStar/Bancroft.h"
#include "Entities/Platformer/Npcs/VoidStar/Godiva.h"
#include "Entities/Platformer/Npcs/VoidStar/Illia.h"
#include "Entities/Platformer/Npcs/VoidStar/Leon.h"
#include "Entities/Platformer/Npcs/VoidStar/Mara.h"
#include "Entities/Platformer/Npcs/VoidStar/Marcel.h"
#include "Entities/Platformer/Npcs/VoidStar/Piper.h"
#include "Entities/Platformer/Npcs/VoidStar/QueenElise.h"
#include "Entities/Platformer/Npcs/VoidStar/Radon.h"
#include "Entities/Platformer/Npcs/VoidStar/Ralston.h"
#include "Entities/Platformer/Npcs/VoidStar/Xenon.h"
#include "Entities/Platformer/Npcs/VoidStar/Ysara.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/VoidStar/HexusChapterPreviewVoidStar.h"

using namespace cocos2d;

HexusOpponentMenuVoidStar* HexusOpponentMenuVoidStar::instance = nullptr;

HexusOpponentMenuVoidStar* HexusOpponentMenuVoidStar::getInstance()
{
	if (HexusOpponentMenuVoidStar::instance == nullptr)
	{
		HexusOpponentMenuVoidStar::instance = new HexusOpponentMenuVoidStar();

		HexusOpponentMenuVoidStar::instance->autorelease();
		GlobalDirector::registerGlobalScene(HexusOpponentMenuVoidStar::instance);
	}

	return HexusOpponentMenuVoidStar::instance;
}

HexusOpponentMenuVoidStar::HexusOpponentMenuVoidStar() : super(HexusChapterPreviewVoidStar::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Atreus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Bancroft::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Godiva::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Illia::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Leon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mara::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Marcel::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Piper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(QueenElise::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Radon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ralston::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Xenon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ysara::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuVoidStar::~HexusOpponentMenuVoidStar()
{
}
