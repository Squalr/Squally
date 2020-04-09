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

private:
	typedef SmartNode super;

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	ClickableTextNode* constructLanguageButton(LocalizedString* string);

	std::vector<ClickableTextNode*> languageButtons;
};
