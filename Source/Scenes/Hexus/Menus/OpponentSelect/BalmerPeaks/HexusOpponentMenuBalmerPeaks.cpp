#include "HexusOpponentMenuBalmerPeaks.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Aspen.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Aster.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Bodom.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Cookie.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Cooper.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Irmik.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Jingles.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Juniper.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Kringle.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Nessie.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/PrincessPepper.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Thatcher.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Theldar.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Tinsel.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/BalmerPeaks/HexusChapterPreviewBalmerPeaks.h"

using namespace cocos2d;

HexusOpponentMenuBalmerPeaks* HexusOpponentMenuBalmerPeaks::instance = nullptr;

HexusOpponentMenuBalmerPeaks* HexusOpponentMenuBalmerPeaks::getInstance()
{
	if (HexusOpponentMenuBalmerPeaks::instance == nullptr)
	{
		HexusOpponentMenuBalmerPeaks::instance = new HexusOpponentMenuBalmerPeaks();

		HexusOpponentMenuBalmerPeaks::instance->autorelease();
		GlobalDirector::registerGlobalScene(HexusOpponentMenuBalmerPeaks::instance);
	}

	return HexusOpponentMenuBalmerPeaks::instance;
}

HexusOpponentMenuBalmerPeaks::HexusOpponentMenuBalmerPeaks() : super(HexusChapterPreviewBalmerPeaks::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Aspen::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Aster::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Bodom::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Cookie::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Cooper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Irmik::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Jingles::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Juniper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Kringle::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Nessie::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PrincessPepper::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Thatcher::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Theldar::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Tinsel::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuBalmerPeaks::~HexusOpponentMenuBalmerPeaks()
{
}
