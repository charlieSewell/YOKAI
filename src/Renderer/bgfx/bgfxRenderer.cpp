#include "bgfxRenderer.hpp"

void bgfxRenderer::Init()
{
    bgfx::PlatformData platformData;
	memset( &platformData, 0, sizeof( platformData ) );
    #if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        platformData.nwh = ( void* )( uintptr_t )glfwGetX11Window( m_window );
        platformData.ndt = glfwGetX11Display();
    #elif BX_PLATFORM_OSX
        platformData.nwh = glfwGetCocoaWindow( m_window );
    #elif BX_PLATFORM_WINDOWS
        platformData.nwh = glfwGetWin32Window( m_window );
    #endif // BX_PLATFORM_
	bgfx::setPlatformData( platformData );

	// Init bgfx
	bgfx::Init init;
	init.type = bgfx::RendererType::Count;
	init.vendorId = BGFX_PCI_ID_NONE;
	init.deviceId = 0;
	init.callback = NULL;
	init.allocator = NULL;
	bgfx::init( init );

	// Setup ImGui
	imguiInit(m_window);


}
void bgfxRenderer::DrawScene(float dt)
{
	imguiEvents( dt );
	ImGui::NewFrame();
	//RENDER CODE HERE
	ImGui::Render();
	imguiRender( ImGui::GetDrawData() );
	bgfx::frame();
}