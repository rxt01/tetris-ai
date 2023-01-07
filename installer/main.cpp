#include <iostream>
#include <fstream>
#include <json.h>
#include <json-forwards.h>
#include <direct.h>
#include <string>
#include <stdio.h>



#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "urlmon.lib")

#else
#include <unistd.h>

#endif 


using namespace std;

LPCWSTR ConvertString(string original) {
	std::wstring stemp = std::wstring(original.begin(), original.end());
	LPCWSTR sw = stemp.c_str();
	return sw;
}



int	LoadFiles(string version){
	#ifdef _WIN32 
	if (_mkdir("assets") == -1){
		if (errno != 17){
			cerr << "Error: " << strerror(errno) << endl;
			cout << errno << endl;
			return -1;
		}
		
	}
	if (_mkdir("assets/characters") == -1) {
		if (errno != 17) {
			cerr << "Error: " << strerror(errno) << endl;
			return -1;
		}
	}
	if (_mkdir("assets/sounds") == -1) {
		if (errno != 17) {
			cerr << "Error: " << strerror(errno) << endl;
			return -1;
		}
	}
	if (_mkdir("assets/sprites") == -1) {
		if (errno != 17) {
			cerr << "Error: " << strerror(errno) << endl;
			return -1;
		}
	}
	


	#elif __linux__


	#elif __APPLE__


	#endif
}
enum class Current {
	trash=0,
	X=1,
	Y=2,
	Z=3
 };
int last = 0;
string retreiveVersionNumber(string input) {
	string result;
	Current version = Current::trash;
	bool continu = true;
	for (int i = 0; i < input.length(); i++){
		if (continu){
			if (isdigit(input[i])){
				result.append(string(1, input[i]));
				if (version == Current::trash){
					version = Current::X;
				}
			}else if (input[i]=='.'){
				switch (version) {
				case Current::X:
					result.append(".");
					version = Current::Y;
					break;
				case Current::Y:
					result.append(".");
					version = Current::Z;
					break;
				default:
					break;
				}
			}else{
				switch (version)
				{
				case Current::trash:
					break;
				case Current::X:
					return "invalid";
					break;
				case Current::Y:
					continu = false;
					break;
				case Current::Z:
					continu = false;
					break;
				default:
					break;
				}
			}
		}
	}
	last = (int)version;
	return result;
}


string getValidVersion(string input) {
	string result = retreiveVersionNumber(input);

	if (input.c_str() == "release-latest") {
		//get the latest release
	}else if (input.c_str() == "beta-latest") {
		//get the latest version
	}else if (result.c_str() == "invalid") {
		return "invalid";
	}else if (last == 2){
		return string("release-V").append(result);
	}else if (last == 3) {
		return string("beta-V").append(result);
	}
}



int main() {
	string inputVersion;
	string version;
	do{
		cout << "version: " << endl;
	
		cin >> inputVersion;
		version = getValidVersion(inputVersion);
		if (version.c_str() == "invalid") {
			cout << "invalid version, valid versions go as follow:" << endl << "(\"release - \" or \"V\") folowed by the version number(x.y), to get a certain release version" << endl << "(\"beta - \" or \"B\") folowed by the version number(x.y.z), to get a certain beta version" << endl << "the version number(x.y for release, x.y.z for beta) to get that version" << endl << "\"release - latest\" for the latest release version" << endl << "\"beta - latest\" for the latest version " << endl;
		}
	} while (version.c_str()=="invalid");
	

	if (LoadFiles(version) == -1){
		cin.get();
		return -1;
	}
	


}


















