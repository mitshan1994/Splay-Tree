#include <iostream>
#include <memory>
#include <vector>
#include <initializer_list>

template <typename T>
class SplayTree {
private:
    struct Node {
        T val;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> parent;
    };
    
public:
    SplayTree() : root_(nullptr) { }
    // copy and move constructor
    SplayTree(const SplayTree &rhs);
    SplayTree(SplayTree &&rhs);
    
    SplayTree(const std::vector<T> &v);
    SplayTree(std::initializer_list<T> il);

    ~SplayTree() { root_ = nullptr; }

    // member functions
    void Insert(const T &val);
    bool Delete(const T &val);
    bool Find(const T &val);

    // helper functions
    void InOrderTraverse();

    // test functions
    // comment out when finished
    static void Test1()
        {
            SplayTree<int> a = {1, 3, 2};
//            a.InOrderTraverse();
            a.Splay(a.root_->right->left);
            std::cout << a.root_->val << " " << a.root_->left->val << " "
                      << a.root_->right->val << "\n";
            a.Splay(a.root_->right);
            std::cout << a.root_->val << " " << a.root_->left->val << " "
                      << a.root_->left->left->val << "\n";
            std::cout << "Test1 finished\n";
        }
    
private:
    std::shared_ptr<Node> root_;
    
    void Splay(std::shared_ptr<Node> b);
    void DoTraverse(std::shared_ptr<Node>);

    // helper
    // return the same contents of the Node
    std::shared_ptr<Node> MakeSameNode(std::shared_ptr<Node>);

    // return a same tree (you create it)
    std::shared_ptr<Node> MakeSameSubTree(std::shared_ptr<Node>);

    // find the max value of a subtree, return the node pointer
    std::shared_ptr<Node> FindMax(std::shared_ptr<Node>);
};


template <typename T>
void SplayTree<T>::Insert(const T &val)
{
    auto parent = root_;
    auto child = root_;
    auto new_node = std::make_shared<Node>();

    new_node->left = new_node->right = nullptr;
    new_node->parent = nullptr;
    new_node->val = val;

    // if empty
    if (root_ == nullptr) {
        root_ = new_node;
        return;
    }
    // if not empty
    while (child != nullptr) {
        parent = child;
        if (val < child->val)
            child = child->left;
        else
            child = child->right;
    }
    
    new_node->parent = parent;
    if (val < parent->val)  // 应当放在左子节点处
        parent->left = new_node;
    else
        parent->right = new_node;
}

template <typename T>
void SplayTree<T>::InOrderTraverse()
{
    DoTraverse(root_);
}

template <typename T>
void SplayTree<T>::DoTraverse(std::shared_ptr<Node> b)
{
    if (b == nullptr)
        return;
    DoTraverse(b->left);
    std::cout << b->val << " ";
    DoTraverse(b->right);
}

template <typename T>
SplayTree<T>::SplayTree(const SplayTree &rhs)
{
    
}

template <typename T>
SplayTree<T>::SplayTree(SplayTree &&rhs)
{
    if (root_ == rhs.root_)  // same tree
        return;
    root_ = rhs.root_;
    rhs.root_ = nullptr;
}

template <typename T>
SplayTree<T>::SplayTree(const std::vector<T> &v)
{
    for(auto val : v)
        Insert(val);
}

template <typename T>
SplayTree<T>::SplayTree(std::initializer_list<T> il)
{
    for (auto val : il)
        Insert(val);
}

template <typename T>
void SplayTree<T>::Splay(std::shared_ptr<Node> b)
{
    auto new_root = b;
    auto parent = b;
    auto grandparent = b;
    auto ggparent = b; // parent of grandparent
    // 若new_root已经是root,则结束循环
    while (new_root->parent != nullptr) {
        if (new_root->parent->parent == nullptr) {
            // new_root是root节点的子节点
            root_ = new_root;
            parent = new_root->parent;
            if (new_root == new_root->parent->left) {
                // 左子节点
                new_root->parent = nullptr;
                parent->left = new_root->right;
                if (parent->left)
                    parent->left->parent = parent;
                new_root->right = parent;
                parent->parent = new_root;
            } else {
                // 右子节点
                new_root->parent = nullptr;
                parent->right = new_root->left;
                if (parent->right)
                    parent->right->parent = parent;
                new_root->left = parent;
                parent->parent = new_root;
            }
        } else {
            // new_root有祖父节点(总共有4种情况)
            parent = new_root->parent;
            grandparent = parent->parent;
            ggparent = grandparent->parent;
            // 先处理new_root与其新父节点的关系
            if (ggparent != nullptr) {
                // 如果祖父还有父节点
                new_root->parent = ggparent;
                if (ggparent->left == grandparent)
                    ggparent->left = new_root;
                else
                    ggparent->right = new_root;
            } else {
                // 祖父是根节点
                new_root->parent = nullptr;
                root_ = new_root;
            }
            if (grandparent->left == parent && parent->left == new_root) {
                // left-left zig-zig
                parent->left = new_root->right;
                if (parent->left)
                    parent->left->parent = parent;
                new_root->right = parent;
                parent->parent = new_root;
                grandparent->left = parent->right;
                if (grandparent->left)
                    grandparent->left->parent = grandparent;
                parent->right = grandparent;
                grandparent->parent = parent;
            }
            else if (grandparent->right == parent && parent->right == new_root) {
                // right-right zig-zig
                grandparent->right = parent->left;
                if (grandparent->right)
                    grandparent->right->parent = grandparent;
                parent->right = new_root->left;
                if (parent->right)
                    parent->right->parent = parent;
                parent->left = grandparent;
                grandparent->parent = parent;
                new_root->left = parent;
                parent->parent = new_root;
            }
            else if (grandparent->left == parent && parent->right == new_root) {
                // left-right zig-zag
                parent->right = new_root->left;
                if (parent->right)
                    parent->right->parent = parent;
                grandparent->left = new_root->right;
                if (grandparent->left)
                    grandparent->left->parent = grandparent;
                new_root->left = parent;
                new_root->right = grandparent;
                grandparent->parent = parent->parent = new_root;
            }
            else {
                // right-left zig-zag
                grandparent->right = new_root->left;
                if (grandparent->right)
                    grandparent->right->parent = grandparent;
                parent->left = new_root->right;
                if (parent->left)
                    parent->left->parent = parent;
                new_root->left = grandparent;
                new_root->right = parent;
                grandparent->parent = parent->parent = new_root;
            }
        }
    }
}

template <typename T>
bool SplayTree<T>::Find(const T &val)
{
    auto cur_pos = root_;
    while (cur_pos != nullptr) {
        if (cur_pos->val == val)
            break;
        if (cur_pos->val > val)
            cur_pos = cur_pos->left;
        else
            cur_pos = cur_pos->right;
    }
    if (cur_pos == nullptr)  // not found
        return false;
    Splay(cur_pos);
    return true;
}

template <typename T>
std::shared_ptr<typename SplayTree<T>::Node>
SplayTree<T>::MakeSameNode(std::shared_ptr<Node> old)
{
    if (old == nullptr)
        return nullptr;
    auto new_node = std::make_shared<Node>(*old);
    return new_node;
}

template <typename T>
std::shared_ptr<typename SplayTree<T>::Node>
SplayTree<T>::MakeSameSubTree(std::shared_ptr<Node> old)
{
    if (nullptr == old)
        return nullptr;
    // YOUR CODE HERE (HAVEN'T FINISHED)
    // DIFFICULTY: make node parent correct
}

template <typename T>
bool SplayTree<T>::Delete(const T &val)
{
    if (Find(val) == false)
        return false;
    auto left_max = FindMax(root_->left);
    if (nullptr == left_max) {
        // 使用智能指针,这里应该会自动释放需要删除的节点
        root_ = root_->right;
        root_->parent = nullptr;
        return true;
    }
    auto to_delete = root_;
    // TODO HERE
    
    return false;
}

template <typename T>
std::shared_ptr<typename SplayTree<T>::Node>
SplayTree<T>::FindMax(std::shared_ptr<Node> subtree)
{
    if (nullptr == subtree)  // empty subtree
        return nullptr;
    while (subtree->right != nullptr)
        subtree = subtree->right;
    return subtree;
}
