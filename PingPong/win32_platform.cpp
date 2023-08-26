#include <Windows.h>
//windows platform layer
bool running = true;
void* buffer_memory;
int buffer_height;

//pointer to an application-defined function
LRESULT CALLBACK Wndproc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam) {
	LRESULT result = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;

		} break;

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			int buffer_width = rect.right - rect.left;
			int buffer_height = rect.bottom - rect.top;

			int buffer_size = buffer_width * buffer_height * sizeof(unsigned int);
			if (buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE);
			buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		}break;

		default: {
			result = DefWindowProc(hwnd, uMsg, wparam, lparam);
		}

	}
	return result;
}

//user-provided entry point for a graphical Windows-based application
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	//Create Window Class
	WNDCLASS window_class = {};
	//can change window size horizontally and vertically
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	//callback function
	window_class.lpfnWndProc = Wndproc;

	//Register Class
	RegisterClass(&window_class);
	LPCWSTR a = L"My First Game!";


	//Call Create Window
	HWND window = CreateWindow(window_class.lpszClassName, a, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);

	while (running) {
		//input
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		//simulate

		//render
	}
}
