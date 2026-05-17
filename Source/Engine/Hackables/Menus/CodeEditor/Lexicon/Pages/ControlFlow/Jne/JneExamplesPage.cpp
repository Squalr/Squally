#include "JneExamplesPage.h"

#include "2d/CCDrawNode.h"
#include "2d/CCSprite.h"

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string JneExamplesPage::Identifier = "JNE_EXAMPLES_PAGE";

JneExamplesPage* JneExamplesPage::create()
{
	JneExamplesPage* instance = new JneExamplesPage();

	instance->autorelease();

	return instance;
}

JneExamplesPage::JneExamplesPage() : super(JneExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->codePanel = Sprite::create(UIResources::Menus_LexiconMenu_RegisterBlockBinary);
	this->registerASelector = Sprite::create(UIResources::Menus_LexiconMenu_SourceSelector);
	this->registerBSelector = Sprite::create(UIResources::Menus_LexiconMenu_SourceSelector);
	this->instructionPointerSelector = Sprite::create(UIResources::Menus_LexiconMenu_DestSelector);
	this->flowArrowNode = DrawNode::create();
	this->executeButton = this->buildExecuteButton();
	this->example0Button = this->buildSetAndResetButton();
	this->example1Button = this->buildSetAndResetButton();
	this->example2Button = this->buildSetAndResetButton();
	this->flagString = ConstantString::create("");
	this->flagLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, this->flagString);
	this->pathLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Hacking_Lexicon_Pages_ControlFlow_Jne_JumpNotTaken::create());
	this->example0Label = this->buildExampleLabel(this->buildRegisterSetupString(8, 8));
	this->example1Label = this->buildExampleLabel(this->buildRegisterSetupString(8, 5));
	this->example2Label = this->buildExampleLabel(this->buildRegisterSetupString(5, 8));

	this->examplesLabel->setTextColor(super::TextColor);
	this->flagLabel->setTextColor(super::TextColor);
	this->pathLabel->setTextColor(super::TextColor);
	this->registerASelector->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->registerBSelector->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->instructionPointerSelector->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->registerASelector->setOpacity(0);
	this->registerBSelector->setOpacity(0);
	this->instructionPointerSelector->setOpacity(0);

	LocalizedString* cmpString = Strings::Menus_Hacking_Lexicon_Assembly_Cmp::create();
	LocalizedString* jneString = Strings::Menus_Hacking_Lexicon_Assembly_Jne::create();
	LocalizedString* movString = Strings::Menus_Hacking_Lexicon_Assembly_Mov::create();
	LocalizedString* addString = Strings::Menus_Hacking_Lexicon_Assembly_Add::create();

	cmpString->setStringReplacementVariables({ this->registerAString(), this->registerBString() });
	jneString->setStringReplacementVariables(ConstantString::create("not_equal"));
	movString->setStringReplacementVariables({ this->registerCString(), ConstantString::create("0") });
	addString->setStringReplacementVariables({ this->registerCString(), ConstantString::create("1") });

	this->buildAddressedCodeLabel("100", cmpString);
	this->buildAddressedCodeLabel("104", jneString);
	this->buildAddressedCodeLabel("108", movString);
	this->buildCodeLabel(ConstantString::create("112: not_equal:"));
	this->buildAddressedCodeLabel("116", addString);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->registerASelector);
	this->addChild(this->registerBSelector);
	this->addChild(this->instructionPointerSelector);
	this->addChild(this->flagLabel);
	this->addChild(this->pathLabel);
	this->addChild(this->codePanel);
	this->addChild(this->flowArrowNode);
	this->addChild(this->executeButton);
	this->addChild(this->example0Button);
	this->addChild(this->example1Button);
	this->addChild(this->example2Button);
	this->addChild(this->example0Label);
	this->addChild(this->example1Label);
	this->addChild(this->example2Label);

	for (LocalizedLabel* next : this->codeLabels)
	{
		this->addChild(next);
	}
}

JneExamplesPage::~JneExamplesPage()
{
}

void JneExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = 178.0f;
	const float buttonSpacing = -50.0f;
	const float codeTop = -50.0f;
	const float codeSpacing = -38.0f;

	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->registerBlock->setPosition(Vec2(-148.0f, 150.0f));
	this->registerASelector->setPosition(Vec2(-256.0f, 262.0f));
	this->registerBSelector->setPosition(Vec2(-256.0f, 234.0f));
	this->instructionPointerSelector->setPosition(Vec2(-256.0f, 38.0f));
	this->flagLabel->setPosition(Vec2(116.0f, 266.0f));
	this->pathLabel->setPosition(Vec2(116.0f, 232.0f));
	this->codePanel->setPosition(Vec2(0.0f, -150.0f));
	this->example0Button->setPosition(Vec2(56.0f, buttonOffset + buttonSpacing * 0.0f));
	this->example1Button->setPosition(Vec2(56.0f, buttonOffset + buttonSpacing * 1.0f));
	this->example2Button->setPosition(Vec2(56.0f, buttonOffset + buttonSpacing * 2.0f));
	this->example0Label->setPosition(Vec2(142.0f, buttonOffset + buttonSpacing * 0.0f));
	this->example1Label->setPosition(Vec2(142.0f, buttonOffset + buttonSpacing * 1.0f));
	this->example2Label->setPosition(Vec2(142.0f, buttonOffset + buttonSpacing * 2.0f));
	this->executeButton->setPosition(Vec2(56.0f, buttonOffset + buttonSpacing * 3.0f));

	for (int index = 0; index < int(this->codeLabels.size()); index++)
	{
		this->codeLabels[index]->setPosition(Vec2(-204.0f, codeTop + codeSpacing * float(index)));
	}
}

void JneExamplesPage::initializeListeners()
{
	super::initializeListeners();

	this->executeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->executeExample(); });
	this->example0Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setExample(0); });
	this->example1Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setExample(1); });
	this->example2Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setExample(2); });

	this->executeButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightExecute(); });
	this->example0Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightSetAndReset(); });
	this->example1Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightSetAndReset(); });
	this->example2Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightSetAndReset(); });

	this->executeButton->setMouseOutCallback([=](InputEvents::MouseEventArgs* args)
	{
		if (args == nullptr || !this->isMouseOverActionButton(args->mouseCoords))
		{
			this->hideSelectors();
		}
	});

	this->example0Button->setMouseOutCallback([=](InputEvents::MouseEventArgs* args)
	{
		if (args == nullptr || !this->isMouseOverActionButton(args->mouseCoords))
		{
			this->hideSelectors();
		}
	});

	this->example1Button->setMouseOutCallback([=](InputEvents::MouseEventArgs* args)
	{
		if (args == nullptr || !this->isMouseOverActionButton(args->mouseCoords))
		{
			this->hideSelectors();
		}
	});

	this->example2Button->setMouseOutCallback([=](InputEvents::MouseEventArgs* args)
	{
		if (args == nullptr || !this->isMouseOverActionButton(args->mouseCoords))
		{
			this->hideSelectors();
		}
	});
}

void JneExamplesPage::resetState()
{
	this->selectedExampleIndex = 0;
	this->registerBlock->initEax(8);
	this->registerBlock->initEbx(8);
	this->registerBlock->initEcx(7);
	this->registerBlock->initEdx(0);
	this->registerBlock->initEdi(0);
	this->registerBlock->initEsi(0);
	this->registerBlock->initEbp(0x0E20000);
	this->registerBlock->initEsp(0x0E20008);
	this->registerBlock->initEip(100);

	this->flagString->setString("ZF = 1");
	this->pathLabel->setLocalizedString(Strings::Menus_Hacking_Lexicon_Pages_ControlFlow_Jne_JumpNotTaken::create());
	this->updateCodeHighlights(false, false);
	this->drawFlowArrows(false);
}

void JneExamplesPage::setExample(int exampleIndex)
{
	this->selectedExampleIndex = exampleIndex;
	this->updateState(exampleIndex, false);
}

void JneExamplesPage::executeExample()
{
	this->updateState(this->selectedExampleIndex, true);
}

void JneExamplesPage::highlightSetAndReset()
{
	this->registerASelector->setOpacity(255);
	this->registerBSelector->setOpacity(255);
	this->instructionPointerSelector->setOpacity(0);
}

void JneExamplesPage::highlightExecute()
{
	this->registerASelector->setOpacity(0);
	this->registerBSelector->setOpacity(0);
	this->instructionPointerSelector->setOpacity(255);
}

void JneExamplesPage::clearHighlights()
{
	this->registerBlock->clearHighlights();
	this->hideSelectors();
}

void JneExamplesPage::hideSelectors()
{
	this->registerASelector->setOpacity(0);
	this->registerBSelector->setOpacity(0);
	this->instructionPointerSelector->setOpacity(0);
}

bool JneExamplesPage::isMouseOverActionButton(Vec2 mouseCoords)
{
	return GameUtils::intersects(this->executeButton, mouseCoords, true)
		|| GameUtils::intersects(this->example0Button, mouseCoords, true)
		|| GameUtils::intersects(this->example1Button, mouseCoords, true)
		|| GameUtils::intersects(this->example2Button, mouseCoords, true);
}

void JneExamplesPage::updateState(int exampleIndex, bool executeWholeExample)
{
	const unsigned long long registerAValues[] = { 8, 8, 5 };
	const unsigned long long registerBValues[] = { 8, 5, 8 };
	const bool jumps = registerAValues[exampleIndex] != registerBValues[exampleIndex];

	this->registerBlock->setEax(registerAValues[exampleIndex]);
	this->registerBlock->setEbx(registerBValues[exampleIndex]);
	this->registerBlock->setEcx(executeWholeExample ? (jumps ? 8 : 1) : 7);
	this->registerBlock->setEip(executeWholeExample ? 120 : 100);
	this->flagString->setString(jumps ? "ZF = 0" : "ZF = 1");
	this->pathLabel->setLocalizedString(jumps ? Strings::Menus_Hacking_Lexicon_Pages_ControlFlow_Jne_JumpTaken::create() : Strings::Menus_Hacking_Lexicon_Pages_ControlFlow_Jne_JumpNotTaken::create());

	this->updateCodeHighlights(jumps, executeWholeExample);
	this->drawFlowArrows(jumps);
}

void JneExamplesPage::updateCodeHighlights(bool jumps, bool executeWholeExample)
{
	for (LocalizedLabel* next : this->codeLabels)
	{
		next->setTextColor(super::TextColor);
	}

	if (executeWholeExample)
	{
		this->codeLabels[0]->setTextColor(super::TextColorChanged);
		this->codeLabels[1]->setTextColor(super::TextColorChanged);
		this->codeLabels[3]->setTextColor(super::TextColorChanged);
		this->codeLabels[4]->setTextColor(super::TextColorChanged);

		if (!jumps)
		{
			this->codeLabels[2]->setTextColor(super::TextColorChanged);
		}
	}
}

void JneExamplesPage::drawFlowArrows(bool jumps)
{
	this->flowArrowNode->clear();

	const Color4F activeColor = Color4F(super::TextColorChanged);
	const Color4F inactiveColor = Color4F(Color4B(120, 120, 120, 120));
	const Color4F fallthroughColor = jumps ? inactiveColor : activeColor;
	const Color4F jumpColor = jumps ? activeColor : inactiveColor;

	this->drawArrowSegment(Vec2(-230.0f, -88.0f), Vec2(-230.0f, -126.0f), fallthroughColor);
	this->flowArrowNode->drawSegment(Vec2(76.0f, -88.0f), Vec2(220.0f, -88.0f), 2.0f, jumpColor);
	this->flowArrowNode->drawSegment(Vec2(220.0f, -88.0f), Vec2(220.0f, -164.0f), 2.0f, jumpColor);
	this->drawArrowSegment(Vec2(220.0f, -164.0f), Vec2(154.0f, -164.0f), jumpColor);
}

void JneExamplesPage::drawArrowSegment(Vec2 from, Vec2 to, const Color4F& color)
{
	const float arrowHeadLength = 12.0f;
	const float arrowHeadWidth = 6.0f;
	Vec2 direction = to - from;
	const float length = direction.length();

	if (length <= 0.0f)
	{
		return;
	}

	direction.normalize();
	const Vec2 normal = Vec2(-direction.y, direction.x);
	const Vec2 base = to - direction * arrowHeadLength;

	this->flowArrowNode->drawSegment(from, to, 2.0f, color);
	this->flowArrowNode->drawTriangle(to, base + normal * arrowHeadWidth, base - normal * arrowHeadWidth, color);
}

ClickableTextNode* JneExamplesPage::buildSetAndResetButton()
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Hacking_Lexicon_SetAndReset::create());
	LocalizedLabel* labelSelected = label->clone();
	ClickableTextNode* button = ClickableTextNode::create(label, labelSelected, UIResources::Menus_LexiconMenu_ExecuteButton, UIResources::Menus_LexiconMenu_ExecuteButtonSelected);

	label->setTextColor(super::TextColor);
	labelSelected->setTextColor(super::TextColor);

	return button;
}

void JneExamplesPage::buildAddressedCodeLabel(std::string address, LocalizedString* instruction)
{
	LocalizedString* addressedInstruction = Strings::Common_XColonYSpaced::create();

	addressedInstruction->setStringReplacementVariables({ ConstantString::create(address), instruction });
	this->buildCodeLabel(addressedInstruction);
}

void JneExamplesPage::buildCodeLabel(LocalizedString* text)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, text);

	label->setTextColor(super::TextColor);
	label->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->codeLabels.push_back(label);
}

LocalizedLabel* JneExamplesPage::buildExampleLabel(LocalizedString* text)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, text);

	label->setTextColor(super::TextColor);
	label->setAnchorPoint(Vec2(0.0f, 0.5f));

	return label;
}

LocalizedString* JneExamplesPage::buildRegisterSetupString(unsigned long long valueA, unsigned long long valueB)
{
	LocalizedString* registerASetupString = Strings::Common_XEqualsY::create();
	LocalizedString* registerBSetupString = Strings::Common_XEqualsY::create();
	LocalizedString* registerASetupWithCommaString = Strings::Common_Concat::create();
	LocalizedString* setupString = Strings::Common_Concat::create();

	registerASetupString->setStringReplacementVariables({
		this->registerAString(),
		ConstantString::create(std::to_string(valueA))
	});
	registerBSetupString->setStringReplacementVariables({
		this->registerBString(),
		ConstantString::create(std::to_string(valueB))
	});
	registerASetupWithCommaString->setStringReplacementVariables({
		registerASetupString,
		ConstantString::create(", ")
	});
	setupString->setStringReplacementVariables({
		registerASetupWithCommaString,
		registerBSetupString
	});

	return setupString;
}

LocalizedString* JneExamplesPage::registerAString()
{
	return sizeof(void*) == 4 ? Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create() : Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create();
}

LocalizedString* JneExamplesPage::registerBString()
{
	return sizeof(void*) == 4 ? Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create() : Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create();
}

LocalizedString* JneExamplesPage::registerCString()
{
	return sizeof(void*) == 4 ? Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create() : Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create();
}
