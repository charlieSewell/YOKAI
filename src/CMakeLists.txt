# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
		Model/ObjectLoading/ModelLoader.cpp
		Model/Mesh.cpp
        Model/Model.cpp
        Model/GameObject.cpp
		Model/SplashScreen.cpp
        Model/SkeletalAnimation.cpp
		Model/Components/Transform.cpp
        Model/Components/DrawableEntity.cpp
		Model/Components/PlayerControlledMotion.cpp
        Model/Components/ConcaveCollider.cpp
		Model/Components/SphereCollider.cpp


        View/Renderer/Shader.cpp
        View/Renderer/DataTypes.cpp
        View/Renderer/Renderer.cpp
        View/Renderer/RenderAPI.cpp
        View/Renderer/OpenGL/OpenGLRenderer.cpp
        View/Renderer/OpenGL/OpenGLDataTypes.cpp
		Model/Components/Camera.cpp
        View/Renderer/OpenGL/FileIO.cpp
		View/Window.cpp

		Controller/Yokai.cpp
        Controller/ModelManager.cpp
		Controller/EventManager.cpp
		Controller/InputManagerGLFW.cpp
        Controller/Physics/PhysicsSystem.cpp
		Controller/Physics/ReactMath.cpp
		Controller/Physics/RigidBody.cpp
		Controller/Animator.cpp
        Controller/Physics/Shapes/ReactBoxShape.cpp
        Controller/Physics/Shapes/ReactShape.cpp
        Controller/Physics/Shapes/ReactSphereShape.cpp
        Controller/Physics/Shapes/ReactTerrainShape.cpp
        Controller/Physics/Shapes/ReactConcaveShape.cpp
        Controller/GameObjectManager.cpp
		Controller/TextureManager.cpp
		Controller/KeyframeAnimation.cpp
		Controller/UIManager.cpp
        )

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
