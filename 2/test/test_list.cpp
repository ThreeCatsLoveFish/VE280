#include <assert.h>
#include <iostream>
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

static void
test_reverse(void)
{
    list_t list;
    list_t list_answer;

    list = list_make();
    list_answer = list_make();

    for (int i = 5; i > 0; i--) {
        list = list_make(i, list);
        list_answer = list_make(6 - i, list_answer);
    }
    list = reverse(list);

    assert(list_equal(list, list_answer));
}

static void
test_chop(void)
{
    list_t list;
    list_t list_answer;

    list = list_make();
    list_answer = list_make();

    for (int i = 5; i > 0; i--) {
        list = list_make(i, list);
    }
    list = chop(list, 2);

    list_answer = list_make(3, list_answer);
    list_answer = list_make(2, list_answer);
    list_answer = list_make(1, list_answer);

    assert(list_equal(list, list_answer));
}

static void
test_dot(void)
{
    int    answer;
    list_t listA;
    list_t listB;

    listA = list_make();
    listB = list_make();

    for (int i = 5; i > 0; i--) {
        listA = list_make(i, listA);
        listB = list_make(i, listB);
        listB = list_make(i + 10, listB);
    }

    answer = 11 * 1 + 1 * 2 + 12 * 3 + 2 * 4 + 13 * 5;
    
    assert(dot(listA, listB) == answer);
}

static void
test_filterodd(void)
{
    list_t list;
    list_t list_answer;

    list = list_make();
    list_answer = list_make();

    for (int i = 5; i > 0; i--) {
        list = list_make(i, list);
    }
    list = filter_odd(list);
    for (int i = 5; i > 0; i -= 2) {
        list_answer = list_make(i, list_answer);
    }

    assert(list_equal(list, list_answer));
}

static bool
filter_judge(int elem)
{
    return elem < 4;
}

static void
test_filter(void)
{
    list_t list;
    list_t list_answer;

    list = list_make();
    list_answer = list_make();

    for (int i = 5; i > 0; i--) {
        list = list_make(i, list);
    }
    list = filter(list, filter_judge);
    for (int i = 3; i > 0; i--) {
        list_answer = list_make(i, list_answer);
    }

    assert(list_equal(list, list_answer));
}

static void
test_memberof(void)
{
    list_t list;

    list = list_make();

    for (int i = 5; i > 0; i--) {
        list = list_make(i, list);
    }

    assert(memberOf(list, 1));
    assert(!memberOf(list, 6));
}

static void
test_insert1(void)
{
    list_t listA;
    list_t listB;
    list_t list_answer;

    listA = list_make();
    listB = list_make();
    list_answer = list_make();

    for (int i = 5; i > 0; i--) {
        listA = list_make(i, listA);
        listB = list_make(-i, listB);
    }
    listB = insert_list(listA, listB, 3);
    
    list_answer = list_make(5, list_answer);
    list_answer = list_make(4, list_answer);
    list_answer = list_make(-5, list_answer);
    list_answer = list_make(-4, list_answer);
    list_answer = list_make(-3, list_answer);
    list_answer = list_make(-2, list_answer);
    list_answer = list_make(-1, list_answer);
    list_answer = list_make(3, list_answer);
    list_answer = list_make(2, list_answer);
    list_answer = list_make(1, list_answer);

    assert(list_equal(listB, list_answer));
}

static void
test_insert2(void)
{
    list_t listA;
    list_t listB;
    list_t listC;

    listA = list_make();
    listB = list_make();
    listC = list_make();

    for (int i = 5; i > 0; i--) {
        listA = list_make(i, listA);
        listB = list_make(-i, listB);
        listC = list_make(i, listC);
    }
    for (int i = 5; i > 0; i--) {
        listC = list_make(-i, listC);
    }
    listB = insert_list(listA, listB, 0);

    assert(list_equal(listC, listB));
}

static void
test_insert(void)
{
    test_insert1();
    test_insert2();
}

static void
test_isArithmetic(void)
{
    list_t listA;
    list_t listB;
    list_t listC;

    listA = list_make();
    listB = list_make();
    listC = list_make();
    assert(isArithmeticSequence(listA));
    listC = list_make(1, listC);
    assert(isArithmeticSequence(listC));
    listC = list_make(1, listC);
    assert(isArithmeticSequence(listC));

    for (int i = 5; i > 0; i--) {
        listA = list_make(i, listA);
        listB = list_make(-i, listB);
        listC = list_make(i, listC);
    }

    assert(isArithmeticSequence(listA));
    assert(isArithmeticSequence(listB));
    assert(!isArithmeticSequence(listC));
}

static void
test_isincreasing(void)
{
    list_t listA;
    list_t listB;
    list_t listC;

    listA = list_make();
    listB = list_make();
    listC = list_make();
    assert(isIncreasing(listA));

    for (int i = 5; i > 0; i--) {
        listA = list_make(i, listA);
        listB = list_make(-i, listB);
        listC = list_make(1, listC);
    }

    assert(isIncreasing(listA));
    assert(!isIncreasing(listB));
    assert(isIncreasing(listC));
}

static void
test_append(void)
{
    list_t listA;
    list_t listB;
    list_t list_answer;

    listA = list_make();
    listB = list_make();
    list_answer = list_make();

    for (int i = 5; i > 0; i--) {
        listA = list_make(i, listA);
        listB = list_make(i + 10, listB);
        list_answer = list_make(i + 10, list_answer);
    }
    for (int i = 5; i > 0; i--) {
        list_answer = list_make(i, list_answer);
    }
    listB = append(listA, listB);

    assert(list_equal(listB, list_answer));
}

static void
test_size(void)
{
    list_t list;

    list = list_make();
    assert(size(list) == 0);

    for (int i = 5; i > 0; i--) {
        list = list_make(i, list);
    }

    assert(size(list) == 5);
}

static void
test_unique(void)
{
    list_t list;
    list_t list_answer;

    list = list_make();
    list_answer = list_make();

    for (int i = 5; i > 0; i--) {
        list = list_make(i, list);
        list = list_make(i + 1, list);
    }
    list = unique(list);
    
    list_answer = list_make(6, list_answer);
    list_answer = list_make(5, list_answer);
    list_answer = list_make(4, list_answer);
    list_answer = list_make(3, list_answer);
    list_answer = list_make(1, list_answer);
    list_answer = list_make(2, list_answer);

    assert(list_equal(list, list_answer));
}

int
main(void)
{
    test_append();
    test_chop();
    test_dot();
    test_filter();
    test_filterodd();
    test_insert();
    test_isArithmetic();
    test_isincreasing();
    test_memberof();
    test_reverse();
    test_size();
    test_unique();
    cout << "List Success!\n";
    return 0;
}
