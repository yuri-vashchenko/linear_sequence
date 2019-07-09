#include "linear_sequence.h"

typedef struct node nodeT;

struct node
{
    LSQ_BaseTypeT value;
    nodeT* next;
    nodeT* previous;
};

struct container
{
    nodeT* prefirst;
    nodeT* end;
    int count;
};

typedef struct container containerT;
//typedef struct container* containerT*;

struct iterator
{
    nodeT* node;
    containerT* handle;
};

typedef struct iterator iteratorT;

iteratorT* make_iterator(containerT* handle)
{
    iteratorT* iterator = (iteratorT*)malloc(sizeof(iteratorT));
    if (iterator)
    {
        iterator->node = NULL;
        iterator->handle = handle;
    }
    return iterator;
}

nodeT* make_node(LSQ_BaseTypeT value)
{
    nodeT* node = (nodeT*)malloc(sizeof(nodeT));
    if (node)
    {
        node->value = value;
        node->next = NULL;
        node->previous = NULL;
    }
    return node;
}

LSQ_HandleT LSQ_CreateSequence(void)
{
    containerT* handle;
    handle = (containerT*)malloc(sizeof(containerT));
    if (handle) {
        handle->count = 0;
        handle->prefirst = make_node(0);
        handle->end = make_node(0);
        handle->prefirst->next = handle->end;
        handle->end->previous = handle->prefirst;
    }
    return (LSQ_HandleT) handle;
}

void LSQ_DestroySequence(LSQ_HandleT handle)
{
    if (handle) {
        containerT* container = (containerT*)handle;
        while(container->count > 0)
        {
            LSQ_DeleteFrontElement(handle);
        }
    }
    free(handle);
}

LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle)
{
    if (handle) {
        containerT* container = (containerT*)handle;
        LSQ_IntegerIndexT result = container->count;
        return result;
    }

}

/* Функция, определяющая, может ли данный итератор быть разыменован */
int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator)
{

    iteratorT* it = (iteratorT*)iterator;
    if (it == NULL)
    {
        return 0;
    }
    if ((it->node == it->handle->prefirst) ||
        (it->node == it->handle->end))
    {
        return 0;
    }
    return 1;
}

/* Функция, определяющая, указывает ли данный итератор на элемент, следующий за последним в контейнере */
int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator)
{
    if (iterator) {
        iteratorT* it = (iteratorT*)iterator;
        return it->node == it->handle->end;
    }

}

/* Функция, определяющая, указывает ли данный итератор на элемент, предшествующий первому в контейнере */
int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator)
{
    if (iterator){
        iteratorT* it = (iteratorT*)iterator;
        return it->node == it->handle->prefirst;
    }

}

/* Функция разыменовывающая итератор. Возвращает указатель на элемент, на который ссылается данный итератор */
LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator)
{
    if (iterator) {
        iteratorT* it = (iteratorT*)iterator;

        return &(it->node->value);
    }
}

/* Следующие три функции создают итератор в памяти и возвращают его дескриптор */
/* Функция, возвращающая итератор, ссылающийся на элемент с указанным индексом */
LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index)
{
    if (handle) {
        iteratorT* it = make_iterator(handle);
        containerT* container = (containerT*)handle;
        if (container->count > 0) {
            it->node = container->prefirst->next;

            while(it->node->next != container->end && 0 < index)
            {
                it->node = it->node->next;
                index--;
            }
            return (LSQ_IteratorT)it;
        }

    }

}

/* Функция, возвращающая итератор, ссылающийся на первый элемент контейнера */
LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle)
{
    if (handle) {
        iteratorT* it = make_iterator(handle);
        containerT* container = (containerT*)handle;
        if (container->count > 0) {
            it->node = container->prefirst->next;
            return it;
        }
    }
}

/* Функция, возвращающая итератор, ссылающийся на последний элемент контейнера */
LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle)
{
    if (handle) {
        iteratorT* it = make_iterator(handle);
        containerT* container = (containerT*)handle;
        it->node = container->end;
        return (LSQ_IteratorT)it;
    }
}

/* Функция, уничтожающая итератор с заданным дескриптором и освобождающая принадлежащую ему память */
void LSQ_DestroyIterator(LSQ_IteratorT iterator)
{
    free(iterator);
}

/* Функция, перемещающая итератор на один элемент вперед */
void LSQ_AdvanceOneElement(LSQ_IteratorT iterator)
{
    if (iterator) {
        iteratorT* it = (iteratorT*)iterator;
        if (it->node != it->handle->end)
        {
            it->node = it->node->next;
        }
    }
}

/* Функция, перемещающая итератор на один элемент назад */
void LSQ_RewindOneElement(LSQ_IteratorT iterator)
{
    if (iterator) {
        iteratorT* it = (iteratorT*)iterator;
        if (it->handle->count > 0)
        {
            if (it->node->previous != it->handle->prefirst)
            {
                it->node = it->node->previous;
            }
        }
    }
}

/* Функция, перемещающая итератор на заданное смещение со знаком */
void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)
{
    if (iterator) {
        if (shift == 0)
        {
            return;
        }
        iteratorT* it = (iteratorT*)iterator;

        if (shift >= 0)
        {
            while (shift > 0 && it->node->next != it->handle->end)
            {
                it->node = it->node->next;
                shift--;
            }
        }
        else
        {
            while (shift < 0 && it->node->previous != it->handle->prefirst)
            {
                it->node = it->node->previous;
                shift++;
            }
        }
    }
}

void delete_node(nodeT* node)
{
    if (node->next != NULL)
    {
        if (node->previous != NULL)
        {
            nodeT *prev = node->previous;
            node->previous = node->next;
            node->next = prev;
            free(node);
        }
    }
}

/* Функция, устанавливающая итератор на элемент с указанным номером */
void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)
{
    if (iterator != NULL)
    {
        iteratorT* it = (iteratorT*)iterator;
        it->node = it->handle->prefirst;
        if (it->handle->count < pos)
        {
            it->node = it->handle->end->previous;
        }
        else {
            while (it->node->next != it->handle->end && pos > 0)
            {
                pos--;
                it->node = it->node->next;
            }
        }

    }

}

/* Функция, добавляющая элемент в начало контейнера */
void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if (handle)
    {
        containerT* container = (containerT*)handle;
        nodeT* el = make_node(element);
        nodeT* tmp = container->prefirst->next;
        container->prefirst->next = el;
        el->next = tmp;
        el->previous = container->prefirst;
        tmp->previous = el;
        container->count++;
    }
}
/* Функция, добавляющая элемент в конец контейнера */
void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if (handle)
    {
        containerT* container = (containerT*)handle;
        nodeT* el = make_node(element);
        nodeT* tmp = container->end->previous;
        container->end->previous = el;
        el->previous = tmp;
        el->next = container->end;
        tmp->next = el;
        container->count++;
    }
}
/* Функция, добавляющая элемент в контейнер на позицию, указываемую в данный момент итератором. Элемент, на который  *
 * указывает итератор, а также все последующие, сдвигается на одну позицию в конец.                                  */
void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement)
{
    if (iterator)
    {
        iteratorT* it = (iteratorT*)iterator;
        if (it->node != it->handle->prefirst)
        {
            nodeT* el = make_node(newElement);
            nodeT* pr = it->node->previous;
            it->node->previous = el;
            el->next = it->node;
            pr->next = el;
            el->previous = pr;
            it->handle->count++;
        }
    }
}

/* Функция, удаляющая первый элемент контейнера */
void LSQ_DeleteFrontElement(LSQ_HandleT handle)
{
    if (handle)
    {
        containerT* container = (containerT*)handle;
        if (container->count > 0)
        {
            nodeT* first = container->prefirst->next;
            delete_node(first);
            container->count--;
        }
    }

}
/* Функция, удаляющая последний элемент контейнера */
void LSQ_DeleteRearElement(LSQ_HandleT handle)
{
    if (handle)
    {
        containerT* container = (containerT*)handle;
        if (container->count > 0)
        {
            nodeT* last = container->end->previous;
            delete_node(last);
            container->count--;
        }
    }

}
/* Функция, удаляющая элемент контейнера, указываемый заданным итератором. Все последующие элементы смещаются на     *
 * одну позицию в сторону начала.                                                                                    */
void LSQ_DeleteGivenElement(LSQ_IteratorT iterator)
{
    if (iterator != NULL)
    {
        iteratorT* it = (iteratorT*)iterator;
        if (it->node != it->handle->prefirst &&
            it->node != it->handle->end)
        {
            if (it->handle->count > 0)
            {
                nodeT* node = it->node;
                it->node = it->node->next;
                delete_node(node);
                it->handle->count--;
            }
        }
    }
}
