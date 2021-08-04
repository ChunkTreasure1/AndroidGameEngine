cmake_minimum_required(VERSION 3.6)

project(MY_APP)

find_library(SDL2 SDL2)
find_library(log-lib log)
find_library(android-lib android)

add_library(main SHARED)
add_subdirectory(vendor)

target_sources(main PRIVATE             
	    	Application/main.cpp
            Application/Application.cpp
            Application/Application.h
            Application/Window.cpp
            Application/Window.h
			Application/Timestep.h
            Application/Events/Event.h
			Application/Events/ApplicationEvent.h
			Application/Events/KeyEvent.h
			Application/Events/MouseEvent.h
			Application/Layers/Layer.cpp
			Application/Layers/Layer.h
			Application/Layers/ApplicationLayer.cpp
			Application/Layers/ApplicationLayer.h
			Application/Layers/ImGuiLayer.h
			Application/Layers/ImGuiLayer.cpp
			Application/Layers/ApplicationLayer/ImGuiRenderer.cpp
            Application/Layers/ApplicationLayer/VisualScriptingEditor.cpp
            Application/Layers/ApplicationLayer/VisualScriptingEditor.h
            Application/ImGui/ImGuiBuild.cpp
			Application/Input/Input.cpp
			Application/Input/Input.h
			Application/Filesystem/Filesystem.cpp
			Application/Filesystem/Filesystem.h
			Application/Settings/Language.cpp
			Application/Settings/Language.h
			Application/Settings/Settings.h
			Application/Settings/Settings.cpp
			Core.h
			stb_image.h
            Rendering/Renderer.cpp
            Rendering/Renderer.h
			Rendering/Framebuffer.cpp
			Rendering/Framebuffer.h
            Rendering/Buffers/VertexBuffer.cpp
            Rendering/Buffers/VertexBuffer.h
            Rendering/Buffers/VertexArray.cpp
            Rendering/Buffers/VertexArray.h
			Rendering/Buffers/BufferLayout.h
			Rendering/Shaders/Shader.h
			Rendering/Shaders/Shader.cpp
			Rendering/Camera/OrthographicCamera.cpp
			Rendering/Camera/OrthographicCamera.h
			Rendering/Camera/OrthographicCameraController.cpp
			Rendering/Camera/OrthographicCameraController.h
			Rendering/Texture2D/Texture2D.cpp
			Rendering/Texture2D/Texture2D.h
			Rendering/Texture2D/TextureCache.cpp
			Rendering/Texture2D/TextureCache.h
			Rendering/Texture2D/TextureLoader.cpp
			Rendering/Texture2D/TextureLoader.h
			Objects/Object.cpp
			Objects/Object.h
			VisualScripting/Node.cpp
			VisualScripting/Node.h
			VisualScripting/CodeGraph.cpp
			VisualScripting/CodeGraph.h
            VisualScripting/Link.h
)

target_include_directories(main PUBLIC
		./
		/vendor/)

target_link_libraries(main
		SDL2
		${log-lib}
		${android-lib}
		EGL
		GLESv3
		glm
		IMGUI
		IMNODES)


