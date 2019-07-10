#include "HexusOpponentMenuEndianForest.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Npcs/EndianForest/Appolo.h"
#include "Entities/Platformer/Npcs/EndianForest/Ara.h"
#include "Entities/Platformer/Npcs/EndianForest/Bard.h"
#include "Entities/Platformer/Npcs/EndianForest/Blackbeard.h"
#include "Entities/Platformer/Npcs/EndianForest/Chiron.h"
#include "Entities/Platformer/Npcs/EndianForest/Elriel.h"
#include "Entities/Platformer/Npcs/EndianForest/Gramps.h"
#include "Entities/Platformer/Npcs/EndianForest/Liana.h"
#include "Entities/Platformer/Npcs/EndianForest/Lycan.h"
#include "Entities/Platformer/Npcs/EndianForest/Minos.h"
#include "Entities/Platformer/Npcs/EndianForest/Polyphemus.h"
#include "Entities/Platformer/Npcs/EndianForest/PrincessMatu.h"
#include "Entities/Platformer/Npcs/EndianForest/Robin.h"
#include "Entities/Platformer/Npcs/EndianForest/Toben.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/EndianForest/HexusChapterPreviewEndianForest.h"

using namespace cocos2d;

HexusOpponentMenuEndianForest* HexusOpponentMenuEndianForest::instance = nullptr;

HexusOpponentMenuEndianForest* HexusOpponentMenuEndianForest::getInstance()
{
	if (HexusOpponentMenuEndianForest::instance == nullptr)
	{
		HexusOpponentMenuEndianForest::instance = new HexusOpponentMenuEndianForest();

		HexusOpponentMenuEndianForest::instance->autorelease();
		GlobalDirector::registerGlobalScene(HexusOpponentMenuEndianForest::instance);
	}

	return HexusOpponentMenuEndianForest::instance;
}

HexusOpponentMenuEndianForest::HexusOpponentMenuEndianForest() : super(HexusChapterPreviewEndianForest::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Appolo::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ara::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Bard::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Blackbeard::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Chiron::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Elriel::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Gramps::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Liana::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Lycan::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Minos::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Polyphemus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PrincessMatu::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Robin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Toben::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuEndianForest::~HexusOpponentMenuEndianForest()
{
}
