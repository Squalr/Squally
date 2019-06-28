#include "ChapterSelectPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Pages/ChapterSelect/ChooseAChapter.h"
#include "Strings/Hacking/Lexicon/Pages/Binary/Title.h"
#include "Strings/Hacking/Lexicon/Pages/ControlFlow/Title.h"
#include "Strings/Hacking/Lexicon/Pages/Data/Title.h"
#include "Strings/Hacking/Lexicon/Pages/FloatingPoint/Title.h"
#include "Strings/Hacking/Lexicon/Pages/Vector/Title.h"

using namespace cocos2d;

const std::string ChapterSelectPage::Identifier = "CHAPTER_SELECT_PAGE";

ChapterSelectPage* ChapterSelectPage::create()
{
	ChapterSelectPage* instance = new ChapterSelectPage();

	instance->autorelease();

	return instance;
}

ChapterSelectPage::ChapterSelectPage() : super(ChapterSelectPage::Identifier, PageType::Right)
{
	this->decorLine = Sprite::create(UIResources::Menus_LexiconMenu_DecorLine);

	this->chapterSelectLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Hacking_Lexicon_Pages_ChapterSelect_ChooseAChapter::create());
	LocalizedLabel* dataLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Pages_Data_Title::create());
	LocalizedLabel* dataLabelSelected = dataLabel->clone();
	LocalizedLabel* binaryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Pages_Binary_Title::create());
	LocalizedLabel* binaryLabelSelected = binaryLabel->clone();
	LocalizedLabel* controlFlowLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Pages_ControlFlow_Title::create());
	LocalizedLabel* controlFlowLabelSelected = controlFlowLabel->clone();
	LocalizedLabel* vectorLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Pages_Vector_Title::create());
	LocalizedLabel* vectorLabelSelected = vectorLabel->clone();
	LocalizedLabel* floatingPointLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Pages_FloatingPoint_Title::create());
	LocalizedLabel* floatingPointSelected = floatingPointLabel->clone();

	this->dataChapterButton = ClickableTextNode::create(dataLabel,dataLabelSelected, UIResources::Menus_LexiconMenu_ChapterMarker, UIResources::Menus_LexiconMenu_ChapterMarkerSelected);
	this->binaryChapterButton = ClickableTextNode::create(binaryLabel, binaryLabelSelected, UIResources::Menus_LexiconMenu_ChapterMarker, UIResources::Menus_LexiconMenu_ChapterMarkerSelected);
	this->controlFlowChapterButton = ClickableTextNode::create(controlFlowLabel, controlFlowLabelSelected, UIResources::Menus_LexiconMenu_ChapterMarker, UIResources::Menus_LexiconMenu_ChapterMarkerSelected);
	this->vectorChapterButton = ClickableTextNode::create(vectorLabel, vectorLabelSelected, UIResources::Menus_LexiconMenu_ChapterMarker, UIResources::Menus_LexiconMenu_ChapterMarkerSelected);
	this->floatingPointChapterButton = ClickableTextNode::create(floatingPointLabel, floatingPointSelected, UIResources::Menus_LexiconMenu_ChapterMarker, UIResources::Menus_LexiconMenu_ChapterMarkerSelected);

	this->dataChapterButton->setTextOffset(Vec2(0.0f, -8.0f));
	this->binaryChapterButton->setTextOffset(Vec2(0.0f, -8.0f));
	this->controlFlowChapterButton->setTextOffset(Vec2(0.0f, -8.0f));
	this->vectorChapterButton->setTextOffset(Vec2(0.0f, -8.0f));
	this->floatingPointChapterButton->setTextOffset(Vec2(0.0f, -8.0f));

	this->chapterSelectLabel->setTextColor(super::TextColor);
	dataLabel->setTextColor(super::TextColor);
	dataLabelSelected->setTextColor(super::TextColor);
	binaryLabel->setTextColor(super::TextColor);
	binaryLabelSelected->setTextColor(super::TextColor);
	controlFlowLabel->setTextColor(super::TextColor);
	controlFlowLabelSelected->setTextColor(super::TextColor);
	vectorLabel->setTextColor(super::TextColor);
	vectorLabelSelected->setTextColor(super::TextColor);
	floatingPointLabel->setTextColor(super::TextColor);
	floatingPointSelected->setTextColor(super::TextColor);

	this->addChild(this->decorLine);
	this->addChild(this->chapterSelectLabel);
	this->addChild(this->dataChapterButton);
	this->addChild(this->binaryChapterButton);
	this->addChild(this->controlFlowChapterButton);
	this->addChild(this->vectorChapterButton);
	this->addChild(this->floatingPointChapterButton);
}

ChapterSelectPage::~ChapterSelectPage()
{
}

void ChapterSelectPage::initializePositions()
{
	super::initializePositions();

	const float vOffset = -48.0f;

	this->decorLine->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset));
	this->chapterSelectLabel->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 56.0f));
	this->dataChapterButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 128.0f - 104.0f * 0.0f));
	this->binaryChapterButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset  - 128.0f - 104.0f * 1.0f));
	this->controlFlowChapterButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset  - 128.0f - 104.0f * 2.0f));
	this->vectorChapterButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset  - 128.0f - 104.0f * 3.0f));
	this->floatingPointChapterButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset  - 128.0f - 104.0f * 4.0f));
}

void ChapterSelectPage::initializeListeners()
{
	super::initializeListeners();

	this->dataChapterButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(DataIntroPage::Identifier));
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(DataSelectPage::Identifier));
	});

	this->binaryChapterButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(BinaryIntroPage::Identifier));
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(BinarySelectPage::Identifier));
	});

	this->controlFlowChapterButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(ControlFlowIntroPage::Identifier));
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(ControlFlowSelectPage::Identifier));
	});

	this->vectorChapterButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(VectorIntroPage::Identifier));
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(VectorSelectPage::Identifier));
	});

	this->floatingPointChapterButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(FloatingPointIntroPage::Identifier));
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(FloatingPointSelectPage::Identifier));
	});
}
