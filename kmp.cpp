/*
    NLP Assignment
    kmp.cpp
    Purpose: counts the no. of paragraphs in a text file and
    implements dictionary search using KMP algorithm.
    @author Niraj(roll no. 11519), Ridhwan(roll no. 11526)
    @version 2.1.3 6/9/16
    ## the text file should be text.txt
*/
#include <iostream>    //for cin and cout
#include <fstream>    //for file handeling
#include <string>    //to store text file in string format
#include <sstream>    // for splitting line in words
using namespace std;    //makeing it easy to use standard input output

/*
    Constructs an array from substring needed for kmp algorithm.
    @param {string} substr - substring from with lps is to be computed
    @param {integer} substr_length - maximum length of the substring
    @param {integer*} lps - pointer to the array to be created
    Description: given substring to be found,
    lps[i] refers to the length of the longest suffix
    of substring pattern[0,i-1] that matches its prefix.
*/

void get_lps(string substr, int substr_length, int *lps) {
    int len = 0;	//length of longest prefix suffix till now
    int substr_cnt;

    lps[0] = 0;    //because no prefix can exist
    substr_cnt = 1;

    while (substr_cnt < substr_length) {
        if (substr[substr_cnt] == substr[len]) {   //if match increment both
        	len++;
            lps[substr_cnt] = len;
            substr_cnt++;
        } else {
            if (len != 0) {    //if useable prefix exists
            	len = lps[len-1];
        	} else {    //else start from scratch
            	lps[substr_cnt] = 0;
            	substr_cnt++;
            }
       }
    }
}
/*
    Executes kmp search on the text
    @param {string} substr - the substring to be searched
    @param {string} text - the text file from with to search
    @return {integer} word_count - returns total words found
    Description: given a text and substring to be found,
    if the substring is found that word is printed,
    also the word_count is incremented to count total words found
*/
int execute_kmp_search(string substr, string text) {
    int lps[substr.length()];
    int substr_cnt  = 0;
    int word_count = 0;
    get_lps(substr, substr.length(), lps);    //creates lps array

    istringstream splitting(text);    //using sstream for word parsing

    int text_cnt = 0;
    do {
        string word;
        splitting >> word;		// getting the next word in word
        while (text_cnt < word.length()) {
        	if (substr[substr_cnt] == word[text_cnt]) {//increment if match
            	substr_cnt++;
                text_cnt++;
            }

            if (substr_cnt == substr.length()) { //print word if substr match
            	substr_cnt = lps[substr_cnt-1];
	            cout<<word<<endl;
	            word_count++;
	            break;
            } else if (text_cnt < word.length() &&
                    substr[substr_cnt] != word[text_cnt]) {
	            if (substr_cnt != 0) {
	            	substr_cnt = lps[substr_cnt-1];
                } else
	            	text_cnt++;
            }
        }
        text_cnt = 0;
        substr_cnt = 0;
    } while(splitting);
    cout<<endl;
    return word_count;
}


int main() {
	cout<<"The name of file you want to use is file.txt"<<endl;
	cout<<"Make sure the file is in this directory."<<endl;
    ifstream fin("file.txt");

    //will not count first word and last line so initial value is 1
    int line=1;
    int words=1;
    int para=1;
    char ch;    // for searching spaces and /n
    string word;    //
    string text = "";   //for storing whole test file 
    int searched_word_count;    //for counting no of words found
    float probability;  // storing probability
    int gate = 1;   //infinite loop
    while(gate == 1) {
        cout<<endl;
    	cout<<endl;
    	cout<<"Type 1 - find no. of lines, words and ";
    	cout<<"paragraphs in the file"<<endl;
    	cout<<"Type 2 - dictionary search"<<endl;
    	cout<<"Type 3 - probability first do dictionary search and ";
    	cout<<"you will get an option for probaility."<<endl;
    	int input;
    	cin>>input;
    	fin.seekg(0);  //bring file pointer to the start of the file
        while(fin) {
        	fin.get(ch);  //getting character and comparing it to " " and /n
            text += ch;
            if(ch==' ' ||ch=='\n') {
                words++;    //counting no of words
            }
            if(ch == '\n') {
                fin.get(ch);
                if(ch == '\n') {
                    para++;    // counting paras
                    line++;
                }
                line++;    //counting lines
            }
          }
    	switch(input) {
    		case 1:
                cout<<"Lines= "<<line;
                cout<<"\nWords= "<<words;
                cout<<"\nparagraph= "<<para<<endl;
                break;
			case 2:
				cout<<"Enter string to search"<<endl;
    			cin>>word;
    			cout<<endl;
    			//calling kmp search function
    			searched_word_count = execute_kmp_search(word, text);
				break;
            case 3:
				cout<<"Enter string to search"<<endl;
    			cin>>word;
    			cout<<endl;
    			searched_word_count = execute_kmp_search(word, text);
    			//calculating the probability
    			probability = (float)searched_word_count / (float)words;
    			cout<<"The number of words ";
    			cout<<"found: "<<searched_word_count<<endl;
    			cout<< "The Total number of words: "<< words<<endl<<endl;
    			cout<<"The probability of words containing "<<word;
    			cout<<" is - "<<probability<<endl;
    			cout<<endl;
				break;
			default:
				cout<<"INVALID ENTRY"<<endl;
				return 0;
		}
		cout<<"Type 1 to continue"<<endl;
		cout<<"Type 2 to exit"<<endl;
		cin>>gate;
   }
   return 0;
}