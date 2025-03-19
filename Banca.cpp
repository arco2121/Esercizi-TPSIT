#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

mutex m;
condition_variable cv;
int saldo = 0;

void aggiungiSoldi(int soldi) {
    this_thread::sleep_for(chrono::seconds(2));
    lock_guard<mutex> lock(m);
    saldo += soldi;
    cout << "Deposito di " << soldi << " effettuato. Nuovo saldo: " << saldo << endl;
    cv.notify_one(); // Notifica il thread che aspetta sul prelievo
}

void prelevaSoldi(int soldi) {
    unique_lock<mutex> lock(m);
    cv.wait(lock, [] { return saldo > 0; }); 
    
    if (saldo >= soldi) {
        saldo -= soldi;
        cout << "Prelievo di " << soldi << " effettuato. Nuovo saldo: " << saldo << endl;
    } else {
        cout << "Saldo insufficiente per prelevare " << soldi << ". Saldo attuale: " << saldo << endl;
    }
}

int main() {
    srand(time(0));
    int deposito = rand() % 500 + 1; 
    int prelievo = rand() % 500 + 1;

    thread t1(prelevaSoldi, prelievo);
    thread t2(aggiungiSoldi, deposito);

    t1.join();
    t2.join();

    return 0;
}
