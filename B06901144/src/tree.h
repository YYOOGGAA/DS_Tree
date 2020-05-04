#ifndef  TREE_H
#define  TREE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "file.h"

using namespace std;


class BTree;
class SplayTree;

class TreeNode
{
	friend class Tree;

public:
	TreeNode(int d, TreeNode* r, TreeNode* l, TreeNode* p, int le) :
		data(d), childr(r), childl(l), parent(p), levelnum(le) {}
	~TreeNode () {}
    
    int getLoc() {return loc;}
    int getData() {return data;}
	bool haveChild()
	{
		if(childl != 0 || childr != 0) return true;
		return false;
	}

private:
    int data;
    int loc;
    int levelnum;
    TreeNode* childr;
    TreeNode* childl;
    TreeNode* parent;
};

class Tree
{
public:
	Tree(string t) : treeType(t), size(0), level(0) { }
    ~Tree() {}
    
    bool empty();
    void insertAll();
    void saveTree(fstream&, fstream&);

private:
	string treeType;
	TreeNode* root;
	TreeNode* cur;
	int level;
	int subsize;
	size_t size;
	void insertB(int);
    void insertS(int);
    void leftRotate(TreeNode*);
    void rightRotate(TreeNode*);
    void splay(TreeNode*&);
    void preorderTreeWalk(fstream&,TreeNode*&);
    void TreeWalk(TreeNode*&);
    void FindBoundary(fstream& B);
    void updateLoc(TreeNode*&);
    int  findNext(int);
};

#endif   //TREE_H
