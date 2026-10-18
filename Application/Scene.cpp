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

#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::createShaders()
{
	// Index 0: Red 
    Shader sphereVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader sphereFragmentShader(GL_FRAGMENT_SHADER, "shaders/red.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(sphereVertexShader), std::move(sphereFragmentShader)));

    // Index 1: Blue 
    Shader suziVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader suziFragmentShader(GL_FRAGMENT_SHADER, "shaders/blue.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(suziVertexShader), std::move(suziFragmentShader)));

	// Index 2: rainbow (basic colors from vertices for triangle and square)
    Shader rainbowVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader rainbowFragmentShader(GL_FRAGMENT_SHADER, "shaders/basic.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(rainbowVertexShader), std::move(rainbowFragmentShader)));

	//Index 3: Tree shader
	Shader treeVertexShader(GL_VERTEX_SHADER, "shaders/tree.vert");
	Shader treeFragmentShader(GL_FRAGMENT_SHADER, "shaders/tree.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(treeVertexShader), std::move(treeFragmentShader)));

	//Index 4: Clock shader
	Shader clockVertexShader(GL_VERTEX_SHADER, "shaders/clock.vert");
	Shader clockFragmentShader(GL_FRAGMENT_SHADER, "shaders/basic.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(clockVertexShader), std::move(clockFragmentShader)));

	//Index 5: Ground shader
	Shader BrownVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
	Shader BrownFragmentShader(GL_FRAGMENT_SHADER, "shaders/ground.frag");
	shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
		std::move(BrownVertexShader), std::move(BrownFragmentShader)));

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
		// 1. triangle with vertex colors
		std::vector<float> triangleData = {
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		static Model triangleModel(triangleData, 3, GL_TRIANGLES);
		auto triangle = std::make_unique<DrawableObject>(*shaderPrograms_[2], triangleModel);
		auto composite = std::make_shared<TransformationComposite>();
		
		composite->addTransformation(std::make_shared<Rotate>(0.0f, glm::vec3(0.0f, 0.0f, 1.0f), 0.02f));
		composite->addTransformation(std::make_shared<Translate>(glm::vec3(0.5f, 0.0f, 0.0f)));
		

		triangle->setTransformation(composite);
		drawableObjects_.push_back(std::move(triangle));
		signature();
	}
	else if(mode == 2)
	{
		if (shaderPrograms_.empty()) //sphere
			return;

		static std::vector<float> sphereData(sphere, sphere + sizeof(sphere) / sizeof(float));
		static Model sphereModel(sphereData, static_cast<int>(sphereData.size() / 6), GL_TRIANGLES);

		auto sphereObject = std::make_unique<DrawableObject>(*shaderPrograms_[0], sphereModel);
		auto composite = std::make_shared<TransformationComposite>();
		composite->addTransformation(std::make_shared<Translate>(glm::vec3(0.0f, 0.0f, 0.0f)));
		composite->addTransformation(std::make_shared<Scale>(glm::vec3(0.5f)));
		sphereObject->setTransformation(composite);

		drawableObjects_.push_back(std::move(sphereObject));
		signature();
	}
	else if(mode == 3)
	{
		groundSetup();
		static std::vector<float> treeData(tree, tree + sizeof(tree) / sizeof(float));
		static std::vector<float> bushData(bushes, bushes + sizeof(bushes) / sizeof(float));
		static Model treeModel(treeData, static_cast<int>(treeData.size() / 6), GL_TRIANGLES);
		static Model bushModel(bushData, static_cast<int>(bushData.size() / 6), GL_TRIANGLES);
	
	
		for (int i = 0; i < 74; i++)
		{
			auto treeObj = std::make_unique<DrawableObject>(*shaderPrograms_[3], treeModel);
			auto trans = std::make_shared<TransformationComposite>();
			
			float posX = ((rand() % 3000) / 100.0f) - 15.0f; // -15 to +15
			float posZ = ((rand() % 3000) / 100.0f) - 15.0f; // -15 to +15
			float scale = ((rand() % 50) / 100.0f) + 0.10f;

			float rotY = ((rand() % 360) * 3.14159f) / 180.0f; 

			trans->addTransformation(std::make_shared<Translate>(glm::vec3(posX, 0.0f, posZ)));
			trans->addTransformation(std::make_shared<Scale>(glm::vec3(scale)));
			trans->addTransformation(std::make_shared<Rotate>(rotY, glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
			treeObj->setTransformation(trans);
			drawableObjects_.push_back(std::move(treeObj));

		}
		for (int i = 0; i < 40; i++)
		{
			auto bushObj = std::make_unique<DrawableObject>(*shaderPrograms_[3], bushModel);
			auto trans = std::make_shared<TransformationComposite>();

			float posX = ((rand() % 3000) / 100.0f) - 15.0f;
			float posZ = ((rand() % 3000) / 100.0f) - 15.0f;
			float scale = ((rand() % 50) / 100.0f) + 0.50f;

			trans->addTransformation(std::make_shared<Translate>(glm::vec3(posX, 0.0f, posZ)));
			trans->addTransformation(std::make_shared<Scale>(glm::vec3(scale)));

			bushObj->setTransformation(trans);
			drawableObjects_.push_back(std::move(bushObj));
		}
		clock(glm::vec3(-1.8f, 2.0f, 1.0f), 0.7f);
		clock(glm::vec3(1.8f, 2.0f, 1.0f), 0.7f);
		planets(glm::vec3(0.0f, 18.0f, -25.0f), 4.0f);
		signature(glm::vec3(0.0f, 1.8f, 1.0f), 0.5f);

	}
	else if (mode == 4) //login
	{
		static std::vector<float> LoginData(login, login + sizeof(login) / sizeof(float));
		static Model LoginModel(LoginData, static_cast<int>(LoginData.size() / 6), GL_TRIANGLES);

		auto LoginObject = std::make_unique<DrawableObject>(*shaderPrograms_[1], LoginModel);
		LoginObject->setTransformation(std::make_shared<Translate>(glm::vec3(0.0f, 0.0f, 0.0f)));
		drawableObjects_.push_back(std::move(LoginObject));
	}
	else if (mode == 5) 
	{
		// square with 4th vextex color (yellow) and using GL_TRIANGLE_STRIP
		std::vector<float> squareData = {
			-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, //   1
			-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, //   2
			0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, //  3
			0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f  //             4 
		};
		static Model squareModel(squareData, 4, GL_TRIANGLE_STRIP);
		drawableObjects_.push_back(std::make_unique<DrawableObject>(*shaderPrograms_[2], squareModel));
		signature();
	}
	else if (mode == 6)
	{
		planets();
	}

	else if(mode == 7)
	{ 
		clock();
	}
}
void Scene::groundSetup()
{
	static std::vector<float> GroundData(ground, ground + sizeof(ground) / sizeof(float));
	static Model GroundModel(GroundData, static_cast<int>(GroundData.size() / 6), GL_TRIANGLES);

	auto GroundObject = std::make_unique<DrawableObject>(*shaderPrograms_[5], GroundModel);
	auto comp = std::make_shared<TransformationComposite>();

	comp->addTransformation(std::make_shared<Translate>(glm::vec3(0.0f, -0.05f, 0.0f)));
	comp->addTransformation(std::make_shared<Rotate>(-glm::half_pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	comp->addTransformation(std::make_shared<Scale>(glm::vec3(30.0f, 30.0f, 1.0f)));

	GroundObject->setTransformation(comp);
	drawableObjects_.push_back(std::move(GroundObject));
}

void Scene::planets(glm::vec3 basePosition, float baseScale)
{
	static std::vector<float> sunData(sun, sun + sizeof(sun) / sizeof(float));
	static std::vector<float> earthData(earth, earth + sizeof(earth) / sizeof(float));
	static std::vector<float> moonData(moon, moon + sizeof(moon) / sizeof(float));

	static Model sunModel(sunData, static_cast<int>(sunData.size() / 9), GL_TRIANGLES);
	static Model earthModel(earthData, static_cast<int>(earthData.size() / 9), GL_TRIANGLES);
	static Model moonModel(moonData, static_cast<int>(moonData.size() / 9), GL_TRIANGLES);

	// Shared rotation around the Sun for Earth and Moon (later)
	auto earthRotation = std::make_shared<Rotate>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), 0.01f);
	earthRotation->setRotationDirection(1);
	auto earthDistTrans = std::make_shared<Translate>(glm::vec3(0.6f * baseScale, 0.0f, 0.0f));

	// Share rotation around the Sun for Earth and Moon
	auto moonRotation = std::make_shared<Rotate>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), 0.03f);
	moonRotation->setRotationDirection(1);
	auto moonDistTrans = std::make_shared<Translate>(glm::vec3(0.15f * baseScale, 0.0f, 0.0f));

	// Shared rotation around its own axis for all planets
	auto axisRotation = std::make_shared<Rotate>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), 0.05f);
	axisRotation->setRotationDirection(1);


	// 1. Sun (In the center. S1 R1)
	auto sunObj = std::make_unique<DrawableObject>(*shaderPrograms_[2], sunModel);
	auto sunTrans = std::make_shared<TransformationComposite>();
	sunTrans->addTransformation(std::make_shared<Translate>(basePosition));
	sunTrans->addTransformation(std::make_shared<Scale>(glm::vec3(0.2f * baseScale)));
	sunTrans->addTransformation(axisRotation);
	sunObj->setTransformation(sunTrans);
	drawableObjects_.push_back(std::move(sunObj));

	//2. Earth R1 T1 S1 R2
	auto earthObj = std::make_unique<DrawableObject>(*shaderPrograms_[2], earthModel);
	auto earthTrans = std::make_shared<TransformationComposite>();
	earthTrans->addTransformation(std::make_shared<Translate>(basePosition));
	earthTrans->addTransformation(earthRotation);                           // R around Sun
	earthTrans->addTransformation(earthDistTrans);                          // T from Sun
	earthTrans->addTransformation(std::make_shared<Scale>(glm::vec3(0.1f * baseScale)));
	earthTrans->addTransformation(axisRotation);                                 // R around its own axis
	earthObj->setTransformation(earthTrans);
	drawableObjects_.push_back(std::move(earthObj));

	// 3. Moon R1 T1 R2 T2 S1 R3
	auto moonObj = std::make_unique<DrawableObject>(*shaderPrograms_[2], moonModel);
	auto moonTrans = std::make_shared<TransformationComposite>();
	moonTrans->addTransformation(std::make_shared<Translate>(basePosition));
	moonTrans->addTransformation(earthRotation);                            // R from Sun (inherited from Earth)
	moonTrans->addTransformation(earthDistTrans);                           // T from Earth
	moonTrans->addTransformation(moonRotation);                             // R around Earth
	moonTrans->addTransformation(moonDistTrans);                            // T from Earth
	moonTrans->addTransformation(std::make_shared<Scale>(glm::vec3(0.02f * baseScale)));
	moonTrans->addTransformation(axisRotation);                                  // R around its own axis
	moonObj->setTransformation(moonTrans);
	drawableObjects_.push_back(std::move(moonObj));

}

void Scene::clock(glm::vec3 basePosition, float baseScale)
{
	static std::vector<float> Clockdata(clockModel, clockModel + sizeof(clockModel) / sizeof(float));
	static Model ClockModel(Clockdata, static_cast<int>(Clockdata.size() / 9), GL_TRIANGLES);

	auto ClockObject = std::make_unique<DrawableObject>(*shaderPrograms_[4], ClockModel);

	auto composite = std::make_shared<TransformationComposite>();
	composite->addTransformation(std::make_shared<Translate>(basePosition));
	composite->addTransformation(std::make_shared<Scale>(glm::vec3(baseScale)));
	composite->addTransformation(std::make_shared<Rotate>(glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));

	composite->addTransformation(std::make_shared<Scale>(glm::vec3(-0.5f * baseScale, 0.5f * baseScale, 0.5f * baseScale)));

	ClockObject->setTransformation(composite);
	drawableObjects_.push_back(std::move(ClockObject));
}

void Scene::signature(glm::vec3 basePosition, float baseScale)
{
	static std::vector<float> LoginData(login, login + sizeof(login) / sizeof(float));
	static Model LoginModel(LoginData, static_cast<int>(LoginData.size() / 6), GL_TRIANGLES);

	auto LoginObject = std::make_unique<DrawableObject>(*shaderPrograms_[1], LoginModel);
	auto composite = std::make_shared<TransformationComposite>();

	composite->addTransformation(std::make_shared<Translate>(basePosition));
	composite->addTransformation(std::make_shared<Scale>(glm::vec3(baseScale)));

	LoginObject->setTransformation(composite);
	drawableObjects_.push_back(std::move(LoginObject));
}


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