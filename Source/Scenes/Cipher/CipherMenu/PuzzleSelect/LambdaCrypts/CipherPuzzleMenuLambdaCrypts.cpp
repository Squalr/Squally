#include "CipherPuzzleMenuLambdaCrypts.h"

#include "Engine/GlobalDirector.h"
#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzlePreview.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleDeserializer.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

CipherPuzzleMenuLambdaCrypts* CipherPuzzleMenuLambdaCrypts::instance = nullptr;
std::string CipherPuzzleMenuLambdaCrypts::ChapterSavekey = "CIPHER_CHAPTER_LAMBDA_CRYPTS";

CipherPuzzleMenuLambdaCrypts* CipherPuzzleMenuLambdaCrypts::getInstance()
{
	if (CipherPuzzleMenuLambdaCrypts::instance == nullptr)
	{
		CipherPuzzleMenuLambdaCrypts::instance = new CipherPuzzleMenuLambdaCrypts();

		CipherPuzzleMenuLambdaCrypts::instance->autorelease();
		GlobalDirector::registerGlobalScene(CipherPuzzleMenuLambdaCrypts::instance);
	}

	return CipherPuzzleMenuLambdaCrypts::instance;
}

CipherPuzzleMenuLambdaCrypts::CipherPuzzleMenuLambdaCrypts() : super(CipherPuzzleMenuLambdaCrypts::ChapterSavekey)
{
	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_LambdaCrypts_Chest0,
		CipherResources::Menus_LambdaCrypts_Chest0,
		CipherResources::Menus_LambdaCrypts_Chest0
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_LambdaCrypts_Chest1,
		CipherResources::Menus_LambdaCrypts_Chest1,
		CipherResources::Menus_LambdaCrypts_Chest1
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_LambdaCrypts_Chest2,
		CipherResources::Menus_LambdaCrypts_Chest2,
		CipherResources::Menus_LambdaCrypts_Chest2
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_LambdaCrypts_Chest3,
		CipherResources::Menus_LambdaCrypts_Chest3,
		CipherResources::Menus_LambdaCrypts_Chest3
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_LambdaCrypts_Chest4,
		CipherResources::Menus_LambdaCrypts_Chest4,
		CipherResources::Menus_LambdaCrypts_Chest4
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_LambdaCrypts_Chest5,
		CipherResources::Menus_LambdaCrypts_Chest5,
		CipherResources::Menus_LambdaCrypts_Chest5
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_LambdaCrypts_Chest6,
		CipherResources::Menus_LambdaCrypts_Chest6,
		CipherResources::Menus_LambdaCrypts_Chest6
	));

	this->chests.push_back(CipherPuzzlePreview::create(
		CipherPuzzleDeserializer::deserialize(
			super::buildCipherJson("({i}+5)^8", { "a", "b", "c"}),
			true
		),
		CipherResources::Menus_LambdaCrypts_Chest7,
		CipherResources::Menus_LambdaCrypts_Chest7,
		CipherResources::Menus_LambdaCrypts_Chest7
	));

	this->buildCipherList();
}

CipherPuzzleMenuLambdaCrypts::~CipherPuzzleMenuLambdaCrypts()
{
}
