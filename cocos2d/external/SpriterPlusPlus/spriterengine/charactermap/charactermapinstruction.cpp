#include "charactermapinstruction.h"

#include "../file/filereference.h"

namespace SpriterEngine
{

	CharacterMapInstruction::CharacterMapInstruction(int initialFileToReplaceIndex, File *initialReplacementFile) :
		fileToReplace(initialFileToReplaceIndex),
		replacementFile(initialReplacementFile)
	{
	}


	void CharacterMapInstruction::applyMapInstruction(FileReferenceVector *mappedFiles)
	{
		mappedFiles->at(fileToReplace)->setFile(replacementFile);
	}

}
