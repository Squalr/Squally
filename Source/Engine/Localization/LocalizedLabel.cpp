#include "LocalizedLabel.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Localization/Localization.h"

#include "Resources/FontResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

LocalizedLabel* LocalizedLabel::create(
	FontStyle fontStyle,
	FontSize fontSize,
	LocalizedString* localizedString,
	const Size& dimensions,
	TextHAlignment hAlignment,
	TextVAlignment vAlignment)
{
	LocalizedLabel* label = new LocalizedLabel(fontStyle, fontSize, localizedString, dimensions, hAlignment, vAlignment);

	label->autorelease();

	return label;
}

LocalizedLabel::LocalizedLabel(
	FontStyle fontStyle,
	FontSize fontSize,
	LocalizedString* localizedString,
	const Size& dimensions,
	TextHAlignment hAlignment,
	TextVAlignment vAlignment)
{
	this->fontStyle = fontStyle;
	this->fontSize = fontSize;
	this->translationButton = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);
	this->localizedString = nullptr; // Do not set here; set via the setter function

	this->translationButton->setClickModifier(EventKeyboard::KeyCode::KEY_ALT);

	this->setDimensions(dimensions.width, dimensions.height);
	this->setAlignment(hAlignment, vAlignment);

	this->setOverflow(Label::Overflow::RESIZE_HEIGHT);

	this->setLocalizedString(localizedString);
	this->addChild(this->translationButton);
}

LocalizedLabel::~LocalizedLabel()
{
}

void LocalizedLabel::onEnter()
{
	super::onEnter();

	// We don't have access to initializePositions/initializeListeners because we're inheriting directly from a cocos object
	this->updateTranslationEditHitbox();
	this->translationButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		LocalizationEvents::TriggerTranslationBeginEdit(LocalizationEvents::TranslationBeginEditArgs(this->localizedString));
	});
}

LocalizedLabel* LocalizedLabel::clone()
{
	LocalizedLabel* result = nullptr;

	if (this->localizedString == nullptr)
	{
		result = LocalizedLabel::create(this->fontStyle, this->fontSize, nullptr);
	}
	else
	{
		result = LocalizedLabel::create(this->fontStyle, this->fontSize, this->localizedString->clone());
	}

	result->setAnchorPoint(this->getAnchorPoint());
	result->setPosition(this->getPosition());

	return result;
}

void LocalizedLabel::setLocalizedString(LocalizedString* localizedString)
{
	if (this->localizedString != nullptr)
	{
		this->removeChild(this->localizedString);
	}

	this->localizedString = localizedString;

	if (this->localizedString == nullptr)
	{
		return;
	}

	this->onStringUpdate(this->localizedString);

	this->localizedString->setOnStringUpdateCallback(CC_CALLBACK_1(LocalizedLabel::onStringUpdate, this));

	this->addChild(this->localizedString); // Retain as a child so it can listen for events (no visuals)
}

void LocalizedLabel::setStringReplacementVariables(LocalizedString* stringReplacementVariables)
{
	this->setStringReplacementVariables(std::vector<LocalizedString*>({ stringReplacementVariables }));
}

void LocalizedLabel::setStringReplacementVariables(std::vector<LocalizedString*> stringReplacementVariables)
{
	if (this->localizedString != nullptr)
	{
		this->localizedString->setStringReplacementVariables(stringReplacementVariables);
	}
}

float LocalizedLabel::getFontSize()
{
	switch (this->fontSize)
	{
		case FontSize::M1:
		{
			return LocalizedLabel::getFontSizeM1(this->getFont());
			break;
		}
		case FontSize::M2:
		{
			return LocalizedLabel::getFontSizeM2(this->getFont());
			break;
		}
		case FontSize::M3:
		{
			return LocalizedLabel::getFontSizeM3(this->getFont());
			break;
		}
		case FontSize::H1:
		{
			return LocalizedLabel::getFontSizeH1(this->getFont());
			break;
		}
		case FontSize::H2:
		{
			return LocalizedLabel::getFontSizeH2(this->getFont());
			break;
		}
		case FontSize::H3:
		{
			return LocalizedLabel::getFontSizeH3(this->getFont());
			break;
		}
		default:
		case FontSize::P:
		{
			return LocalizedLabel::getFontSizeP(this->getFont());
			break;
		}
		case FontSize::Small:
		{
			return LocalizedLabel::getFontSizeSmall(this->getFont());
			break;
		}
	}
}

std::string LocalizedLabel::getFont()
{
	switch (this->fontStyle)
	{
		default:
		case FontStyle::Main:
		{
			return LocalizedLabel::getMainFont();
		}
		case FontStyle::Coding:
		{
			return LocalizedLabel::getCodingFont();
		}
		case FontStyle::Monospaced:
		{
			return LocalizedLabel::getMonospacedFont();
		}
		case FontStyle::Pixel:
		{
			return LocalizedLabel::getPixelFont();
		}
	}
}

void LocalizedLabel::toggleAllowTranslationEdit(bool allowTranslationEdit)
{
	if (allowTranslationEdit)
	{
		this->translationButton->enableInteraction();
	}
	else
	{
		this->translationButton->disableInteraction();
	}
}

void LocalizedLabel::onStringUpdate(LocalizedString* localizedString)
{
	// Save some state we wish to keep
	int outlineSize = int(this->getOutlineSize());
	Color4B outlineColor = Color4B(_effectColorF);

	this->initWithTTF(
		localizedString->getString(),
		this->getFont(),
		this->getFontSize(),
		this->getDimensions(), 
		this->getHorizontalAlignment(),
		this->getVerticalAlignment()
	);

	// Restore that state
	if (outlineSize > 0)
	{
		this->enableOutline(outlineColor, outlineSize);
	}

	this->updateTranslationEditHitbox();
}

cocos2d::LanguageType LocalizedLabel::getCurrentLanguage()
{
	if (this->localizedString == nullptr)
	{
		return Localization::getLanguage();
	}

	if (this->localizedString->getOverrideLanguage() != LanguageType::NONE)
	{
		return this->localizedString->getOverrideLanguage();
	}

	return Localization::getLanguage();
}

std::string LocalizedLabel::getPixelFont()
{
	switch (this->getCurrentLanguage())
	{
		default:
		case LanguageType::ENGLISH:
		case LanguageType::CHINESE_SIMPLIFIED:
		case LanguageType::CHINESE_TRADITIONAL:
		case LanguageType::JAPANESE:
		case LanguageType::KOREAN:
		{
			return FontResources::Pixel_Standard_Pixel_Zpix;
		}
		case LanguageType::ARABIC:
		case LanguageType::BULGARIAN:
		case LanguageType::CZECH:
		case LanguageType::DANISH:
		case LanguageType::DUTCH:
		case LanguageType::FINNISH:
		case LanguageType::FRENCH:
		case LanguageType::GERMAN:
		case LanguageType::GREEK:
		case LanguageType::HUNGARIAN:
		case LanguageType::ITALIAN:
		case LanguageType::NORWEGIAN:
		case LanguageType::POLISH:
		case LanguageType::PORTUGUESE:
		case LanguageType::PORTUGUESE_BRAZIL:
		case LanguageType::ROMANIAN:
		case LanguageType::RUSSIAN:
		case LanguageType::SPANISH:
		case LanguageType::SPANISH_LATIN_AMERICAN:
		case LanguageType::SWEDISH:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::UKRAINIAN:
		case LanguageType::VIETNAMESE:
		{
			// TODO
			return FontResources::Pixel_Standard_Pixel_Zpix;
		}
	}
}

std::string LocalizedLabel::getMainFont()
{
	switch (this->getCurrentLanguage())
	{
		case LanguageType::CHINESE_SIMPLIFIED:
		{
			return FontResources::Main_ChineseSimplified_NotoSansCJKsc_Medium;
		}
		case LanguageType::CHINESE_TRADITIONAL:
		{
			return FontResources::Main_ChineseTraditional_NotoSansCJKtc_Medium;
		}
		case LanguageType::JAPANESE:
		{
			return FontResources::Main_Japanese_NotoSansCJKjp_Medium;
		}
		case LanguageType::KOREAN:
		{
			return FontResources::Main_Korean_NotoSansCJKkr_Medium;
		}
		case LanguageType::ARABIC:
		{
			return FontResources::Main_Arabic_NotoSansArabic_Medium;
		}
		case LanguageType::THAI:
		{
			return FontResources::Main_Thai_NotoSansThai_Medium;
		}
		default:
		{
			// This covers almost all languages with a standard alphabet (cyrillic, greek, latin based)
			return FontResources::Main_Standard_NotoSans_Medium;
		}
	}
}

std::string LocalizedLabel::getMonospacedFont()
{
	switch (this->getCurrentLanguage())
	{
		case LanguageType::CHINESE_SIMPLIFIED:
		{
			return FontResources::Main_ChineseSimplified_NotoSansMonoCJKsc_Regular;
		}
		case LanguageType::CHINESE_TRADITIONAL:
		{
			return FontResources::Main_ChineseTraditional_NotoSansMonoCJKtc_Regular;
		}
		case LanguageType::JAPANESE:
		{
			return FontResources::Main_Japanese_NotoSansMonoCJKjp_Regular;
		}
		case LanguageType::KOREAN:
		{
			return FontResources::Main_Korean_NotoSansMonoCJKkr_Regular;
		}
		case LanguageType::ARABIC:
		{
			return FontResources::Main_Arabic_NotoSansArabic_Bold;
		}
		case LanguageType::THAI:
		{
			return FontResources::Main_Thai_NotoSansThai_Bold;
		}
		default:
		{
			// This covers almost all languages with a standard alphabet (cyrillic, greek, latin based)
			return FontResources::Main_Standard_NotoMono_Regular;
		}
	}
}

std::string LocalizedLabel::getCodingFont()
{
	return FontResources::Coding_UbuntuMono_Bold;
}

float LocalizedLabel::getFontSizeM1(std::string fontResource)
{
	return 80.0f;
}

float LocalizedLabel::getFontSizeM2(std::string fontResource)
{
	return 64.0f;
}

float LocalizedLabel::getFontSizeM3(std::string fontResource)
{
	return 48.0f;
}

float LocalizedLabel::getFontSizeH1(std::string fontResource)
{
	return 32.0f;
}

float LocalizedLabel::getFontSizeH2(std::string fontResource)
{
	return 28.0f;
}

float LocalizedLabel::getFontSizeH3(std::string fontResource)
{
	return 24.0f;
}

float LocalizedLabel::getFontSizeP(std::string fontResource)
{
	return 20.0f;
}

float LocalizedLabel::getFontSizeSmall(std::string fontResource)
{
	return 16.0f;
}

void LocalizedLabel::updateTranslationEditHitbox()
{
	this->translationButton->setContentSize(this->getContentSize());
	this->translationButton->setPosition(Vec2(this->getContentSize() / 2.0f));
}
