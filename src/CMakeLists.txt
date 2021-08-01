# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
        main.cpp

		Model/ObjectLoading/ModelLoader.cpp
		Model/Mesh.cpp
        Model/Model.cpp
        Model/Chunk.cpp
		Model/GameObjects/GameObject.cpp
        Model/Components/PlayerControlledMotion.cpp
		Model/GameObjects/Player.cpp
		Model/GameObjects/StaticObject.cpp
		Model/GameObjects/NPC.cpp
		Model/SplashScreen.cpp
		Model/Components/PhysicsComponent.cpp
        Model/SkeletalAnimation.cpp
		Model/Components/AutomatedBehaviours.cpp
		Model/Components/Weapon.cpp
		Model/Components/Transform.cpp
		Model/Components/RayCaster.cpp


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
        Controller/TerrainManager.cpp
		Controller/Factory/TerrainFactory.cpp
		Controller/LuaManager.cpp
		Controller/EventManager.cpp
		Controller/InputManagerGLFW.cpp
        Controller/Physics/Shapes/ReactTerrainShape.cpp
        Controller/Physics/CollisionEventHandler.cpp
        Controller/Physics/PhysicsSystem.cpp
		Controller/Physics/ReactMath.cpp
		Controller/Physics/RigidBody.cpp
		Controller/Animator.cpp
        Controller/Physics/Shapes/ReactBoxShape.cpp
        Controller/Physics/Shapes/ReactShape.cpp
        Controller/Physics/Shapes/ReactSphereShape.cpp
        Controller/Factory/GameAssetFactory.cpp
		Controller/DemoScene.cpp
        Controller/GameObjectManager.cpp
		Controller/LuaTypes.cpp
		Controller/TextureManager.cpp
		Controller/KeyframeAnimation.cpp
		Controller/MainMenuScene.cpp
		Controller/UIManager.cpp
        )

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
