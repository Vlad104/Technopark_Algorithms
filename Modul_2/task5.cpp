#include "Huffman.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <queue>


void Encode(IInputStream& original, IOutputStream& compressed) {
    std::string input;
    char byte = 0;
    while (original.Read(byte)) {
    	input += byte;
    }

    std::unordered_map<std::string, int> haf_freq;    
    auto cmp = [] ( std::pair<std::string, int> A, std::pair<std::string, int> B) { return A.second > B.second; };

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(cmp)> q(cmp);

    for (auto c_char : input) {
		std::string c(1, c_char);
        if ( haf_freq.find(c) == haf_freq.end() ) {
            haf_freq[c] = 1;    
        }
        else {
            haf_freq[c] += 1;    
        }
    }
    int k = haf_freq.size();

    for ( auto p : haf_freq ) {
        q.push(p);    
    }    
    std::map <char, std::string> haf_dict;
  	
	if ( k == 1) {
		haf_dict[input[0]] = "0";
	} 
	else {	
		while (q.size() > 1) {
			auto qq1 = q.top();
			q.pop();
			auto qq2 = q.top();
			q.pop();
			
			for ( auto c : qq1.first ) {
				haf_dict[c] = "0" + haf_dict[c];
			}    		
			for ( auto c : qq2.first ) {
				haf_dict[c] = "1" + haf_dict[c];
			}   
			
			qq2.first  = qq1.first  + qq2.first;
			qq2.second = qq1.second + qq2.second;
			q.push(qq2);
		}
	}
    std::string encoded;
    for ( auto c : input ) {
        encoded += haf_dict[c];
    }

    char empty_bits = encoded.size() % 8;
    compressed.Write(empty_bits);
    char alphabet_size = haf_dict.size();
    compressed.Write(alphabet_size);
    for (auto it = haf_dict.begin(); it != haf_dict.end(); it++) {
    	char symbol = it->first;
    	compressed.Write(symbol);
    	std::string code = it->second;
    	char temp = 0;
    	for (int j = 0; j < code.size(); j++) {
    		if (code == '1') {
    			temp |= 1 << (7-j);   			
    		}
    	}
    	compressed.Write(temp);
    }
    for (auto symbol : encoded) {
    	char temp = 0;
    	for (int i = 0; i < 8; i++) {
    		if (symbol == '1') {
    			temp |= 1 << (7 - i);
    		}
    	}
    	compressed.Write(temp);
    }
    for (int i = 0; i < empty_bits; i++) {
    	compressed.Write(0);
    }

}


void Decode(IInputStream& compressed, IOutputStream& original) {
    char empty_bits = 0;
    compressed.Read(empty_bits);
    char alphabet_size = 0;
    compressed.Read(alphabet_size);   
    
    std::unordered_map<char, std::string> haf;    
    std::unordered_map<std::string, char> rhaf;
    for (int i = 0; i < alphabet_size; i++) {
    	char symbol = 0;
    	compressed.Read(symbol); 
    	char temp = 0;
    	compressed.Read(temp); 
    	std::string code;
    	for (int j = 0; j < 8; j++) {
    		if (1 & (temp >> (7 - j))) {
    			code += "1";
    		}
    		else {
    			code += "0";
    		}
    	}
    	haf[symbol] = code;
    	rhaf[code] = symbol;
    }
    std::vector<char> bits;
    char ff = 0;
    while(compressed.Read(ff)) {
    	bytes.push_back(ff);
    }
    std::string dec_str;
    for (int i = 0; i < bytes.size() - empty_bits; i++) {
    	char sym = 0;
    	for (int j = 0; j < 8; j++) {
    		sym |= (1 & (bytes[i] >> (7 - j))) << (7 - j);
    	}
    	dec_str += sym;
    }

    std::string res_str;
    
    int pos = 0;
    while ( pos < len ) {
        int ofset = 1;
        while (1 == 1) {
            std::string buf = dec_str.substr(pos, ofset);
            if (rhaf.find(buf) == rhaf.end()) {
                ofset++;
            }
            else {
                pos += buf.size();
                res_str += rhaf[buf];
                break;
            }
        }
    }
    
    for (auto sym : res_str) {
    	original.Write(sym);
    }
}
