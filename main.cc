#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "utils.h"

using namespace std;

int main(int argc, char* argv[]){
	string fileToRead;/* the name of file to read */
	if(argc < 2){
		cout<< "ERROR: expecting a file name" << endl;
		exit(1);/* no input provided, error */
	}else{
		stringstream ss(argv [1]);/* take in the file name from ocmmand line args */
		fileToRead = ss.str();
	}	

	ifstream file{fileToRead};
	string line; /*a single line we read */
	int totalLines = 0; /* total Lines of code */
	int lastBlockStart = 0; /* the last line where a block comment start */
	int totalTodos = 0;
	int totalBlocks = 0;
	int totalComments = 0;
	int singleComments = 0;/*single comments means comments that are not trailing */
	int blockComments = 0;
	/*get the extension of the file we are checking */
	string extension = getExtension(fileToRead);
	/*syntaxCode determines which comment syntax to follow based on file surfix */
	int syntaxCode;
	string commentMark;
	string blockStartMark;
	string blockEndMark;
	string todo = "TODO";
	vector<int> comments;
	setMarkers(extension, syntaxCode, blockStartMark, blockEndMark, commentMark);
	/*a syntax code 0 means there is no separate syntax for single/block comments */
	/*a syntax code 1 means there are separate formats for single/block comments*/
	/* in this loop we parse the file line by line*/
	while(getline(file,line)){
		//cout << line << endl;
		totalLines ++;
		if(isEmpty(line))continue;
		if(syntaxCode == 0){
			if(!tooShort(line, commentMark)){
				if(findMarker(line, commentMark)){
					totalComments ++;
					if(separateComment(line, commentMark)){
						comments.emplace_back(totalLines);
					}
					if(!tooShort(line, todo)){
						if(findMarker(line,todo)){
							totalTodos ++;
						}
					}
				}
			}
		}else{/* syntaxCode == 1 */
			if(!tooShort(line, blockStartMark)){
				if(findMarker(line,blockStartMark)){
					totalBlocks ++;
					lastBlockStart = totalLines;
				}
			}
			if(!tooShort(line,blockEndMark)){
				if(findMarker(line,blockEndMark)){
					int blockLines = totalLines - lastBlockStart + 1;
					totalComments += blockLines;
					blockComments += blockLines;
				}
			}

			if(!tooShort(line, commentMark)){
				if(findMarker(line, commentMark)){
					totalComments += 1;
					singleComments += 1;
				}
			}

		}
	}

	if(syntaxCode == 0){// we get to deal with vector<int> comments
		int size = comments.size();
		int acc = 1;
		for (int i = 0; i < size -1; i ++){
			if(comments.at(i+1)-comments.at(i)==1){
				acc ++;
			}else{
				if(acc > 1){
					/*we have more than one line of non-trailing comments which counts as a block*/
					totalBlocks ++;
					blockComments += acc;
					acc = 1;
				}
			}
		}
		if(acc > 1){
			totalBlocks ++;
			blockComments += acc;
		}

		singleComments = totalComments - blockComments;
	}

	cout << "Total # of lines: " << totalLines  << endl;
	cout << "Total # of comment lines: " << totalComments << endl;
	cout << "Total # of single line comments: "  <<singleComments << endl;
	cout << "Total # of comment lines within block comments: " << blockComments << endl;
	cout << "Total # of block line comments: " << totalBlocks << endl;
	cout << "Total # of TODO's: " <<totalTodos << endl;
}
