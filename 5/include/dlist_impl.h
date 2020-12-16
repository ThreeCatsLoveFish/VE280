/**
 * @file dlist_impl.h
 * @author Zhimin Sun
 * @date 2020-11-25
 * @course 2020FA VE280
 */
template <class T>
void
Dlist<T>::removeAll()
{
    while (first) {
        node *tmp = first;

        first = first->next;
        delete tmp;
    }
    first = last = nullptr;
}

template <class T>
void
Dlist<T>::copyAll(const Dlist<T> &l)
{
    first = last = nullptr;
    if (l.isEmpty()) {
        return;
    }
    node *tmp = l.first;
    node *prevNode;
    node *newNode;

    while (tmp) {
        newNode       = new node();
        newNode->op   = tmp->op;
        newNode->prev = nullptr;
        if (first == nullptr) {
            first = newNode;
        } else {
            prevNode->next = newNode;
            newNode->prev  = prevNode;
        }
        prevNode = newNode;
        tmp      = tmp->next;
    }
    newNode->next = nullptr;
    last          = newNode;
}

template <class T>
Dlist<T>::Dlist() : first(nullptr), last(nullptr)
{}

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l)
{
    copyAll(l);
}

template <class T>
Dlist<T> &
Dlist<T>::operator=(const Dlist<T> &l)
{
    removeAll();
    copyAll(l);
    return *this;
}

template <class T>
Dlist<T>::~Dlist()
{
    removeAll();
}

template <class T>
bool
Dlist<T>::isEmpty() const
{
    return first == nullptr;
}

template <class T>
void
Dlist<T>::insertFront(T *op)
{
    if (first == nullptr) {
        first = last = new node();
        first->op    = op;
        first->next = first->prev = nullptr;
        return;
    }
    first->prev       = new node();
    first->prev->op   = op;
    first->prev->next = first;
    first->prev->prev = nullptr;
    first             = first->prev;
}

template <class T>
void
Dlist<T>::insertBack(T *op)
{
    if (first == nullptr) {
        first = last = new node();
        first->op    = op;
        first->next = first->prev = nullptr;
        return;
    }
    last->next       = new node();
    last->next->op   = op;
    last->next->prev = last;
    last->next->next = nullptr;
    last             = last->next;
}

template <class T>
T *
Dlist<T>::removeFront()
{
    if (first == nullptr) {
        throw emptyList();
    }
    node *tmp  = first;
    T *   data = first->op;

    first = first->next;
    if (first == nullptr) {
        last = nullptr;
    } else {
        first->prev = nullptr;
    }
    delete tmp;
    return data;
}

template <class T>
T *
Dlist<T>::removeBack()
{
    if (last == nullptr) {
        throw emptyList();
    }
    node *tmp  = last;
    T *   data = last->op;

    last = last->prev;
    if (last == nullptr) {
        first = nullptr;
    } else {
        last->next = nullptr;
    }
    delete tmp;
    return data;
}

/**
 * @brief Clean the double-linked list
 *
 * @param doubleList Double-linked list that will be cleaned
 */
template <class T>
static void
cleanDList(Dlist<T> &doubleList)
// EFFECTS: Clean the double-linked list
// MODIFIES: doubleList
{
    while (!doubleList.isEmpty()) {
        delete doubleList.removeBack();
    }
}
