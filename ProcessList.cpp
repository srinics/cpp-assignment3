/*
* Author: M1043833 ( Srinivasan Rajendran )
* Description: This file (ProcessList.c) contains functions to display and count process running in the host. 
* It has the function for windows and linux.
*
* */
#include <iostream>
#include <stdio.h>
#include <tchar.h>


using namespace std;


#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else 
#include <stdio.h> 
#include <dirent.h> 
#include <algorithm> 
#include <string>
#endif

#ifdef __WIN32

/*
Author: M1043833
Function Name: PrintProcessNameAndID(DWORD)
Description:
Function to display to Process Name and Id and it will processID (DWORD) as the argument.
This function uses windows api.
Note: To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS and compile with -DPSAPI_VERSION=1
*/
void PrintProcessNameAndID(DWORD processID)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	// Get a handle to the process.

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	// Get the process name.

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
		}
	}

	// Print the process name and identifier.

	//_tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);
	std::cout << "Process name: " << szProcessName << ", PID: " << processID << std::endl;
	// Release the handle to the process.

	CloseHandle(hProcess);
}
/*
Author: M1043833
Function Name: GetWindowsProcessCount()
Description:
Function will return count of Process running in the host.
This function uses windows api.
Note: To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS and compile with -DPSAPI_VERSION=1
*/
int GetWindowsProcessCount()
{
	// Get the list of process identifiers.

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}


	// Calculate how many process identifiers were returned.

	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.

	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			PrintProcessNameAndID(aProcesses[i]);
		}
	}

	return i;
}
#else
bool is_number(const std::string& s)
{
	    return !s.empty() && std::find_if(s.begin(), 
			            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
/*
Author: M1043833
Function Name: GetLinuxProcessCount()
Description:
Function will return count of Process running in the host.
This function uses Linux enviroment.
*/
int GetLinuxProcessCount() 
{ 
    struct dirent *de;  // Pointer for directory entry 
  
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir("/proc/"); 
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        std::cout << "Could not open current directory" << std::endl; 
        return 0; 
    } 

    int proc_cnt=0;
  
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
    // for readdir() 
    while ((de = readdir(dr)) != NULL) {
		if(de->d_type == DT_DIR && is_number(std::string(de->d_name))){
            		//printf("%s\n", de->d_name); 
			//std::cout << "Could not open current directory" << std::endl;
			proc_cnt++;
		}
    }
    std::cout << "Total proc count:" << proc_cnt << std::endl; 
    closedir(dr);     
    return proc_cnt; 
} 

#endif

int main(int argc, char **argv){
int c=0;
#ifdef _WIN32
	c = GetWindowsProcessCount();
#else
	c = GetLinuxProcessCount();
#endif
	std::cout << "\n\n\n\n";
	std::cout << "Total Process count: " << c << std::endl;
}

/*
* Author: M1043833 ( Srinivasan Rajendran )
* Description: This file (Source.h) contains functions to display and count process running in the host.
* It has the function for windows and linux.
*
* */
#include <iostream>
#include <stdio.h>
#include <tchar.h>


using namespace std;


#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else 
#include <stdio.h> 
#include <dirent.h> 
#include <algorithm> 
#include <string>
#endif

#ifdef _WIN32

/*
Author: M1043833
Function Name: PrintProcessNameAndID(DWORD)
Description:
Function to display to Process Name and Id and it will processID (DWORD) as the argument.
This function uses windows api.
Note: To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS and compile with -DPSAPI_VERSION=1
*/
void PrintProcessNameAndID(DWORD processID)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	// Get a handle to the process.

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	// Get the process name.

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
		}
	}

	// Print the process name and identifier.

	//_tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);
	std::cout << "Process name: " << szProcessName << ", PID: " << processID << std::endl;
	// Release the handle to the process.

	CloseHandle(hProcess);
}
/*
Author: M1043833
Function Name: GetWindowsProcessCount()
Description:
Function will return count of Process running in the host.
This function uses windows api.
Note: To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS and compile with -DPSAPI_VERSION=1
*/
int GetWindowsProcessCount()
{
	// Get the list of process identifiers.

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}


	// Calculate how many process identifiers were returned.

	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.

	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			PrintProcessNameAndID(aProcesses[i]);
		}
	}

	return i;
}
#else
bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
/*
Author: M1043833
Function Name: GetLinuxProcessCount()
Description:
Function will return count of Process running in the host.
This function uses Linux enviroment.
*/
int GetLinuxProcessCount()
{
	struct dirent *de;  // Pointer for directory entry 

	// opendir() returns a pointer of DIR type.  
	DIR *dr = opendir("/proc/");

	if (dr == NULL)  // opendir returns NULL if couldn't open directory 
	{
		std::cout << "Could not open current directory" << std::endl;
		return 0;
	}

	int proc_cnt = 0;

	// Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
	// for readdir() 
	while ((de = readdir(dr)) != NULL) {
		if (de->d_type == DT_DIR && is_number(std::string(de->d_name))){
			//printf("%s\n", de->d_name); 
			//std::cout << "Could not open current directory" << std::endl;
			proc_cnt++;
		}
	}
	std::cout << "Total proc count:" << proc_cnt << std::endl;
	closedir(dr);
	return proc_cnt;
}

#endif

int main(int argc, char **argv){
	int c = 0;
#ifdef _WIN32
	c = GetWindowsProcessCount();
#else
	c = GetLinuxProcessCount();
#endif
	std::cout << "\n\n\n\n";
	std::cout << "Total Process count: " << c << std::endl;
}



