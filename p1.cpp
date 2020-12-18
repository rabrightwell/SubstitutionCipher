#include <iostream>
#include <list>
#include <string>
#include <fstream>

using namespace std;

const char ALPHABET[] = { ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' } ;
const int NUM_LETTERS = 27 ; //Update if alphabet is changed
const int SUM_ASCII = 2015 ; //Sum of all listed alphabet values
const int PLACEHOLDER = 32 ; //Placeholder in cipher is ' ', which has ASCII value of 32

//Prototypes
int letterCount(string & message, int posi) ;
list<string> parseForLength(string & message, int & keyLength) ;
string codeThis(string & toCode, char cipher[][NUM_LETTERS]) ;
string decodeThis(string & toDecode, char cipher[][NUM_LETTERS]) ;
string matchKeyWord(list<string> parsedForLength, string keyWord, char cipher[][NUM_LETTERS]) ;



int main(int argc, char** argv)
{
  //Coded/Decoded Message Variables
  char cipher[2][NUM_LETTERS] ; //Holds alphabet in top row [1][i] and corresponding code in bottom row [2][i]
  string keyWord ; 
  string codedKeyWord ;
  string message ;
  string decode ; //partial cipher values mapped to
  string code ; //partial cipher values that map
  char finalLetter ; //

  //Logical Variables
  string tmpline; //Used to capture message line by line
  int keyWordLength ; //Number of letters in the keyword
  list<string> parsedForLength ; //Holds words of same length as keyword
  int sum = 0 ; //Used to sum ASCII values of cipher values to confirm completion
 
  //Initializing Cipher
  for(int i = 0; i< NUM_LETTERS; i++)
  {
    cipher[0][i] = ALPHABET[i] ;
    cipher[1][i] = ' ' ;
  }


  //Imports:
    ifstream fin ;
    ifstream fin2 ;
    //Import known substitution cipher
      
      fin.open(argv[1]) ;

      getline(fin, decode) ; //First line of file 1 is always "decoded" letters
      getline(fin, code) ;

      fin.close() ;

        //Create cipher -- decipher relationship
            //could use two separate arrays or a 2D array with blank spaces

    //Import message to decode
      fin.open(argv[2]) ;

      while(getline(fin, tmpline))
        message += "\n" + tmpline ; //Used to ensure all lines of code are read in

      fin.close() ;


    //Import key word
    keyWord = argv[3] ;

    //Completing Cipher
      //Complete as much of cipher possible using decode, code
      for(int i = 0; i< code.length(); i++)
      {
        for(int j = 0; j< NUM_LETTERS; j++)
        {
          if(decode[i] == cipher[0][j])
          {  
            cipher[1][j] = code[i] ;
            break ;
          }
        }
      }

    //Parse words of same size.
    keyWordLength = keyWord.length() ;

    parsedForLength = parseForLength(message, keyWordLength) ;
        
    //Identify which word matches the keyword
    codedKeyWord = matchKeyWord(parsedForLength, keyWord, cipher) ;

    //Update cipher accordingly.
    for(int i = 0; i< codedKeyWord.length(); i++)
    {
      for(int j = 0; j< NUM_LETTERS; j++)
      {
        if(keyWord[i] == cipher[0][j])
        {  
          cipher[1][j] = codedKeyWord[i] ;
          break ;
        }
      }
    }

    //Determine last remaining letter, if applicable.
      //Summing values of current cipher code
      for(int j = 1 ; j<NUM_LETTERS; j++)
      {
        sum += cipher[1][j] ;
      }

      //To be used if sum is not what is expected (meaning letter is missing)
      if(sum != SUM_ASCII)
      {
        sum -= PLACEHOLDER ;
        finalLetter = SUM_ASCII - sum ;

        //Adding letter to cipher
        for(int j = 1 ; j<NUM_LETTERS; j++)
        {
          if(cipher[1][j] == ' ')
          {
            cipher[1][j] = finalLetter ;
          }
        }
      }

  //Decoding Message
    //Use cipher to completely decode message while leaving all non-alpha characters
    for(int i = 0; i< message.length(); i++)
    {
      for(int j = 0; j < NUM_LETTERS; j++)
      {
        if(isalpha(message[i]) && message[i] == cipher[1][j])
        {  message[i] = cipher[0][j] ;
          break ; }
      }
    }
    
    
  //Output Message
  for(int i = 1; i< message.length(); i++)
  {
    cout << message[i] ;
  }
  cout << endl ;
  return 0;
}

//Functions ----------------------------------------------------------------------

/*LetterCount

  Description: Returns the integer number of letters from a given starting position to the next non-alpha character.

  Precondition: Requires an input string message and an initial position to read from.

  Postcondition: Outputs integer representing the difference between starting position and            next whitespace (e.g. "bottle cap" with initial position 0 would return 6, then 1, then 3 with initial position = previous + output)
*/
int letterCount(string & message, int posi)
{
  int posf = posi ;

  if(!isalpha(message[posi]))
  {
    return ((posf+1)-posi) ;
  }

  while(isalpha(message[posf]))
  {
    posf ++ ;
  }

  return (posf-posi) ;
}

/* ParseForLength

  Description: Takes input string message and returns all words within the message of the same legnth as specified keyLength.

  Precondition: Input string and keylength parameters, letterCount function

  Postcondition: Outputs list of strings of same length as keyLength in order from right to left as they appear in the sentence. \
                 For sentence "The dog jumped fences." the output would be <dog the> for keyLength = 3 and <fences jumped> for keyLength = 6

*/
list<string> parseForLength(string & message, int & keyLength)
{
  list<string> parsedForLength ; //Contains all words of the same length as keyword
  
  int posi = 0 ;
  int out = 0 ;
  int posf = posi ;
  
  string toAdd ; //Temporary word placeholder

  while(posf < message.length())
  {
    out = letterCount(message, posi) ;

    posf = posi + out ;

    toAdd = message.substr(posi, out) ;


    if(out == keyLength && isalpha(toAdd[0])) //Ensures word is same length and is not a space or punctuation
    {
      parsedForLength.emplace_front(toAdd) ;
    }

    posi = posf ;
  }

  return parsedForLength ;
}

/*CodeWord
  
  Description:

  Preconditions:

  Postconditions:

*/
string codeThis(string & toCode, char cipher[][NUM_LETTERS])
{
  string toReturn ;
  for(int i = 0; i< toCode.length(); i++)
  {
    for(int j = 0; j< NUM_LETTERS; j++)
    {
      if(toCode[i] == cipher[0][j])
      {  
        toReturn = toReturn + cipher[1][j] ;
        break ;
      }
    }
  }
  return toReturn ;
}

string decodeThis(string & toDecode, char cipher[][NUM_LETTERS])
{
  string toReturn ;
  for(int i = 0; i< toDecode.length(); i++)
  {
    for(int j = 0; j< NUM_LETTERS; j++)
    {
      if(toDecode[i] == cipher[1][j])
      {  
          toReturn = toReturn + cipher[0][j] ;
          break ;
      }
      if(j == NUM_LETTERS - 1)
      {
        toReturn = toReturn + " " ;
      }
    }
  }
  return toReturn ;
}


/*MatchKeyWord

  Description: 

  Precondition: 

  Postcondition: 

*/
string matchKeyWord(list<string> parsedForLength, string keyWord, char cipher[][NUM_LETTERS])
{
  list<string> listCopy = parsedForLength ;
  string toReturn ;
  list<string>::iterator it1 ;
  list<string>:: iterator it2 = parsedForLength.begin() ;

  string keyCompare ; //Processed keyword that list will be compared with

  int i = 0 ;

  //Processing of keyword
  keyCompare = codeThis(keyWord, cipher) ;
  keyCompare = decodeThis(keyCompare, cipher) ;

  //Converting list into decoded values and comparing with remaining list
  for(it1 = listCopy.begin(); it1 != listCopy.end(); it1++)
  { 
    *it1 = decodeThis(*it1, cipher) ;

    if(keyCompare.compare(*it1) == 0)
    {
      advance(it2, i) ;
      return *it2 ;
    }
    i++ ;
  }
  return *it2 ;
}
