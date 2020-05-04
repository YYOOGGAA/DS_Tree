#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "tree.h"

using namespace std;

class File
{
	friend class Tree;

public:
	File() : l(0), max(0) {}
	~File() {}
   
	bool read(fstream&);
   	void writeTree(fstream&);
   	void writePRep(fstream&, int);
   	bool Rightest(int);
   	bool Leftest(int);
   	int  front(int);
   	int  inorderNum(int);

    void clear() 
    {
    	input.clear();
    	tree.clear();
    	inorder.clear();
    	l = 0;
    	max = 0;
    }

private:
	vector<int> input;
	vector<int> tree;
	vector<int> inorder;
	int l;
	int max;
};

#endif  //FILE_H
