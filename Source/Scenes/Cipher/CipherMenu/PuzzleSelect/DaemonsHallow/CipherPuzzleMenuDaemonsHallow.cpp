#include "CipherPuzzleMenuDaemonsHallow.h"

#include "Engine/GlobalDirector.h"
#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzlePreview.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleDeserializer.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherPuzzleMenuDaemonsHallow* CipherPuzzleMenuDaemonsHallow::instance = nullptr;
std::string CipherPuzzleMenuDaemonsHallow::ChapterSavekey = "CIPHER_CHAPTER_DAEMONS_HALLOW";

CipherPuzzleMenuDaemonsHallow* CipherPuzzleMenuDaemonsHallow::getInstance()
{
	if (CipherPuzzleMenuDaemonsHallow::instance == nullptr)
	{
		CipherPuzzleMenuDaemonsHallow::instance = new CipherPuzzleMenuDaemonsHallow();

		CipherPuzzleMenuDaemonsHallow::instance->autorelease();
		GlobalDirector::registerGlobalScene(CipherPuzzleMenuDaemonsHallow::instance);
	}

	return CipherPuzzleMenuDaemonsHallow::instance;
}

CipherPuzzleMenuDaemonsHallow::CipherPuzzleMenuDaemonsHallow() : super(CipherPuzzleMenuDaemonsHallow::ChapterSavekey)
{
	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_DaemonsHallow_Chest0,
		CipherResources::Menus_DaemonsHallow_Chest0,
		CipherResources::Menus_DaemonsHallow_Chest0
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_DaemonsHallow_Chest1,
		CipherResources::Menus_DaemonsHallow_Chest1,
		CipherResources::Menus_DaemonsHallow_Chest1
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_DaemonsHallow_Chest2,
		CipherResources::Menus_DaemonsHallow_Chest2,
		CipherResources::Menus_DaemonsHallow_Chest2
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_DaemonsHallow_Chest3,
		CipherResources::Menus_DaemonsHallow_Chest3,
		CipherResources::Menus_DaemonsHallow_Chest3
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_DaemonsHallow_Chest4,
		CipherResources::Menus_DaemonsHallow_Chest4,
		CipherResources::Menus_DaemonsHallow_Chest4
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_DaemonsHallow_Chest5,
		CipherResources::Menus_DaemonsHallow_Chest5,
		CipherResources::Menus_DaemonsHallow_Chest5
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_DaemonsHallow_Chest6,
		CipherResources::Menus_DaemonsHallow_Chest6,
		CipherResources::Menus_DaemonsHallow_Chest6
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_DaemonsHallow_Chest7,
		CipherResources::Menus_DaemonsHallow_Chest7,
		CipherResources::Menus_DaemonsHallow_Chest7
	));

	this->buildCipherList();
}

CipherPuzzleMenuDaemonsHallow::~CipherPuzzleMenuDaemonsHallow()
{
}
