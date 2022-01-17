add_subdirectory(Graphics)
add_subdirectory(core)
add_subdirectory(Physics)

set(SHADERS
    src/Shaders/common.sh
	src/Shaders/shaderlib.sh
	src/Shaders/util.sh
	src/Shaders/lights.sh
	src/Shaders/pbr.sh
    src/Shaders/varying.def.sc
	src/Shaders/imgui/varying.def.sc
    src/Shaders/vs_shader.sc
	src/Shaders/fs_shader.sc
    src/Shaders/vs_pbrshader.sc
	src/Shaders/fs_pbrshader.sc
	src/Shaders/cs_MS_albedoLUT.sc
	src/Shaders/tonemap/fs_tonemap.sc
	src/Shaders/tonemap/vs_tonemap.sc
	src/Shaders/tonemap/cs_avglum.sc
	src/Shaders/tonemap/cs_histogram.sc
	src/Shaders/imgui/vs_ocornut_imgui.sc
    src/Shaders/imgui/fs_ocornut_imgui.sc
    
	PARENT_SCOPE
)

# Add source files.
set(SOURCES
		src/Components/DrawableEntity.cpp
		src/Components/ConcaveCollider.cpp
		src/Components/SphereCollider.cpp
		src/Components/BoxCollider.cpp
		src/Components/RayCaster.cpp
		src/Components/AutomatedBehaviours.cpp
		src/Components/InputComponent.cpp

		src/Engine/Yokai.cpp
		src/Engine/JSONHelper.cpp
		src/Engine/LightManager.cpp
		src/Engine/Scene.cpp
        PARENT_SCOPE
        )

