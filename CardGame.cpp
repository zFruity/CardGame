#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Card
{
protected:
    int mana;

public:
    Card(int p_mana = 0)
    {
        mana = p_mana;
    }

    void SetMana(int p_mana)
    {
        mana = p_mana;
    }
    int GetMana()
    {
        return mana;
    }
};

class Player : public Card
{
private:
    int hp, energy, multiplier;

public:
    Player(int p_hp = 0, int p_mana = 0, int p_energy = 0, int p_multiplier = 1)
        : Card(p_mana)
    {
        hp = p_hp;
        energy = p_energy;
        multiplier = p_multiplier;
    }

    void SetHp(int p_hp)
    {
        hp = p_hp;
    }
    int GetHp()
    {
        return hp;
    }

    void SetMultiplier(int p_multiplier)
    {
        multiplier = p_multiplier;
    }
    int GetMultiplier()
    {
        return multiplier;
    }

    void SetEnergy(int p_energy)
    {
        energy = p_energy;
    }
    int GetEnergy()
    {
        return energy;
    }

    void DisplayInfo(int p, bool showMana = false)
    {
        cout << "Player " << p << endl;
        cout << "Hp: " << GetHp() << endl;
        cout << "Energy: " << GetEnergy() << endl;
        if (showMana)
        {
            cout << "Multiplier: " << GetMultiplier() << endl;
            cout << "Mana: " << GetMana() << endl;
        }
    }
};

class SkillCard : public Card
{
private:
    int damage, type;
    string name;

public:
    SkillCard(string p_name = "0", int p_damage = 0, int p_mana = 0, int p_type = 0)
        : Card(p_mana)
    {
        name = p_name;
        damage = p_damage;
        type = p_type;
    }

    void SetDamage(int p_damage)
    {
        damage = p_damage;
    }
    int GetDamage()
    {
        return damage;
    }

    void SetName(string p_name)
    {
        name = p_name;
    }
    string GetName()
    {
        return name;
    }

    void SetType(int p_type)
    {
        type = p_type;
    }
    int GetType()
    {
        return type;
    }
};

#pragma region Nodes
struct Node
{
    SkillCard card;
    Node *link;
};

Node *createNewNode(string name, int damage, int mana, int type)
{
    Node *newnode = new Node;

    // newnode->card.SetNumber(number);
    newnode->card.SetName(name);
    newnode->card.SetDamage(damage);
    newnode->card.SetMana(mana);
    newnode->card.SetType(type);
    newnode->link = 0;

    return (newnode);
}

int countNodes(Node *head)
{
    int count = 0;
    Node *current = head;

    while (current != nullptr)
    {
        count++;
        current = current->link;
    }

    return count;
}

void displaylist(Node *head)
{
    Node *current = head;
    int i = 0;

    cout << "Player Attacks\n";
    while (current != 0)
    {
        if (i == 3)
        {
            cout << "\nCard Attacks\n";
        }
        cout << i << ". " << current->card.GetName() << endl;
        current = current->link;
        i++;
    }
}

void addToBegin(Node **head, Node *newnode)
{
    newnode->link = *head;
    *head = newnode;
}

void addToEnd(Node **head, Node *newnode)
{
    Node *current = *head;
    if (!*head)
    {
        *head = newnode;
    }
    else
    {
        while (current->link != 0)
        {
            current = current->link;
        }
        current->link = newnode;
    }
}

void addToN(Node **head, Node *newnode, int n)
{
    Node *current = *head;
    for (int i = 1; i < n - 1 && current; i++)
    {
        current = current->link;
    }
    newnode->link = current->link;
    current->link = newnode;
}

void removeNode(Node **head, int n)
{
    if (n < 3)
    {
        return;
    }

    Node *current = *head;
    Node *prev = nullptr;

    for (int i = 0; i < n && current; i++)
    {
        prev = current;
        current = current->link;
    }

    if (current)
    {
        if (prev == nullptr)
        {
            *head = current->link;
        }
        else
        {
            prev->link = current->link;
        }

        delete current;
    }
}

void sortLinkedList(Node **head)
{
    if (*head == nullptr || (*head)->link == nullptr)
    {
        return;
    }

    Node *current = *head;
    Node *last = nullptr;
    int nodeCount = 0;

    while (current != nullptr)
    {
        ++nodeCount;
        current = current->link;
    }

    if (nodeCount < 4)
    {
        return;
    }

    bool swapped;

    do
    {
        swapped = false;
        current = *head;

        for (int i = 1; i < 4; ++i)
        {
            current = current->link;
        }

        while (current->link != last)
        {
            if (current->card.GetName() > current->link->card.GetName())
            {
                // Swap nodes
                std::swap(current->card, current->link->card);
                swapped = true;
            }

            current = current->link;
        }

        last = current;

    } while (swapped);
}

#pragma endregion

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void GenerateRandomMana(Player *py)
{
    int random = (rand() % 4) + 5;

    py->SetMana(random);
    cout << random << " Mana received!" << endl;
}

void DrawRandomCard(Node **head, bool shout = false)
{
    int random;
    random = rand() % 7;
    switch (random)
    {
    case 0:
        addToEnd(head, createNewNode("Fireball(3 damage, 3 mana)", 3, 3, 0));
        if (shout)
            cout << "Drawed Fireball!\n";
        break;
    case 1:
        addToEnd(head, createNewNode("Cunning(2 draw, 2 mana)", 2, 2, 6));
        if (shout)
            cout << "Drawed Cunning!\n";
        break;
    case 2:
        addToEnd(head, createNewNode("Second Chance(Reroll mana)", 0, 0, 5));
        if (shout)
            cout << "Drawed Seccond Chance!\n";
        break;
    case 3:
        addToEnd(head, createNewNode("Heal(+2 Hp, 1 mana)", 2, 1, 1));
        if (shout)
            cout << "Drawed Heal!\n";
        break;
    case 4:
        addToEnd(head, createNewNode("Buff(2 multiplier, 3 mana)", 2, 3, 2));
        if (shout)
            cout << "Drawed Buff!\n";
        break;
    case 5:
        addToEnd(head, createNewNode("Charge(+1 energy, 2 mana)", 1, 2, 3));
        if (shout)
            cout << "Drawed Charge!\n";
        break;
    case 6:
        addToEnd(head, createNewNode("Replenish(+1 mana, 0 mana)", 1, 0, 4));
        if (shout)
            cout << "Drawed Replenish!\n";
        break;
    default:
        break;
    }
    sortLinkedList(head);
}

void CreateStartingDeck(Node **head)
{
    addToEnd(head, createNewNode("Normal Attack(1 damage, 0 mana, +1 energy)", 1, 0, 0));
    addToEnd(head, createNewNode("Skill(2 damage, 3 mana, +2 energy)", 2, 3, 0));
    addToEnd(head, createNewNode("Ultimate(6 damage, 3 mana, 3 energy)", 6, 3, -1));

    for (int i = 0; i < 5; i++)
    {
        DrawRandomCard(head);
    }
}

void useCard(Node **head, int n, Player *attacker, Player *defender)
{
    Node *current = *head;

    int listSize = countNodes(*head);
    if (n < 0 || n > listSize - 1)
    {
        cout << "Invalid Choice\n";
        return;
    }

    for (int i = 0; i < n && current; i++)
    {
        current = current->link;
    }

    if (attacker->GetMana() < current->card.GetMana())
    {
        cout << "Insuficient Mana\n";
        return;
    }

    switch (current->card.GetType())
    {
    case -1:
        if (attacker->GetEnergy() < 5)
        {
            cout << "Insuficient Energy\n";
            break;
        }
        defender->SetHp(defender->GetHp() - current->card.GetDamage() * attacker->GetMultiplier());
        cout << "Used Ulimate & Dealt " << current->card.GetDamage() * attacker->GetMultiplier() << " Damage!\n";
        attacker->SetMultiplier(1);
        attacker->SetMana(attacker->GetMana() - current->card.GetMana());
        attacker->SetEnergy(0);
        break;
    case 0:
        defender->SetHp(defender->GetHp() - current->card.GetDamage() * attacker->GetMultiplier());
        cout << "Dealt " << current->card.GetDamage() * attacker->GetMultiplier() << " Damage!\n";
        attacker->SetMultiplier(1);
        attacker->SetMana(attacker->GetMana() - current->card.GetMana());
        break;
    case 1:
        attacker->SetHp(attacker->GetHp() + current->card.GetDamage());
        cout << "Healed " << current->card.GetDamage() << " Hp!\n";
        attacker->SetMana(attacker->GetMana() - current->card.GetMana());
        break;
    case 2:
        attacker->SetMultiplier(current->card.GetDamage());
        cout << "Next Attack Damage Multiplied by " << current->card.GetDamage() << "!\n";
        attacker->SetMana(attacker->GetMana() - current->card.GetMana());
        break;
    case 3:
        attacker->SetEnergy(attacker->GetEnergy() + current->card.GetDamage());
        cout << "Charged " << current->card.GetDamage() << " Energy!\n";
        attacker->SetMana(attacker->GetMana() - current->card.GetMana());
        break;
    case 4:
        attacker->SetMana(attacker->GetMana() + current->card.GetDamage());
        cout << "Replenished " << current->card.GetDamage() << " Mana!\n";
        attacker->SetMana(attacker->GetMana() - current->card.GetMana());
        break;
    case 5:
        GenerateRandomMana(attacker);
        break;
    case 6:
        for (int i = 0; i < 2; i++)
            DrawRandomCard(head, true);
        attacker->SetMana(attacker->GetMana() - current->card.GetMana());
        break;
    default:
        break;
    }

    removeNode(head, n);
}

int main()
{
    unsigned seed = time(0);
    srand(seed);

    bool firstTurn = true;
    int option;
    Node *p1cardlist = nullptr;
    Node *p2cardlist = nullptr;
    CreateStartingDeck(&p1cardlist);
    CreateStartingDeck(&p2cardlist);

    Player p1(40);
    Player p2(40);
    do
    {
        cout << "1.Play\n";
        cout << "2.Quit\n";
        cin >> option;
    } while (option < 1 || option > 2);

    if (option == 2)
        return 0;

    clearConsole();

    do
    {
        cout << "PLAYER 1's TURN!!!" << endl;
        if (!firstTurn && countNodes(p1cardlist) <= 15)
            DrawRandomCard(&p1cardlist, true);
        GenerateRandomMana(&p1);
        cout << endl;

        do
        {
            p1.DisplayInfo(1, true);
            cout << endl;
            p2.DisplayInfo(2);
            cout << endl;

            displaylist(p1cardlist);

            cin >> option;

            clearConsole();
            useCard(&p1cardlist, option, &p1, &p2);
            if (p2.GetHp() < 0)
                break;

        } while (option != 0 && option != 1 && (option != 2 || p1.GetEnergy() < 5));
        if (p2.GetHp() < 0)
            break;
        if (p1.GetEnergy() < 5)
        {
            if (option == 0)
                p1.SetEnergy(p1.GetEnergy() + 1);
            if (option == 1)
                p1.SetEnergy(p1.GetEnergy() + 2);
        }

        cout << "PLAYER 2's TURN!!!" << endl;
        if (!firstTurn && countNodes(p2cardlist) <= 15)
            DrawRandomCard(&p2cardlist, true);
        GenerateRandomMana(&p2);
        cout << endl;

        do
        {
            p2.DisplayInfo(2, true);
            cout << endl;
            p1.DisplayInfo(1);
            cout << endl;
            displaylist(p2cardlist);

            cin >> option;

            clearConsole();
            useCard(&p2cardlist, option, &p2, &p1);
            if (p1.GetHp() < 0)
                break;

        } while (option != 0 && option != 1 && (option != 2 || p2.GetEnergy() < 5));
        if (p1.GetHp() < 0)
            break;
        if (p2.GetEnergy() < 5)
        {
            if (option == 0)
                p2.SetEnergy(p2.GetEnergy() + 1);
            if (option == 1)
                p2.SetEnergy(p2.GetEnergy() + 2);
        }

        firstTurn = false;
    } while (p1.GetHp() > 0 && p2.GetHp() > 0);

    clearConsole();
    if (p1.GetHp() <= 0)
    {
        cout << "PLAYER 2 WON!!!" << endl;
    }
    else
    {
        cout << "PLAYER 1 WON!!!" << endl;
    }
    return 0;
}