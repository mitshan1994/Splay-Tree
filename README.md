### 伸展树(splay trees)
#### 概述
伸展树是搜索二叉树的一种延拓,插入与一般二叉树完全相同,只是在搜索元素的时候,
会执行一些额外的操作,来"平衡"二叉树的深度,使之后的搜索平均花费更少的时间.

#### 接口
类的定义形式:

	template <typename T>
	class SplayTree {
		...
	};
	
构造函数:

	// template <typename T>
	// 空树
	SplayTree();

	SplayTree(const SplayTree &);
	SplayTree(SplayTree &&);
	
	SplayTree(const std::vector<T> &);
	SplayTree(std::initializer_list il);
	// and more
	
成员函数(公有):

	// 插入
	void Insert(const T &val);
	
	// 删除. 返回true, 如果删除成功
	bool Delete(const T &val);
	
	// 查找. 返回true, 如果val在树中
	bool Find(const T &val);
	
	// 打印出树的内容,中序
	void InOrderTraverse();
	
成员函数(私有):

	// helper functions
	// 从节点n处,开始执行伸展操作,一路向上直到root
	void Splay(shared_ptr<Node> b);
	
私有数据域:

	// root = nullptr if empty
	shared_ptr<Node> root_;

使用到的数据结构:

	struct Node {
		T val;
		shared_ptr<Node> left;
		shared_ptr<Node> right;
		shared_ptr<Node> parent;
	};

#### Attention
比较过程中使用`<`,当两个比较对象相等是,默认第二个大.
一个节点,左子树元素小于之,右子树元素不小于之.
