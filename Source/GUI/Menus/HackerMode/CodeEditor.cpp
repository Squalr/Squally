#include "CodeEditor.h"

const Size CodeEditor::textSize = Size(480.0f, 640.0f);
const std::string CodeEditor::delimiters = "[],; \n\t";
const Color3B CodeEditor::defaultColor = Color3B::WHITE;
const Color3B CodeEditor::registerColor = Color3B(86, 156, 214);
const Color3B CodeEditor::numberColor = Color3B(181, 206, 168); // Color3B(78, 201, 176);
const Color3B CodeEditor::commentColor = Color3B(87, 166, 74);

const std::set<std::string> CodeEditor::registers =
{
	// General registers
	"ax", "bx", "cx", "dx", "si", "di", "bp", "sp",
	"r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w",
	"al", "bl", "cl", "dl", "sil", "dil", "bpl", "spl",
	"r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b",
	"eax", "ebx", "ecx" ,"edx" ,"esi", "edi", "ebp", "esp",
	"r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d",
	"rax", "rbx", "rcx" ,"rdx" ,"rdi", "rsi", "rbp", "rsp",
	"r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",

	// FPU registers
	"fp0", "fp1", "fp2", "fp3", "fp4", "fp5", "fp6", "fp7",

	// MMX registers
	"mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7",
	"mm8", "mm9", "mm10", "mm11", "mm12", "mm13", "mm14", "mm15",
	"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7",
	"xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15",
	"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7",
	"ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15",

	// Segment registers
	"cs", "ds", "es", "fs", "gs", "ss",

	// Instruction pointers
	"eip", "rip"
};

CodeEditor* CodeEditor::create()
{
	CodeEditor* codeEditor = new CodeEditor();

	codeEditor->autorelease();

	return codeEditor;
}

CodeEditor::CodeEditor()
{
	this->activeHackableCode = nullptr;
	this->displayTextElements = new std::vector<RichElement*>();
	this->outputTextElements = new std::vector<RichElement*>();

	this->codeEditorBackground = Sprite::create(Resources::Menus_HackerModeMenu_CodeEditMenu);
	this->codeEditorScrollView = ScrollView::create();
	this->assemblyCodeText = TextField::create("<Click to Edit Assembly Code>", Resources::Fonts_UbuntuMono_B, 32);
	this->displayText = RichText::create();
	this->cancelButton = MenuSprite::create(Resources::Menus_Buttons_CancelButton, Resources::Menus_Buttons_CancelButtonHover, Resources::Menus_Buttons_CancelButtonClick);
	this->acceptButton = MenuSprite::create(Resources::Menus_Buttons_AcceptButton, Resources::Menus_Buttons_AcceptButtonHover, Resources::Menus_Buttons_AcceptButtonClick);
	this->acceptButtonGrayed = Sprite::create(Resources::Menus_Buttons_AcceptButtonGray);
	this->codeEditorTitle = MenuLabel::create("Code Editor", Resources::Fonts_Montserrat_Medium, 32);

	this->allocEditorBackground = Sprite::create(Resources::Menus_HackerModeMenu_OutputMenu);
	this->allocEditorTitle = MenuLabel::create("Alloc Editor", Resources::Fonts_Montserrat_Medium, 32);

	this->outputBackground = Sprite::create(Resources::Menus_HackerModeMenu_OutputMenu);
	this->outputTitle = MenuLabel::create("Status", Resources::Fonts_Montserrat_Medium, 32);
	this->outputScrollView = ScrollView::create();
	this->outputText = RichText::create();

	this->acceptButtonGrayed->setVisible(false);

	this->assemblyCodeText->setOpacity(0);
	this->assemblyCodeText->setCascadeOpacityEnabled(false);
	this->assemblyCodeText->setCursorEnabled(true);
	this->assemblyCodeText->setHighlighted(true);

	this->codeEditorScrollView->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->assemblyCodeText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->displayText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->outputScrollView->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->outputText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->outputText->setSize(CodeEditor::textSize);
	this->outputText->ignoreContentAdaptWithSize(false);

	this->codeEditorScrollView->setSize(CodeEditor::textSize);
	this->codeEditorScrollView->setDirection(SCROLLVIEW_DIR_BOTH);
	this->codeEditorScrollView->setInnerContainerSize(Size(CodeEditor::textSize.width, CodeEditor::textSize.height * 2));

	this->outputScrollView->setSize(CodeEditor::textSize);
	this->outputScrollView->setDirection(SCROLLVIEW_DIR_BOTH);
	this->outputScrollView->setInnerContainerSize(Size(CodeEditor::textSize.width, CodeEditor::textSize.height * 2));

	this->codeEditorScrollView->addChild(this->assemblyCodeText);
	this->codeEditorScrollView->addChild(this->displayText);
	this->outputScrollView->addChild(this->outputText);

	this->addChild(this->codeEditorBackground);
	this->addChild(this->codeEditorScrollView);
	this->addChild(this->cancelButton);
	this->addChild(this->acceptButton);
	this->addChild(this->acceptButtonGrayed);
	this->addChild(this->codeEditorTitle);

	this->addChild(this->allocEditorBackground);
	this->addChild(this->allocEditorTitle);

	this->addChild(this->outputBackground);
	this->addChild(this->outputTitle);
	this->addChild(this->outputScrollView);

	this->initializePositions();
	this->initializeListeners();
	this->scheduleUpdate();
}

CodeEditor::~CodeEditor()
{
	delete(this->displayTextElements);
	delete(this->outputTextElements);
}

void CodeEditor::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->codeEditorBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->acceptButton->setPosition(Vec2(this->codeEditorBackground->getPositionX() + 224.0f, this->codeEditorBackground->getPositionY() - 336.0f));
	this->cancelButton->setPosition(Vec2(this->codeEditorBackground->getPositionX() - 224.0f, this->codeEditorBackground->getPositionY() - 336.0f));
	this->acceptButtonGrayed->setPosition(this->acceptButton->getPosition());
	this->codeEditorScrollView->setPosition(Vec2(this->codeEditorBackground->getPositionX() - CodeEditor::textSize.width / 2, this->codeEditorBackground->getPositionY() + CodeEditor::textSize.height / 2 - 32.0f));
	this->assemblyCodeText->setPosition(Vec2(0.0f, this->codeEditorScrollView->getInnerContainerSize().height));
	this->displayText->setPosition(this->assemblyCodeText->getPosition());
	this->codeEditorTitle->setPosition(this->codeEditorBackground->getPositionX(), this->codeEditorBackground->getPositionY() + 340.0f);

	this->allocEditorBackground->setPosition(Vec2(visibleSize.width / 2.0f + 640.0f, visibleSize.height / 2.0f));
	this->allocEditorTitle->setPosition(this->allocEditorBackground->getPositionX(), this->allocEditorBackground->getPositionY() + 340.0f);

	this->outputBackground->setPosition(Vec2(visibleSize.width / 2.0f - 640.0f, visibleSize.height / 2.0f));
	this->outputTitle->setPosition(this->outputBackground->getPositionX(), this->outputBackground->getPositionY() + 340.0f);
	this->outputScrollView->setPosition(Vec2(this->outputBackground->getPositionX() - CodeEditor::textSize.width / 2, this->outputBackground->getPositionY() + CodeEditor::textSize.height / 2 - 32.0f));
	this->outputText->setPosition(Vec2(0.0f, this->outputScrollView->getInnerContainerSize().height));
}

void CodeEditor::initializeListeners()
{
	this->acceptButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onAccept, this));
	this->cancelButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onCancel, this));
}

void CodeEditor::update(float dt)
{
	std::string currentText = this->assemblyCodeText->getString();

	this->assemblyCodeText->attachWithIME();

	if (this->previousAssemblyText == currentText)
	{
		return;
	}

	this->previousAssemblyText = currentText;
	this->constructCodeRichText(currentText);
	this->compile(currentText);
}

void CodeEditor::compile(std::string rawText)
{
	if (this->activeHackableCode == nullptr)
	{
		return;
	}

	// Remove existing rich text
	for (auto iterator = this->outputTextElements->begin(); iterator != this->outputTextElements->end(); iterator++)
	{
		this->outputText->removeElement(*iterator);
	}

	this->outputTextElements->clear();

	Fasm::FasmResult* compileResult = HackUtils::assemble(rawText, this->activeHackableCode->codePointer);

	switch (compileResult->Condition)
	{
	case Fasm::FasmResultCode::CannotGenerateCode:
	case Fasm::FasmResultCode::Error:
	case Fasm::FasmResultCode::FormatLimitationsExcedded:
	case Fasm::FasmResultCode::InvalidParameter:
	case Fasm::FasmResultCode::OutOfMemory:
	case Fasm::FasmResultCode::SourceNotFound:
	case Fasm::FasmResultCode::StackOverflow:
	case Fasm::FasmResultCode::UnexpectedEndOfSource:
	case Fasm::FasmResultCode::Working:
	case Fasm::FasmResultCode::WriteFailed:
	{
		switch (compileResult->Error)
		{
		case Fasm::FasmErrorCode::FileNotFound:
		case Fasm::FasmErrorCode::ErrorReadingFile:
		case Fasm::FasmErrorCode::InvalidFileFormat:
		case Fasm::FasmErrorCode::InvalidMacroArguments:
		case Fasm::FasmErrorCode::IncompleteMacro:
		case Fasm::FasmErrorCode::UnexpectedCharacters:
		case Fasm::FasmErrorCode::InvalidArgument:
		case Fasm::FasmErrorCode::IllegalInstruction:
		case Fasm::FasmErrorCode::InvalidOperand:
		case Fasm::FasmErrorCode::InvalidOperandSize:
		case Fasm::FasmErrorCode::OperandSizeNotSpecified:
		case Fasm::FasmErrorCode::OperandSizesDoNotMatch:
		case Fasm::FasmErrorCode::InvalidAddressSize:
		case Fasm::FasmErrorCode::AddressSizesDoNotAgree:
		case Fasm::FasmErrorCode::DisallowedCombinationOfRegisters:
		case Fasm::FasmErrorCode::LongImmediateNotEncodable:
		case Fasm::FasmErrorCode::RelativeJumpOutOfRange:
		case Fasm::FasmErrorCode::InvalidExpression:
		case Fasm::FasmErrorCode::InvalidAddress:
		case Fasm::FasmErrorCode::InvalidValue:
		case Fasm::FasmErrorCode::ValueOutOfRange:
		case Fasm::FasmErrorCode::UndefinedSymbol:
		case Fasm::FasmErrorCode::InvalidUseOfSymbol:
		case Fasm::FasmErrorCode::NameTooLong:
		case Fasm::FasmErrorCode::InvalidName:
		case Fasm::FasmErrorCode::ReservedWordUsedAsSymbol:
		case Fasm::FasmErrorCode::SymbolAlreadyDefined:
		case Fasm::FasmErrorCode::MissingEndQuote:
		case Fasm::FasmErrorCode::MissingEndDirective:
		case Fasm::FasmErrorCode::UnexpectedInstruction:
		case Fasm::FasmErrorCode::ExtraCharactersOnLine:
		case Fasm::FasmErrorCode::SectionNotAlignedEnough:
		case Fasm::FasmErrorCode::SettingAlreadySpecified:
		case Fasm::FasmErrorCode::DataAlreadyDefined:
		case Fasm::FasmErrorCode::TooManyRepeats:
		case Fasm::FasmErrorCode::SymbolOutOfScope:
		case Fasm::FasmErrorCode::UserError:
		case Fasm::FasmErrorCode::AssertionFailed:
		{
			break;
		}
		}
		std::string errorMessage(compileResult->OutputData, compileResult->OutputData + sizeof compileResult->OutputLength);
		int lineNumber = compileResult->ErrorLine->LineNumber;

		this->acceptButtonGrayed->setVisible(true);
		this->acceptButton->setVisible(false);

		break;
	}
	case Fasm::FasmResultCode::Ok:
	{
		RichElementText* statusLabel = RichElementText::create(0, CodeEditor::defaultColor, 0xFF, "Status: Compile Successful", Resources::Fonts_UbuntuMono_B, 32);
		RichElementNewLine* newLine1 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementNewLine* newLine2 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementText* addressLabel = RichElementText::create(0, CodeEditor::defaultColor, 0xFF, "Address: " + HackUtils::hexAddressOf(this->activeHackableCode->codePointer, true, true), Resources::Fonts_UbuntuMono_B, 32);
		RichElementNewLine* newLine3 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementNewLine* newLine4 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementText* bytesLabel = RichElementText::create(0, CodeEditor::defaultColor, 0xFF, "Bytes:" + HackUtils::arrayOfByteStringOf(compileResult->OutputData, compileResult->OutputLength, compileResult->OutputLength), Resources::Fonts_UbuntuMono_B, 32);

		this->outputText->pushBackElement(statusLabel);
		this->outputText->pushBackElement(newLine1);
		this->outputText->pushBackElement(newLine2);
		this->outputText->pushBackElement(addressLabel);
		this->outputText->pushBackElement(newLine3);
		this->outputText->pushBackElement(newLine4);
		this->outputText->pushBackElement(bytesLabel);

		this->outputTextElements->push_back(statusLabel);
		this->outputTextElements->push_back(newLine1);
		this->outputTextElements->push_back(newLine2);
		this->outputTextElements->push_back(addressLabel);
		this->outputTextElements->push_back(newLine3);
		this->outputTextElements->push_back(newLine4);
		this->outputTextElements->push_back(bytesLabel);

		this->acceptButtonGrayed->setVisible(false);
		this->acceptButton->setVisible(true);
		break;
	}
	}

	this->outputText->formatText();
}

void CodeEditor::constructCodeRichText(std::string rawText)
{
	// Remove existing rich text
	for (auto iterator = this->displayTextElements->begin(); iterator != this->displayTextElements->end(); iterator++)
	{
		this->displayText->removeElement(*iterator);
	}

	this->displayTextElements->clear();

	// Tokenize x86/x64 assembly
	std::vector <std::string> * tokenStrings = StrUtils::tokenize(rawText, CodeEditor::delimiters);

	for (auto iterator = tokenStrings->begin(); iterator != tokenStrings->end(); iterator++)
	{
		// Create tokens from the token string (usually this is 1:1, but can sometimes break down further due to edge cases with newlines)
		std::vector<CodeEditor::token>* tokens = this->createTokens(*iterator);

		for (auto tokenIterator = tokens->begin(); tokenIterator != tokens->end(); tokenIterator++)
		{
			CodeEditor::token token = *tokenIterator;

			RichElement* element;

			if (token.tokenStr == "\n")
			{
				// For some reason RichElementText is too fucking stupid to handle newlines -- these are their own object
				element = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
			}
			else
			{
				element = RichElementText::create(0, token.color, 0xFF, token.tokenStr, Resources::Fonts_UbuntuMono_B, 32);

			}

			this->displayTextElements->push_back(element);
			this->displayText->pushBackElement(element);
		}

		delete(tokens);
	}

	delete(tokenStrings);

	this->displayText->formatText();
}

std::vector<CodeEditor::token>* CodeEditor::createTokens(std::string tokenStr)
{
	std::vector<CodeEditor::token>* tokens = new std::vector<CodeEditor::token>();
	std::vector <std::string> * tokenStrings = StrUtils::splitOn(tokenStr, "\n");

	for (auto tokenIterator = tokenStrings->begin(); tokenIterator != tokenStrings->end(); tokenIterator++)
	{
		std::string innerToken = *tokenIterator;
		Color3B color = CodeEditor::defaultColor;

		if (CodeEditor::registers.find(innerToken) != CodeEditor::registers.end())
		{
			color = CodeEditor::registerColor;
		}
		else if (StrUtils::isInteger(innerToken) || StrUtils::isFloat(innerToken) || StrUtils::isHexNumber(innerToken))
		{
			color = CodeEditor::numberColor;
		}

		CodeEditor::token nextToken = CodeEditor::token(innerToken, color);
		tokens->push_back(nextToken);
	}

	delete(tokenStrings);

	return tokens;
}

void CodeEditor::open(HackableCode* hackableCode)
{
	this->activeHackableCode = hackableCode;

	this->codeEditorTitle->setText("Function '" + hackableCode->functionName + "'");

	this->assemblyCodeText->setText(HackUtils::disassemble(hackableCode->codePointer, hackableCode->codeOriginalLength).c_str());
	this->assemblyCodeText->attachWithIME();

	this->setVisible(true);
	Utils::focus(this);
}

void CodeEditor::onAccept(MenuSprite* menuSprite)
{
	this->setVisible(false);

	this->getParent()->setOpacity(0xFF);
	Utils::focus(this->getParent());
}

void CodeEditor::onCancel(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::focus(this->getParent());
}
