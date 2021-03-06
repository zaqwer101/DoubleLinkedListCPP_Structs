#include <iostream>

using namespace std;

typedef struct _Node
{
    int value;
    struct _Node *next, *prev;
} Node;

typedef struct _List
{
    int size;
    Node *first, *last;
} List;

List* createList()
{
    List *tmp = new List();
    tmp->size = 0;
    tmp->first = tmp->last = nullptr;

    return tmp;
}
void Add(List *list, int value)
{
    Node *tmp  = new Node();
    tmp->value = value;
    tmp->next  = nullptr;

    if(list->first)
    {
        tmp->prev = list->last;
        list->last->next = tmp;
        list->last = tmp;
    }
    else
    {
        tmp->prev = nullptr;
        list->last = tmp;
        list->first = tmp;
    }
    list->size++;
}

Node* GetById(List *list, int position)
{
    Node *element = nullptr;
    Node *tmp  = list->first;
    Node *tmp2 = nullptr;
    int i = -1;
    while(i != position)
    {
        i++;
        if(i == position)
        {
            element = tmp;
            break;
        }
        tmp2 = tmp->next;
        tmp = tmp2;
    }
    if(element)
        return element;
    else
        return nullptr;
}

void DeleteById(List *list, int position)
{
    // Если в списке нет элементов
    if(!list->first)
    {
        cout << "Камень я не дам" << endl;
        return;
    }

    // Если в списке один элемент
    if(list->first->next == nullptr)
    {
        if(position == 0)
        {
            list->first = nullptr;
            list->last = nullptr;
        }
        else
            cout << "Камень я не дам" << endl;
        list->size--;
        return;
    }

    Node *elem = GetById(list, position);
    // Если удаляемый элемент - последний
    if(!elem->next)
    {
        list->last = elem->prev;
        list->last->next = nullptr;
        list->size--;
        delete elem;
        return;
    }

    // Если удаляемый элемент - первый
    if(!elem->prev)
    {
        list->first = elem->next;
        list->first->prev = nullptr;
        list->size--;
        delete elem;
        return;
    }

    elem->next->prev = elem->prev;
    elem->prev->next = elem->next;
    delete elem;
    list->size--;

    return;
}

void Delete(List *list, int value)
{
    Node *tmp = list->first;
    int id = 0;

    while(tmp->next != nullptr)
    {
        if(tmp->value == value)
        {
            DeleteById(list, id);
            return;
        }
        id ++;
        tmp = GetById(list, id);
        if(tmp->next == nullptr) {
            DeleteById(list, id);
            return;
        }
    }
}

void Insert(List *list, int value, int position)
{
    if(position > list->size || position < 0)
    {
        cout << "Камень я не дам" << endl;
        return;
    }

    Node *newNode = new Node();
    newNode->value = value;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if(position == 0) // Значит вставляем в начало
    {
        list->first->prev = newNode;
        newNode->next = list->first;
        list->first = newNode;
        list->size ++;
        return;
    }

    if(position == (list->size - 1) || position == list->size)
    {
        newNode->next = list->last;
        newNode->prev = list->last->next;
        list->last->prev->next = newNode;
        list->last->prev = newNode;
        list->size ++ ;

        return;
    }

    Node *left  = GetById(list, position - 1);
    Node *right = GetById(list, position);

    left->next = newNode;
    right->prev = newNode;
    newNode->next = right;
    newNode->prev = left;
    list->size ++ ;
    return;
}

void Print(List *list)
{
    Node *tmp = new Node();
    if(list->size > 0)
    {
        int i = -1;
        tmp = list->first;
        while (tmp)
        {
            cout << "Element with position " << ++i << ": " << tmp->value << endl;
            tmp = tmp->next;
        }
    }
}

void Sort(List *list, bool x)
{
    Node *tmp = list->first;
    Node *node1, *node2;

    for(node1 = tmp; node1; node1 = node1->next)
    {
        for(node2 = tmp; node2; node2 = node2->next)
        {
            if((x&&(node1->value > node2->value)) || (!x&&(node1->value < node2->value)))
            {
                int xx = node1->value;
                node1->value = node2->value;
                node2->value = xx;
            }
        }
    }
}

int main()
{
    List* a = createList();
    Add(a, 10);
    Add(a, 20);
    Add(a, 30);
    Insert(a, 24, 1);
    Insert(a, 12, 0);
    Insert(a, 228, a->size);
    Insert(a, 229, a->size - 1);
    DeleteById(a, 0);
    Delete(a, 30);
    Delete(a, 20);
    Sort(a, 0);
    Print(a);
    Sort(a, 1);
    Print(a);
}