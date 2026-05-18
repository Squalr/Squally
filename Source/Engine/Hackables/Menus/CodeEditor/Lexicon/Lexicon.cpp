#include "Lexicon.h"

#include "2d/CCSprite.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Binary/BinaryIntroPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Binary/BinarySelectPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Binary/And/AndPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Binary/BinaryExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Binary/Bswap/BswapPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Binary/Not/NotPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Binary/Or/OrPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Binary/Shl/ShlPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Binary/Shr/ShrPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Binary/Xor/XorPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ChapterSelectPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/ConditionalJumpExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/ControlFlowExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/ControlFlowIntroPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/ControlFlowSelectPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Call/CallPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jmp/JmpPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jnabe/JnabePage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jne/JnePage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jngle/JnglePage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jno/JnoPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jnp/JnpPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jns/JnsPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jnz/JnzPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jzcxz/JzcxzPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Loop/LoopPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Nop/NopPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Ret/RetPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/DataIntroPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/DataSelectPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Add/AddExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Add/AddPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Dec/DecExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Dec/DecPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Div/DivExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Div/DivPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Inc/IncExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Inc/IncPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Mov/MovExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Mov/MovPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Mul/MulExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Mul/MulPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Neg/NegExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Neg/NegPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Pop/PopExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Pop/PopPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Push/PushExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Push/PushPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Sub/SubExamplesPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/Sub/SubPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/IntroPage.h"
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
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/FloatingPointIntroPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/FloatingPointSelectPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Frndint/FrndintPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fsqrt/FsqrtPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Ftst/FtstPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/Fxch/FxchPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Addss/AddssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Comiss/ComissPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Divss/DivssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Maxss/MaxssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Minss/MinssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Mulss/MulssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Sqrtss/SqrtssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Subss/SubssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/VectorIntroPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/VectorSelectPage.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedSprite.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

Lexicon* Lexicon::create()
{
	Lexicon* instance = new Lexicon();

	instance->autorelease();

	return instance;
}

Lexicon::Lexicon()
{
	this->background = Sprite::create(UIResources::Menus_LexiconMenu_desert_background);
	this->banner = Sprite::create(UIResources::Menus_LexiconMenu_Banner);
	this->title = LocalizedSprite::create(UIResources::Menus_LexiconMenu_Title_Lexicon_en);
	this->lexiconBack = Sprite::create(UIResources::Menus_LexiconMenu_LexiconBack);
	this->lexiconFront = Sprite::create(UIResources::Menus_LexiconMenu_LexiconFront);
	this->leftPageNode = Node::create();
	this->rightPageNode = Node::create();

	LocalizedLabel*	backLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	backLabelSelected = backLabel->clone();

	backLabel->enableOutline(Color4B::BLACK, 2);
	backLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(backLabel, backLabelSelected, UIResources::Menus_Buttons_GenericButton, UIResources::Menus_Buttons_GenericButtonHover);
	this->darkFrame = Sprite::create(UIResources::Menus_LexiconMenu_DarkFrame);

	// Intro
	this->pages.push_back(IntroPage::create());
	this->pages.push_back(ChapterSelectPage::create());

	// Data
	this->pages.push_back(DataIntroPage::create());
	this->pages.push_back(DataSelectPage::create());
	this->pages.push_back(IncExamplesPage::create());
	this->pages.push_back(IncPage::create());
	this->pages.push_back(DecExamplesPage::create());
	this->pages.push_back(DecPage::create());
	this->pages.push_back(AddExamplesPage::create());
	this->pages.push_back(AddPage::create());
	this->pages.push_back(SubExamplesPage::create());
	this->pages.push_back(SubPage::create());
	this->pages.push_back(DivExamplesPage::create());
	this->pages.push_back(DivPage::create());
	this->pages.push_back(MulExamplesPage::create());
	this->pages.push_back(MulPage::create());
	this->pages.push_back(MovExamplesPage::create());
	this->pages.push_back(MovPage::create());
	this->pages.push_back(PushExamplesPage::create());
	this->pages.push_back(PushPage::create());
	this->pages.push_back(PopExamplesPage::create());
	this->pages.push_back(PopPage::create());
	this->pages.push_back(NegExamplesPage::create());
	this->pages.push_back(NegPage::create());

	// Binary
	this->pages.push_back(BinaryIntroPage::create());
	this->pages.push_back(BinarySelectPage::create());
	this->pages.push_back(AndPage::create());
	this->pages.push_back(OrPage::create());
	this->pages.push_back(XorPage::create());
	this->pages.push_back(ShlPage::create());
	this->pages.push_back(ShrPage::create());
	this->pages.push_back(NotPage::create());
	this->pages.push_back(BswapPage::create());
	this->pages.push_back(BinaryExamplesPage::create(BinaryExamplesPage::Operation::And));
	this->pages.push_back(BinaryExamplesPage::create(BinaryExamplesPage::Operation::Or));
	this->pages.push_back(BinaryExamplesPage::create(BinaryExamplesPage::Operation::Xor));
	this->pages.push_back(BinaryExamplesPage::create(BinaryExamplesPage::Operation::Shl));
	this->pages.push_back(BinaryExamplesPage::create(BinaryExamplesPage::Operation::Shr));
	this->pages.push_back(BinaryExamplesPage::create(BinaryExamplesPage::Operation::Not));
	this->pages.push_back(BinaryExamplesPage::create(BinaryExamplesPage::Operation::Bswap));

	// Control flow
	this->pages.push_back(ControlFlowIntroPage::create());
	this->pages.push_back(ControlFlowSelectPage::create());
	this->pages.push_back(CallPage::create());
	this->pages.push_back(JmpPage::create());
	this->pages.push_back(JnabePage::create());
	this->pages.push_back(JnePage::create());
	this->pages.push_back(JnglePage::create());
	this->pages.push_back(JnoPage::create());
	this->pages.push_back(JnpPage::create());
	this->pages.push_back(JnsPage::create());
	this->pages.push_back(JnzPage::create());
	this->pages.push_back(JzcxzPage::create());
	this->pages.push_back(LoopPage::create());
	this->pages.push_back(NopPage::create());
	this->pages.push_back(RetPage::create());
	this->pages.push_back(ControlFlowExamplesPage::create(ControlFlowExamplesPage::Operation::Nop));
	this->pages.push_back(ControlFlowExamplesPage::create(ControlFlowExamplesPage::Operation::Jmp));
	this->pages.push_back(ControlFlowExamplesPage::create(ControlFlowExamplesPage::Operation::Call));
	this->pages.push_back(ControlFlowExamplesPage::create(ControlFlowExamplesPage::Operation::Ret));
	this->pages.push_back(ControlFlowExamplesPage::create(ControlFlowExamplesPage::Operation::Loop));
	this->pages.push_back(ConditionalJumpExamplesPage::create(ConditionalJumpExamplesPage::Operation::Jnabe));
	this->pages.push_back(ConditionalJumpExamplesPage::create(ConditionalJumpExamplesPage::Operation::Jne));
	this->pages.push_back(ConditionalJumpExamplesPage::create(ConditionalJumpExamplesPage::Operation::Jngle));
	this->pages.push_back(ConditionalJumpExamplesPage::create(ConditionalJumpExamplesPage::Operation::Jno));
	this->pages.push_back(ConditionalJumpExamplesPage::create(ConditionalJumpExamplesPage::Operation::Jnp));
	this->pages.push_back(ConditionalJumpExamplesPage::create(ConditionalJumpExamplesPage::Operation::Jns));
	this->pages.push_back(ConditionalJumpExamplesPage::create(ConditionalJumpExamplesPage::Operation::Jnz));
	this->pages.push_back(ConditionalJumpExamplesPage::create(ConditionalJumpExamplesPage::Operation::Jzcxz));

	// SIMD
	this->pages.push_back(VectorIntroPage::create());
	this->pages.push_back(VectorSelectPage::create());

	this->pages.push_back(AddssPage::create());
	this->pages.push_back(ComissPage::create());
	this->pages.push_back(DivssPage::create());
	this->pages.push_back(MaxssPage::create());
	this->pages.push_back(MinssPage::create());
	this->pages.push_back(MulssPage::create());
	this->pages.push_back(SqrtssPage::create());
	this->pages.push_back(SubssPage::create());
	
	// FPU
	this->pages.push_back(FloatingPointIntroPage::create());
	this->pages.push_back(FloatingPointSelectPage::create());

	this->pages.push_back(FabsPage::create());
	this->pages.push_back(FcmovnbePage::create());
	this->pages.push_back(FiaddpPage::create());
	this->pages.push_back(FicomppPage::create());
	this->pages.push_back(FidivrpPage::create());
	this->pages.push_back(FildPage::create());
	this->pages.push_back(FimulpPage::create());
	this->pages.push_back(FistpPage::create());
	this->pages.push_back(FisubrpPage::create());
	this->pages.push_back(Fld1Page::create());
	this->pages.push_back(FldpiPage::create());
	this->pages.push_back(FldzPage::create());
	this->pages.push_back(FrndintPage::create());
	this->pages.push_back(FcosPage::create());
	this->pages.push_back(FsinPage::create());
	this->pages.push_back(FsqrtPage::create());
	this->pages.push_back(FtstPage::create());
	this->pages.push_back(FxchPage::create());

	for (LexiconPage* next : this->pages)
	{
		switch(next->getPageType())
		{
			default:
			case LexiconPage::PageType::Left:
			{
				this->leftPageNode->addChild(next);
				break;
			}
			case LexiconPage::PageType::Right:
			{
				this->rightPageNode->addChild(next);
				break;
			}
		}
	}

	this->addChild(this->background);
	this->addChild(this->banner);
	this->addChild(this->title);
	this->addChild(this->lexiconBack);
	this->addChild(this->lexiconFront);
	this->addChild(this->leftPageNode);
	this->addChild(this->rightPageNode);
	this->addChild(this->darkFrame);
	this->addChild(this->backButton);
}

Lexicon::~Lexicon()
{
}

void Lexicon::onEnter()
{
	super::onEnter();

	this->defer([=]()
	{
		HackableEvents::TriggerOpenLexiconPage(OpenLexiconPageArgs(IntroPage::Identifier));
		HackableEvents::TriggerOpenLexiconPage(OpenLexiconPageArgs(ChapterSelectPage::Identifier));
	});
}

void Lexicon::initializePositions()
{
	super::initializePositions();

	const Vec2 BookOffset = Vec2(32.0f, -48.0f);

	CSize visibleSize = Director::getInstance()->getVisibleSize();
	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->banner->setPosition(Vec2(visibleSize.width / 2.0f - 712.0f, visibleSize.height / 2.0f + 32.0f));
	this->title->setPosition(Vec2(visibleSize.width / 2.0f - 712.0f, visibleSize.height / 2.0f + 464.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 788.0f, 96.0f));
	this->lexiconBack->setPosition(Vec2(visibleSize.width / 2.0f + BookOffset.x, visibleSize.height / 2.0f + BookOffset.y));
	this->lexiconFront->setPosition(Vec2(visibleSize.width / 2.0f + BookOffset.x, visibleSize.height / 2.0f + BookOffset.y + 24.0f));
	this->leftPageNode->setPosition(Vec2(visibleSize.width / 2.0f + BookOffset.x - LexiconPage::PageOffset.x, visibleSize.height / 2.0f + BookOffset.y + LexiconPage::PageOffset.y));
	this->rightPageNode->setPosition(Vec2(visibleSize.width / 2.0f + BookOffset.x + LexiconPage::PageOffset.x, visibleSize.height / 2.0f + BookOffset.y + LexiconPage::PageOffset.y));
	this->darkFrame->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}
	
void Lexicon::initializeListeners()
{
	super::initializeListeners();

	this->backButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->close();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isFocused(this))
		{
			return;
		}
		
		args->handle();

		this->goBack();
	});

	this->addEventListener(EventListenerCustom::create(HackableEvents::EventOpenLexiconPage, [=](EventCustom* eventCustom)
	{
		OpenLexiconPageArgs* args = static_cast<OpenLexiconPageArgs*>(eventCustom->getData());

		if (args == nullptr)
		{
			return;
		}

		LexiconPage* page = this->findPage(args->pageIdentifier);

		if (page == nullptr)
		{
			return;
		}

		switch (page->getPageType())
		{
			case LexiconPage::PageType::Left:
			{
				this->currentLeftPage = args->pageIdentifier;
				break;
			}
			case LexiconPage::PageType::Right:
			{
				this->currentRightPage = args->pageIdentifier;
				break;
			}
			case LexiconPage::PageType::Full:
			default:
			{
				this->currentLeftPage = args->pageIdentifier;
				this->currentRightPage.clear();
				break;
			}
		}
	}));
}

void Lexicon::open()
{
	this->setVisible(true);
	GameUtils::focus(this);
}

void Lexicon::close()
{
	if (this->isVisible())
	{
		if (closeCallback != nullptr)
		{
			closeCallback();
		}
		
		this->setVisible(false);
	}
}

void Lexicon::setCloseCallBack(std::function<void()> closeCallback)
{
	this->closeCallback = closeCallback;
}

void Lexicon::openPages(std::string leftPage, std::string rightPage)
{
	HackableEvents::TriggerOpenLexiconPage(OpenLexiconPageArgs(leftPage));
	HackableEvents::TriggerOpenLexiconPage(OpenLexiconPageArgs(rightPage));
}

void Lexicon::goBack()
{
	if (this->isRootOpen())
	{
		this->close();
	}
	else if (this->currentLeftPage == DataIntroPage::Identifier || this->currentRightPage == DataSelectPage::Identifier)
	{
		this->openPages(IntroPage::Identifier, ChapterSelectPage::Identifier);
	}
	else if (this->currentLeftPage == BinaryIntroPage::Identifier || this->currentRightPage == BinarySelectPage::Identifier)
	{
		this->openPages(IntroPage::Identifier, ChapterSelectPage::Identifier);
	}
	else if (this->currentLeftPage == ControlFlowIntroPage::Identifier || this->currentRightPage == ControlFlowSelectPage::Identifier)
	{
		this->openPages(IntroPage::Identifier, ChapterSelectPage::Identifier);
	}
	else if (this->currentLeftPage == VectorIntroPage::Identifier || this->currentRightPage == VectorSelectPage::Identifier)
	{
		this->openPages(IntroPage::Identifier, ChapterSelectPage::Identifier);
	}
	else if (this->currentLeftPage == FloatingPointIntroPage::Identifier || this->currentRightPage == FloatingPointSelectPage::Identifier)
	{
		this->openPages(IntroPage::Identifier, ChapterSelectPage::Identifier);
	}
	else if (this->isDataPage())
	{
		this->openPages(DataIntroPage::Identifier, DataSelectPage::Identifier);
	}
	else if (this->isBinaryPage())
	{
		this->openPages(BinaryIntroPage::Identifier, BinarySelectPage::Identifier);
	}
	else if (this->isControlFlowPage())
	{
		this->openPages(ControlFlowIntroPage::Identifier, ControlFlowSelectPage::Identifier);
	}
	else if (this->isVectorPage())
	{
		this->openPages(VectorIntroPage::Identifier, VectorSelectPage::Identifier);
	}
	else if (this->isFloatingPointPage())
	{
		this->openPages(FloatingPointIntroPage::Identifier, FloatingPointSelectPage::Identifier);
	}
	else
	{
		this->openPages(IntroPage::Identifier, ChapterSelectPage::Identifier);
	}
}

LexiconPage* Lexicon::findPage(std::string pageIdentifier)
{
	for (LexiconPage* next : this->pages)
	{
		if (next->getPageIdentifier() == pageIdentifier)
		{
			return next;
		}
	}

	return nullptr;
}

bool Lexicon::isRootOpen()
{
	return this->currentLeftPage == IntroPage::Identifier && this->currentRightPage == ChapterSelectPage::Identifier;
}

bool Lexicon::isDataPage()
{
	return this->currentLeftPage == IncPage::Identifier || this->currentRightPage == IncExamplesPage::Identifier
		|| this->currentLeftPage == DecPage::Identifier || this->currentRightPage == DecExamplesPage::Identifier
		|| this->currentLeftPage == AddPage::Identifier || this->currentRightPage == AddExamplesPage::Identifier
		|| this->currentLeftPage == SubPage::Identifier || this->currentRightPage == SubExamplesPage::Identifier
		|| this->currentLeftPage == DivPage::Identifier || this->currentRightPage == DivExamplesPage::Identifier
		|| this->currentLeftPage == MulPage::Identifier || this->currentRightPage == MulExamplesPage::Identifier
		|| this->currentLeftPage == MovPage::Identifier || this->currentRightPage == MovExamplesPage::Identifier
		|| this->currentLeftPage == PushPage::Identifier || this->currentRightPage == PushExamplesPage::Identifier
		|| this->currentLeftPage == PopPage::Identifier || this->currentRightPage == PopExamplesPage::Identifier
		|| this->currentLeftPage == NegPage::Identifier || this->currentRightPage == NegExamplesPage::Identifier;
}

bool Lexicon::isBinaryPage()
{
	return this->currentLeftPage == AndPage::Identifier || this->currentRightPage == BinaryExamplesPage::AndIdentifier
		|| this->currentLeftPage == OrPage::Identifier || this->currentRightPage == BinaryExamplesPage::OrIdentifier
		|| this->currentLeftPage == XorPage::Identifier || this->currentRightPage == BinaryExamplesPage::XorIdentifier
		|| this->currentLeftPage == ShlPage::Identifier || this->currentRightPage == BinaryExamplesPage::ShlIdentifier
		|| this->currentLeftPage == ShrPage::Identifier || this->currentRightPage == BinaryExamplesPage::ShrIdentifier
		|| this->currentLeftPage == NotPage::Identifier || this->currentRightPage == BinaryExamplesPage::NotIdentifier
		|| this->currentLeftPage == BswapPage::Identifier || this->currentRightPage == BinaryExamplesPage::BswapIdentifier;
}

bool Lexicon::isControlFlowPage()
{
	return this->currentLeftPage == NopPage::Identifier || this->currentRightPage == ControlFlowExamplesPage::NopIdentifier
		|| this->currentLeftPage == JmpPage::Identifier || this->currentRightPage == ControlFlowExamplesPage::JmpIdentifier
		|| this->currentLeftPage == CallPage::Identifier || this->currentRightPage == ControlFlowExamplesPage::CallIdentifier
		|| this->currentLeftPage == RetPage::Identifier || this->currentRightPage == ControlFlowExamplesPage::RetIdentifier
		|| this->currentLeftPage == LoopPage::Identifier || this->currentRightPage == ControlFlowExamplesPage::LoopIdentifier
		|| this->currentLeftPage == JnabePage::Identifier || this->currentRightPage == ConditionalJumpExamplesPage::JnabeIdentifier
		|| this->currentLeftPage == JnePage::Identifier || this->currentRightPage == ConditionalJumpExamplesPage::JneIdentifier
		|| this->currentLeftPage == JnglePage::Identifier || this->currentRightPage == ConditionalJumpExamplesPage::JngleIdentifier
		|| this->currentLeftPage == JnoPage::Identifier || this->currentRightPage == ConditionalJumpExamplesPage::JnoIdentifier
		|| this->currentLeftPage == JnpPage::Identifier || this->currentRightPage == ConditionalJumpExamplesPage::JnpIdentifier
		|| this->currentLeftPage == JnsPage::Identifier || this->currentRightPage == ConditionalJumpExamplesPage::JnsIdentifier
		|| this->currentLeftPage == JnzPage::Identifier || this->currentRightPage == ConditionalJumpExamplesPage::JnzIdentifier
		|| this->currentLeftPage == JzcxzPage::Identifier || this->currentRightPage == ConditionalJumpExamplesPage::JzcxzIdentifier;
}

bool Lexicon::isVectorPage()
{
	return this->currentLeftPage == AddssPage::Identifier
		|| this->currentLeftPage == ComissPage::Identifier
		|| this->currentLeftPage == DivssPage::Identifier
		|| this->currentLeftPage == MaxssPage::Identifier
		|| this->currentLeftPage == MinssPage::Identifier
		|| this->currentLeftPage == MulssPage::Identifier
		|| this->currentLeftPage == SqrtssPage::Identifier
		|| this->currentLeftPage == SubssPage::Identifier;
}

bool Lexicon::isFloatingPointPage()
{
	return this->currentLeftPage == FabsPage::Identifier
		|| this->currentLeftPage == FcmovnbePage::Identifier
		|| this->currentLeftPage == FiaddpPage::Identifier
		|| this->currentLeftPage == FicomppPage::Identifier
		|| this->currentLeftPage == FidivrpPage::Identifier
		|| this->currentLeftPage == FildPage::Identifier
		|| this->currentLeftPage == FimulpPage::Identifier
		|| this->currentLeftPage == FistpPage::Identifier
		|| this->currentLeftPage == FisubrpPage::Identifier
		|| this->currentLeftPage == Fld1Page::Identifier
		|| this->currentLeftPage == FldpiPage::Identifier
		|| this->currentLeftPage == FldzPage::Identifier
		|| this->currentLeftPage == FrndintPage::Identifier
		|| this->currentLeftPage == FcosPage::Identifier
		|| this->currentLeftPage == FsinPage::Identifier
		|| this->currentLeftPage == FsqrtPage::Identifier
		|| this->currentLeftPage == FtstPage::Identifier
		|| this->currentLeftPage == FxchPage::Identifier;
}
