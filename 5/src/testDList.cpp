/**
 * @file test.cpp
 * @author Zhimin Sun
 * @brief Test double-linked list.
 * @date 2020-11-25
 * @course 2020FA VE280
 */
#include "dlist.h"
#include <cassert>

static const char *names[] = {
    "Alice", "Jim", "John", "Lisa", "Peter",
};

static void
test_copy(Dlist<int> l)
{
    int *ip = new int(1);
    l.insertFront(ip);
    delete ip;
}

static void
test1(void)
{
    Dlist<int> ilist;
    int *      ip = new int(1);
    ilist.insertFront(ip);

    // Now ilist should be (1)

    // test removing from a list of size one.
    ip = ilist.removeFront();
    assert(*ip == 1);
    delete ip;

    assert(ilist.isEmpty());
    // Now ilist should be ()

    ip = new int(4);
    ilist.insertFront(ip);

    // Now ilist should be (4)

    ip = new int(5);
    ilist.insertBack(ip);

    // Now ilist should be (4 5)

    ip = new int(3);
    ilist.insertFront(ip);

    // Now ilist should be (3 4 5)

    ip = new int(2);
    ilist.insertFront(ip);

    // Now ilist should be (2 3 4 5)

    ip = new int(6);
    ilist.insertBack(ip);

    // Now ilist should be (2 3 4 5 6)

    ip = new int(7);
    ilist.insertBack(ip);

    // Now ilist should be (2 3 4 5 6 7)

    ip = ilist.removeFront();
    assert(*ip == 2);
    delete ip;

    assert(!ilist.isEmpty());

    // Now ilist should be (3 4 5 6 7)

    ip = ilist.removeBack();
    assert(*ip == 7);
    delete ip;
    assert(!ilist.isEmpty());
    // Now ilist should be (3 4 5 6)

    ip = new int(7);
    ilist.insertBack(ip);

    // Now ilist should be (3 4 5 6 7)

    ip = ilist.removeFront();
    assert(*ip == 3);
    delete ip;
    assert(!ilist.isEmpty());

    // Now ilist should be (4 5 6 7)

    ip = ilist.removeFront();
    assert(*ip == 4);
    delete ip;
    assert(!ilist.isEmpty());

    // Now ilist should be (5 6 7)

    ip = ilist.removeBack();
    assert(*ip == 7);
    delete ip;
    assert(!ilist.isEmpty());

    // Now ilist should be (5 6)

    ip = ilist.removeBack();
    assert(*ip == 6);
    delete ip;
    assert(!ilist.isEmpty());

    // Now ilist should be (5)

    ip = ilist.removeBack();
    assert(*ip == 5);
    delete ip;
    assert(ilist.isEmpty());

    // Now ilist should be ()

    ip = new int(4);
    ilist.insertFront(ip);

    // Now ilist should be (4)

    ip = new int(5);
    ilist.insertBack(ip);

    // Now ilist should be (4 5)

    ip = new int(3);
    ilist.insertFront(ip);

    // Now ilist should be (3 4 5)

    test_copy(ilist);
    Dlist<int> ilist_copy(ilist);

    ip = ilist_copy.removeBack();
    assert(*ip == 5);
    delete ip;
    assert(!ilist.isEmpty());

    Dlist<int> ilist_assign;
    ilist_assign = ilist;
    Dlist<int> ilist_assign2;
    ilist_assign2 = ilist;

    ilist_copy = ilist_assign;

    ip = ilist_assign.removeBack();
    ip = ilist_assign.removeBack();
    ip = ilist_assign.removeBack();

    ip = ilist_assign2.removeBack();
    ip = ilist_assign2.removeBack();
    delete ip;
    ip = ilist_assign2.removeBack();
    delete ip;

    assert(ilist_assign.isEmpty());
    assert(ilist_assign2.isEmpty());
}

static void
test2(void)
{
    Dlist<const char *> data;

    assert(data.isEmpty());
    data.insertFront(&names[2]);
    data.insertFront(&names[1]);
    data.insertFront(&names[0]);
    data.insertBack(&names[3]);
    data.insertBack(&names[4]);

    Dlist<const char *> newData = /* Dlist<const char *> */ (data);
    // Dlist<const char *> newData = Dlist<const char *>(data);

    assert(data.removeFront() == names);
    assert(data.removeFront() == names + 1);
    assert(data.removeBack() == names + 4);
    assert(!data.isEmpty());
    assert(data.removeBack() == names + 3);
    assert(data.removeBack() == names + 2);
    try {
        data.removeBack();
    } catch (emptyList error) {
        assert(true);
    } catch (...) {
        assert(false);
    }
    assert(data.isEmpty());

    assert(newData.removeFront() == names);
    assert(newData.removeFront() == names + 1);
    assert(newData.removeFront() == names + 2);
    newData.insertFront(&names[0]);
    newData.insertBack(&names[3]);
    assert(newData.removeBack() == names + 3);
    assert(newData.removeBack() == names + 4);
    assert(!newData.isEmpty());
    assert(newData.removeBack() == names + 3);
    assert(newData.removeFront() == names);
    try {
        newData.removeBack();
    } catch (emptyList error) {
        assert(true);
    } catch (...) {
        assert(false);
    }
    assert(newData.isEmpty());
}

static void
test_exception(void)
{
    Dlist<int> ilist;
    try {
        ilist.removeFront();
        assert(false);
    } catch (...) {
        assert(true);
    }
}

int
main(void)
{
    test1();
    test2();
    test_exception();
    return 0;
}
