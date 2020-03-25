#include <stdio.h> 
#include <dirent.h> 
#include <algorithm> 
#include <string>

bool is_number(const std::string& s)
{
	    return !s.empty() && std::find_if(s.begin(), 
			            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
  
int main(void) 
{ 
    struct dirent *de;  // Pointer for directory entry 
  
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir("/proc/"); 
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
        return 0; 
    } 
  
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
    // for readdir() 
    while ((de = readdir(dr)) != NULL) {
		if(de->d_type == DT_DIR && is_number(std::string(de->d_name)))
            		printf("%s\n", de->d_name); 
    }
  
    closedir(dr);     
    return 0; 
} 
