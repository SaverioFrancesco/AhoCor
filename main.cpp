#include <iostream>
#include <vector>
#include <set>
#include <deque>

using namespace std;

int idGen = 0;

class KTNode {

public:

    int id;

    KTNode(char c, int _id) {
        this->c = c;
        failure = nullptr;
        id = _id;
    }

    ~KTNode() = default;

    void setId(int _id) { id = _id; };


    void proliferate(string t) {
        if (t.empty()) return;
        for (auto &son : sons) {
            if (t.front() == son->getChar()) {
                son->proliferate(t.substr(1));
                return;
            }
        }
        auto aux = new KTNode(t.front(), idGen++);
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

        //    cout << "start commpute fl on " << this->id << endl;
        set<KTNode *> nodes;
        for (auto &son:sons)
            nodes.insert(son);
        int x = 0;

        //    cout << "sons:" << endl;
        // for (auto &son:nodes) { cout << son->id << endl; };

        KTNode *currentFL = failure;

        while (!nodes.empty()) {
            set<KTNode *> tbd;
            for (auto &node : nodes) {
                if (currentFL == currentFL->getFailure() && x > 0) { // sono alla radice
                    node->setFailure(currentFL);
                    //nodes.erase(node);
                    tbd.insert(node);
                    continue;
                }
                for (auto &sof:currentFL->getSons()) {
                    if (sof->getChar() == node->getChar() && node->id != sof->id) {
                        node->setFailure(sof);
                        //nodes.erase(node);
                        tbd.insert(node);
                    }
                }
            }
            for (auto &el:tbd) {
                //    cout << "delete " << el->id << endl;
                nodes.erase(el);
            }
            currentFL = currentFL->getFailure();
            x++;

            //for (auto &son:nodes) { cout << "alla fine" << son->id << endl << "........" << endl; };

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
        root = new KTNode('$', idGen++);
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
        deque<KTNode *> q;
        q.push_back(root);
        //for (auto &n : q) { cout << n->getChar() << "," << n->id << endl; }

        while (!q.empty()) {
            KTNode *cur = q.front();
            cur->computeFL();
            for (auto &son:cur->getSons()) {
                q.push_back(son);
            }
            q.pop_front();

            //for (auto &n : q) { cout << n->getChar() << "," << n->id << endl;}
            //cout << "---" << endl;
        }

    }

    void printFL() {
        deque<KTNode *> q;

        q.push_back(root);

        while (!q.empty()) {
            KTNode *cur = q.front();
            KTNode *fl = cur->getFailure();
            //cout << "FL di " << cur->getChar() << "," << cur->id << " è " << fl->getChar() << "," << fl->id << endl;
            for (auto &son:cur->getSons()) {
                q.push_back(son);
            }
            q.pop_front();
        }

    }

    void printPaths(KTNode *n) {

        cout << n->getChar() << "," << n->id << endl;

        cout << n->getFailure()->getChar() << "," << n->getFailure()->id << endl;
        for (auto &son : n->getSons()) {
            cout << "(" << n->getChar() << "," << n->id << ")  -sons->" << son->getChar() << "," << son->id << endl;
        }

        for (auto &son : n->getSons()) { printPaths(son); }
        cout << "--\n";

    }


private:
    KTNode *root;

};


int main() {
    //string inp;

    //cout << "Inserisci un pattern:" << endl;
    //cin >> inp;

    auto k = new KeywordTree();

    //k->insert(inp);
    k->insert("ababa");
    k->insert("abaababa");
    k->insert("cdfababa");

    k->computeFL();

    //k->printFL();

    //k->printPaths(k->getRoot());


    return 0;
}