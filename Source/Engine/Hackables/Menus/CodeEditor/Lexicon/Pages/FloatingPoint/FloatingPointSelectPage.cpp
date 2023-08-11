#include "FloatingPointSelectPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fabs/FabsPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fcmovnbe/FcmovnbePage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fcos/FcosPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fiaddp/FiaddpPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Ficompp/FicomppPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fidivrp/FidivrpPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fild/FildPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fimulp/FimulpPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fistp/FistpPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fsin/FsinPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fisubrp/FisubrpPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fld1/Fld1Page.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fldpi/FldpiPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fldz/FldzPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Frndint/FrndintPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fsqrt/FsqrtPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Ftst/FtstPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fxch/FxchPage.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FloatingPointSelectPage::Identifier = "FLOATING_POINT_SELECT_PAGE";

FloatingPointSelectPage* FloatingPointSelectPage::create()
{
	FloatingPointSelectPage* instance = new FloatingPointSelectPage();

	instance->autorelease();

	return instance;
}

FloatingPointSelectPage::FloatingPointSelectPage() : super(FloatingPointSelectPage::Identifier, PageType::Right)
{
	this->decorLine = Sprite::create(UIResources::Menus_LexiconMenu_DecorLine);

	this->operationSelectLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Pages_ChapterSelect_ChooseAnOperation::create());
	
	this->fabsOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fabs::create(), FabsPage::Identifier);
	this->fcmovnbeOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fcmovnbe::create(), FcmovnbePage::Identifier);
	this->fcosOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fcos::create(), FcosPage::Identifier);
	this->fiaddpOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fiaddp::create(), FiaddpPage::Identifier);
	this->ficomppOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Ficompp::create(), FicomppPage::Identifier);
	this->fidivrpOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fidivrp::create(), FidivrpPage::Identifier);
	this->fildOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fild::create(), FildPage::Identifier);
	this->fimulpOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fimulp::create(), FimulpPage::Identifier);
	this->fistpOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fistp::create(), FistpPage::Identifier);
	this->fisubrpOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fisubrp::create(), FisubrpPage::Identifier);
	this->fld1OperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fld1::create(), Fld1Page::Identifier);
	this->fldpiOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fldpi::create(), FldpiPage::Identifier);
	this->fldzOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fldz::create(), FldzPage::Identifier);
	this->frndintOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Frndint::create(), FrndintPage::Identifier);
	this->fsinOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fcos::create(), FcosPage::Identifier);
	this->fsqrtPageOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fsqrt::create(), FsqrtPage::Identifier);
	this->ftstPageOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Ftst::create(), FtstPage::Identifier);
	this->fxchPageOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fxch::create(), FxchPage::Identifier);

	this->operationSelectLabel->setTextColor(super::TextColor);

	this->addChild(this->decorLine);
	this->addChild(this->operationSelectLabel);
	this->addChild(this->fabsOperationButton);
	this->addChild(this->fcmovnbeOperationButton);
	this->addChild(this->fcosOperationButton);
	this->addChild(this->fiaddpOperationButton);
	this->addChild(this->ficomppOperationButton);
	this->addChild(this->fidivrpOperationButton);
	this->addChild(this->fildOperationButton);
	this->addChild(this->fimulpOperationButton);
	this->addChild(this->fistpOperationButton);
	this->addChild(this->fisubrpOperationButton);
	this->addChild(this->fld1OperationButton);
	this->addChild(this->fldpiOperationButton);
	this->addChild(this->fldzOperationButton);
	this->addChild(this->frndintOperationButton);
	this->addChild(this->fsinOperationButton);
	this->addChild(this->fsqrtPageOperationButton);
	this->addChild(this->ftstPageOperationButton);
	this->addChild(this->fxchPageOperationButton);
}

FloatingPointSelectPage::~FloatingPointSelectPage()
{
}

void FloatingPointSelectPage::initializePositions()
{
	super::initializePositions();

	const float vOffset = -48.0f;
	const float vSpacing = -92.0f;

	this->decorLine->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset));
	this->operationSelectLabel->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 56.0f));

	this->fiaddpOperationButton->setPosition(Vec2(-196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 0.0f));
	this->fisubrpOperationButton->setPosition(Vec2(-196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 1.0f));
	this->fidivrpOperationButton->setPosition(Vec2(-196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 2.0f));
	this->fimulpOperationButton->setPosition(Vec2(-196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 3.0f));
	this->fabsOperationButton->setPosition(Vec2(-196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 4.0f));
	this->fsqrtPageOperationButton->setPosition(Vec2(-196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 5.0f));

	this->fld1OperationButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 0.0f + vSpacing / 2.0f));
	this->fldpiOperationButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 1.0f + vSpacing / 2.0f));
	this->fldzOperationButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 2.0f + vSpacing / 2.0f));
	this->fildOperationButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 3.0f + vSpacing / 2.0f));
	this->fistpOperationButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 4.0f + vSpacing / 2.0f));
	this->ficomppOperationButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 5.0f + vSpacing / 2.0f));

	this->fcmovnbeOperationButton->setPosition(Vec2(196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 0.0f));
	this->fcosOperationButton->setPosition(Vec2(196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 1.0f));
	this->fsinOperationButton->setPosition(Vec2(196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 2.0f));
	this->ftstPageOperationButton->setPosition(Vec2(196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 3.0f));
	this->fxchPageOperationButton->setPosition(Vec2(196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 4.0f));
	this->frndintOperationButton->setPosition(Vec2(196.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 5.0f));
}

void FloatingPointSelectPage::initializeListeners()
{
	super::initializeListeners();
}
