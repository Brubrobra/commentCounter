#include <string>

using namespace std;

//check if it's an emptyline
bool isEmpty(string line);
//check if the line is too short to contain marker
bool tooShort(string line, string marker);
//check if the line contains a marker
bool findMarker(string line, string marker);
//check if the line contains a sepearte (non-trailing) comment
bool separateComment(string line, string marker);
// given a file, determine its extension
string getExtension(string fileName);
//given a file extension, determine the syntax rules for comments
void setMarkers(string extension,int &code, string &startMark, string &endMark, string &commentMark);
