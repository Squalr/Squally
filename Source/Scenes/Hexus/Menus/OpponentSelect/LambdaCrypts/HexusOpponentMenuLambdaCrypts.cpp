////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuLambdaCrypts.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Abomination.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Gargoyle.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/KingZul.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedFighter.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedPig.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalBaron.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalCleaver.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalKnight.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalPriestess.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Undead.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/VoidArcher.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/VoidDemon.h"
#include "Entities/Platformer/Helpers/LambdaCrypts/Ghost.h"
#include "Entities/Platformer/Helpers/LambdaCrypts/Grim.h"
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
#include "Entities/Platformer/Enemies/LambdaCrypts/Abomination.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Gargoyle.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/KingZul.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedFighter.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedPig.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalBaron.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalCleaver.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalKnight.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalPriestess.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Undead.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/VoidArcher.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/VoidDemon.h"
#include "Entities/Platformer/Helpers/LambdaCrypts/Ghost.h"
#include "Entities/Platformer/Helpers/LambdaCrypts/Grim.h"
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
	this->opponents.push_back(HexusOpponentPreview::create(Abomination::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Gargoyle::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(KingZul::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ReanimatedFighter::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ReanimatedPig::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalBaron::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalCleaver::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalKnight::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalPriestess::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Undead::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VoidArcher::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VoidDemon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ghost::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Grim::getHexusOpponentData()));
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


	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuLambdaCrypts::~HexusOpponentMenuLambdaCrypts()
{
}
