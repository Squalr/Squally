#include "CipherPuzzleMenuSeaSharpCaverns.h"

#include "Engine/GlobalDirector.h"
#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzlePreview.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleDeserializer.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherPuzzleMenuSeaSharpCaverns* CipherPuzzleMenuSeaSharpCaverns::instance = nullptr;
std::string CipherPuzzleMenuSeaSharpCaverns::ChapterSavekey = "CIPHER_CHAPTER_SEA_SHARP_CAVERNS";

CipherPuzzleMenuSeaSharpCaverns* CipherPuzzleMenuSeaSharpCaverns::getInstance()
{
	if (CipherPuzzleMenuSeaSharpCaverns::instance == nullptr)
	{
		CipherPuzzleMenuSeaSharpCaverns::instance = new CipherPuzzleMenuSeaSharpCaverns();

		CipherPuzzleMenuSeaSharpCaverns::instance->autorelease();
		GlobalDirector::registerGlobalScene(CipherPuzzleMenuSeaSharpCaverns::instance);
	}

	return CipherPuzzleMenuSeaSharpCaverns::instance;
}

CipherPuzzleMenuSeaSharpCaverns::CipherPuzzleMenuSeaSharpCaverns() : super(CipherPuzzleMenuSeaSharpCaverns::ChapterSavekey)
{
	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_SeaSharpCaverns_Chest0,
		CipherResources::Menus_SeaSharpCaverns_Chest0,
		CipherResources::Menus_SeaSharpCaverns_Chest0
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_SeaSharpCaverns_Chest1,
		CipherResources::Menus_SeaSharpCaverns_Chest1,
		CipherResources::Menus_SeaSharpCaverns_Chest1
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_SeaSharpCaverns_Chest2,
		CipherResources::Menus_SeaSharpCaverns_Chest2,
		CipherResources::Menus_SeaSharpCaverns_Chest2
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_SeaSharpCaverns_Chest3,
		CipherResources::Menus_SeaSharpCaverns_Chest3,
		CipherResources::Menus_SeaSharpCaverns_Chest3
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_SeaSharpCaverns_Chest4,
		CipherResources::Menus_SeaSharpCaverns_Chest4,
		CipherResources::Menus_SeaSharpCaverns_Chest4
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_SeaSharpCaverns_Chest5,
		CipherResources::Menus_SeaSharpCaverns_Chest5,
		CipherResources::Menus_SeaSharpCaverns_Chest5
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_SeaSharpCaverns_Chest6,
		CipherResources::Menus_SeaSharpCaverns_Chest6,
		CipherResources::Menus_SeaSharpCaverns_Chest6
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_SeaSharpCaverns_Chest7,
		CipherResources::Menus_SeaSharpCaverns_Chest7,
		CipherResources::Menus_SeaSharpCaverns_Chest7
	));

	this->buildCipherList();
}

CipherPuzzleMenuSeaSharpCaverns::~CipherPuzzleMenuSeaSharpCaverns()
{
}
