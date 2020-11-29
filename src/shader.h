#pragma once



#include <string>

class Shader
{
public:
	unsigned int ID; //programma id
	Shader(const char* vertexPath, const char* fragmentPath);

	void use() const;
	
	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value) const;

	void setFloat(const std::string& name, float value) const;

	void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4) const;
	void setUniform1i(const std::string name, int value) const;
	
private:
	void checkCompileErrors(unsigned int shader, std::string type);
	
};







