#include <iostream>
#include <fstream>
using namespace std;
 
int main()
{
 ifstream fin("file.txt"); //opening text file
 int line=1,word=1,para=1,size; //will not count first word and last line so initial value is 1
 char ch;

 fin.seekg(0,ios::beg); //bring position of file pointer to begining of file
 
 while(fin)
 {
  fin.get(ch);

  	if(ch==' ' ||ch=='\n')
  		word++;
  	if(ch=='\n'){
  		fin.get(ch);
  		if(ch=='\n'){
  			para++;
  			line++;
  		}
  		line++;
  	}
  	
  }
 cout<<"Lines="<<line<<"\nWords="<<word<<"\n"<<"paragraph="<<para<<endl;
 fin.close(); //closing file
 
 return 0;
 
}