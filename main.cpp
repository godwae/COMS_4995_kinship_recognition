#include <sys/stat.h>
#include <iostream>
#include <direct.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <io.h>

void gay_finder(std::string path, std::vector<std::string> &files, std::string ext) {
	intptr_t hFile = 0;
	_finddata_t fileinfo;
	if (-1 != (hFile = _findfirst(path.append("/" + ext)/* get an extension name */.c_str(), &fileinfo))) {
		int flag;
		if ("*" == ext) flag = 0; // option is folder
		else flag = 1; // option is file
		while(0 == _findnext(hFile, &fileinfo)) {
			switch(flag) {
				case 0:
					if(strcmp(fileinfo.name, ".") && strcmp(fileinfo.name, "..")) /* excluding . and .. path */ {
						if(fileinfo.attrib & _A_SUBDIR) files.push_back(fileinfo.name);
					}
					break;
				case 1:
					if(strcmp(fileinfo.name, ".") && strcmp(fileinfo.name, "..")) /* excluding . and .. path */ {
						files.push_back(fileinfo.name);
					}
					break;
			}
		}
	}
	_findclose(hFile);
}

int main (void) {
	system("cls");
	std::string path = "../sample";
	std::vector<std::string> folder_list;
	gay_finder(path, folder_list, "*");
	for (int i = 0; i < folder_list.size(); ++i) /* level 1 */ {
		std::cout << folder_list[i] + ": " << std::endl;
		std::vector<std::string> img_list;
		gay_finder(path + "/" + folder_list[i], img_list, "*.jpg");
		for (int j = 0; j < img_list.size(); ++j) /* level 2 */ {
			std::cout << img_list[j] << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}
