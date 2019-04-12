#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewUnderflowRuinsPuzzle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewUnderflowRuinsPuzzle* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewUnderflowRuinsPuzzle();
	~HexusChapterPreviewUnderflowRuinsPuzzle();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
