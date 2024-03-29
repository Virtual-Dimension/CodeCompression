#include <iostream>
#include <fstream>
using namespace std;
string path;
string getString() {
	char ch = getchar();
	while(ch == '\r' || ch == '\n') ch = getchar();
	string res;
	while(ch != '\r' && ch != '\n') res+= ch, ch = getchar();
	return res;
}
#define PART1
string readPause(const string & str, int &p) {
	int np = p;
	while(str.size() > p && (str[np] == ' ' || str[np] == '\n')) ++p;
	while(str.size() > np && str[np] != ' ' && str[np] != '\n') ++np;
	string res = str.substr(p, np - p);
	p = np;
	return res;
}
#define PART2
string Compression(string instr) {
	char nxtch;
	string ststr, tmpstr, tmpstr2;
	string res;
	int p = 0, infen = 0;
	string fh = "+-*/=;%<>?!~^&(),{}|";
	while(instr.size() > p) {
		nxtch = instr[p];
		int flag = (infen == 1 && nxtch == '\"') || (infen == 2 && nxtch == '\'');
		if(infen && (!flag || (instr[p - 1] == '\\') && instr[p - 2] != '\\')) {
			ststr+= nxtch;
			++p;
			continue;
		}
		switch(nxtch) {
			case '#': {
				if(p && instr[p - 1] != '\n') {
					ststr+= nxtch;
					break;
				}
				if(ststr.size()) {
					res+= ststr;
					if(ststr[ststr.size() - 1] != ';') res+= ";";
					res+= "\n", ststr = "";
				}
				++p;
				tmpstr = readPause(instr, p);
				++p;
				res+= "#" + tmpstr;
				if(instr[p] == '\n') break;
				res+= " ";
				while(instr.size() > p) {
					nxtch = instr[p];
					if (nxtch == ' ' && ststr.size() && ststr[ststr.size() - 1] == ' ') continue;
					if (nxtch == '\n') break;
					ststr+= nxtch, ++p;
				}
				res+= ststr + "\n", ststr = "";
				break;
			}
			case '\n': case '	' : case ' ' : {
				if(ststr.empty() || fh.find(ststr[ststr.size() - 1]) != -1) {
					break;
				}
				if(instr.size() > p + 1 && fh.find(instr[p + 1]) != -1) {
					break;
				}
				if(!ststr.empty() && ststr[ststr.size() - 1] != ' '){
					ststr+= ' ';
				}			
				break;
			}
			case '/' : {
				if(instr.size() > p + 1 && (instr[p + 1] == '/' || instr[p + 1] == '*')) {
					if(instr[p + 1] == '/') {
						while(instr.size() > p) {
							nxtch = instr[p];
							if (nxtch == '\n') break;
							++p;
						}
					}
					else {
						string llstr;
						while(instr.size() > p) {
							nxtch = instr[p];
							llstr += nxtch;
							if (llstr.find("*/") != -1) break;
							++p;
						}
						++p;
					}
				}
				break;
			}
			case'\"' : {
				if(infen) infen = 0;
				else infen = 1;
				ststr+= nxtch;
				break;
			}
			case '\'' : {
				if(infen) infen = 0;
				else infen = 2;
				ststr+= nxtch;
				break;
			} 
			default : {
			    ststr+= nxtch;
				break;
			}
		}
		++p;
	}
	if(ststr.size()) res+= ststr;
	return res;
//	return Compression2(res, m);
}
#define PART3
int main() {
	cout << "In File : ";
	path = getString();
	ifstream ifile(path.c_str());
	string str, tmpstr;
	while(!ifile.eof()){
		getline(ifile, tmpstr);
		str += tmpstr + "\n";
	}
	ifile.close();
	str = Compression(str);
	path+= ".min.cpp";
	ofstream ofile(path.c_str());
	ofile << str;
	ofile.close();
	return 0;
}
