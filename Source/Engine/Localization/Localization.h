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
	static float getFontSizeH1(std::string fontResource);
	static float getFontSizeH2(std::string fontResource);
	static float getFontSizeH3(std::string fontResource);
	static float getFontSizeP(std::string fontResource);

	static std::string getPixelFont();
	static std::string getMainFont();
	static std::string getCodingFont();

private:
	static Localization* getInstance();

	Localization();
	~Localization();

	static cocos2d::LanguageType languageCodeToLanguageType(std::string languageCode);
	static std::string languageTypeToLanguageCode(cocos2d::LanguageType languageType);

	static Localization* instance;
};
