#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include "file.h"
#include "tree.h"

using namespace std;

File f;

bool
Tree::empty()
{
  	if(size == 0) return true;
   	return false;
}

void 
Tree::insertAll()
{
    for(int i = 0; i < f.input.size(); i++)
    {
		if (treeType == "btree")
           	insertB(f.input[i]);
        else 
        {
        	insertS(f.input[i]);
        }
    }
    if (treeType == "stree")
    {
    	updateLoc(root);
        //cerr << "max" << f.max << endl;
        level = ceil(log2(f.max+2));
    }
    //cerr << level << endl;
}

void
Tree::insertB(int d)
{
	int l = 1;
	if (empty()) 
    {
      	root = new TreeNode(d,0,0,0, l);
      	root->loc = 0;
      	cur = root;
    }
    else
    {
        TreeNode* y = 0;
        TreeNode* x = root;
        while (x != 0)
        {
           y = x;
           if (d < x->data) x = x->childl;
           else x = x->childr;
           l++;
        }
        TreeNode* n = new TreeNode(d,0,0,y,l);
        if (d < y->data) 
        {
        	y->childl = n;
        	n->loc = (y->loc)*2+1;
        }
        else 
        {
        	y->childr = n;
        	n->loc = (y->loc)*2+2;
        }
        cur = n;
    }
    if(level < l) level = l;
    size++;
}

void
Tree::insertS(int d)
{
    insertB(d);
    splay(cur);
}

void
Tree::leftRotate(TreeNode* n)
{
	TreeNode* y = n->childr;
    if(y != 0)
	{
      	n->childr = y->childl;
      	if(y->childl != 0) y->childl->parent = n;
      	y->parent = n->parent;
    }
    
    if(n == root) root = y;
    else if(n == n->parent->childl) n->parent->childl = y;
    else n->parent->childr = y;
    if(y != 0) y->childl = n;
    n->parent = y;
}

void
Tree::rightRotate(TreeNode* n)
{
	TreeNode* y = n->childl;
    if(y != 0) 
    {
      	n->childl = y->childr;
      	if(y->childr != 0) y->childr->parent = n;
      	y->parent = n->parent;
    }

    if(n == root) root = y;
    else if(n == n->parent->childl) n->parent->childl = y;
    else n->parent->childr = y;

    if(y != 0) y->childr = n;
    n->parent = y;
}

void
Tree::splay(TreeNode*& n)
{
	while(n->parent != 0) 
	{
      	if(n->parent->parent == 0) 
      	{
        	if(n->parent->childl == n) rightRotate(n->parent);
        	else leftRotate(n->parent);
      	} 
      	else if(n->parent->childl == n && n->parent->parent->childl == n->parent) 
      	{
        	rightRotate(n->parent->parent);
        	rightRotate(n->parent);
      	} 
      	else if(n->parent->childr == n && n->parent->parent->childr == n->parent) 
      	{
        	leftRotate(n->parent->parent);
        	leftRotate(n->parent);
      	} 
      	else if(n->parent->childl == n && n->parent->parent->childr == n->parent) 
      	{
        	rightRotate(n->parent);
        	leftRotate(n->parent);
      	} 
      	else 
      	{
        	leftRotate(n->parent);
        	rightRotate(n->parent);
      	}
    }
}

void
Tree::saveTree(fstream& B, fstream& P)
{
	int full = pow(2,level)-1;
	f.l = level;
	//cerr << level << endl;
	f.tree.resize(full,0);
	TreeWalk(root);
	//cerr << "TreeWalk succeed" <<endl;
	FindBoundary(B);
	//cerr << "FindBoundery succeed" <<endl;
	preorderTreeWalk(P,root);
	P << "\r\n";
	//cerr << "preorderTreeWalk succeed" <<endl;
}

void
Tree::TreeWalk(TreeNode*& n)
{
	if(n != 0)
	{
		f.tree[n->getLoc()] = n->getData();
		TreeWalk(n->childl);
		f.inorder.push_back(n->getData());
		TreeWalk(n->childr);
	}
}

void
Tree::FindBoundary(fstream& B)
{
	//cerr << level <<endl;
	int i = 0;
	while(1)
	{
		int le = ceil(log2(i+2));
		if(f.tree[i] != 0)
		{
			//cerr << i <<" ";
			B << f.tree[i];
			if(le != level) 
			{
				B << "\u00A0";
				int a = pow(2,le)-1;
				i = findNext(a);
			}
			else 
			{
				B << "\r\n";
				//cerr << endl;
				return;
			}
		}
	}
	
}

void
Tree::preorderTreeWalk(fstream& P,TreeNode*& n)
{
	// ( :-1 
	// ) :-2
	// space : -3
	// - :-4
	if(n != 0)
	{
		if(n != root && n->parent->childr == n) f.writePRep(P, -3); //存在的右小孩前都有空格

		f.writePRep(P, n->getData());

		if(n->haveChild()) f.writePRep(P, -1);//有小孩的n後要有()
		if(n->childl == 0 && n->haveChild()) //有右小孩但沒有左
		{ 
			f.writePRep(P, -4);
		}

		preorderTreeWalk(P,n->childl);
		if(n->childr == 0 && n->haveChild()) //有左小孩但沒右
		{
			f.writePRep(P, -3);
			f.writePRep(P, -4);
		}
		preorderTreeWalk(P,n->childr);
	    if(n->haveChild()) f.writePRep(P, -2);
	}
}

void
Tree::updateLoc(TreeNode*& n)
{
	if(n != 0)
	{

		if(n == root) n->loc = 0;
		else
		{
			if(n->parent->childl == n) 
				n->loc = 2*(n->parent->loc)+1; 
			else if(n->parent->childr == n)
				n->loc = 2*(n->parent->loc)+2;
		}
		if(n->loc > f.max) f.max = n->loc;
		updateLoc(n->childl);
		updateLoc(n->childr);
	}
}

int
Tree::findNext(int k)
{
	int i = k;
	while(i)
	{
		if(f.tree[i] != 0) return i;
		i++;
	}
}
