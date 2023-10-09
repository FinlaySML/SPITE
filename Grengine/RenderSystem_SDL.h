#pragma once
#include "pch.h"
#include "RenderSystem.h"
#include "Texture_GL.h"

//Forward declarations
class SDL_Window;
class SDL_Renderer;

namespace Spite {
    class RenderSystem_SDL :
        public RenderSystem
    {
	public:
		RenderSystem_SDL();
		~RenderSystem_SDL();

		//Inherited from Subsystem interface
		int			Initialise() final;
		int			Shutdown() final;

	public:
		//Inherited from RenderSystem interface
		int			OpenWindow(int width, int height) final;
		int			CreateRenderer() final;
		void		Clear() final;
		void		DrawSprite(const Sprite& sprite) final;
		void		Display() final;
		void		HandleWindowEvent(GR_WindowEvent& e) final;
		Spite::Camera& Camera() final;
		glm::vec3& BackgroundColour() final;

		inline int	GetScreenWidth()		const { return m_ScreenWidth; };
		inline int	GetScreenHeight()	const { return m_ScreenHeight; };

	private:
		struct ShaderSpriteData {
			glm::vec2 translation{ 0,0 };
			glm::vec2 scale{ 1,1 };
			float rotation{ 0 };
			float z{ 0 };
			glm::vec2 uvOrigin{ 0,0 };
			glm::vec2 uvDimension{ 1,1 };
		};
		std::vector<ShaderSpriteData> spriteBatch;

		Spite::Camera camera;

		SDL_Window*		m_Window;
		
		int				m_ScreenWidth;
		int				m_ScreenHeight;
		
		//OpenGL
		unsigned int VBO;
		unsigned int VAO;
		unsigned int program;
		unsigned int viewProjectionLoc;
		Spite::Texture_GL testTexture;
		glm::vec3 backgroundColour;
		unsigned int LoadShader(std::string path, int shaderType);
    };
}

