#pragma once

#include "Scenes/Hexus/Menus//ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewCastleValgrindPuzzle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewCastleValgrindPuzzle* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewCastleValgrindPuzzle();
	~HexusChapterPreviewCastleValgrindPuzzle();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
