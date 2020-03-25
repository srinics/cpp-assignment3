/*
* Author: M1043833 ( Srinivasan Rajendran )
* Description: This file (Main.c) contains main function for Creating Single Instance Application using mutex*
* */

#include <iostream>
#include <csignal>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
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
/*
Author: M1043833
Function Name: WindowsSingleInstanceApp()
Description:
Function to create single instance.
This function will use/invoke in Windows enviroment.
*/
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

/*
Author: M1043833
Function Name: SignalHandler(int SigNum)
Description:
This is the callback function SIGINT signal.
This function will use/invoke in Windows & Linux enviroment.
*/
void SignalHandler(int signum) {
	std::cout << "Interrupt signal (" << signum << ") received.\n";
	
#ifdef _WIN32
	ReleaseMutex(hMutexHandle);
	CloseHandle(hMutexHandle);
#endif
	exit(signum);
}


/*
Author: M1043833
Function Name: int main(int argc, char *argv[])
Description:
This is main execution function.
*/
int main(int argc, char *argv[])
{
	signal(SIGINT, SignalHandler);

#ifdef _WIN32
	auto r = WindowsSingleInstanceApp();
	if (!r){
		std::cout << "Application start failed" << std::endl;
		return 0;
	}
#endif


	return 0;
}
