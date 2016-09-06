#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;

void get_lps(string substr, int substr_length, int *lps) {
    int len = 0;
    int index;

    lps[0] = 0;
    index = 1;

    while (index < substr_length) {
        if (substr[index] == substr[len]) {
        	len++;
            lps[index] = len;
            index++;
        }
        else {
        	if (len != 0) {
            	len = lps[len-1];
        	}
        	else {
            	lps[i] = 0;
            	index++;
            }
       }
    }
}

int execute_kmp_search(string substr, string text) {
    int lps[substr.length()];
    int substr_index  = 0;
    int counter = 0;
    get_lps(substr, substr.length(), lps);

    istringstream splitting(text);

    int text_index = 0;
    do {
        string word;
        splitting >> word;
        while (text_index < word.length()) {
        	if (substr[substr_index] == word[text_index]) {
            	substr_index++;
                text_index++;
            }

            if (substr_index == word.length()) {
            	substr_index = lps[substr_index-1];
	            cout<<word<<endl;
	            counter++;
	            break;
            }

            else if (text_index < word.length() && substr[substr_index] != word[text_index]) {
	            if (substr_index != 0)
	            	substr_index = lps[substr_index-1];
	            else
	            	text_index++;
            }
        }
        text_index = 0;
        substr_index = 0;
    } while(splitting);
    cout<<endl;
    return counter;
}


int main() {
    ifstream fin("text.txt");

    int line=1,words=1,para=1; //will not count first word and last line so initial value is 1
    char ch;
    string word;
    string text = "";
    int searched_word_count;
    float probability;
    int gate = 1;
    while(gate == 1) {
        cout<<endl;
    	cout<<endl;
    	cout<<"Type 1 - find no. of lines, words and paragraphs in the file"<<endl;
    	cout<<"Type 2 - dictionary search"<<endl;
    	cout<<"Type 3 - probability first do dictionary search and you will get an option for probaility."<<endl;
    	int input;
    	cin>>input;
    	fin.seekg(0);
        while(fin) {
        	fin.get(ch);
            text += ch;
            if(ch==' ' ||ch=='\n') {
                words++;
            }
            if(ch == '\n') {
                fin.get(ch);
                if(ch == '\n') {
                    para++;
                    line++;
                }
                line++;
            }
          }
    	switch(input) {
    		case 1:
                cout<<"Lines="<<line<<"\nWords="<<words<<"\n"<<"paragraph="<<para<<endl;
                break;
			case 2:
				cout<<"Enter string to search"<<endl;
    			cin>>word;
    			cout<<endl;
    			searched_word_count = execute_kmp_search(word, text);
				break;
            case 3:
				cout<<"Enter string to search"<<endl;
    			cin>>word;
    			cout<<endl;
    			searched_word_count = execute_kmp_search(word, text);
    			probability = (float)searched_word_count / (float)words;
    			cout<<"The number of words found: "<<searched_word_count<<endl;
    			cout<< "The Total number of words: "<< words<<endl<<endl;
    			cout<<"The probability of words containing "<<word<<" is - "<<probability<<endl;
    			cout<<endl;
				break;
			default:
				cout<<"INVALID ENTRY"<<endl;
				exit(0);
		}
		cout<<"Type 1 to continue"<<endl;
		cout<<"Type 2 to exit"<<endl;
		cin>>gate;
   }
   return 0;
}
