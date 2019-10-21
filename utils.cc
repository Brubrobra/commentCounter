#include <string>
#include "utils.h"

using namespace std;

bool isEmpty(string line){
	if (line.length()== 0)return true;
	return false;
}

bool tooShort(string line, string marker){
	if (line.length() < marker.length()){
		return true;
	}else{
		return false;
	}
}

bool findMarker(string line, string marker){
	int markerLen = marker.length();
	int lineLen = line.length();
	int doubleQuotesBeforeMarker = 0;
	int doubleQuotesAfterMarker = 0;
	int singleQuotesBeforeMarker = 0;
	int singleQuotesAfterMarker= 0;

	for(int i = 0; i <= lineLen - markerLen; i ++){
		if(line.substr(i, markerLen)== marker){/* then we want to check it is not in a string literal */
			//check things before the marker
			for(int j = 0; j < i ; j ++){
				if(line.substr(j,1)=="\"" &&(j==0 || line.substr(j-1,1)!="\\")){
					doubleQuotesBeforeMarker ++;
				}else if(line.substr(j,1)=="\'" &&(j==0 || line.substr(j-1,1)!="\\")){
					singleQuotesBeforeMarker ++;
				}
			
			}
			//check things after the marker
			for(int k = i+markerLen; k < lineLen; k ++){
				if(line.substr(k,1)=="\""&&(k==i+markerLen || line.substr(k-1,1)!="\\")){
					doubleQuotesAfterMarker ++;
				}else if(line.substr(k,1)=="\'" && (k ==i+markerLen || line.substr(k-1,1)!="\\")){
					singleQuotesAfterMarker ++;
				}
			}
			if((singleQuotesBeforeMarker ==0 || doubleQuotesAfterMarker == 0)&&
					(doubleQuotesBeforeMarker ==0 || doubleQuotesAfterMarker ==0)){
				return true;
			}
			if((singleQuotesBeforeMarker%2==0 || singleQuotesAfterMarker%2==0)&&
			(doubleQuotesBeforeMarker%2==0 || doubleQuotesAfterMarker%2 ==0)){
				return true;
			}else{
				doubleQuotesAfterMarker = 0;
				doubleQuotesBeforeMarker = 0;
				singleQuotesBeforeMarker = 0;
				singleQuotesAfterMarker = 0;
			}

			
		}
	}
	return false;
}

bool separateComment(string line, string marker){
	int markerLen = marker.length();
	if(line.substr(0,markerLen)== marker)return true;
	return false;
}

string getExtension(string fileName){
	string extension;
	int size = fileName.length();
	if(fileName.substr(0,1)=="."){
		exit(0);
	}else{
		for(int i = size -1; i > 0; i --){
			if(fileName.substr(i,1)=="."){
				int length = size - i;
				return fileName.substr(i,length);
			}
		}
	}
	exit(0);
}

void setMarkers(string extension, int &code, string &startMark, string &endMark, string &commentMark){
	if(extension == ".c" || extension == ".cc" || extension == ".cpp" || extension == ".cxx" ||
			extension == ".java" || extension == ".jav" || extension == ".j" || extension == "scala"
			||extension == ".sc" || extension == ".as" || extension == ".h"){
		code = 1;
		startMark = "/*";
		endMark = "*/";
		commentMark = "//";
	}else{
		code = 0;
		commentMark = "#";
	}
}
