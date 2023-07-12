#include "../../../AGL/include/crossfunctions.hpp"

int main()
{
	agl::BaseWindow window;

	agl::createWindow(window, {100, 100}, {200, 100}, "test");
	agl::initGL(window);
	agl::mapWindow(window);

	MSG msg;

	auto getAllMessages = [&]()
	{
		while (GetQueueStatus(QS_ALLINPUT) != 0)
		{
			PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE);
			// TranslateMessage(&msg);
			// DispatchMessage(&msg); // calls wndProc

			switch (msg.message)
			{
			// case WM_PAINT:
			// 	PAINTSTRUCT ps;
			// 	draw();
			// 	BeginPaint(window.hndl, &ps);
			// 	EndPaint(window.hndl, &ps);
			// 	break;
			// case WM_SIZE:
			// 	glViewport(0, 0, LOWORD(msg.lParam), HIWORD(msg.lParam));
			// 	break;
			// case WM_KEYDOWN:
			// 	/* ESC */
			// 	if (msg.wParam == 27)
			// 		PostMessage(window.hndl, WM_CLOSE, 0, 0);
			// 	/* F11 */
			// 	else if (msg.wParam == 122)
			// 		setFullscreen(window.fullscreen = !window.fullscreen);
			// 	break;
			case WM_CLOSE:
				wglMakeCurrent(window.deviceContext, NULL);
				wglDeleteContext(window.renderContext);
				ReleaseDC(window.hndl, window.deviceContext);
				DestroyWindow(window.hndl);
				/* stop event queue thread */
				PostQuitMessage(0);
				break;
			default:
				DefWindowProc(window.hndl, msg.message, msg.wParam, msg.lParam);
			}
		}
	};

	while (true)
	{
		printf("rfaw\n");
		getAllMessages();
		// UpdateWindow(window.hndl);
		PAINTSTRUCT ps;
		BeginPaint(window.hndl, &ps);
		// draw();
		EndPaint(window.hndl, &ps);
	}
}