#include "Shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string getFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = getFileContents(vertexFile); // gets code from txt files
	std::string fragmentCode = getFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str(); // convert from string to char arrays
	const char* fragmentSource = fragmentCode.c_str();

	// Create vertex shader object and get reference
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // GLuint = gl unsigned int = positive int
	// Attach vertex shader to the vso (vertex shader obejct)
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // assigns a reference to the shader source to it
	glCompileShader(vertexShader); // compiles shader into machine code

	// Create fragment shader object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach fragment shader to the fso (fragment shader obejct)
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Create program object and get reference (ID is later assigned to a program)
	ID = glCreateProgram(); // program = wrapper for all shaders
	glAttachShader(ID, vertexShader); // attaches vertex and fragment shaders to program
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader); // cleans up shaders as they are contained in the shader program
	glDeleteShader(fragmentShader);

}

void Shader::activate() {
	glUseProgram(ID);
}

void Shader::destroy() {
	glDeleteProgram(ID);
}