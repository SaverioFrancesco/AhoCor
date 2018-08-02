#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;

class KTNode {

    friend ostream &operator<<(ostream &, const KTNode &);

public:


    KTNode(char c) {
        this->c = c;
        this->sons.clear();
    };

    ~KTNode() = default;

    void proliferate(string t) {
        cout << "proliferate\n";
        for (auto &son : sons) {

            if (t.front() == son.getChar()) {

                cout << "uuu\n";
                son.proliferate(t.substr(1));
                return;
            }
        }
        auto aux = new KTNode(t.front());
        sons.push_back(*aux);
        aux->proliferate(t.substr(1));
        cout << "aa\n";
    }

    char getChar() { return c; }

    void print() {
        for (auto &son : sons) {
            cout << c;
            son.print();
        }
        if (sons.empty()) cout << c << endl;
    }

private:
    char c;
    std::vector<struct KTNode> sons;

};


ostream &operator<<(ostream &os, const KTNode &in) {

    return os << "ciao";
}

class KeywordTree {
    friend ostream &operator<<(ostream &, const KeywordTree &);

public:


    KeywordTree() {
        root = new KTNode('$');


    };

    ~KeywordTree() = default;

private:
    KTNode *root;
public:
    KTNode *getRoot() const {
        return root;
    }

    void setRoot(KTNode *root) {
        KeywordTree::root = root;
    }

};

ostream &operator<<(ostream &os, const KeywordTree &in) {

    return os << endl;
}

void insertKT(KeywordTree *k, string inp) {

    k->getRoot()->proliferate(std::move(inp));

}


int main() {

    string inp;

    cin >> inp;

    cout << inp.substr(1);


    auto k = new KeywordTree();

    insertKT(k, inp);

    //k->getRoot()->print();

    cout << inp.substr(1);

    return 0;
}