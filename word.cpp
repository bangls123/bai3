#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void visit(vector<vector<int> > & graph, vector<bool>& marked, int i,int& count) {
    if (marked[i]) return;
    marked[i] = true;
    ++count;
    for (int j = 0; j < graph[i].size(); ++j) {
        visit(graph, marked, graph[i][j], count);
    }

}

bool isConnected(string a, string b) {
    if (a.length() != b.length()) return false;
    int diff = 0;
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] != b[i]) ++diff;
    }
    if (diff == 1) return true;
    return false;
}

int main() {
    ifstream file;
    file.open("sgb-words.txt");
    vector<string> words(0);
    string s;
    while(file >> s) {
        words.push_back(s);
    }

    vector<bool> marked(words.size());
    int components = 0;

    vector<vector<int> > graph(words.size());

    for (int i = 0; i < words.size(); ++i) {
        for (int j = 0; j < words.size(); ++j) {
            if (isConnected(words[i], words[j]) && i != j) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    int count = 0, i = 0;
    while (count < words.size()) {
        if (!marked[i]) {
            ++components;
            visit(graph, marked, i, count);
        }
        else {
            ++i;
        }
    }
    cout << "thanh phan lien thong: " << components;
    file.close();
}

