String replaceInitialToUpper(String str)
{
	String initial = str.get(0);
	initial = initial.convert(to:upper);
	str = str.substring(1, str.getSize());
	return initial.concat(str);
}

void writeGetter(OutputStream ous, String prototype, String propertyName, String retType)
{
	ous <<< prototype + ".get" + replaceInitialToUpper(propertyName) + " = function() {" <<< EOL;
	switch(retType) {
		case "int":
		case "float" :
		case "boolean" :
			ous <<< "\treturn this.rawptr." + propertyName + ";" <<< EOL;
			break;
		case "String" :
			ous <<< "\treturn new konoha.String(this.rawptr." + propertyName + ");" <<< EOL;
			break;
		default:
			ous <<< "\treturn new js.box2d." + retType + "(this.rawptr." + propertyName + ");" <<< EOL;
			break;
	}
	ous <<< "}" <<< EOL;
	ous.flush();
}

void writeSetter(OutputStream ous, String prototype, String propertyName)
{
	ous <<< prototype + ".set" + replaceInitialToUpper(propertyName) + " = function() {" <<< EOL;
	ous <<< "\tvar args = verifyArgs(arguments);" <<< EOL;
	ous <<< "\tthis.rawptr." + propertyName + " = args[0];" <<< EOL;
	ous <<< "};" <<< EOL;
	ous.flush();
}

void writeMethod(OutputStream ous, String prototype, String methodName, String retType, int argc)
{
	String strArgs = "";

	for(i = 0; i < argc; i++) {
		if(i != 0) strArgs += ", ";
		strArgs += "args[";
		strArgs += i;
		strArgs += "]";
	}

	ous <<< prototype + "." + methodName + " = function() {" <<< EOL;
	if(argc != 0) ous <<< "\tvar args = verifyArgs(arguments);" <<< EOL;
	switch(retType) {
		case "void":
			ous <<< "\tthis.rawptr." + replaceInitialToUpper(methodName) + "(" + strArgs + ");" <<< EOL;
			break;
		case "int":
		case "float":
		case "boolean":
			ous <<< "\treturn this.rawptr." + replaceInitialToUpper(methodName) + "(" + strArgs + ");" <<< EOL;
			break;
		case "String":
			ous <<< "\treturn new konoha.String(this.rawptr." + replaceInitialToUpper(methodName) + "(" + strArgs + "));" <<< EOL;
			break;
		default:
			ous <<< "\treturn new js.box2d." + retType + "(this.rawptr." + replaceInitialToUpper(methodName) + "(" + strArgs + "));" <<< EOL;
	}
	ous <<< "}" <<< EOL;
}

void main(String[] args)
{
	int argc;
	String line;
	String className;
	String fullClassName;
	String methodName;
	String prototype;
	String propertyName;
	String retType;
	InputStream ins = new(args[0], "r");
	OutputStream ous = new("out.js", "w");
	while((line = ins.readline()) != EOL) {
		if(line == "}") break;
		if(line == "") continue;

		if(line.startsWith("//")) continue;
		else if(line.startsWith("class")) {
			className = line.split(" ")[1];
			fullClassName = "js.box2d." + className;
			ous <<< fullClassName + " = function(rawptr) {" <<< EOL;
			ous <<< "\tthis.rawptr = rawptr" <<< EOL;
			ous <<< "}" <<< EOL;
			prototype = fullClassName + ".prototype";
			ous <<< prototype + " = new konoha.Object();" <<< EOL;
			ous <<< prototype + '.konohaclass = "' + fullClassName + '";' <<< EOL;
		}
		else {
			line -= "\t";
			strs = line.split(" ");
			retType = strs[0];
			if(line.search("""(""") != -1) {
				methodName = strs[1].split("""(""")[0];
				arg = line.split("""(""")[1];
				if(arg[1].startsWith(""")""")) argc = 0;
				else argc = arg.split(",").getSize();
				writeMethod(ous, prototype, methodName, retType, argc);
			}
			else {
				propertyName = strs[1] - ";";
				writeGetter(ous, prototype, propertyName, retType);
				writeSetter(ous, prototype, propertyName);
			}
		}
		ous.flush();
	}
}
