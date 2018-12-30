#pragma once
#include <string>

#include "cocos/platform/CCCommon.h"

class Localization
{
public:
	static cocos2d::LanguageType getLanguage();
	static void setLanguage(cocos2d::LanguageType languageType);
	static std::string getLanguageCode();
	static cocos2d::LanguageType getNativeLanguage();

protected:
	friend class LocalizedLabel;

private:
	static Localization* getInstance();

	Localization();
	~Localization();

	static cocos2d::LanguageType languageCodeToLanguageType(std::string languageCode);
	static std::string languageTypeToLanguageCode(cocos2d::LanguageType languageType);

	static Localization* instance;
};
