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
	Localization();
	virtual ~Localization();

private:
	friend class LocalizedLabel;
	friend class LocalizedSprite;

	static Localization* getInstance();

	static cocos2d::LanguageType languageCodeToLanguageType(std::string languageCode);
	static std::string languageTypeToLanguageCode(cocos2d::LanguageType languageType);

	static Localization* instance;
};
