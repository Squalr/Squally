#include "CipherImmediateEditor.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Input/InputText.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/RadioButton.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/Special/ImmediateBlock.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

#include "Strings/Menus/Accept.h"
#include "Strings/Cipher/EnterAValue.h"
#include "Strings/Cipher/ValueEditor.h"

using namespace cocos2d;

const int CipherImmediateEditor::GroupIdCipherImmediateEditor = 381435550; // RNG based to avoid conflicts

CipherImmediateEditor* CipherImmediateEditor::create()
{
	CipherImmediateEditor* instance = new CipherImmediateEditor();

	instance->autorelease();

	return instance;
}

CipherImmediateEditor::CipherImmediateEditor()
{
	this->background = Sprite::create(CipherResources::PopupPanelBack);
	this->previewImmediate = ImmediateBlock::create(BlockBase::BlockType::Static);
	this->enterAValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Cipher_EnterAValue::create());
	this->inputFrame = Sprite::create(CipherResources::InputFrame);
	this->inputText = InputText::create(Size(224.0f, 38.0f), LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, true);
	this->frame = Sprite::create(CipherResources::PopupPanelFrame);
	this->toggleButtonBin = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_BinaryButtonActive, CipherResources::Buttons_BinaryButtonActive),
		ClickableNode::create(CipherResources::Buttons_BinaryButton, CipherResources::Buttons_BinaryButtonSelected),
		CipherImmediateEditor::GroupIdCipherImmediateEditor
	);
	this->toggleButtonDec = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_DecimalButtonActive, CipherResources::Buttons_DecimalButtonActive),
		ClickableNode::create(CipherResources::Buttons_DecimalButton, CipherResources::Buttons_DecimalButtonSelected),
		CipherImmediateEditor::GroupIdCipherImmediateEditor
	);
	this->toggleButtonHex = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_HexButtonActive, CipherResources::Buttons_HexButtonActive),
		ClickableNode::create(CipherResources::Buttons_HexButton, CipherResources::Buttons_HexButtonSelected),
		CipherImmediateEditor::GroupIdCipherImmediateEditor
	);
	this->toggleButtonAscii = RadioButton::create(
		ClickableNode::create(CipherResources::Buttons_AsciiButtonActive, CipherResources::Buttons_AsciiButtonActive),
		ClickableNode::create(CipherResources::Buttons_AsciiButton, CipherResources::Buttons_AsciiButtonSelected),
		CipherImmediateEditor::GroupIdCipherImmediateEditor
	);

	LocalizedLabel*	acceptLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Accept::create());
	LocalizedLabel*	acceptLabelSelected = acceptLabel->clone();

	acceptLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	acceptLabel->enableGlow(Color4B::BLACK);

	acceptLabelSelected->setColor(Color3B::YELLOW);
	acceptLabelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	acceptLabelSelected->enableGlow(Color4B::ORANGE);

	this->acceptButton = ClickableTextNode::create(acceptLabel, acceptLabelSelected, CipherResources::Buttons_TestRunButton, CipherResources::Buttons_TestRunButtonSelected);
	this->immediateEditorLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_ValueEditor::create());

	this->enterAValueLabel->enableOutline(Color4B::BLACK, 2);
	this->immediateEditorLabel->enableOutline(Color4B::BLACK, 2);
	this->immediateEditorLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	this->enterAValueLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->inputFrame->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->inputText->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->inputFrame->addChild(this->inputText);
	this->addChild(this->background);
	this->addChild(this->previewImmediate);
	this->addChild(this->enterAValueLabel);
	this->addChild(this->inputFrame);
	this->addChild(this->frame);
	this->addChild(this->toggleButtonBin);
	this->addChild(this->toggleButtonDec);
	this->addChild(this->toggleButtonHex);
	this->addChild(this->toggleButtonAscii);
	this->addChild(this->acceptButton);
	this->addChild(this->immediateEditorLabel);
}

CipherImmediateEditor::~CipherImmediateEditor()
{
}

void CipherImmediateEditor::onEnter()
{
	super::onEnter();

	this->toggleButtonAscii->check();
}

void CipherImmediateEditor::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->previewImmediate->setPosition(Vec2(visibleSize.width / 2.0f - 160.0f, visibleSize.height / 2.0f + 80.0f));
	this->enterAValueLabel->setPosition(Vec2(visibleSize.width / 2.0f + 32.0f, visibleSize.height / 2.0f + 128.0f));
	this->inputFrame->setPosition(Vec2(visibleSize.width / 2.0f + 32.0f, visibleSize.height / 2.0f + 80.0f));
	this->inputText->setPosition(Vec2(12.0f, 0.0f));
	this->toggleButtonDec->setPosition(Vec2(visibleSize.width / 2.0f - 284.0f + 64.0f * 0.0f, visibleSize.height / 2.0f - 180.0f));
	this->toggleButtonHex->setPosition(Vec2(visibleSize.width / 2.0f - 284.0f + 64.0f * 1.0f, visibleSize.height / 2.0f - 180.0f));
	this->toggleButtonBin->setPosition(Vec2(visibleSize.width / 2.0f - 284.0f + 64.0f * 2.0f, visibleSize.height / 2.0f - 180.0f));
	this->toggleButtonAscii->setPosition(Vec2(visibleSize.width / 2.0f - 284.0f + 64.0f * 3.0f, visibleSize.height / 2.0f - 180.0f));
	this->frame->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->acceptButton->setPosition(Vec2(visibleSize.width / 2.0f + 128.0f, visibleSize.height / 2.0f - 180.0f));
	this->immediateEditorLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 240.0f));
}

void CipherImmediateEditor::initializeListeners()
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
	this->acceptButton->setClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->close();
	});
}

void CipherImmediateEditor::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void CipherImmediateEditor::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}

void CipherImmediateEditor::open(ImmediateBlock* immediateBlock, std::function<void()> onCloseCallback)
{
	this->immediateBlock = immediateBlock;
	this->onCloseCallback = onCloseCallback;

	this->setVisible(true);
	GameUtils::focus(this);

	this->inputText->attachWithIME();
}

void CipherImmediateEditor::close()
{
	this->setVisible(false);
	GameUtils::focus(this->getParent());
	MouseEvents::TriggerMouseRefresh(MouseState::getMouseState());

	if (this->onCloseCallback != nullptr)
	{
		this->onCloseCallback();
	}
}
