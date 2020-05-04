#include "file.h"
#include "tree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

bool
File::read(fstream& file)
{
	//cerr << "Start to read!" << endl;
	char str[65536];
	file.getline(str,65536);
	if(str[0] == 0) return false;
	char* a = strtok(str,"\u00A0");
	while(a != 0)
	{
		int b = atoi(a);
		input.push_back(b);
		//cerr << b << " ";
		a = strtok(0,"\u00A0");
	}
	//cerr << endl;
	return true;
}

bool
File::Rightest(int n)
{
	if(n == 0) return true;
	int level = ceil(log2(n+2));
	int biggest = pow(2,level)-2;
	int k = 0;
	for(int i = n+1; i < (biggest+1); i++)
	{
		if(tree[i] == 0) k++;
	}
	if(k == (biggest-n)) return true;
	else return false;
}

bool
File::Leftest(int n)
{
	if(n == 0) return true;
	int level = ceil(log2(n+2));
	int first = pow(2,level-1)-1;
	int k = 0;
	for(int i = first; i < n; i++)
	{
		if(tree[i] == 0) k++;
	}
	if(k == (n-first)) return true;
	else return false;
}

int
File::front(int n)
{
	int i = n-1;
	while(1)
	{
		if(tree[i] != 0) return i;
		i--;
	}
}

int
File::inorderNum(int n)
{
	for(int i = 0; i < inorder.size(); i++)
	{
		if(inorder[i] == tree[n]) return i;
	}
}

void 
File::writeTree(fstream& file)
{
	int i = 0;
	while(i < tree.size())
	{
		if(tree[i] != 0)
		{
			//cerr << i << " " << tree[i] <<endl;
			int le = ceil(log2(i+2));
			int first = pow(2,le-1)-1;
			int n;
			if(Leftest(i)) n =0;
			else
			{
				int space = 3*inorderNum(front(i));
				int k = ceil(log10(tree[front(i)]));
				if(tree[front(i)] == 1) k = 1;
				else if(tree[front(i)] == 10) k = 2;
				else if(tree[front(i)] == 100) k = 3;
				n = space + k;
			}

			for(int j = 0; j < 3*inorderNum(i)-n; j++)
			{
				file << "\u00A0";
			}
			file << tree[i];
			if(Rightest(i)) 
			{
				file <<"\r\n"; 
				i = pow(2,le)-1;
			} 
			else i++;
		}
		else i++;
	}
}

void 
File::writePRep(fstream& file, int k)
{
	// ( :-1 
	// ) :-2
	// space : -3
	// - :-4
	if(k == -1) file << "(";
	else if(k == -2) file << ")";
	else if(k == -3) file << "\u00A0";
	else if(k == -4) file << "-";
	else file << k;

}