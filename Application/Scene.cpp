/*
 * Antonin Harok HAR0199
 *
 * File: Scene.cpp
 * Description:  Implementation file for the Scene class
 */

#include "Scene.h"
#include "DrawableObject.h"
#include "Model.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "TransformationComposite.h"
#include "TransformationLeaf.h"

#include <glad/gl.h>
#include <iterator>
#include <vector>
#include <memory>
#include <random>

#include "Models/sphere.h"
#include "Models/suzi_smooth.h"
#include "Models/login.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/moon.h"
#include "Models/sun.h"
#include "Models/earth.h"
#include "Models/clock.h"
#include "Models/ground.h"
#include "Models/space_gun.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::createShaders()
{
	// Index 0: Red
	createShaderProgram("shaders/2D.vert", "shaders/red.frag");

	// Index 1: Blue
	createShaderProgram("shaders/2D.vert", "shaders/blue.frag");

	// Index 2: rainbow 
	createShaderProgram("shaders/2D.vert", "shaders/basic.frag");

	//Index 3: Tree shader
	createShaderProgram("shaders/tree.vert", "shaders/tree.frag");

	//Index 4: Clock shader
	createShaderProgram("shaders/clock.vert", "shaders/basic.frag");

	//Index 5: Ground shader
	createShaderProgram("shaders/basic.vert", "shaders/ground.frag");

	//Index 6: Ambient
	createShaderProgram("shaders/basic.vert", "shaders/ambient.frag");

	//Index 7: Lambert - Diffuse
	createShaderProgram("shaders/basic.vert", "shaders/diffuse.frag");

	//Index 8: Phong
	createShaderProgram("shaders/basic.vert", "shaders/phong.frag");

	//Index 9: Blinn-Phong
	createShaderProgram("shaders/basic.vert", "shaders/blinn-phong.frag");

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);    
	glm::vec3 ambientLight = glm::vec3(0.2f, 0.2f, 0.2f);  
	glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 0.0f);  

	for (size_t idx = 6; idx <= 9 && idx < shaderPrograms_.size(); ++idx)
	{
		shaderPrograms_[idx]->use();
		shaderPrograms_[idx]->setUniform("lightColor", lightColor);
		shaderPrograms_[idx]->setUniform("ambientLight", ambientLight);
		shaderPrograms_[idx]->setUniform("lightPosition", lightPosition);
	}


	if (!camera_ && !shaderPrograms_.empty())
	{
		camera_ = std::make_unique<Camera>();

		// registration all to camera observer
		for (auto& program : shaderPrograms_)
		{
			program->setCamera(camera_.get());
			camera_->attach(program.get()); 
		}
	}
}


void Scene::createModels(int mode)
{
	if(mode == 1)
	{
		triangleScene();
		signatureScene();
	}
	else if(mode == 2)
	{
		if (shaderPrograms_.empty()) //sphere
			return;
			
		sphereScene(glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.0f, glm::vec3(0, 1, 0), 0.0f, 7);
		sphereScene(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(1.0f), 0.0f, glm::vec3(0, 1, 0), 0.0f, 7);
		sphereScene(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.0f, glm::vec3(0, 1, 0), 0.0f, 7);
		sphereScene(glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(1.0f), 0.0f, glm::vec3(0, 1, 0), 0.0f, 7);

	}
	else if(mode == 3)
	{
		groundScene();

		for (int i = 0; i < 74; i++)
		{
			float posX = ((rand() % 3000) / 100.0f) - 15.0f;
			float posZ = ((rand() % 3000) / 100.0f) - 15.0f;
			float scale = ((rand() % 50) / 100.0f) + 0.10f;
			float rotY = ((rand() % 360) * 3.14159f) / 180.0f;

			treeScene(glm::vec3(posX, 0.0f, posZ), glm::vec3(scale), rotY, glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 3);
			
		}

		for (int i = 0; i < 40; i++)
		{
			float posX = ((rand() % 3000) / 100.0f) - 15.0f;
			float posZ = ((rand() % 3000) / 100.0f) - 15.0f;
			float scale = ((rand() % 50) / 100.0f) + 0.50f;

			bushScene(glm::vec3(posX, 0.0f, posZ), glm::vec3(scale));
		}

		clockScene(glm::vec3(-1.8f, 2.0f, 1.0f), glm::vec3(0.7f));
		clockScene(glm::vec3(1.8f, 2.0f, 1.0f), glm::vec3(0.7f));
		planetsScene(glm::vec3(0.0f, 18.0f, -25.0f), glm::vec3(4.0f));
		signatureScene(glm::vec3(0.0f, 1.8f, 1.0f), glm::vec3(0.5f));

	}
	else if (mode == 4) //login
	{
		signatureScene();
	}
	else if (mode == 5) 
	{
		squareScene();
		signatureScene();
	}
	else if (mode == 6)
	{
		planetsScene();
	}

	else if(mode == 7)
	{ 
		clockScene();
	}
}
void Scene::triangleScene(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis, float rotationSpeed, int shaderIndex)
{
	static std::vector<float> triangleData = {
		0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};
	static Model triangleModel(triangleData, 3, GL_TRIANGLES);

	auto triangle = std::make_unique<DrawableObject>(*shaderPrograms_[shaderIndex], triangleModel);
	auto composite = std::make_shared<TransformationComposite>();

	composite->addTransformation(std::make_shared<Translate>(position));
	composite->addTransformation(std::make_shared<Rotate>(rotationAngle, rotationAxis, rotationSpeed));
	composite->addTransformation(std::make_shared<Scale>(scale));

	triangle->setTransformation(composite);
	drawableObjects_.push_back(std::move(triangle));
}

void Scene::squareScene(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis, float rotationSpeed, int shaderIndex)
{
	static std::vector<float> squareData = {
		-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f
	};
	static Model squareModel(squareData, 4, GL_TRIANGLE_STRIP);

	auto squareObj = std::make_unique<DrawableObject>(*shaderPrograms_[shaderIndex], squareModel);
	auto composite = std::make_shared<TransformationComposite>();

	composite->addTransformation(std::make_shared<Translate>(position));
	if (rotationSpeed != 0.0f || rotationAngle != 0.0f)
		composite->addTransformation(std::make_shared<Rotate>(rotationAngle, rotationAxis, rotationSpeed));
	composite->addTransformation(std::make_shared<Scale>(scale));

	squareObj->setTransformation(composite);
	drawableObjects_.push_back(std::move(squareObj));
}

void Scene::sphereScene(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis, float rotationSpeed, int shaderIndex)
{
	static std::vector<float> sphereData(sphere, sphere + sizeof(sphere) / sizeof(float));
	static Model sphereModel(sphereData, static_cast<int>(sphereData.size() / 6), GL_TRIANGLES);

	auto sphereObject = std::make_unique<DrawableObject>(*shaderPrograms_[shaderIndex], sphereModel);
	auto composite = std::make_shared<TransformationComposite>();

	composite->addTransformation(std::make_shared<Translate>(position));
	if (rotationSpeed != 0.0f || rotationAngle != 0.0f)
		composite->addTransformation(std::make_shared<Rotate>(rotationAngle, rotationAxis, rotationSpeed));
	composite->addTransformation(std::make_shared<Scale>(scale));

	sphereObject->setTransformation(composite);
	drawableObjects_.push_back(std::move(sphereObject));
}

void Scene::treeScene(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis, float rotationSpeed, int shaderIndex)
{
	static std::vector<float> treeData(tree, tree + sizeof(tree) / sizeof(float));
	static Model treeModel(treeData, static_cast<int>(treeData.size() / 6), GL_TRIANGLES);

	auto treeObj = std::make_unique<DrawableObject>(*shaderPrograms_[shaderIndex], treeModel);
	auto trans = std::make_shared<TransformationComposite>();

	trans->addTransformation(std::make_shared<Translate>(position));
	trans->addTransformation(std::make_shared<Scale>(scale));
	trans->addTransformation(std::make_shared<Rotate>(rotationAngle, rotationAxis, rotationSpeed));

	treeObj->setTransformation(trans);
	drawableObjects_.push_back(std::move(treeObj));
}

void Scene::bushScene(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis, float rotationSpeed, int shaderIndex)
{
	static std::vector<float> bushData(bushes, bushes + sizeof(bushes) / sizeof(float));
	static Model bushModel(bushData, static_cast<int>(bushData.size() / 6), GL_TRIANGLES);

	auto bushObj = std::make_unique<DrawableObject>(*shaderPrograms_[shaderIndex], bushModel);
	auto trans = std::make_shared<TransformationComposite>();

	trans->addTransformation(std::make_shared<Translate>(position));
	trans->addTransformation(std::make_shared<Scale>(scale));
	if (rotationSpeed != 0.0f || rotationAngle != 0.0f)
		trans->addTransformation(std::make_shared<Rotate>(rotationAngle, rotationAxis, rotationSpeed));

	bushObj->setTransformation(trans);
	drawableObjects_.push_back(std::move(bushObj));
}

void Scene::signatureScene(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis, float rotationSpeed, int shaderIndex)
{
	static std::vector<float> loginData(login, login + sizeof(login) / sizeof(float));
	static Model loginModel(loginData, static_cast<int>(loginData.size() / 6), GL_TRIANGLES);

	auto loginObject = std::make_unique<DrawableObject>(*shaderPrograms_[shaderIndex], loginModel);
	auto composite = std::make_shared<TransformationComposite>();

	composite->addTransformation(std::make_shared<Translate>(position));
	if (rotationSpeed != 0.0f || rotationAngle != 0.0f)
		composite->addTransformation(std::make_shared<Rotate>(rotationAngle, rotationAxis, rotationSpeed));
	composite->addTransformation(std::make_shared<Scale>(scale));

	loginObject->setTransformation(composite);
	drawableObjects_.push_back(std::move(loginObject));
}

void Scene::clockScene(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis, float rotationSpeed, int shaderIndex)
{
	static std::vector<float> clockData(clockModel, clockModel + sizeof(clockModel) / sizeof(float));
	static Model clockGlModel(clockData, static_cast<int>(clockData.size() / 9), GL_TRIANGLES);

	auto clockObject = std::make_unique<DrawableObject>(*shaderPrograms_[shaderIndex], clockGlModel);

	auto composite = std::make_shared<TransformationComposite>();
	composite->addTransformation(std::make_shared<Translate>(position));
	composite->addTransformation(std::make_shared<Rotate>(glm::pi<float>() + rotationAngle, rotationAxis, rotationSpeed));
	composite->addTransformation(std::make_shared<Scale>(glm::vec3(-0.5f * scale.x, 0.5f * scale.y, 0.5f * scale.z)));

	clockObject->setTransformation(composite);
	drawableObjects_.push_back(std::move(clockObject));
}

void Scene::groundScene(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis, float rotationSpeed, int shaderIndex)
{
	static std::vector<float> groundData(ground, ground + sizeof(ground) / sizeof(float));
	static Model groundModel(groundData, static_cast<int>(groundData.size() / 6), GL_TRIANGLES);

	auto groundObject = std::make_unique<DrawableObject>(*shaderPrograms_[shaderIndex], groundModel);
	auto comp = std::make_shared<TransformationComposite>();

	comp->addTransformation(std::make_shared<Translate>(position));
	comp->addTransformation(std::make_shared<Rotate>(rotationAngle, rotationAxis, rotationSpeed));
	comp->addTransformation(std::make_shared<Scale>(scale));

	groundObject->setTransformation(comp);
	drawableObjects_.push_back(std::move(groundObject));
}

void Scene::planetsScene(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis, float rotationSpeed, int shaderIndex)
{
	static std::vector<float> sunData(sun, sun + sizeof(sun) / sizeof(float));
	static std::vector<float> earthData(earth, earth + sizeof(earth) / sizeof(float));
	static std::vector<float> moonData(moon, moon + sizeof(moon) / sizeof(float));

	static Model sunModel(sunData, static_cast<int>(sunData.size() / 9), GL_TRIANGLES);
	static Model earthModel(earthData, static_cast<int>(earthData.size() / 9), GL_TRIANGLES);
	static Model moonModel(moonData, static_cast<int>(moonData.size() / 9), GL_TRIANGLES);

	auto earthRotation = std::make_shared<Rotate>(rotationAngle, rotationAxis, 0.01f);
	earthRotation->setRotationDirection(1);
	auto earthDistTrans = std::make_shared<Translate>(glm::vec3(0.6f * scale.x, 0.0f, 0.0f));

	auto moonRotation = std::make_shared<Rotate>(rotationAngle, rotationAxis, 0.03f);
	moonRotation->setRotationDirection(1);
	auto moonDistTrans = std::make_shared<Translate>(glm::vec3(0.15f * scale.x, 0.0f, 0.0f));

	auto axisRotation = std::make_shared<Rotate>(rotationAngle, rotationAxis, rotationSpeed);
	axisRotation->setRotationDirection(1);

	// 1. Sun
	auto sunObj = std::make_unique<DrawableObject>(*shaderPrograms_[6], sunModel);
	auto sunTrans = std::make_shared<TransformationComposite>();
	sunTrans->addTransformation(std::make_shared<Translate>(position));
	sunTrans->addTransformation(std::make_shared<Scale>(glm::vec3(0.2f) * scale));
	sunTrans->addTransformation(axisRotation);
	sunObj->setTransformation(sunTrans);
	drawableObjects_.push_back(std::move(sunObj));

	// 2. Earth
	auto earthObj = std::make_unique<DrawableObject>(*shaderPrograms_[8], earthModel);
	auto earthTrans = std::make_shared<TransformationComposite>();
	earthTrans->addTransformation(std::make_shared<Translate>(position));
	earthTrans->addTransformation(earthRotation);
	earthTrans->addTransformation(earthDistTrans);
	earthTrans->addTransformation(std::make_shared<Scale>(glm::vec3(0.1f) * scale));
	earthTrans->addTransformation(axisRotation);
	earthObj->setTransformation(earthTrans);
	drawableObjects_.push_back(std::move(earthObj));

	// 3. Moon
	auto moonObj = std::make_unique<DrawableObject>(*shaderPrograms_[9], moonModel);
	auto moonTrans = std::make_shared<TransformationComposite>();
	moonTrans->addTransformation(std::make_shared<Translate>(position));
	moonTrans->addTransformation(earthRotation);
	moonTrans->addTransformation(earthDistTrans);
	moonTrans->addTransformation(moonRotation);
	moonTrans->addTransformation(moonDistTrans);
	moonTrans->addTransformation(std::make_shared<Scale>(glm::vec3(0.02f) * scale));
	moonTrans->addTransformation(axisRotation);
	moonObj->setTransformation(moonTrans);
	drawableObjects_.push_back(std::move(moonObj));

	
}
/*
void Scene::alienScene(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis, float rotationSpeed, int shaderIndex)
{
	static std::vector<float> spaceGunData(space_gun, space_gun + sizeof(space_gun) / sizeof(float));
	static Model spaceGunModel(spaceGunData, static_cast<int>(spaceGunData.size() / 9), GL_TRIANGLES);

	auto spaceGunObj = std::make_unique<DrawableObject>(*shaderPrograms_[shaderIndex], spaceGunModel);
	auto composite = std::make_shared<TransformationComposite>();
	composite->addTransformation(std::make_shared<Translate>(position));
	composite->addTransformation(std::make_shared<Rotate>(glm::pi<float>() + rotationAngle, rotationAxis, rotationSpeed));
	composite->addTransformation(std::make_shared<Scale>(glm::vec3(-0.5f * scale.x, 0.5f * scale.y, 0.5f * scale.z)));

	drawableObjects_.push_back(std::move(spaceGunObj));

}*/

void Scene::clearModels()
{
	drawableObjects_.clear();
}


void Scene::update()
{
	for (auto& obj : drawableObjects_)
		obj->update();

	float time = static_cast<float>(glfwGetTime());

	float secAngle = -glm::mod(time, 60.0f) / 60.0f * glm::two_pi<float>();
	float minAngle = -glm::mod(time / 60.0f, 60.0f) / 60.0f * glm::two_pi<float>();
	float hourAngle = -glm::mod(time / 3600.0f, 12.0f) / 12.0f * glm::two_pi<float>();

	if (shaderPrograms_.size() > 4)
	{
		shaderPrograms_[4]->use();
		shaderPrograms_[4]->setUniform("secAngle", secAngle);
		shaderPrograms_[4]->setUniform("minAngle", minAngle);
		shaderPrograms_[4]->setUniform("hourAngle", hourAngle);
	}
}

void Scene::setRotationDirection(int direction)
{
	for (auto& obj : drawableObjects_)
		obj->setRotationDirection(direction);
}


void Scene::render()
{
	for (auto& obj : drawableObjects_)
	{
		if (obj)
			obj->draw();
	}
}

void Scene::moveCamera(int direction)
{
	if (!camera_)
		return;
	switch (direction)
	{
	case 0: // forward w
		camera_->moveForward(0.1f); 
		break;
	case 1: // backward s
		camera_->moveBackward(0.1f);
		break;
	case 2: // left a
		camera_->moveLeft(0.1f);
		break;
	case 3: // right d
		camera_->moveRight(0.1f);
		break;
	default:
		break;
	}
}

void Scene::rotateCamera(float xpos, float ypos)
{
	if (camera_)
		camera_->onMouseMove(xpos, ypos);
}

void Scene::createShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	Shader vertexShader(GL_VERTEX_SHADER, vertexPath);
	Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentPath);
	shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
		std::move(vertexShader), std::move(fragmentShader)));
}

void Scene::windowResize(int width, int height)
{
	if (camera_)
	{
		float aspect = static_cast<float>(width) / static_cast<float>(height);
		camera_->setAspectRatio(aspect);
	}
}