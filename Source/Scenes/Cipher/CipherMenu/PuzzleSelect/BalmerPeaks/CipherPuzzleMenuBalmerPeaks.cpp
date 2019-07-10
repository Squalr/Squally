#include "CipherPuzzleMenuBalmerPeaks.h"

#include "Engine/GlobalDirector.h"
#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzlePreview.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleDeserializer.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherPuzzleMenuBalmerPeaks* CipherPuzzleMenuBalmerPeaks::instance = nullptr;
std::string CipherPuzzleMenuBalmerPeaks::ChapterSavekey = "CIPHER_CHAPTER_BALMER_PEAKS";

CipherPuzzleMenuBalmerPeaks* CipherPuzzleMenuBalmerPeaks::getInstance()
{
	if (CipherPuzzleMenuBalmerPeaks::instance == nullptr)
	{
		CipherPuzzleMenuBalmerPeaks::instance = new CipherPuzzleMenuBalmerPeaks();

		CipherPuzzleMenuBalmerPeaks::instance->autorelease();
		GlobalDirector::registerGlobalScene(CipherPuzzleMenuBalmerPeaks::instance);
	}

	return CipherPuzzleMenuBalmerPeaks::instance;
}

CipherPuzzleMenuBalmerPeaks::CipherPuzzleMenuBalmerPeaks() : super(CipherPuzzleMenuBalmerPeaks::ChapterSavekey)
{
	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_BalmerPeaks_Chest0,
		CipherResources::Menus_BalmerPeaks_Chest0,
		CipherResources::Menus_BalmerPeaks_Chest0
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_BalmerPeaks_Chest1,
		CipherResources::Menus_BalmerPeaks_Chest1,
		CipherResources::Menus_BalmerPeaks_Chest1
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_BalmerPeaks_Chest2,
		CipherResources::Menus_BalmerPeaks_Chest2,
		CipherResources::Menus_BalmerPeaks_Chest2
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_BalmerPeaks_Chest3,
		CipherResources::Menus_BalmerPeaks_Chest3,
		CipherResources::Menus_BalmerPeaks_Chest3
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_BalmerPeaks_Chest4,
		CipherResources::Menus_BalmerPeaks_Chest4,
		CipherResources::Menus_BalmerPeaks_Chest4
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_BalmerPeaks_Chest5,
		CipherResources::Menus_BalmerPeaks_Chest5,
		CipherResources::Menus_BalmerPeaks_Chest5
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_BalmerPeaks_Chest6,
		CipherResources::Menus_BalmerPeaks_Chest6,
		CipherResources::Menus_BalmerPeaks_Chest6
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_BalmerPeaks_Chest7,
		CipherResources::Menus_BalmerPeaks_Chest7,
		CipherResources::Menus_BalmerPeaks_Chest7
	));

	this->buildCipherList();
}

CipherPuzzleMenuBalmerPeaks::~CipherPuzzleMenuBalmerPeaks()
{
}
