#include <iostream>
#include <fstream>
#include <cstring>
#include "tree.h"
#include "file.h"

using namespace std;

extern File f;

int main(int argc, char* argv[])
{

	fstream fin(argv[1]);
	fstream fout(argv[2],ios::out);
	fstream foutB(argv[3],ios::out);
	fstream foutP(argv[4],ios::out);

	while(f.read(fin))
	{
		if(strcmp(argv[5],"-b") == 0)
		{
			Tree btree("btree");
			btree.insertAll();
			//cerr << "btree insert successfully" << endl;
			btree.saveTree(foutB,foutP);
			//cerr << "btree saveTree successfully" << endl;
		}
		else
		{
	    	Tree stree("stree");	    
			stree.insertAll();
			//cerr << "stree insert successfully" << endl;
			stree.saveTree(foutB,foutP);
			//cerr << "stree saveTree successfully" << endl;
		}
		
		f.writeTree(fout);
		//cerr << "btree writeTree successfully" << endl;

		f.clear();
	}

	fin.close();
	fout.close();
	foutB.close();
	foutP.close();
}