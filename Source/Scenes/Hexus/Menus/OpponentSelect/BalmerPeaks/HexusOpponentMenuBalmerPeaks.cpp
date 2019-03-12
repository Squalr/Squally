////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuBalmerPeaks.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Cyrogen.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/FrostFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/GoblinElf.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/IceGolem.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Krampus.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinGrunt.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinWarrior.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Santa.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/SnowFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/ToySoldierGoblin.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/WaterElemental.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Yeti.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/YetiWarrior.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/YetiBaby.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Aspen.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Aster.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Bodom.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Cookie.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Irmik.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Jingles.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Juniper.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Kringle.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Nessie.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/PrincessPepper.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Theldar.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Tinsel.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Cyrogen.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/FrostFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/GoblinElf.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/IceGolem.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Krampus.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinGrunt.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinWarrior.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Santa.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/SnowFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/ToySoldierGoblin.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/WaterElemental.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Yeti.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/YetiWarrior.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/YetiBaby.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Aspen.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Aster.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Bodom.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Cookie.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Irmik.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Jingles.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Juniper.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Kringle.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Nessie.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/PrincessPepper.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Theldar.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Tinsel.h"
#include "Scenes/Hexus/Menus/ChapterSelect/BalmerPeaks/HexusChapterPreviewBalmerPeaks.h"

using namespace cocos2d;

HexusOpponentMenuBalmerPeaks* HexusOpponentMenuBalmerPeaks::instance = nullptr;

void HexusOpponentMenuBalmerPeaks::registerGlobalScene()
{
	if (HexusOpponentMenuBalmerPeaks::instance == nullptr)
	{
		HexusOpponentMenuBalmerPeaks::instance = new HexusOpponentMenuBalmerPeaks();

		HexusOpponentMenuBalmerPeaks::instance->autorelease();
		HexusOpponentMenuBalmerPeaks::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuBalmerPeaks::instance);
}

HexusOpponentMenuBalmerPeaks::HexusOpponentMenuBalmerPeaks() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::BalmerPeaks, HexusChapterPreviewBalmerPeaks::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Cyrogen::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(FrostFiend::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(GoblinElf::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(IceGolem::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Krampus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PenguinGrunt::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PenguinWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Santa::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SnowFiend::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ToySoldierGoblin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(WaterElemental::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Yeti::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(YetiWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Snowman::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(YetiBaby::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Aspen::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Aster::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Bodom::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Cookie::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Irmik::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Jingles::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Juniper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Kringle::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Nessie::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PrincessPepper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Theldar::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Tinsel::getHexusOpponentData()));


	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuBalmerPeaks::~HexusOpponentMenuBalmerPeaks()
{
}
