struct Trie {
    int cnt = 0;
    Trie *ptr[27] ;

    Trie() {
        for(int i=0; i<26; i++) {
            ptr[i] = NULL ;
        }
    }
} *root;

void Insert(string &s) {
    Trie *cur = root ;
    for(auto &i : s) {
        int ch = i - 'a' ;
        if(cur->ptr[ch] == NULL)
            cur->ptr[ch] = new Trie();

        cur = cur->ptr[ch] ;
        cur->cnt++ ;
    }
}

int Search(string &s) {
    Trie *cur = root ;
    for(auto &i : s) {
        int ch = i - 'a' ;
        if(cur->ptr[ch] == NULL)
            return 0;

        cur = cur->ptr[ch] ;
    }
    return cur->cnt;
}
int main() {
    root = new Trie() ;
    
}
Footer
