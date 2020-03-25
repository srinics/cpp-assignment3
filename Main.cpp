#include <iostream>
#include <pthread.h>
#include <csignal>

#ifdef _WIN32
#include <windows.h>
#endif


void RunEndless(){
	std::cout << "Application waiting for Signal" << std::endl;
	while (1){
#ifdef _WIN32
		Sleep(30000);
#else
		sleep(300);
#endif
	}
}


#ifdef _WIN32
HANDLE hMutexHandle;

bool WindowsSingleInstanceApp(){
	// ensure only one running instance
	hMutexHandle = CreateMutex(NULL, TRUE, "my.mutex.name");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		std::cout << "Application already exists" << std::endl;
		return false;
	}

	std::cout << "Application started" << std::endl;
	// rest of the program

	RunEndless();
	return true;
}
#endif


void signalHandler(int signum) {
	std::cout << "Interrupt signal (" << signum << ") received.\n";

	// cleanup and close up stuff here  
	// terminate program  

#ifdef _WIN32
	ReleaseMutex(hMutexHandle);
	CloseHandle(hMutexHandle);
#endif
	exit(signum);
}
int main(int argc, char *argv[])
{
	signal(SIGINT, signalHandler);

#ifdef _WIN32
	auto r = WindowsSingleInstanceApp();
	if (!r){
		std::cout << "Application start failed" << std::endl;
		return 0;
	}
#endif


	return 0;
}
