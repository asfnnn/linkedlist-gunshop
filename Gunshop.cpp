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

void display(Weapon *head)
{
    if (!head)
    {
        cout << "Belum ada senjata dalam inventaris.\n";
        return;
    }

    cout << "\n=== Daftar Senjata ===\n";
    int no = 1;
    while (head)
    {
        cout << no++ << ". Nama: " << head->name
             << " | Kategori: " << head->category
             << " | Harga: Rp" << head->price
             << " | Stok: " << head->stock << endl;
        head = head->next;
    }
}

bool search(Weapon *head, string name)
{
    while (head)
    {
        if (head->name == name)
            return true;
        head = head->next;
    }
    return false;
}

void destroy(Weapon *&head, string name)
{
    if (!head)
        return;

    if (head->name == name)
    {
        Weapon *temp = head;
        head = head->next;
        delete temp;
        cout << "Senjata \"" << name << "\" berhasil dihapus.\n";
        return;
    }

    Weapon *current = head;
    Weapon *prev = nullptr;
    while (current && current->name != name)
    {
        prev = current;
        current = current->next;
    }

    if (current)
    {
        prev->next = current->next;
        delete current;
        cout << "Senjata \"" << name << "\" berhasil dihapus.\n";
    }
    else
    {
        cout << "Senjata \"" << name << "\" tidak ditemukan.\n";
    }
}

int stock(Weapon *head)
{
    int total = 0;
    while (head)
    {
        total += head->stock;
        head = head->next;
    }
    return total;
}

void clearAll(Weapon *&head)
{
    while (head)
    {
        Weapon *temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    Weapon *head = nullptr;

        int pilihan;
    string nama, kategori, harga;
    int stok;

    do
    {
        menu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            cout << "Nama senjata: ";
            getline(cin, nama);
            cout << "Kategori senjata (contoh: Pistol/Rifle/Sniper): ";
            getline(cin, kategori);
            cout << "Harga: Rp";
            cin >> harga;
            cout << "Stok: ";
            cin >> stok;
            add(head, nama, kategori, harga, stok);
            break;
        case 2:
            display(head);
            break;
        case 3:
            cout << "Nama senjata yang dicari: ";
            getline(cin, nama);
            if (search(head, nama))
                cout << "Senjata ditemukan!\n";
            else
                cout << "Senjata tidak ditemukan.\n";
            break;
        case 4:
            cout << "Nama senjata yang ingin dihapus: ";
            getline(cin, nama);
            destroy(head, nama);
            break;
        case 5:
            cout << "Total stok senjata: " << stock(head) << " unit\n";
            break;
        case 6:
            clearAll(head);
            cout << "Semua senjata berhasil dihapus.\n";
            break;
        case 0:
            cout << "Keluar dari program...\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    clearAll(head);
    return 0;
}