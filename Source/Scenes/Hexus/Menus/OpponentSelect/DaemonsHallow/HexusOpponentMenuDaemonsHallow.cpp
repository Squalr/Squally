#include "HexusOpponentMenuDaemonsHallow.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Ash.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Brine.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Celeste.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Cindra.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Drak.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Igneus.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Lucifer.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Magnus.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Pan.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/PrincessMittens.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Ragnis.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Rupert.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Rusty.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Scaldor.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/DaemonsHallow/HexusChapterPreviewDaemonsHallow.h"

using namespace cocos2d;

HexusOpponentMenuDaemonsHallow* HexusOpponentMenuDaemonsHallow::instance = nullptr;

HexusOpponentMenuDaemonsHallow* HexusOpponentMenuDaemonsHallow::getInstance()
{
	if (HexusOpponentMenuDaemonsHallow::instance == nullptr)
	{
		HexusOpponentMenuDaemonsHallow::instance = new HexusOpponentMenuDaemonsHallow();

		HexusOpponentMenuDaemonsHallow::instance->autorelease();
		GlobalDirector::registerGlobalScene(HexusOpponentMenuDaemonsHallow::instance);
	}

	return HexusOpponentMenuDaemonsHallow::instance;
}

HexusOpponentMenuDaemonsHallow::HexusOpponentMenuDaemonsHallow() : super(HexusChapterPreviewDaemonsHallow::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Ash::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Brine::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Celeste::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Cindra::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Drak::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Igneus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Lucifer::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Magnus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Pan::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PrincessMittens::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ragnis::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Rupert::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Rusty::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Scaldor::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuDaemonsHallow::~HexusOpponentMenuDaemonsHallow()
{
}
