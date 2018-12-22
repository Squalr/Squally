#pragma once
#include <string>

#include "cocos/platform/CCCommon.h"

class LocalizationEvents
{
public:

	struct LocaleChangeArgs
	{
		cocos2d::LanguageType languageType;

		LocaleChangeArgs(cocos2d::LanguageType languageType) : languageType(languageType) { }
	};

	static void TriggerLocaleChange(LocaleChangeArgs args);

	static const std::string LocaleChangeEvent;
};
