<#@ template debug="false" hostspecific="true" language="C#" #>
<#@ assembly name="System.Core" #>
<#@ import namespace="System.IO" #>
<#@ import namespace="System.Linq" #>
<#@ import namespace="System.Text" #>
<#@ import namespace="System.Collections.Generic" #>
<#@ output extension=".cpp" #>
<#
WriteLine("#include \"Resources.h\"");
WriteLine("#include <string>");
WriteLine("");

foreach (string file in Directory.EnumerateFiles(this.Host.ResolvePath("../Resources"), "*.*", SearchOption.AllDirectories))
{
	if (!file.EndsWith(".png") &&
		!file.EndsWith(".jpg") &
		!file.EndsWith(".ttf")) {
			continue;
		}
		
	string variableName = Path.GetFileNameWithoutExtension(file.Replace(this.Host.ResolvePath("../Resources"), "").TrimStart('\\').Replace(@"\", "_").Replace(" ", "_"));
	string relativeFilePath = file.Replace(this.Host.ResolvePath("../Resources"), "").TrimStart('\\').Replace(@"\", @"\\");

	WriteLine("const string Resources::" + variableName + " = \"" + relativeFilePath + "\";");
}
#>