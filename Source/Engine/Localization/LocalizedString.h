#pragma once
#include <string>
#include <functional>

#include "cocos/platform/CCCommon.h"

#include "Engine/SmartNode.h"

class LocalizedString : public SmartNode
{
public:
	virtual LocalizedString* clone() = 0;
	std::string getString();
	cocos2d::LanguageType getOverrideLanguage();
	void setOverrideLanguage(cocos2d::LanguageType overrideLanguage);
	LocalizedString* setStringReplacementVariables(LocalizedString* stringReplacementVariable);
	LocalizedString* setStringReplacementVariables(std::vector<LocalizedString*> stringReplacementVariables);
	void setOnStringUpdateCallback(std::function<void(LocalizedString* newString)> onStringUpdate);
	virtual std::string getStringIdentifier() = 0;

protected:
	LocalizedString();
	virtual ~LocalizedString();

	void onEnter() override;

	void copyAttributesTo(LocalizedString* localizedString);
	virtual std::string getStringByLanguage(cocos2d::LanguageType languageType) = 0;

	std::function<void(LocalizedString* newString)> onStringUpdate;
	std::vector<LocalizedString*> stringReplacementVariables;
	cocos2d::LanguageType currentLanguage;
	cocos2d::LanguageType overrideLanguage;

private:
	typedef SmartNode super;
	friend class TypeWriterEffect; // I dont care if this is bad practice

	bool runOnce;
};
