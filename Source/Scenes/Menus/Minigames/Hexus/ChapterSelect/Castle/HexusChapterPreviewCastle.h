#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

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
