#ifndef _CHARACTER_CLASS_HPP_
#define _CHARACTER_CLASS_HPP_

#include <string>
#include "GlobalDefines.hpp"

namespace Character
{
    class Template
    {
    public:
        void DamageCharacter(unsigned short damage);
        void HealCharacter(unsigned short health);

        unsigned short GetCurrentHealth();
        unsigned short GetMaxHealth();
        CHARACTER_STATUS GetStatus();
        std::string GetCharacterName();

        void SetCurrentHealth(unsigned short current);
        void SetMaxHealth(unsigned short max);
        void SetCharacterName(std::string characterName);


    private:
        unsigned short m_curHealth;
        unsigned short m_maxHealth;

        std::string m_characterName;
    };
};

#endif