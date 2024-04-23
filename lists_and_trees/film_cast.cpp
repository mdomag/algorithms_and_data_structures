#include <iostream>
#include<string>
using namespace std;

struct actor {
    string name;
    unsigned long int fanbase = 0;
    actor* prev = nullptr;
    actor* next = nullptr;
};

actor* head = nullptr;
actor* tail = nullptr;

void add(actor* actor) {
    actor->next = nullptr;
    if (head != nullptr) {
        tail->next = actor;
        actor->prev = tail;
        tail = actor;
    }
    else {
        actor->prev = nullptr;
        head = actor;
        tail = actor;
    }
    return;
}

void del(actor* actor) {
    if (actor != nullptr) {
        if (actor != head && actor != tail) {
            actor->prev->next = actor->next;
            actor->next->prev = actor->prev;
        }
        else if (actor == head) {
            if (actor == tail) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                head = actor->next;
                actor->next->prev = nullptr;
            }
        }
        else {
            tail = actor->prev;
            tail->next = nullptr;
        }
        delete actor;
    }
    return;
}

void search(actor* search) {
    actor* actor = head;
    bool found = false;
    while (actor != nullptr) {
        if (search->name == actor->name && search->fanbase == actor->fanbase) {
            cout << "NIE\n";
            found = true;
            break;
        }
        actor = actor->next;
    }
    if (!found) {
        add(search);
        cout << "TAK\n";
    }
}

void max_limited(unsigned int limit) {
    unsigned long int max = 0;
    actor* best = nullptr;
    actor* current = head;

    while (current != nullptr) {
        if (current->fanbase <= limit && current->fanbase > max) {
            max = current->fanbase;
            best = current;
        }
        else if (best != nullptr && current->fanbase == max && current->name < best->name) {
            best = current;
        }
        current = current->next;
    }

    if (best != nullptr) {
        cout << best->name << "\n";
        del(best);
    }
    else {
        cout << "NIE\n";
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    unsigned int n;
    string option;
    unsigned long int fanbase;
    cin >> n;
    for (unsigned int i = 0; i < n; i++) {
        cin.ignore();
        getline(cin, option);
        if (option.find("1") != string::npos) {
            actor* actor_new = new actor;
            getline(cin, actor_new->name);
            cin >> actor_new->fanbase;
            search(actor_new);
        }
        else {
            cin >> fanbase;
            if (head != nullptr) {
                max_limited(fanbase);
            }
            else {
                cout << "NIE\n";
            }
        }
    }
}
