#pragma once
#include "pch.h"
#include "RenderSystem.h"
#include "Texture_GL.h"
#include "SpriteBatch_GL.h"

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
		std::unique_ptr<Texture> CreateTexture() final;
		std::unique_ptr<Atlas> CreateAtlas() final;
		void		Display() final;
		void		HandleWindowEvent(GR_WindowEvent& e) final;
		void SetFullscreen(bool) final;
		bool GetFullscreen() final;
		Spite::Camera& Camera() final;
		SpriteBatch* GetDefaultSpriteBatch() final;
		glm::vec3& BackgroundColour() final;
		std::shared_ptr<Texture> GetTexture(const std::string& path) final;

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
		std::unordered_map<std::string, std::weak_ptr<Texture_GL>> textures;
		std::unique_ptr<Spite::SpriteBatch_GL> defaultSpriteBatch;
		glm::vec3 backgroundColour;
    };
}

