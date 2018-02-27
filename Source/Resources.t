<#@ template debug="false" hostspecific="true" language="C#" #>
<#@ assembly name="System.Core" #>
<#@ import namespace="System.IO" #>
<#@ import namespace="System.Linq" #>
<#@ import namespace="System.Text" #>
<#@ import namespace="System.Collections.Generic" #>
<#@ output extension=".cpp" #>
<#
WriteLine("///////////////////////////////////////////////////////////////////////////////////////////////");
WriteLine("// THIS C++ FILE IS GENERATED DO NOT EDIT. MAKE CHANGES IN THE RESOURCE TEXT TEMPLATING FILE //");
WriteLine("///////////////////////////////////////////////////////////////////////////////////////////////");
WriteLine("");
WriteLine("#pragma init_seg(\".CRT$XCU-010\")");
WriteLine("#include \"Resources.h\"");
WriteLine("#include <string>");
WriteLine("");

foreach (string file in Directory.EnumerateFiles(this.Host.ResolvePath("../Resources"), "*.*", SearchOption.AllDirectories))
{
	string fileToLower = file.ToLower();

	if (!fileToLower.EndsWith(".png") &&
		!fileToLower.EndsWith(".jpg") &&
		!fileToLower.EndsWith(".bmp") &&
		!fileToLower.EndsWith(".tif") &&
		!fileToLower.EndsWith(".ttf") &&
		!fileToLower.EndsWith(".frag") &&
		!fileToLower.EndsWith(".vert") &&
		!fileToLower.EndsWith(".mp3") &&
		!fileToLower.EndsWith(".wav") &&
		!fileToLower.EndsWith(".plist") &&
		!fileToLower.EndsWith(".json") &&
		!fileToLower.EndsWith(".tmx")) {
			continue;
		}
		
	string variableName = Path.GetFileNameWithoutExtension(file.Replace(this.Host.ResolvePath("../Resources"), "").TrimStart('\\').Replace(@"\", "_").Replace(" ", "_").Replace("-", "_").Replace("(", "_").Replace(")", "_"));
	string relativeFilePath = file.Replace(this.Host.ResolvePath("../Resources"), "").TrimStart('\\').Replace(@"\", @"\\");

	WriteLine("const std::string Resources::" + variableName + " = \"" + relativeFilePath + "\";");
}
#>