#include "lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace spg;


// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/SPG-Framework/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	nrInstances = 0;
	maxInstances = 50;
	shrink = 0;

	auto camera = GetSceneCamera();
	camera->SetPositionAndRotation(glm::vec3(0, 5, 4), glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
	camera->Update();

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("bamboo");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDirPath, RESOURCE_PATH::MODELS, "vegetation", "bamboo"), "bamboo.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for rendering to texture
	{
		Shader *shader = new Shader("Instances");
		shader->AddShader(PATH_JOIN(window->props.selfDirPath, SOURCE_PATH::SPG, "lab1", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDirPath, SOURCE_PATH::SPG, "lab1", "shaders", "GeometryShader.glsl"), GL_GEOMETRY_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDirPath, SOURCE_PATH::SPG, "lab1", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	ClearScreen();

	{
		auto shader = shaders["Instances"];

		shader->Use();

		int loc_instances = shader->GetUniformLocation("instances");
		glUniform1i(loc_instances, nrInstances);
		//TODO add a shrink parameter for scaling each triangle in geometry shader
		

		RenderMesh(meshes["bamboo"], shaders["Instances"], glm::vec3(-3.3f, 0.5f, 0), glm::vec3(0.1f));
	}
}

void Laborator1::FrameEnd()
{
	DrawCoordinateSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/SPG-Framework/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input with window->KeyHold()

	//TODO add update for modifying the shrink parameter
}

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event

	if (key == GLFW_KEY_EQUAL)
	{
		nrInstances++;
		nrInstances %= maxInstances;
	}

	if (key == GLFW_KEY_MINUS)
	{
		nrInstances--;
		nrInstances %= maxInstances;
	}
}

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
