#include "simpleai.h"

int readMaxGuess()
{
    int maxGuess;
    cout << endl << "Enter the number of incorrect guesses: ";
    cin >> maxGuess;
    return maxGuess;
}

int readWordLen()
{
    int wordLen;
    cout << endl << "Enter the number characters of your secret word: ";
    cin >> wordLen;
    return wordLen;
    
}

/***
    Args:
        wordLen (int): The desired length of input word
        vocabulary (vector<string>): The vocabulary
    Returns:
        answer (vector<string>) : A set or word from the vocabulary where the number of character is equal to wordLen
***/
vector<string> filterWordsByLen(int wordLen, const vector<string>& vocabulary)
{
    vector<string> answer;
    for (int i = 0; i < vocabulary.size(); i++)
    {
        if (vocabulary[i].length() == wordLen)
        {
            answer.push_back(vocabulary[i]);
        }
        
    }
    return answer;
}

/***
    Args:
        selectedChars (set<char>): The predicted characters
    Returns:
        answer (char) : The next character given the provided word is not in the vocabulary
***/

char nextCharWhenWordIsNotInDictionary(const set<char>& selectedChars)
{
    char answer = 'a';
    while (answer != 'z')
    {
        if (selectedChars.find(answer) == selectedChars.end())
        {
            return answer;
        } 
        answer++;
    }
    answer = ' ';
    return answer;
}

/***
    Args:
        candidateWords (vector<string>): The candidate words for the current given string 
    Returns:
        answer (map) : The map which count the occurences of character in the set of candidate words
***/

map<char, int> countOccurrences(const vector<string>& candidateWords)
{
    map<char, int> answer;
    for (int i = 0; i < candidateWords.size(); i++)
    {
        for (int j = 0; j < candidateWords[i].length(); j++)
        {
            answer[candidateWords[i][j]]++;
        }
        
    }
    return answer;
}

/***
    Args:
        occurrences (map<char, int>): The map which count the occurences of character in the set of candidate words
        selectedChars (set<char>): The predicted characters
    Returns:
        answer (char) : The most frequent character
***/

char findMostFrequentChar(const map<char, int>& occurrences, const set<char>& selectedChars)
{
    char answer;
    int temp = 0;
    for (map<char, int>::const_iterator ptr = occurrences.begin(); ptr != occurrences.end(); ptr++)
    {
        if (selectedChars.find(ptr->first) == selectedChars.end())
        {
            if (temp < ptr->second)
            {
                temp = ptr->second;
                answer = ptr->first;
            }
            
        }
        
    }
    return answer;
}

/***
    Args:
        candidateWords (vector<string>): The candidate words for the current given string 
        selectedChars (set<char>): The predicted characters
    Returns:
        answer (char) : The most suitable character for prediction
***/

char findBestChar(const vector<string>& candidateWords, const set<char>& selectedChars)
{
    char answer;
    map<char, int> frequency_table;
    frequency_table = countOccurrences(candidateWords);
    answer = findMostFrequentChar(frequency_table, selectedChars);
    return answer;
}

string getWordMask(char nextChar)
{
    string mask;
    cout << "The next char is: " << nextChar << endl;
    cout << "Please give me your answer: ";
    cin >> mask;
    return mask;
}

/***
    Args:
        ch (char): The predicted character by the AI
        mask (string): The response mask by the player
    Returns:
        answer (bool) : return False if the predicted character is the wrong one, True otherwise
***/

bool isCorrectChar(char ch, const string& mask)
{
    bool answer;
    for (int i = 0; i < mask.length(); i++)
    {
        if (ch == mask[i])
        {
            answer = true;
            return answer;
        }
        
    }
    answer = false;
    return answer;
}

/***
    Args:
        mask (string): The response mask by the player
    Returns:
        answer (bool) : return False if the provided mask is not a whole word, True otherwise
        (Example: -False: g__d
                  -True:  good)
***/
bool isWholeWord(const string& mask)
{
    bool answer;
    for (int i = 0; i < mask.length(); i++)
    {
        if (mask[i] == '-')
        {
            answer = false;
            return answer;
        }
    }
    answer = true;
    return answer;
}

/***
    This function should be used to support the filterWordsByMask function below
    Args:
        mask (string): The response mask by the player
        word (string): input word
        ch (char): The predicted character by the AI
    Returns:
        answer (bool) : return False if the provided mask and the given word is not in the same form.
        Example: - False: mask(-ood), char 'd' vs word(boot)
                 - True: mask(-ood), char 'd'  vs word(good)

***/
bool wordConformToMask(const string& word, const string& mask, char ch) 
{
    bool answer;
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] != mask[i])
        {
            answer = false;
            return answer;
        }
        
    }
    answer = true;
    return answer;
}

/***
    Args:
        mask (string): The response mask by the player
        words (vector<string>): The candidate words
        ch (char): The predicted character by the AI
    Returns:
        answer (bool) : a list of word which satisfiy the mask and the predicted character
        Examples: input words: (good,boot,hood,...)
                  input mask: -ood
                  predicted char: d
                  Return: good,hood
***/
vector<string> filterWordsByMask(const vector<string>& words, const string& mask, char ch)
{
    vector<string> answer;
    for (vector<string>::const_iterator ptr = words.begin(); ptr != words.end(); ptr++)
    {
        if (wordConformToMask(*ptr, mask, ch) == true)
        {
            answer.push_back(*ptr);
        }
        
    }
    return answer;
}