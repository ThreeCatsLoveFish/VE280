/**
 * Author: Zhimin Sun
 * Course: VE280 2020FA
 */
#include "p2.h"

int
size(list_t list)
{
    if (list_isEmpty(list)) {
        return 0;
    }
    return 1 + size(list_rest(list));
}

bool
memberOf(list_t list, int val)
{
    if (list_isEmpty(list)) {
        return false;
    }
    return list_first(list) == val || memberOf(list_rest(list), val);
}

int
dot(list_t v1, list_t v2)
{
    if (list_isEmpty(v1) || list_isEmpty(v2)) {
        return 0;
    }
    /* Both are not empty */
    return list_first(v1) * list_first(v2) + dot(list_rest(v1), list_rest(v2));
}

bool
isIncreasing(list_t v)
{
    if (list_isEmpty(v) || list_isEmpty(list_rest(v))) {
        return true;
    }
    /* First and second elements are not empty. */
    return list_first(v) <= list_first(list_rest(v))
           && isIncreasing(list_rest(v));
}

list_t
reverse(list_t list)
{
    if (list_isEmpty(list)) {
        return list_make();
    }
    return append(reverse(list_rest(list)),
                  list_make(list_first(list), list_make()));
}

list_t
append(list_t first, list_t second)
{
    if (list_isEmpty(first)) {
        return second;
    }
    return list_make(list_first(first), append(list_rest(first), second));
}

static bool
isArithmeticSequence_helper(list_t list, int delta)
// REQUIRES: list is not empty
// EFFECTS: Determines whether list is arithmetic with delta as
//          common difference.
{
    if (list_isEmpty(list_rest(list))) {
        return true;
    }
    /* Second element is not empty. */
    return list_first(list_rest(list)) - list_first(list) == delta
           && isArithmeticSequence_helper(list_rest(list), delta);
}

bool
isArithmeticSequence(list_t v)
{
    if (list_isEmpty(v) || list_isEmpty(list_rest(v))) {
        return true;
    }
    /* First and second elements are not empty. */
    return  isArithmeticSequence_helper(
                list_rest(v),
                list_first(list_rest(v)) - list_first(v)
            );
}

list_t
filter_odd(list_t list)
{
    if (list_isEmpty(list)) {
        return list_make();
    }
    if (list_first(list) % 2 == 1) {
        /* Element is odd. */
        return list_make(list_first(list), filter_odd(list_rest(list)));
    }
    /* Element is even. */
    return filter_odd(list_rest(list));
}

list_t
filter(list_t list, bool (*fn)(int))
{
    if (list_isEmpty(list)) {
        return list_make();
    }
    if (fn(list_first(list))) {
        /* Function return true. */
        return list_make(list_first(list), filter(list_rest(list), fn));
    }
    /* Function return false. */
    return filter(list_rest(list), fn);
}

static list_t
unique_helper(list_t old_list, list_t new_list = list_make())
// EFFECTS: Return new_list if old_list is empty, else determines
//          whether the first element of old_list is in new_list,
//          if true, then appends this element to new_list, else
//          ignores that and handles the rest part.
{
    if (list_isEmpty(old_list)) {
        return new_list;
    }
    if (!memberOf(new_list, list_first(old_list))) {
        /* Element does not exist. */
        new_list = append(new_list,
                          list_make(list_first(old_list), list_make()));
    }
    return unique_helper(list_rest(old_list), new_list);
}

list_t
unique(list_t list)
{
    return unique_helper(list);
}

list_t
insert_list(list_t first, list_t second, unsigned int n)
{
    if (n == 0) {
        return append(second, first);
    }
    return list_make(list_first(first),
                     insert_list(list_rest(first), second, n - 1));
}

static list_t
chop_helper(list_t reverse_list, unsigned int n)
// EFFECTS: Returns reverse_list if n equals to 0, else chops one
//          element and handles the rest part.
{
    if (n == 0) {
        /* Directly return the reversed list. */
        return reverse(reverse_list);
    }
    return chop_helper(list_rest(reverse_list), n - 1);
}

list_t
chop(list_t list, unsigned int n)
{
    return chop_helper(reverse(list), n);
}

//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int
tree_sum(tree_t tree)
{
    if (tree_isEmpty(tree)) {
        return 0;
    }
    return tree_elt(tree)
           + tree_sum(tree_left(tree))
           + tree_sum(tree_right(tree));
}

bool
tree_search(tree_t tree, int val)
{
    if (tree_isEmpty(tree)) {
        return false;
    }
    return tree_elt(tree) == val
           || tree_search(tree_left(tree), val)
           || tree_search(tree_right(tree), val);
}

static int
max(int a, int b)
// EFFECTS: Return the maximum of two integers.
{
    return a > b ? a : b;
}

int
depth(tree_t tree)
{
    if (tree_isEmpty(tree)) {
        return 0;
    }
    return 1 + max(depth(tree_left(tree)), depth(tree_right(tree)));
}

int
tree_max(tree_t tree)
{
    bool    left_empty;
    bool    right_empty;

    left_empty  = tree_isEmpty(tree_left(tree));
    right_empty = tree_isEmpty(tree_right(tree));
    if (left_empty) {
        if (right_empty) {
            /* Both children are empty. */
            return tree_elt(tree);
        }
        /* Only left child is empty. */
        return max(tree_elt(tree), tree_max(tree_right(tree)));
    }
    if (right_empty) {
        /* Only right child is empty. */
        return max(tree_elt(tree), tree_max(tree_left(tree)));
    }
    return max(tree_elt(tree),
               max(tree_max(tree_left(tree)), tree_max(tree_right(tree))));
}

list_t
traversal(tree_t tree)
{
    if (tree_isEmpty(tree)) {
        return list_make();
    }
    return append(traversal(tree_left(tree)),
                  list_make(tree_elt(tree), traversal(tree_right(tree))));
}

static bool
larger(int a, int b)
// EFFECTS: Determines which one is larger.
{
    return a > b;
}

static bool
smaller(int a, int b)
// EFFECTS: Determines which one is smaller.
{
    return a < b;
}

static bool
tree_hasMonotonicPath_helper(tree_t tree, bool (*fn)(int, int))
// REQUIRES: tree is not empty
// EFFECTS: Returns true if and only if "tree" has at least one
//          root-to-leaf path such that all the elements along the
//          path form a monotonically sequence.
{
    bool    left_empty;
    bool    right_empty;

    left_empty  = tree_isEmpty(tree_left(tree));
    right_empty = tree_isEmpty(tree_right(tree));
    if (left_empty) {
        if (right_empty) {
            /* Both children of leaf are empty. */
            return true;
        }
        /* Only left child is empty. */
        return fn(tree_elt(tree), tree_elt(tree_right(tree)))
               && tree_hasMonotonicPath_helper(tree_right(tree), fn);
    }
    if (right_empty) {
        /* Only right child is empty. */
        return fn(tree_elt(tree), tree_elt(tree_left(tree)))
               && tree_hasMonotonicPath_helper(tree_left(tree), fn);
    }
    return (fn(tree_elt(tree), tree_elt(tree_right(tree)))
           && tree_hasMonotonicPath_helper(tree_right(tree), fn))
           || (fn(tree_elt(tree), tree_elt(tree_left(tree)))
           && tree_hasMonotonicPath_helper(tree_left(tree), fn));
}

bool
tree_hasMonotonicPath(tree_t tree)
{
    if (tree_isEmpty(tree)) {
        return false;
    }
    return tree_hasMonotonicPath_helper(tree, larger)
           || tree_hasMonotonicPath_helper(tree, smaller);
}

bool
tree_allPathSumGreater(tree_t tree, int sum)
{
    bool    left_empty;
    bool    right_empty;
    int     result;

    result = sum - tree_elt(tree);
    if (result < 0) {
        return true;
    }
    left_empty  = tree_isEmpty(tree_left(tree));
    right_empty = tree_isEmpty(tree_right(tree));
    if (left_empty) {
        if (right_empty) {
            /* Both children are empty. */
            return false;
        }
        /* Only left child is empty. */
        return tree_allPathSumGreater(tree_right(tree), result);
    }
    if (right_empty) {
        /* Only right child is empty. */
        return tree_allPathSumGreater(tree_left(tree), result);
    }
    return tree_allPathSumGreater(tree_left(tree), result)
           && tree_allPathSumGreater(tree_right(tree), result);
}

bool
covered_by(tree_t A, tree_t B)
{
    if (tree_isEmpty(A)) {
        return true;
    }
    if (tree_isEmpty(B)) {
        return false;
    }
    if (tree_elt(A) != tree_elt(B)) {
        return false;
    }
    return covered_by(tree_left(A), tree_left(B))
           && covered_by(tree_right(A), tree_right(B));
}     

bool
contained_by(tree_t A, tree_t B)
{
    if (tree_isEmpty(A)) {
        return true;
    }
    if (tree_isEmpty(B)) {
        return false;
    }
    return covered_by(A, B)
           || covered_by(A, tree_left(B))
           || covered_by(A, tree_right(B));
}

tree_t
insert_tree(int elt, tree_t tree)
{
    if (tree_isEmpty(tree)) {
        return tree_make(elt, tree_make(), tree_make());
    }
    if (tree_elt(tree) > elt) {
        return tree_make(tree_elt(tree),
                         insert_tree(elt, tree_left(tree)),
                         tree_right(tree));
    }
    return tree_make(tree_elt(tree),
                     tree_left(tree),
                     insert_tree(elt, tree_right(tree)));
}
