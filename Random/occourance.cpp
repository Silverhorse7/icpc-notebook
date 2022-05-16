unordered_map<int, vector<int> > store;
 
int occourance(int element, int left, int right) {
    int a = lower_bound(store[element].begin(),
                        store[element].end(),
                        left)
            - store[element].begin();
    int b = upper_bound(store[element].begin(),
                        store[element].end(),
                        right)
            - store[element].begin();
 
    return b - a;
}
