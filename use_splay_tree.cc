#include <iostream>
#include <vector>
#include "splay_tree.h"

using namespace std;

int main()
{
    // SplayTree<int> st;
    // st.Insert(1);
    // st.Insert(2);
    // st.Insert(0);
    // st.Insert(5);
    // st.Insert(4);
    // st.InOrderTraverse();

    vector<int> a = {1, 3, 2, 5, 4};
    SplayTree<int> st2(a);
    // st2.InOrderTraverse();
    cout << st2.Find(2);
    cout << st2.Find(6);
    cout << st2.Find(3);

    // SplayTree<int> st3({1, 3, 2, 5, 4});
    // st3.InOrderTraverse();

    // SplayTree<int>::Test1();
    

    return 0;
}
