#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<string>
#include<sstream>
#include<stack>
#include"b2/ch8/heap.h"

typedef std::tuple<std::string, int> af_pair; // tuple of <alphabet, frequency>
typedef std::tuple<int, af_pair*> heapnode; // tuple of <freq, <alphabet, freq>> where freq is the same
typedef std::tuple<std::string, std::string> encode_map; // tuple of <alphabet, encoding>

std::string groupAlphabets(af_pair a, af_pair b) {
    std::string str_a = std::get<0>(a);
    std::string str_b = std::get<0>(b);
    if(str_a.length() <= str_b.length()) {
        return ('(' + str_a + ',' + str_b + ')');
    } else {
        return ('(' + str_b + ',' + str_a + ')');
    }
}

void printEncodingList(std::vector<encode_map>& map) {
    for(encode_map& e : map) {
        std::string a = std::get<0>(e);
        std::string encoding = std::get<1>(e);
        std::cout << "(" << a << ", " << encoding << ")" << '\n'; 
    }
}

heapnode _combine(heapnode& a, heapnode& b) {
    int newFreq = std::get<0>(a) + std::get<0>(b);
    af_pair* tup_a = std::get<1>(a);
    af_pair* tup_b = std::get<1>(b);
    af_pair* newPair = new af_pair(groupAlphabets(*tup_a,*tup_b), newFreq);
    delete tup_a;
    delete tup_b;
    return std::make_tuple(newFreq, newPair);
}

std::vector<encode_map>* _encodeAlphabet(const std::string& tree) {
    // ex. ((a,b),((f,c),(d,e)))
    // every '(' adds 0, ',' replaces last with 1
    if(tree.empty()) { return NULL; }
    std::vector<encode_map>* map = new std::vector<encode_map>();
    int stack = 0;
    std::string currentEncoding = "";

    for(int i = 0; i < tree.length(); i++) {
        const char& c = tree[i];
        switch(c) {
            case '(':
                currentEncoding += '0';
                stack++;
                break;
            case ',':
                currentEncoding.replace(stack-1, 1,"1");
                break;
            case ')':
                currentEncoding.erase(currentEncoding.size()-1);
                stack--;
                break;
            default:
                if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) 
                    map->push_back(std::make_tuple(std::string() + c, currentEncoding));
                break;
        }

    }

    return map;
}

// creates a "tree" of encodings based on alphabet & their frequencies
// 'hack' using heap.h that only allows integer keys... (frequencies is then ints in '% form')
std::vector<encode_map>* huffmanEncoding(std::vector<std::string> alphabet, std::vector<int> frequencies) {
    if((alphabet.size() != frequencies.size()) || alphabet.size() == 0) { return NULL; }
    Heap<af_pair*> pairs{};
    // "heapify"
    for(int i = 0; i < alphabet.size(); i++) {
        pairs.insert(frequencies[i], new af_pair(alphabet[i], frequencies[i]));
    }
    heapnode pop; // guaranteed to exist
    while(!pairs.isEmpty()) {
        pop = pairs.extractTop();
        if(pairs.isEmpty()) { break; }
        heapnode combinePair = pairs.extractTop();
        pairs.insert(_combine(pop, combinePair));
    }
    // pop is the final tuple that contains the tree
    af_pair* final_pair = std::get<1>(pop);
    std::string treestr = std::get<0>(*final_pair);
    delete final_pair;
    return _encodeAlphabet(treestr);
}

int main(int argc, char** argv) {
    std::vector<std::string> alphabet = {
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
    };
    std::vector<int> frequencies = {
        30,
        20,
        10,
        5,
        7,
        28,
    };

    std::vector<encode_map>* encodingList = huffmanEncoding(alphabet, frequencies);
    printEncodingList(*encodingList);
    delete encodingList;
    return 0;
}