#ifndef _INVENTORY_CLASS_HPP_
#define _INVENTORY_CLASS_HPP_

#include "GlobalDefines.hpp"
#include <string>

namespace Inv
{
    struct Item;
    class Inventory;
};

namespace Inv
{
    struct Item
    {
        Item(unsigned int itemID, std::string itemName) : m_itemID(itemID), m_itemName(itemName) { }

        unsigned int m_itemID;
        std::string m_itemName;

        Inv::Item* next;
        Inv::Item* prev;
    };

    class Inventory
    {
    public:
        Inventory();
        ~Inventory();

        void AddItem(Inv::Item item);
        void RemoveItem(unsigned int itemID);
        bool HasItem(unsigned int itemID);

        void ListItems();

    private:
        Inv::Item* m_itemHead;
        Inv::Item* m_itemTail;
    };
};

#endif