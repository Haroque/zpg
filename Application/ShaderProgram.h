/*
 * Antonin Harok HAR0199
 *
 * File: ShaderProgram.h
 * Description:  Header file for the ShaderProgram class
 */

#pragma once
#include <glad/gl.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <vector>

#include "Shader.h"
#include "Observer.h"
class Camera;

class ShaderProgram : public Observer
{
public:
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	~ShaderProgram();


	bool setShaderProgram();
	void use() const;
	
	GLint uniformLocation(const GLchar* name) const;
	void setUniform(const GLchar* name, float value) const; //rotation
	void setUniform(const GLchar* name, int value) const;
	void setUniform(const GLchar* name, const glm::vec3& value) const;

	// transformation in projection space
	void setUniform(const GLchar* name, const glm::mat4 matrix) const;

	//ShaderProgram(Camera* camera);
	void setCamera(const Camera* camera);
	void notify() override;
	
	
	

private:
	const Camera* camera_ = nullptr;

	GLuint id = 0;
	Shader vertexShader_;
	Shader fragmentShader_;
	GLuint getId() const { return id; }

};