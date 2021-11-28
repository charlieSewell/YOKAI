set(SHADERS
        src/Shaders/varying.def.sc
        src/Shaders/vs_ocornut_imgui.sc
        src/Shaders/fs_ocornut_imgui.sc
        PARENT_SCOPE
)


# Add source files.
set(SOURCES
		src/Model/ObjectLoading/ModelLoader.cpp
		src/Model/Mesh.cpp
        src/Model/Model.cpp
        src/Model/SkeletalAnimation.cpp
		src/Model/Animator.cpp
		src/Model/Animator.cpp

		src/Components/Transform.cpp
		src/Components/DrawableEntity.cpp
		src/Components/ConcaveCollider.cpp
		src/Components/SphereCollider.cpp
		src/Components/BoxCollider.cpp
		src/Components/Camera.cpp
		src/Components/RayCaster.cpp
		src/Components/AutomatedBehaviours.cpp
		src/Components/InputComponent.cpp

        src/Renderer/Shader.cpp
        src/Renderer/DataTypes.cpp
        src/Renderer/Renderer.cpp
        src/Renderer/RenderAPI.cpp
        src/Renderer/Window.cpp
        src/Renderer/OpenGL/OpenGLRenderer.cpp
        src/Renderer/OpenGL/OpenGLDataTypes.cpp
        src/Renderer/OpenGL/FileIO.cpp
		src/Renderer/LightManager.cpp
		src/Renderer/bgfx/bgfxutil.cpp
		src/Renderer/bgfx/bgfxDataTypes.cpp
		src/Renderer/bgfx/bgfxShader.cpp

		src/Engine/GameObject.cpp
		src/Engine/Yokai.cpp
		src/Engine/ModelManager.cpp
		src/Engine/EventManager.cpp
		src/Engine/InputManagerGLFW.cpp
		src/Engine/GameObjectManager.cpp
		src/Engine/TextureManager.cpp
		src/Engine/JSONHelper.cpp
		src/Engine/JSONTypes.cpp
		src/Engine/Scene.cpp

        src/Physics/Shapes/ReactTerrainShape.cpp
        src/Physics/PhysicsSystem.cpp
        src/Physics/ReactMath.cpp
        src/Physics/CollisionBody.cpp
		src/Physics/RigidBody.cpp
        src/Physics/Shapes/ReactBoxShape.cpp
        src/Physics/Shapes/ReactShape.cpp
        src/Physics/Shapes/ReactSphereShape.cpp
        src/Physics/Shapes/ReactTerrainShape.cpp
        src/Physics/Shapes/ReactConcaveShape.cpp
		src/Physics/ResolutionFunctions.cpp
		src/Physics/PhysicsResolution.cpp
        PARENT_SCOPE
        )

