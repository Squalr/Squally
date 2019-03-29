#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewDaemonsHallowPuzzle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewDaemonsHallowPuzzle * create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewDaemonsHallowPuzzle();
	~HexusChapterPreviewDaemonsHallowPuzzle();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
