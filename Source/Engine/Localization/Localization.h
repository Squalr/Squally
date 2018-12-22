#pragma once
#include <string>

#include "cocos/platform/CCCommon.h"

// rapidjson forwards header
#include "fwd.h"

class Localization
{
public:
	static std::string resolveFile(std::string fileEn);
	static std::string resolveString(std::string resourceKey);
	static cocos2d::LanguageType getLanguage();
	static void setLanguage(cocos2d::LanguageType languageType);
	static std::string getLanguageCode();
	static cocos2d::LanguageType getNativeLanguage();

	static std::string getPixelFont();
	static std::string getMainFont();
	static std::string getCodingFont();
	static float getFontSizeH1(std::string fontResource);
	static float getFontSizeH2(std::string fontResource);
	static float getFontSizeH3(std::string fontResource);
	static float getFontSizeP(std::string fontResource);

private:
	static Localization* getInstance();

	Localization();
	~Localization();

	static cocos2d::LanguageType languageCodeToLanguageType(std::string languageCode);
	static std::string languageTypeToLanguageCode(cocos2d::LanguageType languageType);

	rapidjson::Document* localizationMap;

	static Localization* instance;
};
