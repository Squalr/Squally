#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewVoidStarPuzzle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewVoidStarPuzzle* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewVoidStarPuzzle();
	~HexusChapterPreviewVoidStarPuzzle();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
