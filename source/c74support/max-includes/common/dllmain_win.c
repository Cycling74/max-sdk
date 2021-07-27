#ifdef WIN_VERSION

#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved )
{
	// Perform actions based on the reason for calling.
	switch( fdwReason )
	{
		case DLL_PROCESS_ATTACH:
		 // Initialize once for each new process.  Return FALSE to fail DLL load.
			// Since we do nothing in our DLL_THREAD_ATTACH and DLL_THREAD_DETACH calls below,
			// we don't need to actually receive those calls. The below call tells the OS to
			// optimize those out.
			DisableThreadLibraryCalls(hinstDLL);
#if defined(_DEBUG) && defined(PRINT_DLL_PROCESS_ATTACH_MESSAGES)
			{
				char buff[_MAX_PATH];
				OutputDebugStringA("DLL_PROCESS_ATTACH: ");
				GetModuleFileNameA(hinstDLL, buff, _MAX_PATH);
				OutputDebugStringA(buff);
				OutputDebugStringA("\n");
			}
#endif
			break;
		case DLL_THREAD_ATTACH:
			// Do thread-specific initialization.
			break;
		case DLL_THREAD_DETACH:
			// Do thread-specific cleanup.
			break;
		case DLL_PROCESS_DETACH:
			// Perform any necessary cleanup.
			break;
	}
	return TRUE;
}

#endif // #ifdef WIN_VERSION
