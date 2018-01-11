#include "Fasm.h"

Fasm::FasmResult* Fasm::assemble(string assembly, void* baseAddress)
{
	char buff[64];
	snprintf(buff, sizeof(buff), "use32\norg 0x%X\n", baseAddress);
	std::string buffAsStdStr = buff;
	assembly = buffAsStdStr + assembly;

	// assembly = snprintf("use32\norg 0x{0:X8}\n") + assembly;
	int lineCount = 1;

	// Count the number of instructions given to us (well, just count the newlines because it's easier)
	for (int i = 0; i < assembly.size(); i++)
	{
		if (assembly[i] == '\n')
		{
			lineCount++;
		}
	}

	// 15 is the max length of an x86 instruction, so just assume worse case because space is cheap. If we're under 4096 bytes, just return 4096 bytes.
	int bufferSize = (lineCount * 15) < 4096 ? 4096 : (lineCount * 15);

	unsigned char* resultBuffer = (unsigned char*)calloc(bufferSize, sizeof(unsigned char));

	// Assemble the mnemonics
	FasmResultCode ret = (FasmResultCode)fasm_Assemble(_strdup(assembly.c_str()), resultBuffer, bufferSize, 100, nullptr);
	FasmResult* result = static_cast<FasmResult*>((void*)resultBuffer);

	return result;
}
