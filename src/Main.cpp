/*

 This Tool was created by GitRubbens on 2021 

*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
using namespace std;
bool isNmbr(string number) {
	int nmbr = 0;
	for (int i = 0;i < number.length()    ;i++) {
		if (((string)"0123456789").find(number.substr(i,i+1)) != -1) {
			continue;
		}else{
			false;
		}
	}
	return true;
}
int fsize = 1024;
int lsize = 16;
int lamount = 5;
string tmpdirname = "temp";
string newtmpdirname = "temp1";
string args[] = {"--lamount","--fsize","--lsize","--help"};
void checkArg(int argc,int i,int i_) {
	if (i+1 >= argc) {
		cout << "[X] missing argument for option \"" + args[i_] + "\"" << endl;
		exit(1);
	}
}
int getNumber(string to_conv) {
	if (!isNmbr(to_conv)) {
		cout << "[X] \""+to_conv+"\" isn't a number" << endl;
		exit(1);
	}
	return atoi(to_conv.c_str());
}
int main(int argc,char *argv[]) {
	cout << "RZGT - Recursive Zip Generation Tool" << endl;
	cout << "Created by: https://github.com/GitRubbens/RZGT" << endl;
	for (int i = 0;i < argc;i++) {
		string opt = (string) argv[i];
		for (int i_ = 0;i_ < sizeof(args)/sizeof(args[0]);i_++) {
			if (args[i_] == opt) {
				switch(i_) {
					case 0:{
						checkArg(argc,i,i_);
						lamount = getNumber((string) argv[i+1]);
						break;
					}
					case 1:{
						checkArg(argc,i,i_);
						fsize = getNumber((string) argv[i+1]);
						break;
					}
					case 2:{
						checkArg(argc,i,i_);
						cout << "[D] " << getNumber((string) argv[i+1]) << endl;
						return 1;
						break;
					}
					case 3:{
						cout << "[i] usage: RZGT [options]" << endl <<
					    "--lamount [number] - set the number of layers (default 5)" << endl <<
						"--lisize [numer] - set the size of layers (default 5)" << endl <<
						"--fsize [number] - set the size of the \"master file\" (file that wil be on the root of the zip,numner in bytes) (default 1kb)" << endl;
						return 0;
					}
				}
			}
		}
	}
	cout << "[i] start the program with the arg --help for help" << endl;
	cout << "[i] creating temp dirs" << endl;
	int retcode = system(("mkdir "+tmpdirname).c_str());
	if (retcode != 0) {
		cout << "[X] create directory \""+tmpdirname+"\" failed" << endl;
		return 1;
	}
	retcode = system(("mkdir "+newtmpdirname).c_str());
	if (retcode != 0) {
		cout << "[X] create directory \""+newtmpdirname+"\" failed" << endl;
		return 1;
	}
	cout << "[i] temp dirs created" << endl;
	cout << "[i] creating \"master file\" (0%)";
	string fcontent;
	
	for (int i = fsize;i > 0;i--) {
		fcontent = fcontent + "0";
		double percentage = fcontent.length() / fsize;
		cout << "\r[i] creating \"master file\" (" << percentage <<"%)";
	}
	ofstream mfile("temp/file.file");
	if (mfile.bad()) {
		cout << "\n[X] failed to open \"file.file\"" << endl;
		return 1;
	}
	mfile << fcontent;
	mfile.close();
	cout << "\n[i] \"master file\" created" << endl;
	cout << "[i] starting layer generation";
	for (int i = lamount;i > 0;i--) {
		cout << "[i] generating layer " << lamount - i << endl;
		for (int i_ = lsize;i_ > 0;i_--) {
			cout << "[i] generating file " << lsize - i_ << " for layer " << lamount - i<< endl;
			string name = "";
			for (int i = i_+1;i > 0;i--) {
				name += "0";
			}
			retcode = system(("7za a "+newtmpdirname+"\\"+name+".zip .\\"+tmpdirname+"\\* -mx9").c_str());
			if (retcode != 0) {
				cout << "[X] zip creation failed" << endl;
				return 1;
			}
		}
		string oldtmpname = tmpdirname;
		retcode = system(("del "+tmpdirname+"\\* /Q").c_str());
		if (retcode != 0) {
			cout << "[X] tmp directory clear failed" << endl;
			return 1;
		}
		//cout << "[D] path replaced " << endl;
		tmpdirname = newtmpdirname;
		newtmpdirname = oldtmpname;	
	}
	cout << "[i] layer generation finished" << endl;
	cout << "[i] creating zip file";
	retcode = system(("7za a 0.zip .\\"+tmpdirname+"\\*").c_str());
	if (retcode != 0) {
		cout << "[X] zip creation failed" << endl;
		return 1;		
	}
	cout << "[i] zip generation finished" << endl;
	cout << "[i] deleting temp dirs" << endl;
	retcode = system(("del "+newtmpdirname).c_str());
	if (retcode != 0) {
		cout << "[X] delete directory \""+newtmpdirname+"\" failed" << endl;
		return 1;
	}
	retcode = system(("del "+tmpdirname).c_str());
	if (retcode != 0) {
		cout << "[X] delete directory \""+tmpdirname+"\" failed" << endl;
		return 1;
	}
	cout << "[i] temp dirs deleted" << endl;
	return 0;
}
