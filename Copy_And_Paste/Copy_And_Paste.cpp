#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define RED 0
#define BLACK 1
struct treenode{
    treenode *right, *left;
    int color, rank, size;
    char letter;
    treenode(){}
    treenode(char l){
	color = BLACK;
	left = right = 0;
	letter = l;
	rank = 0;
	size = 1;
    }
    treenode(treenode *l, treenode *r, int c){
	color = c;
	left = l;
	right = r;
	size = l->size + r->size;
	rank = l->rank + l->color;
	letter = ' ';
    }
};
int pp = 0;
typedef pair<treenode*, treenode*> P;
treenode* merge(treenode* l, treenode* r){
    if(l->rank == r->rank){
	return new treenode(l, r, RED);
    }
    if(l->rank > r->rank){
	treenode *tmp = merge(l->right, r);
	if(l->color == BLACK && tmp->color == RED && tmp->right == RED){
	    if(l->left->color == BLACK){
		return new treenode(new treenode(l->left, tmp->left, RED), tmp->right, BLACK);
	    }
	    else{
		return new treenode(new treenode(l->left, tmp->left, BLACK), new treenode(tmp->right->left, tmp->right->right, BLACK), RED);
	    }
	}
	else{
	    return new treenode(l->left, tmp, RED);
	}
    }
    if(l->rank < r->rank){
	treenode *tmp = merge(l, r->left);
	if(r->color == BLACK && tmp->color == RED && tmp->left == RED){
	    if(r->right->color == BLACK){
		return new treenode(tmp->left, new treenode(tmp->right, r->right, RED), BLACK);
	    }
	    else{
		return new treenode(new treenode(l->left, tmp->left, BLACK), new treenode(tmp->right->left, tmp->right->right, BLACK), RED);
		return new treenode(new treenode(tmp->left->left, tmp->left->right, BLACK),new treenode(tmp->right, r->right, BLACK), RED);
	    }
	}
	else{
	    return new treenode(tmp, r->right, RED);
	}
    }
}

treenode* xmerge(treenode *x, treenode *y){
    if(x == 0)return y;
    if(y == 0)return x;
    treenode* tmp = merge(x, y);
    if(tmp->color == RED)
	tmp = new treenode(tmp->left, tmp->right, BLACK);
    return tmp;
}

string to_str(treenode* root){
    string res = "";
    if(root->rank == 0)res += root->letter;
    else res = to_str(root->left) + to_str(root->right);
    return res;
}

pair<treenode*, treenode*> split(treenode* root, int pos){
    if(pos == 0)return P(0, root);
    if(root->size <= pos)return P(root, 0);
    if(root->left->size >= pos){
	P tmp = split(root->left, pos);
	return P(tmp.first, xmerge(tmp.second, root->right));
    }  
    else{
	P tmp = split(root->right, pos - root->left->size);
	return P(xmerge(root->left, tmp.first), tmp.second);
    }
}

treenode* initialize(string* str, int l, int r){
    if(r - l == 1)return new treenode((*str)[l]);
    int mid = (l + r) / 2;
    return xmerge(initialize(str, l, mid), initialize(str, mid, r));
}

treenode* subtree(treenode* root, int left, int right){
    return split(split(root, right).first , left).second;
}

treenode* paste(treenode* root, treenode* in, int pos){
    P tmp = split(root, pos);
    return xmerge(xmerge(tmp.first, in), tmp.second);
}

int main(){
    int m, n, a, b, c;
    string str;
    cin >> m;
    cin >> str;
    treenode* root = initialize(&str, 0, str.size());
    cin >> n;
    for(int i = 0;i < n;i++){
	cin >> a >> b >> c;
	treenode *tmp = subtree(root, a, b);
	root = paste(root, tmp, c);
	root = split(root, m).first;
    }
    cout << to_str(root) << endl;
}
