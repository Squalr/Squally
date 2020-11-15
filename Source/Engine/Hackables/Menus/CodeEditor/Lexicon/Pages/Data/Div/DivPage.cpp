#include "DivPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/DataIntroPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/DataSelectPage.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DivPage::Identifier = "DIV_PAGE";

DivPage* DivPage::create()
{
	DivPage* instance = new DivPage();

	instance->autorelease();

	return instance;
}

DivPage::DivPage() : super(DivPage::Identifier, PageType::Left)
{
	this->decorSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Shield);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Instructions_Data_Div::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Common_Triconcat::create()->setStringReplacementVariables(
			{
				Strings::Common_ConstantNewlineNewline::create()->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Pages_Data_Div_Intro::create()),
				Strings::Common_ConstantNewlineNewline::create()->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Pages_Data_Div_IntroPt2::create()),
				Strings::Menus_Hacking_Lexicon_Pages_Data_Div_IntroPt3::create(),
			}
		),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->decorSprite);
	this->addChild(this->chapterSprite);
	this->addChild(this->titleLabel);
	this->addChild(this->introText);
}

DivPage::~DivPage()
{
}

void DivPage::initializePositions()
{
	super::initializePositions();

	this->decorSprite->setPosition(Vec2(112.0f, -180.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void DivPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(DataIntroPage::Identifier, DataSelectPage::Identifier);
}
