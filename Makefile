main : use_splay_tree.cc splay_tree.h
	$(CXX) use_splay_tree.cc -std=c++11 -o main

clean :
	rm -f *.o *~ main
