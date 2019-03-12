#pragma once

#include "Scenes/Hexus/Menus//ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewCastleValgrind : public HexusChapterPreview
{
public:
	static HexusChapterPreviewCastleValgrind* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewCastleValgrind();
	~HexusChapterPreviewCastleValgrind();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
