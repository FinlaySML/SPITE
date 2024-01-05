#pragma once
#include "pch.h"
#include "Subsystem.h"
#include <cstdint>
#include "SpriteComponent.h"
#include "Camera.h"
#include "SpriteBatch.h"
#include "Atlas.h"

namespace Spite {
	struct WindowEvent;
	/// <summary>
	/// Base on SDL's Window Event ID, this enum is used for the abstraction
	/// of window events we might need to handle
	/// </summary>

	class RenderSystem : public Subsystem
	{
	public:
		//Internal
		virtual int OpenWindow(int width, int height) = 0;
		virtual int CreateRenderer() = 0;
		virtual void Display() = 0;
		virtual void Clear() = 0;
		virtual void HandleWindowEvent(WindowEvent& e) = 0;
		//Create objects
		virtual std::unique_ptr<SpriteBatch> CreateSpriteBatch() = 0;
		virtual std::unique_ptr<Texture> CreateTexture() = 0;
		virtual std::unique_ptr<Atlas> CreateAtlas() = 0;
		//Render settings
		virtual void SetFullscreen(bool) = 0;
		virtual bool GetFullscreen() = 0;
		/// <summary>
		/// The camera that controls how you see the world
		/// </summary>
		/// <returns></returns>
		virtual Camera& Camera() = 0;
		/// <summary>
		/// Set the rendering clear colour / background colour
		/// </summary>
		/// <returns></returns>
		virtual glm::vec3& BackgroundColour() = 0;
		/// <summary>
		/// Set whether the aspect ratio is locked in using blackbars, or will expand with the window.
		/// </summary>
		/// <returns></returns>
		virtual bool& BlackBars() = 0;
		//Misc
		virtual SpriteBatch* GetDefaultSpriteBatch() = 0;
		//Textures
		/// <summary>
		/// Get a texture from the Asset folder, will return an existing texture if it has already been loaded
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		virtual std::shared_ptr<Texture> GetTexture(const std::string& path) = 0;
		/// <summary>
		/// Clears all the textures that are not currently in use from memory
		/// </summary>
		/// <param name="path"></param>
		virtual void ClearTextures() = 0;
	};

	//Global pointer to the RenderSystem
	extern RenderSystem* render;

	/**
	 * Based on the SDL_WindowEvent
	 * This should really be in its own file and could be a bit more abstracted.
	 * You get the idea though
	 */
	struct WindowEvent
	{
		enum class Type {
			WE_NONE,           /**< Never used */
			WE_SHOWN,          /**< Window has been shown */
			WE_HIDDEN,         /**< Window has been hidden */
			WE_EXPOSED,        /**< Window has been exposed and should be redrawn */

			WE_MOVED,          /**< Window has been moved to data1, data2*/

			WE_RESIZED,        /**< Window has been resized to data1xdata2 */
			WE_SIZE_CHANGED,   /**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */

			WE_MINIMIZED,      /**< Window has been minimized */
			WE_MAXIMIZED,      /**< Window has been maximized */
			WE_RESTORED,       /**< Window has been restored to normal size and position */

			WE_ENTER,          /**< Window has gained mouse focus */
			WE_LEAVE,          /**< Window has lost mouse focus */
			WE_FOCUS_GAINED,   /**< Window has gained keyboard focus */
			WE_FOCUS_LOST,     /**< Window has lost keyboard focus */
			WE_CLOSE,          /**< The window manager requests that the window be closed */
			WE_TAKE_FOCUS,     /**< Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore) */
			WE_HIT_TEST,       /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
			WE_ICCPROF_CHANGED,/**< The ICC profile of the window's display has changed. */
			WE_DISPLAY_CHANGED /**< Window has been moved to display data1. */
		};
		
		uint32_t	type;						/**< Overall event type. Nothing right now */
		uint32_t	timestamp;					/**< In milliseconds, not populated at all! */
		uint32_t	windowID;					/**< The associated window */
		Type event;
		uint8_t		padding1;					//TODO: Check the padding on this
		uint8_t		padding2;
		uint8_t		padding3;
		int32_t		data1;						/**< event dependent data */
		int32_t		data2;						/**< event dependent data */
	};
}
