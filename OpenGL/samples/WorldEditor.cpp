#include "WorldEditor.h"
#include "VertexArray.h"
#include "cameras/PerspectiveCamera.h"
#include "../constants/ScreenParams.h"
#include "../utils/CameraHandler.h"
#include "../../ThirdParty/stb_image/stb_image.h"
#include <iostream>
#include "../renderers/CubeRenderer.h"
#include "../shapes/Cube.h"

namespace samples
{
	static WorldEditor* editorInstance;
	static unsigned skyboxVAO;

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    WorldEditor::WorldEditor(GLFWwindow& window)
    {
		editorInstance = this;

		glfwSetCursorPosCallback(&window, mouse_callback);

        shader.reset(new Shader("Basic.shader"));
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", glm::mat4(1.f));

        skyShader.reset(new Shader("../OpenGL.Common/src/shaders/SkyGradient.glsl"));
		skyboxShader.reset(new Shader("../OpenGL.Common/src/shaders/Skybox.glsl"));

        camera.reset(new open_gl_engine::cameras::PerspectiveCamera(screen_params::Width, screen_params::Height, 45, 0.1f, 1000));
        camera->SetPosition({ 0, 20, 20 });
        camera->SetRotationX(-45);

		std::string str = "resources/models/crysisSuit/scene.fbx";
		//std::string str = "resources/models/house/Toepferhaus_neu.obj";
		model.reset(new open_gl_engine::Model(str.c_str()));


    	//setting skybox
		skyboxCubemapTextureId = LoadSkyBox();

		//Cube cube = Cube(0, 0, 0, 2, 2, 2);
		//vector<float> points = cube.GetPoints();

    	
		// skybox VAO
		unsigned int skyboxVBO;
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }


    WorldEditor::~WorldEditor()
    {
    }

    void samples::WorldEditor::OnUpdate(float deltaTime, GLFWwindow* window)
    {
        UpdateCamera(deltaTime, window);

        glm::mat4 modelViewProjection = camera->GetViewProjectionMatrix() * glm::mat4(1.0f);
        shader->SetUniformMat4f("u_MVP", modelViewProjection);
    }

    void samples::WorldEditor::OnRender()
    {
        //TODO: add camera that looks from above. Draw lines along Z and X
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.4f, 0.4f, 0.4f, 0);

        //DrawSkyGradient();
		DrawSkyBox();
        DrawWorldGrid();
		DrawScene();
    }

    void samples::WorldEditor::UpdateCamera(float deltaTime, GLFWwindow* window)
    {
        utils::CameraHandler cameraHandler;
        cameraHandler.UpdatePosition(deltaTime, window, camera.get());
    }

    void WorldEditor::DrawSkyGradient()
    {
        glDisable(GL_DEPTH_TEST);

        static GLuint background_vao = 0;
        glGenVertexArrays(1, &background_vao);

        skyShader->Bind();
        skyShader->SetUniform4f("top_color_top", 0.5f, 0.8, 0.9,1);
        skyShader->SetUniform4f("top_color_mid", 0.3f, 0.6,0.9,1);
        skyShader->SetUniform4f("bot_color_mid", 0.3,0.3,0.3,1);
        skyShader->SetUniform4f("bot_color_bot", 0.2,0.2,0.2,1);

        glBindVertexArray(background_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glEnable(GL_DEPTH_TEST);
    }

	void WorldEditor::DrawSkyBox()
    {
		skyboxShader->Bind();

		glm::mat4 view = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
		skyboxShader->SetUniformMat4f("view", view);
		skyboxShader->SetUniformMat4f("projection", camera->GetProjectionMatrix());

		// draw skybox as last
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxCubemapTextureId);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default
    }
	
	unsigned int WorldEditor::LoadSkyBox()
	{
		vector<std::string> faces =
		{
			"resources/textures/skybox/right.jpg",
			"resources/textures/skybox/left.jpg",
			"resources/textures/skybox/top.jpg",
			"resources/textures/skybox/bottom.jpg",
			"resources/textures/skybox/front.jpg",
			"resources/textures/skybox/back.jpg"
		};

		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}

    void WorldEditor::DrawWorldGrid()
    {
        shader->Bind();
        //TODO: reduce draw calls
        for(int x = -50; x < 51; x++)
        {
            float zCoord = x * 10;
            std::vector<GLfloat> horizontalLinePoints =
            {
                -static_cast<float>(screen_params::Width) / 2, 0, zCoord,
                static_cast<float>(screen_params::Width) / 2, 0, zCoord
            };

            VertexBuffer vb = VertexBuffer(&horizontalLinePoints[0], horizontalLinePoints.size() * sizeof(float));

            VertexBufferLayout layout;
            layout.Push<float>(3);

            VertexArray va = VertexArray();
            va.AddBuffer(vb, layout);

            glDrawArrays(GL_LINES, 0, horizontalLinePoints.size());

            float xCoord = x * 10;
            std::vector<GLfloat> verticalLinePoints =
            {
                xCoord, 0, -static_cast<float>(screen_params::Height) / 2,
                xCoord, 0, static_cast<float>(screen_params::Height) / 2
            };

            VertexBuffer vb2 = VertexBuffer(&verticalLinePoints[0], verticalLinePoints.size() * sizeof(float));

            VertexBufferLayout layout2;
            layout2.Push<float>(3);

            VertexArray va2 = VertexArray();
            va2.AddBuffer(vb2, layout2);

            glDrawArrays(GL_LINES, 0, verticalLinePoints.size());
        }
    }

	void WorldEditor::DrawScene() {
		model->Draw(*shader);
	}


	float mouseSensitivity = 0.1;
	float lastX = screen_params::Width / 2.0f;
	float lastY = screen_params::Height / 2.0f;
	bool firstMouse = true;
	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		xpos *= mouseSensitivity;
		ypos *= mouseSensitivity;

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
			return;
		}

		const float xoffset = xpos - lastX;
		const float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		editorInstance->camera->RotateY(-xoffset);
		editorInstance->camera->RotateX(yoffset);
	}
}
