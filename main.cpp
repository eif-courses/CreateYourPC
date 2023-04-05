#include <iostream>
#include <utility>
#include <vector>
#include <map>

using namespace std;

// https://pcpartpicker.com/products/cpu/

class Component {
public:
    virtual double GetPrice() = 0;
    virtual void GetSpecifications() = 0;
};

class Part : public Component {
private:
    string name;
    double price;
    map<string, string> specifications;
public:
    Part(string name, double price) : name(std::move(name)), price(price) {}

    double GetPrice() override {
        return price;
    }

    void AddSpecifications(map<string, string> specs) {
        specifications = std::move(specs);
    }

    void AddSpecification(const string &tag, string value) {
        specifications[tag] = std::move(value);
    }

    void GetSpecifications() override {
        cout << "---------------------------------------" << endl;
        cout << name << endl;
        cout << "---------------------------------------" << endl;
        cout << "Price: " << price << "$" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Specifications" << endl;
        cout << "---------------------------------------" << endl;
        for (const auto &spec: specifications) {
            cout << spec.first << ": " << spec.second << endl;
        }
    }

};

class PartsCategory : public Component {
private:
    string name;
    vector<Component*> parts;
public:
    explicit PartsCategory(string name) : name(std::move(name)) {}

    void Add(Component *component) {
        parts.emplace_back(component);
    }

    double GetPrice() override {
        double total = 0;
        for (Component* comp: parts) {
            total += comp->GetPrice();
        }
        return total;
    }

    void GetSpecifications() override {
        cout << "____________________________________________" << endl;
        cout << "_______________" << name << "_______________" << endl;
        cout << "____________________________________________" << endl;
        for (Component* comp: parts) {
            comp->GetSpecifications();
        }
        cout << "____________________________________________" << endl;
        cout << "Total price: " << GetPrice() << endl;
        cout << "____________________________________________" << endl;
    }
};


int main() {

    auto *computer = new PartsCategory("Computer");
    auto *board = new PartsCategory("Motherboard");
    auto *peripherals = new PartsCategory("Peripherals");

    Part *RAM = new Part("Corsair Vengeance LPX 16 GB", 42.99);

    RAM->AddSpecification("Speed", "DDR4-3200");
    RAM->AddSpecification("Modules", "2 x 8GB");
    RAM->AddSpecification("Cas Latency", "16");

    Part *GPU = new Part("MSI GeForce RTX 3060 Ventus 2X 12G", 339.99);
    Part *motherboard = new Part("Asus TUF GAMING X570-PLUS (WI-FI)", 209.99);

    board->Add(RAM);
    board->Add(GPU);
    board->Add(motherboard);


    computer->Add(board);
    computer->Add(peripherals);

    board->GetSpecifications();



    return 0;
}
