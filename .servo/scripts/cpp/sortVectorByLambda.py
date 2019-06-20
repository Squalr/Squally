template = servo.loadTemplateFile('cpp/sortVectorByLambda.cpp')

if args == 'ascending':
	template = template.replace("{{comparison}}", ">")
else:
	template = template.replace("{{comparison}}", "<")

servo.insertText(template)
