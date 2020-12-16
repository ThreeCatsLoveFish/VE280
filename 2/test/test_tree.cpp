#include <iostream>
#include <assert.h>
#include "../src/recursive.h"
#include "../src/p2.h"

using namespace std;

static bool
list_equal(list_t l1, list_t l2)
// EFFECTS: returns true iff l1 == l2.
{
    if (list_isEmpty(l1) && list_isEmpty(l2)) {
        return true;
    } else if (list_isEmpty(l1) || list_isEmpty(l2)) {
        return false;
    } else if (list_first(l1) != list_first(l2)) {
        return false;
    } else {
        return list_equal(list_rest(l1), list_rest(l2));
    }
}

static bool
tree_equal(tree_t t1, tree_t t2)
// EFFECTS: returns true iff t1 == t2
{
    if (tree_isEmpty(t1) && tree_isEmpty(t2)) {
        return true;
    } else if (tree_isEmpty(t1) || tree_isEmpty(t2)) {
        return false;
    } else {
        return ((tree_elt(t1) == tree_elt(t2)) 
            && tree_equal(tree_left(t1), tree_left(t2))
            && tree_equal(tree_right(t1), tree_right(t2)));
    }
}

static void
test_covered_by(void)
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));

    assert(covered_by(start, end));
    assert(!covered_by(end, start));
}

static void
test_contained_by(void)
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(1,
                    tree_make(2,
                        tree_make(1, tree_make(), tree_make()),
                        tree_make(4, 
                              tree_make(3, tree_make(), tree_make()),
                              tree_make())),
                    tree_make());

    assert(!covered_by(start, end));
    assert(contained_by(start, end));
    assert(!contained_by(end, start));
}

static void
test_depth(void)
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));

    assert(depth(start) == 2);
    assert(depth(end) == 3);
}

static void
test_greater(void)
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(6, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));

    assert(!tree_allPathSumGreater(start, 8));
    assert(!tree_allPathSumGreater(start, 3));
    assert(tree_allPathSumGreater(start, 2));
    assert(tree_allPathSumGreater(end, 7));
    assert(!tree_allPathSumGreater(end, 8));
}

static void
test_insert(void)
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));

    assert(tree_equal(insert_tree(3, start), end));
}

static void
test_max(void)
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(5, tree_make(), tree_make()),
                         tree_make()));
    tree_t ano = tree_make(-2,
                   tree_make(0, tree_make(), tree_make()),
                   tree_make(-10, 
                         tree_make(-1, tree_make(), tree_make()),
                         tree_make()));
    tree_t tho = tree_make(0,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(-5, tree_make(), tree_make()),
                         tree_make()));

    assert(tree_max(start) == 4);
    assert(tree_max(end) == 5);
    assert(tree_max(ano) == 0);
    assert(tree_max(tho) == 4);
}

static void
test_monotonic(void)
{
    tree_t case1 =  tree_make(2,
                        tree_make(1, tree_make(), tree_make()),
                        tree_make(4, tree_make(), tree_make()));
    tree_t case2 =  tree_make(2,
                        tree_make(2, tree_make(), tree_make()),
                        tree_make(1, 
                            tree_make(5, tree_make(), tree_make()),
                            tree_make()));
    tree_t case3 =  tree_make(4,
                        tree_make(8,
                            tree_make(3, tree_make(), tree_make()),
                            tree_make(16, tree_make(), tree_make())),
                        tree_make()); 
    tree_t case4 =  tree_make(4,
                        tree_make(20,
                            tree_make(3, tree_make(), tree_make()),
                            tree_make(16, tree_make(), tree_make())),
                        tree_make()); 
    tree_t case5 =  tree_make(2,
                        tree_make(),
                        tree_make());

    assert(tree_hasMonotonicPath(case1));
    assert(!tree_hasMonotonicPath(case2));
    assert(tree_hasMonotonicPath(case3));
    assert(!tree_hasMonotonicPath(case4));
    assert(tree_hasMonotonicPath(case5));
    assert(!tree_hasMonotonicPath(tree_make()));
}

static void
test_search(void)
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));

    assert(!tree_search(start, 3));
    assert(tree_search(start, 4));
}

static void
test_sum(void)
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));

    assert(tree_sum(start) == 7);
}

static void
test_traversal(void)
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));
    list_t result = list_make(1, list_make(2, list_make(4, list_make())));

    assert(!list_equal(traversal(start), traversal(end)));
    assert(list_equal(traversal(start), result));
}

int
main(void)
{
    test_contained_by();
    test_covered_by();
    test_depth();
    test_greater();
    test_insert();
    test_max();
    test_monotonic();
    test_search();
    test_sum();
    test_traversal();
    cout << "Tree Success!\n";
    return 0;
}
