#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;

void computeLPSArray(string pat, int M, int *lps)
{
    int len = 0;
    int i;

    lps[0] = 0;
    i = 1;

    // the loop calculates lps[i] for i = 1 to M-1
    while (i < M)
    {
       if (pat[i] == pat[len])
       {
         len++;
         lps[i] = len;
         i++;
       }
       else // (pat[i] != pat[len])
       {
         if (len != 0)
         {
           // This is tricky. Consider the example
           // AAACAAAA and i = 7.
           len = lps[len-1];

           // Also, note that we do not increment i here
         }
         else // if (len == 0)
         {
           lps[i] = 0;
           i++;
         }
       }
    }
    /*
    for (int i = 0; i < 7; i++) {
        cout<<lps[i]<<" ";
    }
    */
}

int KMPSearch(string pat, string txt)
{
    int M = pat.length();
    int N = txt.length();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];
    int j  = 0;  // index for pat[]
    int counter = 0;
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    istringstream splitting(txt);

    int i = 0;
    do {
        string word;
        splitting >> word;
        while (i < word.length())
        {
          if (pat[j] == word[i])
          {
            j++;
            i++;
          }

          if (j == M)
          {
            j = lps[j-1];
            cout<<word<<endl;
            counter++;
            break;
          }

          // mismatch after j matches
          else if (i < N && pat[j] != word[i])
          {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
             j = lps[j-1];
            else
             i++;
          }
        }
        i = 0;
        j = 0;
        //cout<<word<<endl;
    }while(splitting);
    cout<<endl;
    return counter;
}


int main()
{
    /*
   string txt = "ABAB DA BA CDAB ABC ABAB";
   //char *pat = "ABCABAB";
   string pat = "AB";
    */
   ifstream fin("text.txt");


    int line=1,words=1,para=1; //will not count first word and last line so initial value is 1
    char ch;
   string word;
   string text = "";
   char temp;
   int searched_word_count;
   float probability;
   int gate = 1;
   while(gate == 1){
        cout<<endl;
    	cout<<endl;
    	cout<<"Type 1 - find no. of lines, words and paragraphs in the file"<<endl;
    	cout<<"Type 2 - dictionary search"<<endl;
    	cout<<"Type 3 - probability first do dictionary search and you will get an option for probaility."<<endl;
    	int input;
    	cin>>input;
    	fin.seekg(0);
         while(fin)
         {
          fin.get(ch);
            text += ch;
            if(ch==' ' ||ch=='\n'){
                words++;
            }
            if(ch=='\n'){
                fin.get(ch);
                if(ch=='\n'){
                    para++;
                    line++;
                }
                line++;
            }

          }
    	switch(input){
    		case 1:
                 cout<<"Lines="<<line<<"\nWords="<<words<<"\n"<<"paragraph="<<para<<endl;
                break;
			case 2:
				cout<<"Enter string to search"<<endl;
    			cin>>word;
    			cout<<endl;
    			searched_word_count = KMPSearch(word, text);
				break;
            case 3:
				cout<<"Enter string to search"<<endl;
    			cin>>word;
    			cout<<endl;

    			searched_word_count = KMPSearch(word, text);
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
