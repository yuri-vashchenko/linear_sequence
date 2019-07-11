#include <stdio.h>
#include "linear_sequence.h"

struct node
{
    LSQ_BaseTypeT value;
    struct node* next;
    struct node* previous;
};

typedef struct node nodeT;

struct container
{
    nodeT* prefirst;
    nodeT* end;
    int count;
};

typedef struct container containerT;

struct iterator
{
    containerT* handle;
    nodeT* node;
};

typedef struct iterator iteratorT;

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
        free(container->end);
        free(container->prefirst);
        free(handle);
        handle = NULL;
    }
}

LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle)
{
    if (handle) {
        containerT* container = (containerT*)handle;
        LSQ_IntegerIndexT result = container->count;
        return result;
    }
    return 0;
}

/* Р¤СѓРЅРєС†РёСЏ, РѕРїСЂРµРґРµР»СЏСЋС‰Р°СЏ, РјРѕР¶РµС‚ Р»Рё РґР°РЅРЅС‹Р№ РёС‚РµСЂР°С‚РѕСЂ Р±С‹С‚СЊ СЂР°Р·С‹РјРµРЅРѕРІР°РЅ */
int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator)
{
    if (iterator != NULL) {
        iteratorT* it = (iteratorT*)iterator;
        nodeT* node = it->node;
        if (node != NULL) {
            if ((node->previous != NULL) && (node->next != NULL)) {
                return 1;
            }
        }
    }
    return 0;
}

/* Р¤СѓРЅРєС†РёСЏ, РѕРїСЂРµРґРµР»СЏСЋС‰Р°СЏ, СѓРєР°Р·С‹РІР°РµС‚ Р»Рё РґР°РЅРЅС‹Р№ РёС‚РµСЂР°С‚РѕСЂ РЅР° СЌР»РµРјРµРЅС‚, СЃР»РµРґСѓСЋС‰РёР№ Р·Р° РїРѕСЃР»РµРґРЅРёРј РІ РєРѕРЅС‚РµР№РЅРµСЂРµ */
int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator)
{
    if (iterator) {
        iteratorT* it = (iteratorT*)iterator;
        if (it->node != NULL)
        {
            return it->node->next == NULL;
        }
    }
    return 0;
}

/* Р¤СѓРЅРєС†РёСЏ, РѕРїСЂРµРґРµР»СЏСЋС‰Р°СЏ, СѓРєР°Р·С‹РІР°РµС‚ Р»Рё РґР°РЅРЅС‹Р№ РёС‚РµСЂР°С‚РѕСЂ РЅР° СЌР»РµРјРµРЅС‚, РїСЂРµРґС€РµСЃС‚РІСѓСЋС‰РёР№ РїРµСЂРІРѕРјСѓ РІ РєРѕРЅС‚РµР№РЅРµСЂРµ */
int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator)
{
    if (iterator){
        iteratorT* it = (iteratorT*)iterator;
        if (it->node != NULL)
        {
            return it->node->previous == NULL;
        }
    }
    return 0;
}

/* Р¤СѓРЅРєС†РёСЏ СЂР°Р·С‹РјРµРЅРѕРІС‹РІР°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ. Р’РѕР·РІСЂР°С‰Р°РµС‚ СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЌР»РµРјРµРЅС‚, РЅР° РєРѕС‚РѕСЂС‹Р№ СЃСЃС‹Р»Р°РµС‚СЃСЏ РґР°РЅРЅС‹Р№ РёС‚РµСЂР°С‚РѕСЂ */
LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator)
{
    if (LSQ_IsIteratorDereferencable(iterator)) {
        iteratorT* it = (iteratorT*)iterator;
        return &(it->node->value);
    }
    return NULL;
}


/* РЎР»РµРґСѓСЋС‰РёРµ С‚СЂРё С„СѓРЅРєС†РёРё СЃРѕР·РґР°СЋС‚ РёС‚РµСЂР°С‚РѕСЂ РІ РїР°РјСЏС‚Рё Рё РІРѕР·РІСЂР°С‰Р°СЋС‚ РµРіРѕ РґРµСЃРєСЂРёРїС‚РѕСЂ */
/* Р¤СѓРЅРєС†РёСЏ, РІРѕР·РІСЂР°С‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ, СЃСЃС‹Р»Р°СЋС‰РёР№СЃСЏ РЅР° СЌР»РµРјРµРЅС‚ СЃ СѓРєР°Р·Р°РЅРЅС‹Рј РёРЅРґРµРєСЃРѕРј */
LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index)
{
    if (handle) {
        iteratorT* it = malloc(sizeof(iteratorT));
        if (it != NULL)
        {
            containerT* container = (containerT*)handle;
            it->handle = container;

            it->node = container->prefirst->next;

            while (!LSQ_IsIteratorPastRear(it) && (index > 0))
            {
                LSQ_AdvanceOneElement(it);
                index--;
            }
        }
        return it;
    }
    return NULL;
}

/* Р¤СѓРЅРєС†РёСЏ, РІРѕР·РІСЂР°С‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ, СЃСЃС‹Р»Р°СЋС‰РёР№СЃСЏ РЅР° РїРµСЂРІС‹Р№ СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР° */
LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle)
{
    if (handle) {
        iteratorT* it = malloc(sizeof(iteratorT));
        if (it != NULL)
        {
            containerT* container = (containerT*)handle;
            it->handle = container;
            it->node = container->prefirst->next;
        }
        return it;
    }
    return NULL;
}

/* Р¤СѓРЅРєС†РёСЏ, РІРѕР·РІСЂР°С‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ, СЃСЃС‹Р»Р°СЋС‰РёР№СЃСЏ РЅР° РїРѕСЃР»РµРґРЅРёР№ СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР° */
LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle)
{
    if (handle) {
        iteratorT* it = malloc(sizeof(iteratorT));
        if (it != NULL)
        {
            containerT* container = (containerT*)handle;
            it->handle = container;
            it->node = container->end;
        }
        return it;
    }
    return NULL;
}

/* Р¤СѓРЅРєС†РёСЏ, СѓРЅРёС‡С‚РѕР¶Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ СЃ Р·Р°РґР°РЅРЅС‹Рј РґРµСЃРєСЂРёРїС‚РѕСЂРѕРј Рё РѕСЃРІРѕР±РѕР¶РґР°СЋС‰Р°СЏ РїСЂРёРЅР°РґР»РµР¶Р°С‰СѓСЋ РµРјСѓ РїР°РјСЏС‚СЊ */
void LSQ_DestroyIterator(LSQ_IteratorT iterator)
{
    if (iterator){
        iteratorT* it = (iteratorT*)iterator;
        free(it);
    }
}

/* Р¤СѓРЅРєС†РёСЏ, РїРµСЂРµРјРµС‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ РЅР° РѕРґРёРЅ СЌР»РµРјРµРЅС‚ РІРїРµСЂРµРґ */
void LSQ_AdvanceOneElement(LSQ_IteratorT iterator)
{
    if (iterator) {
        iteratorT* it = (iteratorT*)iterator;
        if (it->node != it->handle->end) {
            it->node = it->node->next;
        }
    }
}

/* Р¤СѓРЅРєС†РёСЏ, РїРµСЂРµРјРµС‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ РЅР° РѕРґРёРЅ СЌР»РµРјРµРЅС‚ РЅР°Р·Р°Рґ */
void LSQ_RewindOneElement(LSQ_IteratorT iterator)
{
    if (iterator) {
        iteratorT* it = (iteratorT*)iterator;
        if (it->node != it->handle->prefirst) {
            it->node = it->node->previous;
        }
    }
}

/* Р¤СѓРЅРєС†РёСЏ, РїРµСЂРµРјРµС‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ РЅР° Р·Р°РґР°РЅРЅРѕРµ СЃРјРµС‰РµРЅРёРµ СЃРѕ Р·РЅР°РєРѕРј */
void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)
{
    if (iterator) {

        iteratorT* it = (iteratorT*)iterator;

        if (shift == 0)
        {
            return;
        }

        if (shift > 0)
        {
            while (shift > 0 && !LSQ_IsIteratorPastRear(it))
            {
                LSQ_AdvanceOneElement(it);
                shift--;
            }
        }
        else
        {
            while (shift < 0 && !LSQ_IsIteratorBeforeFirst(it))
            {
                LSQ_RewindOneElement(it);
                shift++;
            }
        }
    }
}

/* Р¤СѓРЅРєС†РёСЏ, СѓСЃС‚Р°РЅР°РІР»РёРІР°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ РЅР° СЌР»РµРјРµРЅС‚ СЃ СѓРєР°Р·Р°РЅРЅС‹Рј РЅРѕРјРµСЂРѕРј */
void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)
{
    if (iterator)
    {
        if (pos < 0) // sporyshev difference
        {
            return;
        }
        iteratorT* it = (iteratorT*)iterator;
        it->node = it->handle->end; // sporyshev difference

        if (it->handle != NULL)
        {
            LSQ_IntegerIndexT size = LSQ_GetSize(it->handle);
            if (size == 0 || pos > size)
            {
                return;
            }
            if (it->handle->prefirst != NULL)
            {
                it->node = it->handle->prefirst->next;
                LSQ_ShiftPosition(it, pos);
            }
        }
    }
}

/* Р¤СѓРЅРєС†РёСЏ, РґРѕР±Р°РІР»СЏСЋС‰Р°СЏ СЌР»РµРјРµРЅС‚ РІ РЅР°С‡Р°Р»Рѕ РєРѕРЅС‚РµР№РЅРµСЂР° */
void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if (handle)
    {
        LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);
        if (iterator != NULL)
        {
            LSQ_InsertElementBeforeGiven(iterator, element);
            LSQ_DestroyIterator(iterator);
        }
    }
}
/* Р¤СѓРЅРєС†РёСЏ, РґРѕР±Р°РІР»СЏСЋС‰Р°СЏ СЌР»РµРјРµРЅС‚ РІ РєРѕРЅРµС† РєРѕРЅС‚РµР№РЅРµСЂР° */
void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if (handle)
    {
        LSQ_IteratorT iterator = LSQ_GetPastRearElement(handle);
        if (iterator != NULL)
        {
            LSQ_InsertElementBeforeGiven(iterator, element);
            LSQ_DestroyIterator(iterator);
        }
    }
}
/* Р¤СѓРЅРєС†РёСЏ, РґРѕР±Р°РІР»СЏСЋС‰Р°СЏ СЌР»РµРјРµРЅС‚ РІ РєРѕРЅС‚РµР№РЅРµСЂ РЅР° РїРѕР·РёС†РёСЋ, СѓРєР°Р·С‹РІР°РµРјСѓСЋ РІ РґР°РЅРЅС‹Р№ РјРѕРјРµРЅС‚ РёС‚РµСЂР°С‚РѕСЂРѕРј. Р­Р»РµРјРµРЅС‚, РЅР° РєРѕС‚РѕСЂС‹Р№  *
 * СѓРєР°Р·С‹РІР°РµС‚ РёС‚РµСЂР°С‚РѕСЂ, Р° С‚Р°РєР¶Рµ РІСЃРµ РїРѕСЃР»РµРґСѓСЋС‰РёРµ, СЃРґРІРёРіР°РµС‚СЃСЏ РЅР° РѕРґРЅСѓ РїРѕР·РёС†РёСЋ РІ РєРѕРЅРµС†.                                  */
void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement)
{
    if (iterator)
    {
        iteratorT* it = (iteratorT*)iterator;
        nodeT* el = make_node(newElement);

        el->previous = it->node->previous;
        el->next = it->node;
        it->node->previous->next = el;
        it->node->previous = el;
        it->node = el;
        if (it->handle != NULL)
        {
            it->handle->count++;
        }
    }
}

/* Р¤СѓРЅРєС†РёСЏ, СѓРґР°Р»СЏСЋС‰Р°СЏ РїРµСЂРІС‹Р№ СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР° */
void LSQ_DeleteFrontElement(LSQ_HandleT handle)
{
    if (handle)
    {
        LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);
        if (iterator != NULL)
        {
            LSQ_DeleteGivenElement(iterator);
            LSQ_DestroyIterator(iterator);
        }
    }

}
/* Р¤СѓРЅРєС†РёСЏ, СѓРґР°Р»СЏСЋС‰Р°СЏ РїРѕСЃР»РµРґРЅРёР№ СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР° */
void LSQ_DeleteRearElement(LSQ_HandleT handle)
{
    if (handle)
    {
        LSQ_IteratorT iterator = LSQ_GetPastRearElement(handle);
        if (iterator != NULL)
        {
            LSQ_RewindOneElement(iterator);
            LSQ_DeleteGivenElement(iterator);
            LSQ_DestroyIterator(iterator);
        }
    }
}
/* Р¤СѓРЅРєС†РёСЏ, СѓРґР°Р»СЏСЋС‰Р°СЏ СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР°, СѓРєР°Р·С‹РІР°РµРјС‹Р№ Р·Р°РґР°РЅРЅС‹Рј РёС‚РµСЂР°С‚РѕСЂРѕРј. Р’СЃРµ РїРѕСЃР»РµРґСѓСЋС‰РёРµ СЌР»РµРјРµРЅС‚С‹ СЃРјРµС‰Р°СЋС‚СЃСЏ РЅР°     *
 * РѕРґРЅСѓ РїРѕР·РёС†РёСЋ РІ СЃС‚РѕСЂРѕРЅСѓ РЅР°С‡Р°Р»Р°.                                                                                    */
void LSQ_DeleteGivenElement(LSQ_IteratorT iterator)
{
    if (LSQ_IsIteratorDereferencable(iterator))
    {
        iteratorT* it = (iteratorT*)iterator;
        nodeT* node = it->node;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        it->node = it->node->next;
        if (it->handle != NULL)
        {
            if (it->handle->count > 0)
            {
                it->handle->count--;
            }
        }
        free(node);
    }
}
