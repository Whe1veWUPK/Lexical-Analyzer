#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
//hash map that stored the keywords
std::unordered_map<std::string, std::string> keyWords;

// the declaration of the functions
void initialKeyWords();
char onStatus1(std::fstream *ifs,std::fstream *ofs,char ch);
char onStatus2(std::fstream *ifs,std::fstream *ofs, char ch);
char onStatus3(std::fstream *ifs,std::fstream *ofs, char ch, std::string word);
char onStatus4(std::fstream *ifs,std::fstream *ofs, char ch);
char onStatus5(std::fstream *ifs,std::fstream *ofs, char ch, std::string word);
char onStatus6(std::fstream *ifs,std::fstream *ofs,char ch);
char onStatus7(std::fstream *ifs, std::fstream *ofs, char ch);
char onStatus8(std::fstream *ifs, std::fstream *ofs, char value, char ch);
char onStatus9(std::fstream *ifs, std::fstream *ofs, char ch);
char onStatus10(std::fstream *ifs, std::fstream *ofs, std::string word, char ch);
// initial the keywords
void initialKeyWords(){
    //keywords
    keyWords.insert(std::pair<std::string, std::string>("main", "MAIN"));
    keyWords.insert(std::pair<std::string, std::string>("if", "IF"));
    keyWords.insert(std::pair<std::string, std::string>("then", "THEN"));
    keyWords.insert(std::pair<std::string, std::string>("while", "WHILE"));
    keyWords.insert(std::pair<std::string, std::string>("do", "DO"));
    keyWords.insert(std::pair<std::string, std::string>("static", "STATIC"));
    keyWords.insert(std::pair<std::string, std::string>("int", "INT"));
    keyWords.insert(std::pair<std::string, std::string>("double", "DOUBLE"));
    keyWords.insert(std::pair<std::string, std::string>("struct", "STRUCT"));
    keyWords.insert(std::pair<std::string, std::string>("break", "BREAK"));
    keyWords.insert(std::pair<std::string, std::string>("else", "ELSE"));
    keyWords.insert(std::pair<std::string, std::string>("long", "LONG"));
    keyWords.insert(std::pair<std::string, std::string>("switch", "SWITCH"));
    keyWords.insert(std::pair<std::string, std::string>("case", "CASE"));
    keyWords.insert(std::pair<std::string, std::string>("typedef", "TYPEDEF"));
    keyWords.insert(std::pair<std::string, std::string>("char", "CHAR"));
    keyWords.insert(std::pair<std::string, std::string>("return", "RETURN"));
    keyWords.insert(std::pair<std::string, std::string>("const", "CONST"));
    keyWords.insert(std::pair<std::string, std::string>("float", "FLOAT"));
    keyWords.insert(std::pair<std::string, std::string>("short", "SHORT"));
    keyWords.insert(std::pair<std::string, std::string>("continue", "CONTINUE"));
    keyWords.insert(std::pair<std::string, std::string>("for", "FOR"));
    keyWords.insert(std::pair<std::string, std::string>("void", "VOID"));
    keyWords.insert(std::pair<std::string, std::string>("default", "DEFAULT"));
    keyWords.insert(std::pair<std::string, std::string>("sizeof", "SIZEOF"));
 
    
    //relation operator and operator
    keyWords.insert(std::pair<std::string, std::string>("<", "LT"));
    keyWords.insert(std::pair<std::string, std::string>(">", "GT"));
    keyWords.insert(std::pair<std::string, std::string>("==", "EQ"));
    keyWords.insert(std::pair<std::string, std::string>(">=", "GTE"));
    keyWords.insert(std::pair<std::string, std::string>("<=", "LTE"));
    keyWords.insert(std::pair<std::string, std::string>("!=", "NEQ"));
    keyWords.insert(std::pair<std::string, std::string>("+", "PLUS"));
    keyWords.insert(std::pair<std::string, std::string>("-", "MINUS"));
    keyWords.insert(std::pair<std::string, std::string>("*", "MULTIPLY"));
    keyWords.insert(std::pair<std::string, std::string>("/", "DIVIDE"));
    keyWords.insert(std::pair<std::string, std::string>("%", "MOD"));
    keyWords.insert(std::pair<std::string, std::string>("=", "ASSIGN"));
    

    //other characters
    keyWords.insert(std::pair<std::string, std::string>("#", "PREPREOCESS DIRECTIVE"));
    keyWords.insert(std::pair<std::string, std::string>(";", "DELIMITER"));
}

// detect if the character is a letter (includes '_') 
bool isLetter(char ch){
    if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')|| (ch=='_')){
        return true;
    }
    else{
        return false;
    }
}

// detect if the charactr is a digit 
bool isDigit(char ch){
    if((ch >= '0'&& ch <= '9')){
        return true;
    }
    else{
        return false;
    }
}

//detect if the ID is the keyword
bool isKeyWord(std::string word){
    if(keyWords.count(word)==0){
        return false;
    }
    else{
        return true;
    }
}

//detect if the character is the first charcter of the operator
bool isOperator(char ch){

    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '=' || ch == '!' || ch == '>' || ch == '<' || ch == ';'||ch=='#'){
        return true;
    }
    else{
        return false;
    }
}

// on status1 
char onStatus1(std::fstream*ifs,std::fstream *ofs, char ch){
    std::string word;  //store the ID or key word
    
    if (!ifs->eof()){
       while((!(ifs->eof()))&&(isDigit(ch)||isLetter(ch))){
           word.push_back(ch);
           ch = ifs->get();
       }
       //return from status 1
       //is keyword
       if(isKeyWord(word)){
           std::unordered_map<std::string, std::string>::iterator iter;
           iter = keyWords.find(word);
           *ofs<<  iter->second + "\t" + word<< "\n";
           if(ifs->eof()){
               return EOF;
           }
           return ch;
       }
       else{
           *ofs << "ID\t" + word << "\n";
           if(ifs->eof()){
               return EOF;
           }
           return ch;
       }
    }
    else{
       // the file is over
       *ofs << "ID\t" + word << "\n";
       if(ifs->eof()){
           return EOF;
       }
       return ch;
    }
}


// on status 2
char onStatus2(std::fstream*ifs,std::fstream*ofs,char ch){
    std::string word; //store the number
    if(!ifs->eof()){
         while(!(ifs->eof())&&(isDigit(ch))){
             word.push_back(ch);
             ch = ifs->get();
         }
         if(ifs->eof()){
            //the file is over
            *ofs<< "NUM\t" + word  << "\n";
            return EOF;
         }
         else{
            if(ch == '.'){
                //will go to status 3
                word.push_back(ch);
                ch = ifs->get();
                return onStatus3(ifs, ofs,ch, word);
            }
            else{
                //the num is over
                *ofs << "NUM\t" + word  << "\n";
                return ch;
            }
         }
    }
    else{
        // the file is over
       *ofs<< "NUM\t" + word << "\n";
       return EOF;
    }
}

// on status 3
char onStatus3(std::fstream*ifs,std::fstream*ofs,char ch,std::string word){
    if(!ifs->eof()){
         while(!(ifs->eof())&&(isDigit(ch))){
             word.push_back(ch);
             ch = ifs->get();
         }
         if(ifs->eof()){
            //the file is over
            *ofs << "NUM\t" + word << "\n";
            return EOF;
         }
         else{
            *ofs << "NUM\t" + word  << "\n";
            return ch;
         }
    }
    else{
       //the file is over

       *ofs << "NUM\t" + word  << "\n";
       return EOF;  
    }
}

//on status 4
char onStatus4(std::fstream*ifs,std::fstream*ofs,char ch){
    std::string word;
    std::unordered_map<std::string, std::string>::iterator iter;

    if (ch == '#' || ch == ';'||ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'){
        word.push_back(ch);
        iter = keyWords.find(word);
        *ofs <<  iter->second + "\t" +word << "\n";
        if(ifs->eof()){
            //the file is over
            return EOF;
        }
        else{
            //the file is not over
            ch = ifs->get();
            return ch;
        }
    }
    else if(ch=='<'||ch=='>'||ch=='='){
        //determine whether go to status 5
        if(ifs->eof()){
            //the will not go to status 5
            word = ch;
            iter = keyWords.find(word);
            *ofs <<  iter->second + "\t" +word << "\n";
            return EOF;
        }
        else{
            //the file is not over
            word = ch;
            ch = ifs->get();
            if(ch=='='){
                //go to status 5
                word.push_back(ch);
                ch = ifs->get();
                return onStatus5(ifs,ofs, ch, word);
            }
            else{
                //will not go to status 5
                iter = keyWords.find(word);
                *ofs<<  iter->second + "\t" +word << "\n";
                return ch;
            }
        }
    }
    else if(ch=='!'){
        if(ifs->eof()){
            //error condition
            return EOF;
        }
        else{
            word = ch;
            ch = ifs->get();
            if(ch=='='){
                //go to status 5
                word.push_back(ch);
                ch = ifs->get();
                return onStatus5(ifs,ofs, ch, word);
            }
            else{
                return ch;
            }
            
        }
    }
    else{   
        if(ifs->eof()){
        return EOF;
        }
        else{
            ch = ifs->get();
            return ch;
        }
    }
}


// on status 5
char onStatus5(std::fstream *ifs, std::fstream*ofs,char ch, std::string word){
    std::unordered_map<std::string, std::string>::iterator iter;
    if(ifs->eof()){
        //the file is over
        iter = keyWords.find(word);
        *ofs<<  iter->second + "\t" +word<< "\n";
        return EOF;
    }
    else{
        iter = keyWords.find(word);
        *ofs << iter->second + "\t" +word<< "\n";
        return ch;
    }
    
}

// on status 6
char onStatus6(std::fstream *ifs,std::fstream*ofs,char ch){

    //std::cout << "On status 6.\n";
    if(!ifs->eof()){
        //the file is not over
        ch = ifs->get();
        if(isLetter(ch)||isDigit(ch)||isOperator(ch)){
            // go to status 7
            //std::cout << "go to status 7.\n";
            return onStatus7(ifs,ofs, ch);
        }
        else{
            // is not a single char defined
            if(!(ifs->eof())){
                ch = ifs->get();
                if(ch=='\''){
                    //fetch the next char
                    if(!(ifs->get())){
                        ch = ifs->get();
                        return ch;
                    }
                    else{
                        //the file is over
                        return EOF;
                    }
                }
                else{
                    return ch;
                }
            }
            else{
                // the file is over
                return EOF;
            }
         
        }
    }
    else{
        // the file is over
        return EOF;
    }

}

// on status 7
char onStatus7(std::fstream *ifs,std::fstream *ofs,char ch){
    char temp = ch;
    if(!(ifs->eof())){
        // the file is not over
        ch = ifs->get();
        if(ch=='\''){
            // go to status 8
            //std::cout << "Go to status 8.\n";
            return onStatus8(ifs,ofs,temp,ch);
        }
        else{
            //error condition
            return ch;
        }
    }
    else{
        //the file is over
        return EOF;
    }
}

// on status 8
char onStatus8(std::fstream *ifs,std::fstream *ofs,char value,char ch){
    if(!(ifs->eof())){
        // the file is not over
         *ofs << "SINGLE CHAR\t" << "'"<<value<<"'" << "\n";
        ch = ifs->get();
        return ch;
    }
    else{
        // the file is over
         *ofs << "SINGLE CHAR\t" <<"'"<<value<<"'" << "\n";
        return EOF;
    }
}

// on status 9
char onStatus9(std::fstream*ifs,std::fstream *ofs,char ch){
    std::string word;//store the string

    if(!(ifs->eof())){
        ch = ifs->get();
        while((!(ifs->eof()))&&(isLetter(ch)||isDigit(ch)||isOperator(ch))){
            word.push_back(ch);
            ch = ifs->get();
        }

        if(ifs->eof()){
            //the file is over
            return EOF;
        }
        else{
            //the file is not over
            if(ch=='"'){
                //go to status 10
                return onStatus10(ifs, ofs, word, ch);
            }
            else{
                //error condition, fetch next character
                ch = ifs->get();
                return ch;
            }
        }
    } 
    else{
        // the file is over
        return EOF;
    }
}

//on status 10
char onStatus10(std::fstream *ifs,std::fstream*ofs, std::string word,char ch){
    *ofs << "STR\t"<<"\""<<word<<"\"" << "\n";
    if(!(ifs->eof())){
        //the file is not over, fetch next character
        ch = ifs->get();
        return ch;
    }
    else{
        //the file is over
        return EOF;
    }
}
int main(){
    //initial keywords
    initialKeyWords();
    
    int status = 0; //start at 0 status

    std::fstream ifs; // open the test file
    std::fstream ofs;
    std::string inputPath="Input.txt";
    std::string outputPath = "Output.txt";
    ifs.open(inputPath, std::ios::in);
    ofs.open(outputPath, std::ios::out);
    ofs << "Tag \t Attr\n";
    char ch;
    ch=ifs.get();
    while(ch!=EOF){
       if(isLetter(ch)){
           //ch is a letter
           status = 1;
       }
       else if(isDigit(ch)){
           //ch is a digit
           status = 2;
       }
       else if(isOperator(ch)){
           status = 4;
       }
       else if(ch=='\''){
           status = 6;
       }
       else if(ch=='"'){
           status = 9;
       }
       else{
           ch = ifs.get();
           continue;
       }
       //std::cout << "Come in.\n";
       switch(status){
           
            case 1:
                ch=onStatus1(&ifs,&ofs,ch);
                break;
            case 2:
                ch = onStatus2(&ifs,&ofs,ch);
                break;
            case 4:
                ch = onStatus4(&ifs,&ofs,ch);
                break;
            case 6:
                ch = onStatus6(&ifs,&ofs,ch);
                break;
            case 9:
                ch = onStatus9(&ifs,&ofs,ch);
                break;
            case 0:
                break;
       }

  
    }

    //close input file and output file
    ifs.close();
    ofs.close();
    return 0;
}