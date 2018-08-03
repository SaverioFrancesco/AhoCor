#include <iostream>
#include <vector>

using namespace std;

class KTNode {

public:
    explicit KTNode(char c) {
        this->c = c;
        failure = nullptr;
    }

    ~KTNode() = default;

    void proliferate(string t) {
        if (t.empty()) return;
        for (auto &son : sons) {
            if (t.front() == son->getChar()) {
                son->proliferate(t.substr(1));
                return;
            }
        }
        auto aux = new KTNode(t.front());
        aux->proliferate(t.substr(1));
        sons.push_back(aux);
    }

    char getChar() { return c; }

    const vector<KTNode *> &getSons() const {
        return sons;
    }

private:
    char c;
    KTNode *failure;
    vector<KTNode *> sons;
};

class KeywordTree {

public:
    KeywordTree() {
        root = new KTNode('$');
    };

    ~KeywordTree() = default;

    KTNode *getRoot() const {
        return root;
    }

    void setRoot(KTNode *root) {
        KeywordTree::root = root;
    }

    void insert(string inp) {
        root->proliferate(std::move(inp));
    }

    void comuteFl(){

        auto figli =  root->getSons();

        
    }


private:
    KTNode *root;


};

void serialize(KTNode *root, string *linearized) {
    // Base case
    if (root == nullptr) return;

    // Else, store current node and recur for its children
    *linearized += root->getChar();

    auto sons = root->getSons();
    for (auto &son : sons)
        serialize(son, linearized);

    // Store marker at the end of children
    *linearized += ' ';
}




int main() {
    //string inp;

    //cout << "Inserisci un pattern:" << endl;
    //cin >> inp;

    auto k = new KeywordTree();

    //k->insert(inp);
    k->insert("ansa");
    k->insert("ansia");
    k->insert("melania");
    k->insert("melanoma");

    string a;
    serialize(k->getRoot(), &a);
    cout << a;
    return 0;
}