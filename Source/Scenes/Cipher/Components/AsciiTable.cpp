#include "AsciiTable.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/RadioButton.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Cipher/Components/Letters/SmartAsciiLabel.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Return.h"

using namespace cocos2d;

const int AsciiTable::GroupIdAsciiTable = 843638392; // RNG based to avoid conflicts

AsciiTable* AsciiTable::create()
{
	AsciiTable* instance = new AsciiTable();

	instance->autorelease();

	return instance;
}

AsciiTable::AsciiTable()
{
	this->asciiLetters = std::vector<SmartAsciiLabel*>();
	this->immediateBlock = nullptr;
	this->onCloseCallback = nullptr;

	this->background = Sprite::create(CipherResources::PopupPanelBack);
	this->scrollPane = ScrollPane::create(Size(1180.0f, 480.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);

	for (int next = 0; next < 256; next++)
	{
		this->asciiLetters.push_back(SmartAsciiLabel::create((unsigned char)(next)));
	}

	this->frame = Sprite::create(CipherResources::PopupPanelFrame);

	this->toggleButtonBin = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_BinaryButtonActive, CipherResources::Buttons_BinaryButtonActive),
		ClickableNode::create(CipherResources::Buttons_BinaryButton, CipherResources::Buttons_BinaryButtonSelected),
		AsciiTable::GroupIdAsciiTable
	);
	this->toggleButtonDec = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_DecimalButtonActive, CipherResources::Buttons_DecimalButtonActive),
		ClickableNode::create(CipherResources::Buttons_DecimalButton, CipherResources::Buttons_DecimalButtonSelected),
		AsciiTable::GroupIdAsciiTable
	);
	this->toggleButtonHex = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_HexButtonActive, CipherResources::Buttons_HexButtonActive),
		ClickableNode::create(CipherResources::Buttons_HexButton, CipherResources::Buttons_HexButtonSelected),
		AsciiTable::GroupIdAsciiTable
	);
	this->toggleButtonAscii = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_AsciiButtonActive, CipherResources::Buttons_AsciiButtonActive),
		ClickableNode::create(CipherResources::Buttons_AsciiButton, CipherResources::Buttons_AsciiButtonSelected),
		AsciiTable::GroupIdAsciiTable
	);

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelSelected = returnLabel->clone();

	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);

	returnLabelSelected->setColor(Color3B::YELLOW);
	returnLabelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelSelected->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(returnLabel, returnLabelSelected, CipherResources::Buttons_TestRunButton, CipherResources::Buttons_TestRunButtonSelected);	

	this->scrollPane->renderCustomBackground([=](DrawNode* customBackground, Size totalSize, Size paddingSize, Size marginSize)
	{
		std::vector<Vec2> verticies = std::vector<Vec2>();

		const float CornerSizeInner = 72.0f;
		const float CornerSize = 56.0f;

		// Bottom left
		verticies.push_back(Vec2(CornerSizeInner, 0.0f));
		verticies.push_back(Vec2(0.0f, CornerSize));

		// Top left
		verticies.push_back(Vec2(0.0f, totalSize.height - CornerSize));
		verticies.push_back(Vec2(CornerSizeInner, totalSize.height));

		// Top right
		verticies.push_back(Vec2(totalSize.width - CornerSizeInner, totalSize.height));
		verticies.push_back(Vec2(totalSize.width, totalSize.height - CornerSize));

		// Bottom right
		verticies.push_back(Vec2(totalSize.width, CornerSize));
		verticies.push_back(Vec2(totalSize.width - CornerSizeInner, 0.0f));

		for (auto it = verticies.begin(); it != verticies.end(); it++)
		{
			it->y -= marginSize.height;
		}

		customBackground->drawSolidPoly(verticies.data(), verticies.size(), Color4F(Color4B(0, 0, 0, 128)));
	});

	this->addChild(this->background);

	for (auto it = this->asciiLetters.begin(); it != this->asciiLetters.end(); it++)
	{
		this->scrollPane->addChild(*it);
	}

	this->addChild(this->scrollPane);
	this->addChild(this->frame);
	this->addChild(this->toggleButtonBin);
	this->addChild(this->toggleButtonDec);
	this->addChild(this->toggleButtonHex);
	this->addChild(this->toggleButtonAscii);
	this->addChild(this->returnButton);
}

AsciiTable::~AsciiTable()
{
}

void AsciiTable::onEnter()
{
	super::onEnter();
}

void AsciiTable::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	int index = 0;

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->scrollPane->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 52.0f + 24.0f));

	for (auto it = this->asciiLetters.begin(); it != this->asciiLetters.end(); it++, index++)
	{
		const int GridWidth = 8;
		const int GridHeight = 32;

		int x = index / GridHeight;
		int y = index % GridHeight;

		(*it)->setPosition(Vec2((float(x - GridWidth / 2) + 0.5f) * 136.0f, float(-y) * 40.0f));
	}

	this->frame->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	this->toggleButtonDec->setPosition(Vec2(visibleSize.width / 2.0f - 512.0f + 64.0f * 0.0f, visibleSize.height / 2.0f - 356.0f));
	this->toggleButtonHex->setPosition(Vec2(visibleSize.width / 2.0f - 512.0f + 64.0f * 1.0f, visibleSize.height / 2.0f - 356.0f));
	this->toggleButtonBin->setPosition(Vec2(visibleSize.width / 2.0f - 512.0f + 64.0f * 2.0f, visibleSize.height / 2.0f - 356.0f));
	this->toggleButtonAscii->setPosition(Vec2(visibleSize.width / 2.0f - 512.0f + 64.0f * 3.0f, visibleSize.height / 2.0f - 356.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 356.0f));
}

void AsciiTable::initializeListeners()
{
	super::initializeListeners();

	this->toggleButtonBin->setCheckCallback([=](RadioButton*)
	{
		CipherEvents::TriggerChangeDisplayDataType(CipherEvents::CipherChangeDisplayDataTypeArgs(CipherEvents::DisplayDataType::Bin));
	});
	this->toggleButtonDec->setCheckCallback([=](RadioButton*)
	{
		CipherEvents::TriggerChangeDisplayDataType(CipherEvents::CipherChangeDisplayDataTypeArgs(CipherEvents::DisplayDataType::Dec));
	});
	this->toggleButtonHex->setCheckCallback([=](RadioButton*)
	{
		CipherEvents::TriggerChangeDisplayDataType(CipherEvents::CipherChangeDisplayDataTypeArgs(CipherEvents::DisplayDataType::Hex));
	});
	this->toggleButtonAscii->setCheckCallback([=](RadioButton*)
	{
		CipherEvents::TriggerChangeDisplayDataType(CipherEvents::CipherChangeDisplayDataTypeArgs(CipherEvents::DisplayDataType::Ascii));
	});

	this->returnButton->setClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->close();
	});
}

void AsciiTable::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void AsciiTable::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}

void AsciiTable::open(ImmediateBlock* immediateBlock, std::function<void()> onCloseCallback)
{
	this->immediateBlock = immediateBlock;
	this->onCloseCallback = onCloseCallback;

	this->setVisible(true);
	GameUtils::focus(this);

	// TODO: Auto-focus the immediate block's current value
}

void AsciiTable::close()
{
	this->setVisible(false);
	GameUtils::focus(this->getParent());
	MouseEvents::TriggerMouseRefresh(MouseState::getMouseState());
	
	// TODO: Update referenced immediate block's value

	if (this->onCloseCallback != nullptr)
	{
		this->onCloseCallback();
	}
}
