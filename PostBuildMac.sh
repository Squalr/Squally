# Patch bytes in the exe to allow for self modifying code. HackUtils.cpp has a bit more info on this.
printf '\x07' | dd of=build/bin/Squally.app/Contents/MacOS/Squally bs=1 seek=160 count=1 conv=notrunc

