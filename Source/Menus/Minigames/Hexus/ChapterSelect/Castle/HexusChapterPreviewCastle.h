#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewCastle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewCastle * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewCastle();
	~HexusChapterPreviewCastle();

private:
	void initializePositions() override;
};
