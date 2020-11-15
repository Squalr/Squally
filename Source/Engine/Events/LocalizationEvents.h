#pragma once
#include <string>

class LocalizedString;

class LocalizationEvents
{
public:
	struct LocaleChangeArgs
	{
		cocos2d::LanguageType languageType;

		LocaleChangeArgs(cocos2d::LanguageType languageType) : languageType(languageType) { }
	};

	struct TranslationBeginEditArgs
	{
		LocalizedString* localizedString;

		TranslationBeginEditArgs(LocalizedString* localizedString) : localizedString(localizedString) { }
	};

	static void TriggerLocaleChange(LocaleChangeArgs args);
	static void TriggerTranslationBeginEdit(TranslationBeginEditArgs args);

	static const std::string LocaleChangeEvent;
	static const std::string BeforeLocaleChangeEvent;
	static const std::string TranslationBeginEdit;
};
