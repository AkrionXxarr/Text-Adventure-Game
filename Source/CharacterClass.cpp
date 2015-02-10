#include "CharacterClass.hpp"

namespace Character
{
    class Template;
};

void Character::Template::DamageCharacter(unsigned short damage)
{
    if ((m_curHealth - damage) < 0)
    {
        m_curHealth = 0;
    }
    else
    {
        m_curHealth -= damage;
    }
}

void Character::Template::HealCharacter(unsigned short health)
{
    if ((m_curHealth + health) > m_maxHealth)
    {
        m_curHealth = m_maxHealth;
    }
    else
    {
        m_curHealth += m_maxHealth;
    }
}

unsigned short Character::Template::GetCurrentHealth() { return m_curHealth; }
unsigned short Character::Template::GetMaxHealth() { return m_maxHealth; }

CHARACTER_STATUS Character::Template::GetStatus()
{
    if (m_curHealth == 0)
        return DEAD;

    return ALIVE;
}

std::string Character::Template::GetCharacterName() { return m_characterName; }

void Character::Template::SetCurrentHealth(unsigned short current) { m_curHealth = current; }
void Character::Template::SetMaxHealth(unsigned short max) { m_maxHealth = max; }
void Character::Template::SetCharacterName(std::string characterName) { m_characterName = characterName; }
