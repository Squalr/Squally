#include "ChapterSelectPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Pages/ChapterSelect/ChooseAChapter.h"
#include "Strings/Hacking/Lexicon/Pages/ChapterSelect/CommonInstructions.h"
#include "Strings/Hacking/Lexicon/Pages/ChapterSelect/ControlFlowInstructions.h"
#include "Strings/Hacking/Lexicon/Pages/ChapterSelect/FloatingPointInstructions.h"
#include "Strings/Hacking/Lexicon/Pages/ChapterSelect/VectorInstructions.h"

using namespace cocos2d;

const std::string ChapterSelectPage::KeyChapterSelectPage = "CHAPTER_SELECT_PAGE";

ChapterSelectPage* ChapterSelectPage::create()
{
	ChapterSelectPage* instance = new ChapterSelectPage();

	instance->autorelease();

	return instance;
}

ChapterSelectPage::ChapterSelectPage() : super(ChapterSelectPage::KeyChapterSelectPage, PageType::Right)
{
	this->ratSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Rat); 
	this->decorLine = Sprite::create(UIResources::Menus_LexiconMenu_DecorLine);

	this->chapterSelectLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Hacking_Lexicon_Pages_ChapterSelect_ChooseAChapter::create());
	LocalizedLabel* commonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Pages_ChapterSelect_CommonInstructions::create());
	LocalizedLabel* commonLabelSelected = commonLabel->clone();
	LocalizedLabel* controlFlowLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Pages_ChapterSelect_ControlFlowInstructions::create());
	LocalizedLabel* controlFlowLabelSelected = controlFlowLabel->clone();
	LocalizedLabel* vectorLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Pages_ChapterSelect_VectorInstructions::create());
	LocalizedLabel* vectorLabelSelected = vectorLabel->clone();
	LocalizedLabel* floatingPointLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Pages_ChapterSelect_FloatingPointInstructions::create());
	LocalizedLabel* floatingPointSelected = floatingPointLabel->clone();

	this->commonChapterButton = ClickableTextNode::create(commonLabel, commonLabelSelected, UIResources::Menus_LexiconMenu_ChapterMarker, UIResources::Menus_LexiconMenu_ChapterMarkerSelected);
	this->controlFlowChapterButton = ClickableTextNode::create(controlFlowLabel, controlFlowLabelSelected, UIResources::Menus_LexiconMenu_ChapterMarker, UIResources::Menus_LexiconMenu_ChapterMarkerSelected);
	this->vectorChapterButton = ClickableTextNode::create(vectorLabel, vectorLabelSelected, UIResources::Menus_LexiconMenu_ChapterMarker, UIResources::Menus_LexiconMenu_ChapterMarkerSelected);
	this->floatingPointChapterButton = ClickableTextNode::create(floatingPointLabel, floatingPointSelected, UIResources::Menus_LexiconMenu_ChapterMarker, UIResources::Menus_LexiconMenu_ChapterMarkerSelected);

	this->ratSprite->setFlippedX(true);
	this->commonChapterButton->setTextOffset(Vec2(0.0f, -8.0f));
	this->controlFlowChapterButton->setTextOffset(Vec2(0.0f, -8.0f));
	this->vectorChapterButton->setTextOffset(Vec2(0.0f, -8.0f));
	this->floatingPointChapterButton->setTextOffset(Vec2(0.0f, -8.0f));

	this->chapterSelectLabel->setTextColor(super::TextColor);
	commonLabel->setTextColor(super::TextColor);
	commonLabelSelected->setTextColor(super::TextColor);
	controlFlowLabel->setTextColor(super::TextColor);
	controlFlowLabelSelected->setTextColor(super::TextColor);
	vectorLabel->setTextColor(super::TextColor);
	vectorLabelSelected->setTextColor(super::TextColor);
	floatingPointLabel->setTextColor(super::TextColor);
	floatingPointSelected->setTextColor(super::TextColor);

	this->addChild(this->ratSprite);
	this->addChild(this->decorLine);
	this->addChild(this->chapterSelectLabel);
	this->addChild(this->commonChapterButton);
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

	this->ratSprite->setPosition(Vec2(104.0f, -256.0f));
	this->decorLine->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f - 16.0f));
	this->chapterSelectLabel->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f - 72.0f));
	this->commonChapterButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f - 144.0f - 104.0f * 0.0f));
	this->controlFlowChapterButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f - 144.0f - 104.0f * 1.0f));
	this->vectorChapterButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f - 144.0f - 104.0f * 2.0f));
	this->floatingPointChapterButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f - 144.0f - 104.0f * 3.0f));
}

void ChapterSelectPage::initializeListeners()
{
	super::initializeListeners();
}
