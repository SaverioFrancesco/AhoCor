#include <iostream>
#include <vector>
#include <set>
#include <queue>

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

    KTNode *getFailure() const {
        return failure;
    }

    void setFailure(KTNode *fl) {
        this->failure = fl;
    }

    void computeFL() {
        set<KTNode *> nodes;
        for (auto &son:sons)
            nodes.insert(son);
        int x=0;

        KTNode *currentFL = failure;

        while (!nodes.empty()) {
            set<KTNode *> tbd;
            for (auto &node : nodes) {
                if(currentFL==currentFL->getFailure() && x>0){ // sono alla radice
                    node->setFailure(currentFL);
                    //nodes.erase(node);
                    tbd.insert(node);
                    continue;
                }
                for (auto &sof:currentFL->getSons()) {
                    if (sof->getChar() == node->getChar()) {
                        node->setFailure(sof);
                        //nodes.erase(node);
                        tbd.insert(node);
                    }
                }
            }
            for(auto &el:tbd){
                nodes.erase(el);
            }
            currentFL = currentFL->getFailure();
            x++;
        }
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
        root->setFailure(root);
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

    void computeFL() {
        queue<KTNode *> q;

        q.push(root);

        while (!q.empty()) {
            KTNode *cur = q.front();
            cur->computeFL();
            for (auto &son:cur->getSons()) {
                q.push(son);
            }
            q.pop();
        }
    }

    void printFL() {
        queue<KTNode *> q;

        q.push(root);

        while (!q.empty()) {
            KTNode *cur = q.front();
            KTNode *fl = cur->getFailure();
            cout << "FL di " << cur->getChar() << " è " << fl->getChar() << endl;
            for (auto &son:cur->getSons()) {
                q.push(son);
            }
            q.pop();
        }

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
    k->insert("abc");
    k->insert("cab");

    k->computeFL();

    k->printFL();

    string a;
    serialize(k->getRoot(), &a);
    cout << a;
    return 0;
}