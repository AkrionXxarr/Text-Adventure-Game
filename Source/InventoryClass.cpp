#include "InventoryClass.hpp"
#include <iostream>
using namespace std;

Inv::Inventory::Inventory()
{
    m_itemHead = new Inv::Item(0, "");
    m_itemTail = new Inv::Item(0, "");

    m_itemHead->next = m_itemTail;
    m_itemHead->prev = NULL;
    m_itemTail->prev = m_itemHead;
    m_itemTail->next = NULL;
}

Inv::Inventory::~Inventory()
{
    // DEBUG //
    if (_DEBUG_MESSAGES)
        cout << "In Inventory destructor" << endl;
    ///////////

    Inv::Item* itemIterator = m_itemHead;

    while (itemIterator->next != NULL)
    {
        itemIterator = itemIterator->next;
        delete itemIterator->prev;
    }
    delete itemIterator;
}

// Note: Can probably replace Room::Template::AddObject() with this linking method
void Inv::Inventory::AddItem(Inv::Item item)
{
    Inv::Item* tempItem = new Inv::Item(item);

    tempItem->next = m_itemHead->next;
    tempItem->next->prev = tempItem;
    tempItem->prev = m_itemHead;
    m_itemHead->next = tempItem;
}

void Inv::Inventory::RemoveItem(unsigned int itemID)
{
    Inv::Item* itemIterator = m_itemHead;
    Inv::Item* prevItem = m_itemHead;

    while (itemIterator->next != NULL)
    {
        itemIterator = itemIterator->next;

        if (itemIterator->m_itemID == itemID)
        {
            itemIterator->prev->next = itemIterator->next;
            itemIterator->next->prev = itemIterator->prev;

            delete itemIterator;
            break;
        }
    }
}

bool Inv::Inventory::HasItem(unsigned int itemID)
{
    Inv::Item* itemIterator = m_itemHead;

    while (itemIterator->next != NULL)
    {
        itemIterator = itemIterator->next;

        if (itemIterator->m_itemID == itemID)
        {
            return true;
        }
    }
    return false;
}

void Inv::Inventory::ListItems()
{
    Inv::Item* itemIterator = m_itemHead;

    cout << "/=Inventory=\\" << endl;
    cout << "|-" << endl;
    while (itemIterator->next != m_itemTail)
    {
        itemIterator = itemIterator->next;
        cout << "*" << itemIterator->m_itemName << endl;
    }
    cout << "|-" << endl;
    cout << "\\===========/";
}

