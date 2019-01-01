#pragma once
#include <string>
#include <functional>

#include "Engine/SmartNode.h"

class LocalizedString : public SmartNode
{
public:
	virtual LocalizedString* clone() = 0;
	std::string getString();
	void setStringReplacementVariables(std::vector<std::string> stringReplacementVariables);
	void setOnStringUpdateCallback(std::function<void(LocalizedString* newString)> onLocaleChange);

protected:
	LocalizedString();
	~LocalizedString();

	virtual std::string getStringAr() = 0;
	virtual std::string getStringBg() = 0;
	virtual std::string getStringCs() = 0;
	virtual std::string getStringDa() = 0;
	virtual std::string getStringDe() = 0;
	virtual std::string getStringEl() = 0;
	virtual std::string getStringEn() = 0;
	virtual std::string getStringEs() = 0;
	virtual std::string getStringEs419() = 0;
	virtual std::string getStringFi() = 0;
	virtual std::string getStringFr() = 0;
	virtual std::string getStringHu() = 0;
	virtual std::string getStringIt() = 0;
	virtual std::string getStringJa() = 0;
	virtual std::string getStringKo() = 0;
	virtual std::string getStringNl() = 0;
	virtual std::string getStringNo() = 0;
	virtual std::string getStringPl() = 0;
	virtual std::string getStringPt() = 0;
	virtual std::string getStringPtBr() = 0;
	virtual std::string getStringRo() = 0;
	virtual std::string getStringRu() = 0;
	virtual std::string getStringSv() = 0;
	virtual std::string getStringTh() = 0;
	virtual std::string getStringTr() = 0;
	virtual std::string getStringUk() = 0;
	virtual std::string getStringVi() = 0;
	virtual std::string getStringZhCn() = 0;
	virtual std::string getStringZhTw() = 0;

private:
	typedef SmartNode super;
	void onEnter() override;
	void initializeListeners() override;

	std::function<void(LocalizedString* newString)> onStringUpdate;
	std::vector<std::string> stringReplacementVariables;
	cocos2d::LanguageType currentLanguage;
};
