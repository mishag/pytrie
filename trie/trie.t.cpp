#include <trie.h>

#include <memory>

struct X {
    int x;
};


int main(int argc, char * argv[])
{
    TrieMap<X> trie;

    std::shared_ptr<X> ptr(new X());

    trie.insert("abc", ptr);

    return 0;
}
