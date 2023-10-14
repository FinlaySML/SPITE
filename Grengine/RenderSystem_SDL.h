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
		//Inherited from RenderSystem interface
		int			OpenWindow(int width, int height) final;
		int			CreateRenderer() final;
		void		Clear() final;
		std::unique_ptr<SpriteBatch> CreateSpriteBatch() final;
		void		Display() final;
		void		HandleWindowEvent(GR_WindowEvent& e) final;
		void SetFullscreen(bool) final;
		bool GetFullscreen() final;
		Spite::Camera& Camera() final;
		glm::vec3& BackgroundColour() final;

		glm::mat4x4 CalculateCameraMatrix();

		inline int	GetScreenWidth()		const { return m_ScreenWidth; };
		inline int	GetScreenHeight()	const { return m_ScreenHeight; };

	private:
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
    };
}

