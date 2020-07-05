#include "LocalizedLabel.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Utils/GameUtils.h"

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
	this->localizedString = nullptr; // Do not set here; set via the setter function

	this->setDimensions(dimensions.width, dimensions.height);
	this->setAlignment(hAlignment, vAlignment);

	this->setOverflow(Label::Overflow::RESIZE_HEIGHT);

	this->setLocalizedString(localizedString);
}

LocalizedLabel::~LocalizedLabel()
{
}

void LocalizedLabel::onEnter()
{
	super::onEnter();
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

	this->localizedString->setOnStringUpdateCallback([=](LocalizedString* string)
	{
		this->onStringUpdate(string);
	});

	// Retain as a child so it can listen for events (no visuals). Use changeParent in case the child is already added.
	GameUtils::changeParent(this->localizedString, this, false);
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
	
void LocalizedLabel::setFontSize(FontSize fontSize)
{
	if (this->fontSize == fontSize)
	{
		return;
	}

	this->fontSize = fontSize;

	// Refresh
	this->onStringUpdate(this->localizedString);
}

bool LocalizedLabel::increaseFontSize()
{
	if (this->fontSize == FontSize::MAX)
	{
		return false;
	}

	this->setFontSize(FontSize(int(this->fontSize) - 1));

	return true;
}

bool LocalizedLabel::decreaseFontSize()
{
	if (this->fontSize == FontSize::MIN)
	{
		return false;
	}

	this->setFontSize(FontSize(int(this->fontSize) + 1));

	return true;
}

float LocalizedLabel::getFontSize()
{
	switch (this->fontSize)
	{
		case FontSize::S1:
		{
			return LocalizedLabel::getFontSizeS1();
		}
		case FontSize::S2:
		{
			return LocalizedLabel::getFontSizeS2();
		}
		case FontSize::S3:
		{
			return LocalizedLabel::getFontSizeS3();
		}
		case FontSize::M1:
		{
			return LocalizedLabel::getFontSizeM1();
		}
		case FontSize::M2:
		{
			return LocalizedLabel::getFontSizeM2();
		}
		case FontSize::M3:
		{
			return LocalizedLabel::getFontSizeM3();
		}
		case FontSize::H1:
		{
			return LocalizedLabel::getFontSizeH1();
		}
		case FontSize::H2:
		{
			return LocalizedLabel::getFontSizeH2();
		}
		case FontSize::H3:
		{
			return LocalizedLabel::getFontSizeH3();
		}
		case FontSize::H4:
		{
			return LocalizedLabel::getFontSizeH4();
		}
		default:
		case FontSize::P:
		{
			return LocalizedLabel::getFontSizeP();
		}
		case FontSize::Small:
		{
			return LocalizedLabel::getFontSizeSmall();
		}
		case FontSize::Tiny:
		{
			return LocalizedLabel::getFontSizeTiny();
		}
		case FontSize::Micro:
		{
			return LocalizedLabel::getFontSizeMicro();
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
		case FontStyle::Monospaced:
		{
			return LocalizedLabel::getMonospacedFont();
		}
		case FontStyle::Coding:
		{
			return LocalizedLabel::getCodingFont();
		}
	}
}

void LocalizedLabel::onStringUpdate(LocalizedString* localizedString)
{
	// Save some state we wish to keep
	int outlineSize = int(this->getOutlineSize());
	Color4B outlineColor = Color4B(_effectColorF);

	this->cleanupState();
	
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
}

void LocalizedLabel::cleanupState()
{
	if (_letters.size() > 0)
	{
		this->removeLetters();
		int max = this->getStringLength();

		for (int index = 0; index < max; index++)
		{
			Sprite* letter = this->getLetter(index);

			if (letter != nullptr)
			{
				letter->stopAllActions();
				letter->setTextureAtlas(nullptr);
			}
		}
		
		this->_letters.clear();
	}

	this->_contentDirty = true;
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
			return FontResources::Mono_ChineseSimplified_NotoSansMonoCJKsc_Regular;
		}
		case LanguageType::CHINESE_TRADITIONAL:
		{
			return FontResources::Mono_ChineseTraditional_NotoSansMonoCJKtc_Regular;
		}
		case LanguageType::JAPANESE:
		{
			return FontResources::Mono_Japanese_NotoSansMonoCJKjp_Regular;
		}
		case LanguageType::KOREAN:
		{
			return FontResources::Mono_Korean_NotoSansMonoCJKkr_Regular;
		}
		case LanguageType::ARABIC:
		{
			return FontResources::Mono_Arabic_NotoSansArabic_Regular;
		}
		case LanguageType::THAI:
		{
			return FontResources::Mono_Thai_NotoSansThai_Medium;
		}
		default:
		{
			// This covers almost all languages with a standard alphabet (cyrillic, greek, latin based)
			return FontResources::Mono_Standard_NotoMono_Regular;
		}
	}
}

std::string LocalizedLabel::getCodingFont()
{
	switch (this->getCurrentLanguage())
	{
		case LanguageType::CHINESE_SIMPLIFIED:
		{
			return FontResources::Coding_ChineseSimplified_NotoSansMonoCJKsc_Bold;
		}
		case LanguageType::CHINESE_TRADITIONAL:
		{
			return FontResources::Coding_ChineseTraditional_NotoSansMonoCJKtc_Bold;
		}
		case LanguageType::JAPANESE:
		{
			return FontResources::Coding_Japanese_NotoSansMonoCJKjp_Bold;
		}
		case LanguageType::KOREAN:
		{
			return FontResources::Coding_Korean_NotoSansMonoCJKkr_Bold;
		}
		case LanguageType::ARABIC:
		{
			return FontResources::Coding_Arabic_Ubuntu_Arabic_Bold;
		}
		case LanguageType::THAI:
		{
			return FontResources::Coding_Thai_NotoSansThai_Bold;
		}
		default:
		{
			// This covers almost all languages with a standard alphabet (cyrillic, greek, latin based)
			return FontResources::Coding_Standard_UbuntuMono_Bold;
		}
	}
}

float LocalizedLabel::getFontSizeS1()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 140.0f : 128.0f;
}

float LocalizedLabel::getFontSizeS2()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 120.0f : 112.0f;
}

float LocalizedLabel::getFontSizeS3()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 104.0f : 96.0f;
}

float LocalizedLabel::getFontSizeM1()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 88.0f : 80.0f;
}

float LocalizedLabel::getFontSizeM2()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 72.0f : 64.0f;
}

float LocalizedLabel::getFontSizeM3()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 54.0f : 48.0f;
}

float LocalizedLabel::getFontSizeH1()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 36.0f : 32.0f;
}

float LocalizedLabel::getFontSizeH2()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 32.0f : 28.0f;
}

float LocalizedLabel::getFontSizeH3()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 28.0f : 24.0f;
}

float LocalizedLabel::getFontSizeH4()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 24.0f : 22.0f;
}

float LocalizedLabel::getFontSizeP()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 24.0f : 20.0f;
}

float LocalizedLabel::getFontSizeSmall()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 20.0f : 16.0f;
}

float LocalizedLabel::getFontSizeTiny()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 16.0f : 12.0f;
}

float LocalizedLabel::getFontSizeMicro()
{
	return this->getFont() == FontResources::Coding_Standard_UbuntuMono_Bold ? 12.0f : 8.0f;
}
