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
    cout << "2. Tampilkan senjata\n";
    cout << "3. Cari senjata\n";
    cout << "4. Hapus senjata\n";
    cout << "5. Total semua stok\n";
    cout << "6. Hapus semua data\n";
    cout << "7. Sisipkan senjata setelah senjata tertentu\n";
    cout << "8. Edit data senjata\n";
    cout << "0. Keluar\n";
    cout << "Pilih No: ";
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

    int pilihan;
    cout << "\nTampilkan daftar senjata berdasarkan:\n";
    cout << "1. Semua senjata\n";
    cout << "2. Filter (Kategori/Harga/Stok)\n";
    cout << "Pilih No: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1)
    {
        cout << "\n=== Daftar Senjata ===\n";
        int no = 1;
        Weapon *temp = head;
        while (temp)
        {
            cout << no++ << ". Nama: " << temp->name
                 << " | Kategori: " << temp->category
                 << " | Harga: Rp" << temp->price
                 << " | Stok: " << temp->stock << endl;
            temp = temp->next;
        }
    }
    else if (pilihan == 2)
    {
        int filter;
        cout << "Filter berdasarkan:\n";
        cout << "1. Kategori\n";
        cout << "2. Harga\n";
        cout << "3. Stok\n";
        cout << "Pilih No: ";
        cin >> filter;
        cin.ignore();

        if (filter == 1)
        {
            string kategori;
            cout << "Masukkan kategori (contoh: Pistol/Rifle/Sniper): ";
            getline(cin, kategori);
            int no = 1;
            Weapon *temp = head;
            bool found = false;
            cout << "\n=== Senjata dengan Kategori \"" << kategori << "\" ===\n";
            while (temp)
            {
                if (temp->category == kategori)
                {
                    cout << no++ << ". Nama: " << temp->name
                         << " | Harga: Rp" << temp->price
                         << " | Stok: " << temp->stock << endl;
                    found = true;
                }
                temp = temp->next;
            }
            if (!found)
                cout << "Tidak ada senjata dengan kategori tersebut.\n";
        }
        else if (filter == 2)
        {
            string harga;
            cout << "Masukkan harga (tanpa Rp): ";
            getline(cin, harga);
            int no = 1;
            Weapon *temp = head;
            bool found = false;
            cout << "\n=== Senjata dengan Harga Rp" << harga << " ===\n";
            while (temp)
            {
                if (temp->price == harga)
                {
                    cout << no++ << ". Nama: " << temp->name
                         << " | Kategori: " << temp->category
                         << " | Stok: " << temp->stock << endl;
                    found = true;
                }
                temp = temp->next;
            }
            if (!found)
                cout << "Tidak ada senjata dengan harga tersebut.\n";
        }
        else if (filter == 3)
        {
            int stok;
            cout << "Masukkan stok: ";
            cin >> stok;
            cin.ignore();
            int no = 1;
            Weapon *temp = head;
            bool found = false;
            cout << "\n=== Senjata dengan Stok " << stok << " ===\n";
            while (temp)
            {
                if (temp->stock == stok)
                {
                    cout << no++ << ". Nama: " << temp->name
                         << " | Kategori: " << temp->category
                         << " | Harga: Rp" << temp->price << endl;
                    found = true;
                }
                temp = temp->next;
            }
            if (!found)
                cout << "Tidak ada senjata dengan stok tersebut.\n";
        }
        else
        {
            cout << "Pilihan filter tidak valid.\n";
        }
    }
    else
    {
        cout << "Pilihan tidak valid.\n";
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

void sisip(Weapon *&head, string after, string name, string kategori, string price, int stock)
{
    Weapon *temp = head;
    while (temp && temp->name != after)
        temp = temp->next;

    if (!temp)
    {
        cout << "Senjata \"" << after << "\" tidak ditemukan. Penyisipan gagal.\n";
        return;
    }

    Weapon *newWeapon = new Weapon{name, kategori, price, stock, temp->next};
    temp->next = newWeapon;
    cout << "Senjata berhasil disisipkan setelah \"" << after << "\".\n";
}

void edit(Weapon *head, string name)
{
    Weapon *temp = head;
    while (temp && temp->name != name)
        temp = temp->next;

    if (!temp)
    {
        cout << "Senjata \"" << name << "\" tidak ditemukan.\n";
        return;
    }

    cout << "Edit data senjata \"" << name << "\":\n";
    cout << "Nama baru (kosongkan jika tidak ingin mengubah): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty())
        temp->name = newName;

    cout << "Kategori baru (contoh: Pistol/Rifle/Sniper | kosongkan jika tidak ingin mengubah): ";
    string kategori;
    getline(cin, kategori);
    if (!kategori.empty())
        temp->category = kategori;

    cout << "Harga baru (kosongkan jika tidak ingin mengubah): ";
    string newPrice;
    getline(cin, newPrice);
    if (!newPrice.empty())
        temp->price = newPrice;

    cout << "Stok baru (isi -1 jika tidak ingin mengubah): ";
    int newStock;
    cin >> newStock;
    cin.ignore();
    if (newStock != -1)
        temp->stock = newStock;

    cout << "Data senjata berhasil diubah.\n";
}

int main()
{
    Weapon *head = nullptr;

    int pilihan, stokBaru;
    string nama, kategori, harga, namaBaru, kategoriBaru, hargaBaru;
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
        case 7:
            cout << "Setelah senjata bernama: ";
            getline(cin, nama);
            cout << "Nama senjata baru: ";
            getline(cin, namaBaru);
            cout << "Kategori senjata (contoh: Pistol/Rifle/Sniper): ";
            getline(cin, kategoriBaru);
            cout << "Harga: Rp";
            cin >> hargaBaru;
            cout << "Stok: ";
            cin >> stokBaru;
            cin.ignore();
            sisip(head, nama, namaBaru, kategoriBaru, hargaBaru, stokBaru);
            break;
        case 8:
            cout << "Nama senjata yang ingin diedit: ";
            getline(cin, nama);
            edit(head, nama);
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