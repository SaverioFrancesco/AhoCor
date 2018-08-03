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

        if(t.empty()) return;

        bool beenPut=false;
        //cout << "(proliferate\n";
        for (auto &son : sons) {

           // cout << "ho gia figli\n";
            if (t.front() == son->getChar()) {
                son->proliferate(t.substr(1));
                beenPut=true;
            }
        }
        if(!beenPut) {
           // cout << "non ho figli con questo carattere\n";
            auto aux = new KTNode(t.front());
            sons.push_back(aux);
            aux->proliferate(t.substr(1));
        }
       // cout << ")\n";
    }

    char getChar() { return c; }

    void print(){

        for (auto &son : sons) {
            cout << c;
            son->print();
            //cout << endl;
        }
        if(sons.size()==0){
            cout<<c;
        }


    }

private:
    char c;
    std::vector<struct KTNode*> sons;

};


ostream &operator<<(ostream &os, const KTNode &in) {

    return os << in.c ;
}

class KeywordTree {
    friend ostream &operator<<(ostream &, const KeywordTree &);

public:


    KeywordTree() {
        root = new KTNode('$');
        nome="ROOT";
    };

    ~KeywordTree() = default;

public:
    KTNode *root;
    string nome;
public:
    string getNome(){return nome;}
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

    k->root->proliferate(std::move(inp));

}




int main() {



    KeywordTree* k = new KeywordTree();

    insertKT(k, "carola");

    insertKT(k, "carel");


    k->getRoot()->print();

    return 0;
}