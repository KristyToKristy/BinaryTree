#include <queue>
#include <stack>
#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	T _data;

	BinaryTreeNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(const T* a, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreateTree(a, size, index, invalid);
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void PostOrder();

	void LevelOrder()
	{
		queue<Node*> q;
		if (_root)
		{
			q.push(_root);
		}

		while (!q.empty())
		{
			Node* front = q.front();
			cout << front->_data << " ";
			if (front->_left)
			{
				q.push(front->_left);
			}

			if (front->_right)
			{
				q.push(front->_right);
			}

			q.pop();
		}

		cout << endl;
	}

	void PrevOrder_NonR() // 
	{
		stack<Node*> s;
		if (_root)
		{
			s.push(_root);
		}

		while (!s.empty())
		{
			Node* top = s.top();
			s.pop();
			cout << top->_data << " ";

			if (top->_right)
			{
				s.push(top->_right);
			}

			if (top->_left)
			{
				s.push(top->_left);
			}
		}

		cout << endl;
	}

	void InOrder_NonR()
	{
		Node* cur = _root;
		stack<Node*> s;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			cout << top->_data << " ";
			s.pop();

			cur = top->_right;
		}

		cout << endl;
	}

	void PostOrder_NonR()
	{
		Node* prev = NULL;
		Node* cur = _root;
		stack<Node*> s;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			if (top->_right == NULL || top->_right == prev)
			{
				cout << top->_data << " ";
				s.pop();
				prev = top;
			}
			else
			{
				cur = top->_right;
			}
		}

		cout << endl;
	}

	Node* Find(const T& x)
	{
		return _Find(_root, x);
	}



	size_t Size()
	{
		size_t size = 0;
		_Size(_root, size);
		return size;
	}
	
	size_t Depth()
	{
		return _Depth(_root);
	}

	size_t LeafSize()
	{
		return _LeafSize(_root);
	}

	bool IsComplete()
	{
		queue<Node*> q;
		q.push(_root);
		Node* cur = NULL;
		//进行广度优先遍历（层次遍历），并把NULL节点也放入
		while(q.front() != NULL)
		{
			cur = q.front();
			q.pop();
			q.push(cur->_left);
			q.push(cur->_right);
		}
		//判断是否还有未访问到的节点
		while (!q.empty())
		{
			cur = q.front();
			q.pop();
			if (cur != NULL)
			{
				return false;
			}
		}
		return true;
	}
	size_t GetKLevel(int k)
	{
		size_t size = 0;
		size_t level = 1;
		_GetKLevel(_root, level, k, size);
		return size;
	}

protected:
	void _GetKLevel(Node* root, size_t level, size_t k,
		size_t& size)
	{
		if (root == NULL)
		{
			return;
		}

		if (k == level)
		{
			++size;
			return;
		}

		_GetKLevel(root->_left, level + 1, k, size);
		_GetKLevel(root->_right, level + 1, k, size);
	}

	Node* _Find(Node* root, const T& x)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_data == x)
		{
			return root;
		}

		Node* ret = _Find(root->_left, x);
		if (ret)
			return ret;

		return _Find(root->_right, x);
	}

	BinaryTreeNode<T>* _CreateTree(const T* a, size_t size, size_t& index, const T& invalid)
	{
		BinaryTreeNode<T>* root = NULL;
		if (index < size && a[index] != invalid)
		{
			root = new BinaryTreeNode<T>(a[index]);
			root->_left = _CreateTree(a, size, ++index, invalid);
			root->_right = _CreateTree(a, size, ++index, invalid);
		}

		return root;
	}

protected:
	//size_t _GetKLevel(Node* root, int k)
	//{
	//	if (root == NULL)
	//	{
	//		return 0;
	//	}

	//	if (k == 1)
	//	{
	//		return 1;
	//	}

	//	return _GetKLevel(root->_left, k-1) + _GetKLevel(root->_right, k-1);
	//}

	void _PrevOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

	/*size_t _Size(Node* root)
	{
	if (root == NULL)
	{
	return 0;
	}

	return _Size(root->_left) + _Size(root->_right)+1;
	}*/

	/*void _Size(Node* root)
	{
	if (root == NULL)
	{
	return;
	}

	++gSize;
	_Size(root->_left);
	_Size(root->_right);
	}*/

	//size_t _Size(Node* root)
	//{
	//	static size_t sSize = 0;

	//	if (root == NULL)
	//	{
	//		return 0;
	//	}

	//	++sSize;
	//	_Size(root->_left);
	//	_Size(root->_right);

	//	return sSize;
	//}

	void _Size(Node* root, size_t& size)
	{
		if (root == NULL)
		{
			return;
		}

		++size;
		_Size(root->_left, size);
		_Size(root->_right, size);
	}


	size_t _Depth(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int left = _Depth(root->_left) + 1;
		int right = _Depth(root->_right) + 1;

		return left > right ? left : right;
	}

	size_t _LeafSize(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		if (root->_left == NULL && root->_right == NULL)
		{
			return 1;
		}

		return _LeafSize(root->_left) + _LeafSize(root->_right);
	}

protected:
	BinaryTreeNode<T>* _root;
};


void Test1()
{
	int array1[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int array2[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int array3[10] = { 1, 2, 3, '#', '#', 4};
	int array4[10] = { 1, 2, '#', 4, '#', '#', 5, 6 };
	int array5[13] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6,'#','#',7 };
	

	BinaryTree<int> t1(array1, 10, '#');
	BinaryTree<int> t2(array2, 15, '#');
	BinaryTree<int> t3(array2, 15, '#');
	BinaryTree<int> t4(array2, 15, '#');
	BinaryTree<int> t5(array2, 15, '#');

	//t1.IsComplete();
	if (t5.IsComplete())
	{
		printf("YES");
	}
	else
	{
		printf("NO");
	}

}

int main()
{
	Test1();
	system("pause");
	return 0;
}