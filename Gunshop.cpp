#include <iostream>
#include <string>
using namespace std;

struct Weapon
{
    string name;
    string category;
    string price;
    int stock;
    Weapon *next;
};

void menu()
{
    cout << "\n=== GUN SHOP MENU ===\n";
    cout << "1. Tambah senjata\n";
    cout << "2. Tampilkan semua senjata\n";
    cout << "3. Cari senjata\n";
    cout << "4. Hapus senjata\n";
    cout << "5. Total semua stok\n";
    cout << "6. Hapus semua data\n";
    cout << "0. Keluar\n";
    cout << "Pilih: ";
}

void add(Weapon *&head, string name, string category, string price, int stock)
{
    Weapon *newWeapon = new Weapon{name, category, price, stock, nullptr};

    if (!head)
    {
        head = newWeapon;
    }
    else
    {
        Weapon *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newWeapon;
    }
}

int main()
{
    Weapon *head = nullptr;
    return 0;
}