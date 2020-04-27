#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;
class ClickableTextNode;

class LanguageTab : public SmartNode
{
public:
	static LanguageTab* create();

protected:
	LanguageTab();
	virtual ~LanguageTab();
	
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	ClickableTextNode* constructLanguageButton(LocalizedString* string);

	std::vector<ClickableTextNode*> languageButtons;
};
