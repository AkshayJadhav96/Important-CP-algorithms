#include<bits/stdc++.h>
using namespace std;

class TrieNode{
public:
    TrieNode* links[26];
    bool flag = false;
    
    bool containsKey(char ch){
        return links[ch-'a'] != NULL;
    }

    void put(char ch,TrieNode* node){
        links[ch-'a'] = node;
    }

    TrieNode* get(char ch){
        return links[ch-'a'];
    }

    void setEnd(){
        flag = true;
    }

    void revokeEnd(){
        flag = false;
    }

    bool isEnd(){
        return flag;
    }

    
};

class Trie{
public:
    TrieNode* root;
    
    Trie(){
        root = new TrieNode();
    }

    ~Trie() {
        deleteTrie(root);
    }

    void deleteTrie(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 26; i++) {
            deleteTrie(node->links[i]);
        }
        delete node;
    }

    void insert(string word){
        TrieNode* node = root;
        for(int i = 0;i<word.length();i++){
            if(!node->containsKey(word[i])){
                node->put(word[i],new TrieNode());
            }
            node = node->get(word[i]);
        }
        node->setEnd();
    }

    bool search(string word){
        TrieNode* node = root;
        for(int i = 0;i<word.length();i++){
            if(!node->containsKey(word[i])) return false;
            node = node->get(word[i]);
        }
        return node->isEnd();
    }

    bool startsWith(string prefix){
        TrieNode* node = root;
        for(int i = 0;i<prefix.length();i++){
            if(!node->containsKey(prefix[i])) return false;
            node = node->get(prefix[i]);
        }
        return true;
    }

    void remove(string word){
        if(!this->search(word)) return;
        TrieNode* node = root;
        for(int i = 0;i<word.length();i++){
            node = node->get(word[i]);
        }
        node->revokeEnd();
    }
};

int main(){
    Trie* obj = new Trie();
    obj->insert("apple");
    obj->insert("banana");
    obj->insert("bananas");
    obj->insert("banner");
    obj->insert("appear");
    cout<<obj->search("banner")<<endl;
    cout<<obj->startsWith("bann")<<endl;
    cout<<obj->search("banana")<<endl;
    obj->remove("banana");
    cout<<obj->search("banana")<<endl;
}
