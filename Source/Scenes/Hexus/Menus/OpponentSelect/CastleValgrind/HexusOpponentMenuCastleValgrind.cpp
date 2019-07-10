#include "HexusOpponentMenuCastleValgrind.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Elric.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Garin.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Gaunt.h"
#include "Entities/Platformer/Npcs/CastleValgrind/KingRedsong.h"
#include "Entities/Platformer/Npcs/CastleValgrind/KingRedsongSlime.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Leopold.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Leroy.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Mabel.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Merlin.h"
#include "Entities/Platformer/Npcs/CastleValgrind/PrincessOpal.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Raven.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Rogas.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Thurstan.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Tyracius.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/CastleValgrind/HexusChapterPreviewCastleValgrind.h"

using namespace cocos2d;

HexusOpponentMenuCastleValgrind* HexusOpponentMenuCastleValgrind::instance = nullptr;

HexusOpponentMenuCastleValgrind* HexusOpponentMenuCastleValgrind::getInstance()
{
	if (HexusOpponentMenuCastleValgrind::instance == nullptr)
	{
		HexusOpponentMenuCastleValgrind::instance = new HexusOpponentMenuCastleValgrind();

		HexusOpponentMenuCastleValgrind::instance->autorelease();
		GlobalDirector::registerGlobalScene(HexusOpponentMenuCastleValgrind::instance);
	}

	return HexusOpponentMenuCastleValgrind::instance;
}

HexusOpponentMenuCastleValgrind::HexusOpponentMenuCastleValgrind() : super(HexusChapterPreviewCastleValgrind::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Elric::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Garin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Gaunt::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(KingRedsong::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(KingRedsongSlime::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Leopold::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Leroy::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mabel::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Merlin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PrincessOpal::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Raven::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Rogas::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Thurstan::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Tyracius::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuCastleValgrind::~HexusOpponentMenuCastleValgrind()
{
}
