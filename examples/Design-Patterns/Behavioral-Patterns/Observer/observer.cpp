#include <vector>
#include <iostream>
#include <string>
#include <mutex> // locking
#include <algorithm> //erase

using namespace std;

template<typename T>
struct Observer {
    virtual void emit( T &src ) = 0;
};

template<typename T>
struct Observable {
public:
    void notify(T& src, bool b) {
        mtx.lock();
        for(auto i : observers) {
            i->emit(src);
        }
        mtx.unlock();
    }
    void subscribe(Observer<T>* o) {
        mtx.lock();
        observers.push_back(o);
        mtx.unlock();
    }
    void unsubscribe(Observer<T>* o) {
        mtx.lock();
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
        mtx.unlock();
    }

private:
    vector<Observer<T>*> observers;
    mutex mtx;
};

/* Implementation with a Switch. Notify an Event on toggle */
struct Switch : Observable<Switch> {
public:
    Switch() {
        state = false;
    }
    void printState() const {
        cout << "State : ";
        state ? cout << "on\n" : cout << "off\n";
    }
    void toggle() {
        state = !state;
        notify(*this, state);
    }

    bool state;
};
/* Handle the incoming Event */
class SwitchObserver : public Observer<Switch> {
    void emit( Switch &src) override {
        src.printState();
    }
};

int main() {
    Switch room, hall, studio;
    SwitchObserver switchObserver;
    room.subscribe(&switchObserver);
    hall.subscribe(&switchObserver);
    studio.subscribe(&switchObserver);

    room.toggle();
    hall.toggle();
    room.toggle();
    room.unsubscribe(&switchObserver);
    room.toggle();
    room.toggle();

    return 0;
}