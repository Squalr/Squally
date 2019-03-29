#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewLambdaCryptsPuzzle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewLambdaCryptsPuzzle* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewLambdaCryptsPuzzle();
	~HexusChapterPreviewLambdaCryptsPuzzle();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
