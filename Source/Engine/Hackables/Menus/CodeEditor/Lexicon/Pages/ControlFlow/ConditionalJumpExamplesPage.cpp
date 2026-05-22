#include "ConditionalJumpExamplesPage.h"

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

const std::string ConditionalJumpExamplesPage::JnabeIdentifier = "JNABE_EXAMPLES_PAGE";
const std::string ConditionalJumpExamplesPage::JneIdentifier = "JNE_EXAMPLES_PAGE";
const std::string ConditionalJumpExamplesPage::JngleIdentifier = "JNGLE_EXAMPLES_PAGE";
const std::string ConditionalJumpExamplesPage::JnoIdentifier = "JNO_EXAMPLES_PAGE";
const std::string ConditionalJumpExamplesPage::JnpIdentifier = "JNP_EXAMPLES_PAGE";
const std::string ConditionalJumpExamplesPage::JnsIdentifier = "JNS_EXAMPLES_PAGE";
const std::string ConditionalJumpExamplesPage::JnzIdentifier = "JNZ_EXAMPLES_PAGE";
const std::string ConditionalJumpExamplesPage::JzcxzIdentifier = "JZCXZ_EXAMPLES_PAGE";

ConditionalJumpExamplesPage* ConditionalJumpExamplesPage::create(Operation operation)
{
	ConditionalJumpExamplesPage* instance = new ConditionalJumpExamplesPage(operation);

	instance->autorelease();

	return instance;
}

ConditionalJumpExamplesPage::ConditionalJumpExamplesPage(Operation operation) : super(ConditionalJumpExamplesPage::getIdentifier(operation), PageType::Right)
{
	this->operation = operation;
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
	this->flagLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, this->conditionString(0));
	this->pathLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, this->pathString(0));
	this->example0Label = this->buildExampleLabel(0);
	this->example1Label = this->buildExampleLabel(1);
	this->example2Label = this->buildExampleLabel(2);

	if (this->usesHexDisplay())
	{
		this->registerBlock->setDisplayMode(RegisterBlock::DisplayMode::Hex);
		this->registerBlock->setDisplayBitCount(int(sizeof(void*) * 8));
	}

	this->registerBlock->setMemoryTitleLocalizedString(Strings::Menus_Hacking_Lexicon_Flags::create());
	this->registerBlock->setMemoryTitleVisible(true);
	this->examplesLabel->setTextColor(super::TextColor);
	this->flagLabel->setTextColor(super::TextColor);
	this->pathLabel->setTextColor(super::TextColor);
	this->flagLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->pathLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->registerASelector->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->registerBSelector->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->instructionPointerSelector->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->registerASelector->setOpacity(0);
	this->registerBSelector->setOpacity(0);
	this->instructionPointerSelector->setOpacity(0);

	this->buildCodeLabels();
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

ConditionalJumpExamplesPage::~ConditionalJumpExamplesPage()
{
}

const std::string& ConditionalJumpExamplesPage::getIdentifier(Operation operation)
{
	switch (operation)
	{
		case Operation::Jnabe: return ConditionalJumpExamplesPage::JnabeIdentifier;
		case Operation::Jne: return ConditionalJumpExamplesPage::JneIdentifier;
		case Operation::Jngle: return ConditionalJumpExamplesPage::JngleIdentifier;
		case Operation::Jno: return ConditionalJumpExamplesPage::JnoIdentifier;
		case Operation::Jnp: return ConditionalJumpExamplesPage::JnpIdentifier;
		case Operation::Jns: return ConditionalJumpExamplesPage::JnsIdentifier;
		case Operation::Jnz: return ConditionalJumpExamplesPage::JnzIdentifier;
		case Operation::Jzcxz: return ConditionalJumpExamplesPage::JzcxzIdentifier;
		default: return ConditionalJumpExamplesPage::JneIdentifier;
	}
}

void ConditionalJumpExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = 186.0f;
	const float buttonSpacing = -50.0f;
	const float buttonX = 56.0f;
	const float buttonLeftX = -20.0f;
	const float codeTop = -50.0f;
	const float codeSpacing = -38.0f;

	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->registerBlock->setPosition(Vec2(-148.0f, 150.0f));
	this->registerBlock->setMemoryTitleX(buttonLeftX - this->registerBlock->getPositionX());
	this->registerASelector->setPosition(this->usesConditionRegisterSelector() ? Vec2(-256.0f, 206.0f) : Vec2(-256.0f, 262.0f));
	this->registerBSelector->setPosition(Vec2(-256.0f, 234.0f));
	this->instructionPointerSelector->setPosition(Vec2(-256.0f, 38.0f));
	this->flagLabel->setPosition(Vec2(buttonLeftX, 274.0f));
	this->pathLabel->setPosition(Vec2(buttonLeftX, 240.0f));
	this->codePanel->setPosition(Vec2(0.0f, -150.0f));
	this->example0Button->setPosition(Vec2(buttonX, buttonOffset + buttonSpacing * 0.0f));
	this->example1Button->setPosition(Vec2(buttonX, buttonOffset + buttonSpacing * 1.0f));
	this->example2Button->setPosition(Vec2(buttonX, buttonOffset + buttonSpacing * 2.0f));
	this->example0Label->setPosition(Vec2(142.0f, buttonOffset + buttonSpacing * 0.0f));
	this->example1Label->setPosition(Vec2(142.0f, buttonOffset + buttonSpacing * 1.0f));
	this->example2Label->setPosition(Vec2(142.0f, buttonOffset + buttonSpacing * 2.0f));
	this->executeButton->setPosition(Vec2(buttonX, buttonOffset + buttonSpacing * 3.0f));

	for (int index = 0; index < int(this->codeLabels.size()); index++)
	{
		this->codeLabels[index]->setPosition(Vec2(-204.0f, codeTop + codeSpacing * float(index)));
	}
}

void ConditionalJumpExamplesPage::initializeListeners()
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

void ConditionalJumpExamplesPage::resetState()
{
	this->selectedExampleIndex = 0;
	this->registerBlock->initEax(this->registerAValue(0));
	this->registerBlock->initEbx(this->registerBValue(0));
	this->registerBlock->initEcx(this->usesConditionRegisterSelector() ? this->conditionRegisterValue(0) : 7);
	this->registerBlock->initEdx(0);
	this->registerBlock->initEdi(0);
	this->registerBlock->initEsi(0);
	this->registerBlock->initEbp(0x0E20000);
	this->registerBlock->initEsp(0x0E20008);
	this->registerBlock->initEip(100);

	this->flagLabel->setLocalizedString(this->conditionString(0));
	this->pathLabel->setLocalizedString(this->pathString(0));
	this->updateCodeHighlights(this->jumps(0), false);
	this->drawFlowArrows(this->jumps(0));
}

void ConditionalJumpExamplesPage::setExample(int exampleIndex)
{
	this->selectedExampleIndex = exampleIndex;
	this->updateState(exampleIndex, false);
}

void ConditionalJumpExamplesPage::executeExample()
{
	this->updateState(this->selectedExampleIndex, true);
}

void ConditionalJumpExamplesPage::highlightSetAndReset()
{
	this->registerASelector->setOpacity(255);
	this->registerBSelector->setOpacity(this->usesRegisterBSelector() ? 255 : 0);
	this->instructionPointerSelector->setOpacity(0);
}

void ConditionalJumpExamplesPage::highlightExecute()
{
	this->registerASelector->setOpacity(0);
	this->registerBSelector->setOpacity(0);
	this->instructionPointerSelector->setOpacity(255);
}

void ConditionalJumpExamplesPage::clearHighlights()
{
	this->registerBlock->clearHighlights();
	this->hideSelectors();
}

void ConditionalJumpExamplesPage::hideSelectors()
{
	this->registerASelector->setOpacity(0);
	this->registerBSelector->setOpacity(0);
	this->instructionPointerSelector->setOpacity(0);
}

bool ConditionalJumpExamplesPage::isMouseOverActionButton(Vec2 mouseCoords)
{
	return GameUtils::intersects(this->executeButton, mouseCoords, true)
		|| GameUtils::intersects(this->example0Button, mouseCoords, true)
		|| GameUtils::intersects(this->example1Button, mouseCoords, true)
		|| GameUtils::intersects(this->example2Button, mouseCoords, true);
}

void ConditionalJumpExamplesPage::updateState(int exampleIndex, bool executeWholeExample)
{
	unsigned long long nextRegisterA = executeWholeExample ? this->registerAExecutedValue(exampleIndex) : this->registerAValue(exampleIndex);

	if (this->usesConditionRegisterSelector())
	{
		nextRegisterA = this->resultRegisterValue(exampleIndex, executeWholeExample);
	}

	this->registerBlock->setEax(nextRegisterA);
	this->registerBlock->setEbx(this->registerBValue(exampleIndex));
	this->registerBlock->setEcx(this->usesConditionRegisterSelector() ? this->conditionRegisterValue(exampleIndex) : this->resultRegisterValue(exampleIndex, executeWholeExample));
	this->registerBlock->setEip(executeWholeExample ? this->finalInstructionPointer() : 100);
	this->flagLabel->setLocalizedString(this->conditionString(exampleIndex));
	this->pathLabel->setLocalizedString(this->pathString(exampleIndex));

	this->updateCodeHighlights(this->jumps(exampleIndex), executeWholeExample);
	this->drawFlowArrows(this->jumps(exampleIndex));
}

void ConditionalJumpExamplesPage::updateCodeHighlights(bool jumps, bool executeWholeExample)
{
	for (LocalizedLabel* next : this->codeLabels)
	{
		next->setTextColor(super::TextColor);
	}

	if (executeWholeExample)
	{
		if (this->setupInstruction() != SetupInstruction::None)
		{
			this->codeLabels[0]->setTextColor(super::TextColorChanged);
		}

		this->codeLabels[this->jumpCodeIndex()]->setTextColor(super::TextColorChanged);
		this->codeLabels[this->targetCodeIndex()]->setTextColor(super::TextColorChanged);
		this->codeLabels[this->targetCodeIndex() + 1]->setTextColor(super::TextColorChanged);

		if (!jumps)
		{
			this->codeLabels[this->jumpCodeIndex() + 1]->setTextColor(super::TextColorChanged);
		}
	}
}

void ConditionalJumpExamplesPage::drawFlowArrows(bool jumps)
{
	this->flowArrowNode->clear();

	const float codeTop = -50.0f;
	const float codeSpacing = -38.0f;
	const float jumpY = codeTop + codeSpacing * float(this->jumpCodeIndex());
	const float fallthroughY = codeTop + codeSpacing * float(this->jumpCodeIndex() + 1);
	const float targetY = codeTop + codeSpacing * float(this->targetCodeIndex());
	const Color4F activeColor = Color4F(super::TextColorChanged);
	const Color4F inactiveColor = Color4F(Color4B(120, 120, 120, 120));
	const Color4F fallthroughColor = jumps ? inactiveColor : activeColor;
	const Color4F jumpColor = jumps ? activeColor : inactiveColor;

	this->drawArrowSegment(Vec2(-230.0f, jumpY), Vec2(-230.0f, fallthroughY), fallthroughColor);
	this->flowArrowNode->drawSegment(Vec2(76.0f, jumpY), Vec2(220.0f, jumpY), 2.0f, jumpColor);
	this->flowArrowNode->drawSegment(Vec2(220.0f, jumpY), Vec2(220.0f, targetY), 2.0f, jumpColor);
	this->drawArrowSegment(Vec2(220.0f, targetY), Vec2(154.0f, targetY), jumpColor);
}

void ConditionalJumpExamplesPage::drawArrowSegment(Vec2 from, Vec2 to, const Color4F& color)
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

ClickableTextNode* ConditionalJumpExamplesPage::buildSetAndResetButton()
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Hacking_Lexicon_SetAndReset::create());
	LocalizedLabel* labelSelected = label->clone();
	ClickableTextNode* button = ClickableTextNode::create(label, labelSelected, UIResources::Menus_LexiconMenu_ExecuteButton, UIResources::Menus_LexiconMenu_ExecuteButtonSelected);

	label->setTextColor(super::TextColor);
	labelSelected->setTextColor(super::TextColor);

	return button;
}

void ConditionalJumpExamplesPage::buildCodeLabels()
{
	if (this->setupInstruction() != SetupInstruction::None)
	{
		this->buildAddressedCodeLabel(this->setupAddress(), this->setupInstructionString());
	}

	LocalizedString* jumpString = this->jumpInstructionString();
	LocalizedString* movString = Strings::Menus_Hacking_Lexicon_Assembly_Mov::create();
	LocalizedString* addString = Strings::Menus_Hacking_Lexicon_Assembly_Add::create();

	jumpString->setStringReplacementVariables(ConstantString::create("target"));
	movString->setStringReplacementVariables({ this->resultRegisterString(), ConstantString::create("0") });
	addString->setStringReplacementVariables({ this->resultRegisterString(), ConstantString::create("1") });

	this->buildAddressedCodeLabel(this->jumpAddress(), jumpString);
	this->buildAddressedCodeLabel(this->fallthroughAddress(), movString);
	this->buildCodeLabel(ConstantString::create(this->targetLabelAddress() + ": target:"));
	this->buildAddressedCodeLabel(this->resultAddress(), addString);
}

void ConditionalJumpExamplesPage::buildAddressedCodeLabel(std::string address, LocalizedString* instruction)
{
	LocalizedString* addressedInstruction = Strings::Common_XColonYSpaced::create();

	addressedInstruction->setStringReplacementVariables({ ConstantString::create(address), instruction });
	this->buildCodeLabel(addressedInstruction);
}

void ConditionalJumpExamplesPage::buildCodeLabel(LocalizedString* text)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, text);

	label->setTextColor(super::TextColor);
	label->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->codeLabels.push_back(label);
}

LocalizedLabel* ConditionalJumpExamplesPage::buildExampleLabel(int exampleIndex)
{
	LocalizedLabel* label = nullptr;

	if (this->usesConditionRegisterSelector())
	{
		label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, this->buildRegisterSetupString(this->registerCString(), this->conditionRegisterValue(exampleIndex)));
	}
	else if (this->usesRegisterBSelector())
	{
		label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, this->buildRegisterSetupString(this->registerAValue(exampleIndex), this->registerBValue(exampleIndex)));
	}
	else
	{
		label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, this->conditionString(exampleIndex));
	}

	label->setTextColor(super::TextColor);
	label->setAnchorPoint(Vec2(0.0f, 0.5f));

	return label;
}

LocalizedString* ConditionalJumpExamplesPage::buildRegisterSetupString(LocalizedString* registerString, unsigned long long value)
{
	LocalizedString* setupString = Strings::Common_XEqualsY::create();

	setupString->setStringReplacementVariables({
		registerString,
		ConstantString::create(std::to_string(value))
	});

	return setupString;
}

LocalizedString* ConditionalJumpExamplesPage::buildRegisterSetupString(unsigned long long valueA, unsigned long long valueB)
{
	LocalizedString* registerASetupString = this->buildRegisterSetupString(this->registerAString(), valueA);
	LocalizedString* registerBSetupString = this->buildRegisterSetupString(this->registerBString(), valueB);
	LocalizedString* registerASetupWithCommaString = Strings::Common_Concat::create();
	LocalizedString* setupString = Strings::Common_Concat::create();

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

LocalizedString* ConditionalJumpExamplesPage::registerAString()
{
	return sizeof(void*) == 4 ? Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create() : Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create();
}

LocalizedString* ConditionalJumpExamplesPage::registerBString()
{
	return sizeof(void*) == 4 ? Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create() : Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create();
}

LocalizedString* ConditionalJumpExamplesPage::registerCString()
{
	return sizeof(void*) == 4 ? Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create() : Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create();
}

LocalizedString* ConditionalJumpExamplesPage::resultRegisterString()
{
	return this->usesConditionRegisterSelector() ? this->registerAString() : this->registerCString();
}

LocalizedString* ConditionalJumpExamplesPage::setupInstructionString()
{
	switch (this->setupInstruction())
	{
		case SetupInstruction::Cmp:
		{
			LocalizedString* cmpString = Strings::Menus_Hacking_Lexicon_Assembly_Cmp::create();
			cmpString->setStringReplacementVariables({ this->registerAString(), this->registerBString() });
			return cmpString;
		}
		case SetupInstruction::Add:
		{
			LocalizedString* addString = Strings::Menus_Hacking_Lexicon_Assembly_Add::create();
			addString->setStringReplacementVariables({ this->registerAString(), this->registerBString() });
			return addString;
		}
		case SetupInstruction::Test:
		{
			LocalizedString* testString = Strings::Menus_Hacking_Lexicon_Assembly_Test::create();
			testString->setStringReplacementVariables({ this->registerAString(), this->registerAString() });
			return testString;
		}
		case SetupInstruction::None:
		default:
		{
			return ConstantString::create("");
		}
	}
}

LocalizedString* ConditionalJumpExamplesPage::jumpInstructionString()
{
	switch (this->operation)
	{
		case Operation::Jnabe: return Strings::Menus_Hacking_Lexicon_Assembly_Jb::create();
		case Operation::Jne: return Strings::Menus_Hacking_Lexicon_Assembly_Jne::create();
		case Operation::Jngle: return Strings::Menus_Hacking_Lexicon_Assembly_Jg::create();
		case Operation::Jno: return Strings::Menus_Hacking_Lexicon_Assembly_Jno::create();
		case Operation::Jnp: return Strings::Menus_Hacking_Lexicon_Assembly_Jnp::create();
		case Operation::Jns: return Strings::Menus_Hacking_Lexicon_Assembly_Jns::create();
		case Operation::Jnz: return Strings::Menus_Hacking_Lexicon_Assembly_Jnz::create();
		case Operation::Jzcxz: return sizeof(void*) == 4 ? Strings::Menus_Hacking_Lexicon_Assembly_Jecxz::create() : Strings::Menus_Hacking_Lexicon_Assembly_Jrcxz::create();
		default: return Strings::Menus_Hacking_Lexicon_Assembly_Jne::create();
	}
}

LocalizedString* ConditionalJumpExamplesPage::conditionString(int exampleIndex)
{
	if (this->usesConditionRegisterSelector())
	{
		return this->buildRegisterSetupString(this->registerCString(), this->conditionRegisterValue(exampleIndex));
	}

	switch (this->operation)
	{
		case Operation::Jnabe: return ConstantString::create(this->jumps(exampleIndex) ? "CF = 1" : "CF = 0");
		case Operation::Jne:
		case Operation::Jnz: return ConstantString::create(this->jumps(exampleIndex) ? "ZF = 0" : "ZF = 1");
		case Operation::Jngle:
		{
			switch (exampleIndex)
			{
				case 0: return ConstantString::create("ZF = 1");
				case 1: return ConstantString::create("ZF = 0, SF = OF");
				default: return ConstantString::create("SF != OF");
			}
		}
		case Operation::Jno: return ConstantString::create(this->jumps(exampleIndex) ? "OF = 0" : "OF = 1");
		case Operation::Jnp: return ConstantString::create(this->jumps(exampleIndex) ? "PF = 0" : "PF = 1");
		case Operation::Jns: return ConstantString::create(this->jumps(exampleIndex) ? "SF = 0" : "SF = 1");
		default: return ConstantString::create("");
	}
}

LocalizedString* ConditionalJumpExamplesPage::pathString(int exampleIndex)
{
	LocalizedString* string = this->jumps(exampleIndex)
		? Strings::Menus_Hacking_Lexicon_Pages_ControlFlow_ConditionalJump_JumpTaken::create()
		: Strings::Menus_Hacking_Lexicon_Pages_ControlFlow_ConditionalJump_JumpNotTaken::create();

	string->setStringReplacementVariables(this->conditionString(exampleIndex));

	return string;
}

unsigned long long ConditionalJumpExamplesPage::registerAValue(int exampleIndex) const
{
	switch (this->operation)
	{
		case Operation::Jno:
		{
			const unsigned long long values[] = { 8, this->maxSignedValue(), this->maxSignedValue() };
			return values[exampleIndex];
		}
		case Operation::Jnp:
		{
			const unsigned long long values[] = { 7, 3, 0 };
			return values[exampleIndex];
		}
		case Operation::Jns:
		{
			const unsigned long long values[] = { 5, 0, this->signBitValue() };
			return values[exampleIndex];
		}
		case Operation::Jzcxz:
		{
			return 7;
		}
		default:
		{
			const unsigned long long values[] = { 8, 8, 5 };
			return values[exampleIndex];
		}
	}
}

unsigned long long ConditionalJumpExamplesPage::registerBValue(int exampleIndex) const
{
	switch (this->operation)
	{
		case Operation::Jno:
		{
			const unsigned long long values[] = { 5, 1, 0 };
			return values[exampleIndex];
		}
		case Operation::Jnp:
		case Operation::Jns:
		case Operation::Jzcxz:
		{
			return 0;
		}
		default:
		{
			const unsigned long long values[] = { 8, 5, 8 };
			return values[exampleIndex];
		}
	}
}

unsigned long long ConditionalJumpExamplesPage::conditionRegisterValue(int exampleIndex) const
{
	const unsigned long long values[] = { 0, 3, 1 };
	return values[exampleIndex];
}

unsigned long long ConditionalJumpExamplesPage::registerAExecutedValue(int exampleIndex) const
{
	if (this->setupInstruction() == SetupInstruction::Add)
	{
		return this->registerAValue(exampleIndex) + this->registerBValue(exampleIndex);
	}

	return this->registerAValue(exampleIndex);
}

unsigned long long ConditionalJumpExamplesPage::resultRegisterValue(int exampleIndex, bool executeWholeExample) const
{
	if (!executeWholeExample)
	{
		return 7;
	}

	return this->jumps(exampleIndex) ? 8 : 1;
}

bool ConditionalJumpExamplesPage::jumps(int exampleIndex) const
{
	switch (this->operation)
	{
		case Operation::Jnabe:
		{
			return exampleIndex == 2;
		}
		case Operation::Jne:
		case Operation::Jnz:
		{
			return exampleIndex != 0;
		}
		case Operation::Jngle:
		{
			return exampleIndex == 1;
		}
		case Operation::Jno:
		{
			const bool values[] = { true, false, true };
			return values[exampleIndex];
		}
		case Operation::Jnp:
		{
			const bool values[] = { true, false, false };
			return values[exampleIndex];
		}
		case Operation::Jns:
		{
			const bool values[] = { true, true, false };
			return values[exampleIndex];
		}
		case Operation::Jzcxz:
		{
			return exampleIndex == 0;
		}
		default:
		{
			return false;
		}
	}
}

bool ConditionalJumpExamplesPage::usesRegisterBSelector() const
{
	return this->setupInstruction() == SetupInstruction::Cmp || this->setupInstruction() == SetupInstruction::Add;
}

bool ConditionalJumpExamplesPage::usesConditionRegisterSelector() const
{
	return this->operation == Operation::Jzcxz;
}

bool ConditionalJumpExamplesPage::usesHexDisplay() const
{
	return this->operation == Operation::Jno || this->operation == Operation::Jns;
}

ConditionalJumpExamplesPage::SetupInstruction ConditionalJumpExamplesPage::setupInstruction() const
{
	switch (this->operation)
	{
		case Operation::Jno: return SetupInstruction::Add;
		case Operation::Jnp:
		case Operation::Jns: return SetupInstruction::Test;
		case Operation::Jzcxz: return SetupInstruction::None;
		default: return SetupInstruction::Cmp;
	}
}

int ConditionalJumpExamplesPage::jumpCodeIndex() const
{
	return this->setupInstruction() == SetupInstruction::None ? 0 : 1;
}

int ConditionalJumpExamplesPage::targetCodeIndex() const
{
	return this->setupInstruction() == SetupInstruction::None ? 2 : 3;
}

std::string ConditionalJumpExamplesPage::targetAddress() const
{
	return this->setupInstruction() == SetupInstruction::None ? "108" : "112";
}

std::string ConditionalJumpExamplesPage::setupAddress() const
{
	return "100";
}

std::string ConditionalJumpExamplesPage::jumpAddress() const
{
	return this->setupInstruction() == SetupInstruction::None ? "100" : "104";
}

std::string ConditionalJumpExamplesPage::fallthroughAddress() const
{
	return this->setupInstruction() == SetupInstruction::None ? "104" : "108";
}

std::string ConditionalJumpExamplesPage::targetLabelAddress() const
{
	return this->targetAddress();
}

std::string ConditionalJumpExamplesPage::resultAddress() const
{
	return this->setupInstruction() == SetupInstruction::None ? "112" : "116";
}

unsigned long long ConditionalJumpExamplesPage::finalInstructionPointer() const
{
	return this->setupInstruction() == SetupInstruction::None ? 116 : 120;
}

unsigned long long ConditionalJumpExamplesPage::maxSignedValue() const
{
	return sizeof(void*) == 4 ? 0x7FFFFFFFULL : 0x7FFFFFFFFFFFFFFFULL;
}

unsigned long long ConditionalJumpExamplesPage::signBitValue() const
{
	return sizeof(void*) == 4 ? 0x80000000ULL : 0x8000000000000000ULL;
}
