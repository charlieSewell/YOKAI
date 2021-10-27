# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
		Model/ObjectLoading/ModelLoader.cpp
		Model/Mesh.cpp
        Model/Model.cpp
		Model/SplashScreen.cpp
        Model/SkeletalAnimation.cpp
		Model/Animator.cpp
		Model/Animator.cpp
		Model/KeyframeAnimation.cpp

		Components/Transform.cpp
		Components/DrawableEntity.cpp
		Components/ConcaveCollider.cpp
		Components/SphereCollider.cpp
		Components/BoxCollider.cpp
		Components/Camera.cpp
		Components/RayCaster.cpp
		Components/AutomatedBehaviours.cpp
		Components/InputComponent.cpp

        Renderer/Shader.cpp
        Renderer/DataTypes.cpp
        Renderer/Renderer.cpp
        Renderer/RenderAPI.cpp
        Renderer/Window.cpp
        Renderer/OpenGL/OpenGLRenderer.cpp
        Renderer/OpenGL/OpenGLDataTypes.cpp
        Renderer/OpenGL/FileIO.cpp
		Renderer/LightManager.cpp

		Engine/GameObject.cpp
		Engine/Yokai.cpp
		Engine/ModelManager.cpp
		Engine/EventManager.cpp
		Engine/InputManagerGLFW.cpp
		Engine/GameObjectManager.cpp
		Engine/TextureManager.cpp
		Engine/JSONHelper.cpp
		Engine/JSONTypes.cpp
		Engine/Scene.cpp

        Physics/Shapes/ReactTerrainShape.cpp
        Physics/PhysicsSystem.cpp
        Physics/ReactMath.cpp
        Physics/CollisionBody.cpp
		Physics/RigidBody.cpp
        Physics/Shapes/ReactBoxShape.cpp
        Physics/Shapes/ReactShape.cpp
        Physics/Shapes/ReactSphereShape.cpp
        Physics/Shapes/ReactTerrainShape.cpp
        Physics/Shapes/ReactConcaveShape.cpp
		Physics/ResolutionFunctions.cpp
		Physics/PhysicsResolution.cpp
        )

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
