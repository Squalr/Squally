////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuCastleValgrind.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Castle/HexusChapterPreviewCastle.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Castle/CastleHexusOpponents.h"

#include "Entities/Platformer/Enemies/CastleValgrind/Agnes.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Executioner.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Guard.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Jack.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Reaper.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Scarecrow.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Shade.h"
#include "Entities/Platformer/Enemies/CastleValgrind/VampireLord.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Vampiress.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Wraith.h"
#include "Entities/Platformer/Enemies/CastleValgrind/Zombie.h"
#include "Entities/Platformer/Enemies/CastleValgrind/ZombieElric.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Knight.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Princess.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Blackbeard.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Elric.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Garin.h"
#include "Entities/Platformer/Npcs/CastleValgrind/KingRedsong.h"
#include "Entities/Platformer/Npcs/CastleValgrind/KingRedsongSlime.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Leroy.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Mabel.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Merlin.h"
#include "Entities/Platformer/Npcs/CastleValgrind/PrincessOpal.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Raven.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Rogas.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Thurstan.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Tyracius.h"


using namespace cocos2d;

HexusOpponentMenuCastleValgrind* HexusOpponentMenuCastleValgrind::instance = nullptr;

void HexusOpponentMenuCastleValgrind::registerGlobalScene()
{
	if (HexusOpponentMenuCastleValgrind::instance == nullptr)
	{
		HexusOpponentMenuCastleValgrind::instance = new HexusOpponentMenuCastleValgrind();

		HexusOpponentMenuCastleValgrind::instance->autorelease();
		HexusOpponentMenuCastleValgrind::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuCastleValgrind::instance);
}

HexusOpponentMenuCastleValgrind::HexusOpponentMenuCastleValgrind() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Castle, HexusChapterPreviewCastle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Agnes::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Executioner::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Guard::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Jack::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Reaper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Scarecrow::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Shade::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VampireLord::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Vampiress::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Wraith::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Zombie::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ZombieElric::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Knight::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Princess::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Blackbeard::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Elric::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Garin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(KingRedsong::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(KingRedsongSlime::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Leroy::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mabel::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Merlin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PrincessOpal::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Raven::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Rogas::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Thurstan::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Tyracius::getHexusOpponentData()));


	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuCastleValgrind::~HexusOpponentMenuCastleValgrind()
{
}
