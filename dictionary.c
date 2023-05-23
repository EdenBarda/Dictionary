/***********
* Eden Barda
* 208932202
* ex_5
***********/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct TempWord{
    char **translantions;
    struct TempWord *next;
} Word;

typedef struct {
    char **languages;
    int numOfLanguages;
    Word *wordList;
} Dictionary;

void tabOfContText(int *numOfDictionaries, Dictionary *dictionaries);
void tabOfCont(int *numOfDictionaries, Dictionary *dictionaries);
void createDictionary(int *numOfDictionaries, Dictionary *dictionaries);
void addWord(int *numOfDictionaries, Dictionary *dictionaries);
void deleteWord(int *numOfDictionaries, Dictionary *dictionaries);
Word *addressBefore(Word *wordList, Word *rightWord);
void findWord(int *numOfDictionaries, Dictionary *dictionaries);
Word *whereInDic(char* temp, Word *wordList);
int isSame(char word1[], char word2[]);
void deleteDictionary(int* numOfDictionaries, Dictionary *dictionaries);
void freeAll(int *numOfDictionaries, Dictionary *dictionaries);

/************************************************************************
* Function Name: main
* Input: none
* Output: 0
* Function Operation: the function moves the user to table of contents
************************************************************************/
int main() {
    int numOfDictionaries = 0;
    Dictionary* dictionaries;
    Dictionary* tempDic;
    tempDic = (Dictionary*)calloc(1, sizeof(Dictionary));
    if (tempDic == NULL) {
        printf("The program running is failed!\n");
        return 0;
    }
    dictionaries = tempDic;
    tabOfContText(&numOfDictionaries, dictionaries);
    return 0;
}

/************************************************************************
* Function Name: tabOfContText
* Input: int *numOfDictionaries (the address to the numbers of dictionaries
         that exists until now)
         Dictionary *dictionaries
* Output: none
* Function Operation: the function prints the menu and send the user to
                      tabOfCont function
************************************************************************/
void tabOfContText(int *numOfDictionaries, Dictionary *dictionaries) {
    int num;
    printf("Welcome to the dictionaries manager!\n");
    printf("Choose an option:\n");
    printf("1. Create a new dictionary.\n");
    printf("2. Add a word to a dictionary.\n");
    printf("3. Delete a word from a dictionary.\n");
    printf("4. Find a word in a dictionary.\n");
    printf("5. Delete a dictionary.\n");
    printf("6. Exit.\n");
    tabOfCont(numOfDictionaries, dictionaries);
}

/************************************************************************
* Function Name: tabOfCont
* Input: int *numOfDictionaries (the address to the numbers of dictionaries
         that exists until now)
         Dictionary *dictionaries
         int num (valid numbers: 1 <= num <= 6)
* Output: none
* Function Operation: the function sends the user to the option he
                      selected
************************************************************************/
void tabOfCont(int *numOfDictionaries, Dictionary *dictionaries) {
    int num;
    int i;
    Word *wordTemp;
    scanf("%d", &num);
    switch (num) {
    case 1: createDictionary(numOfDictionaries, dictionaries);
        break;
    case 2:
        if (*numOfDictionaries != 0) {
            addWord(numOfDictionaries, dictionaries);
        }
        else {
            printf("This option is not available right now, try again:\n");
            tabOfCont(numOfDictionaries, dictionaries);
        }
        break;
    case 3:
        if (*numOfDictionaries != 0) {
            deleteWord(numOfDictionaries, dictionaries);
        }
        else {
            printf("This option is not available right now, try again:\n");
            tabOfCont(numOfDictionaries, dictionaries);
        }
        break;
    case 4:
        if (*numOfDictionaries != 0) {
            findWord(numOfDictionaries, dictionaries);
        }
        else {
            printf("This option is not available right now, try again:\n");
            tabOfCont(numOfDictionaries, dictionaries);
        }
        break;
    case 5:
        if (*numOfDictionaries != 0) {
            deleteDictionary(numOfDictionaries, dictionaries);
        }
        else {
            printf("This option is not available right now, try again:\n");
            tabOfCont(numOfDictionaries, dictionaries);
        }
        break;
    case 6: 
        freeAll(numOfDictionaries, dictionaries);
        printf("Bye!\n");
        break;
    default:
        printf("Wrong option, try again:\n");
        tabOfContText(numOfDictionaries, dictionaries);
        break;
    }
}

/************************************************************************
* Function Name: createDictionary
* Input: int *numOfDictionaries (the address to the numbers of dictionaries
         that exists until now)
         Dictionary *dictionaries
* Output: none
* Function Operation: the function creats dictinary with the languages
                      that the user choose
************************************************************************/
void createDictionary(int *numOfDictionaries, Dictionary *dictionaries) {
    int i = 0;
    int j = 0;
    char enter;
    char letter = 'a';
    char* temp;
    char* charTemp;
    char** dubCharTemp;
    Word *wordTemp;
    Dictionary* dicTemp;
    printf("Define a new dictionary:\n");
    dicTemp = (Dictionary*)realloc(dictionaries, sizeof(Dictionary) * (*numOfDictionaries + 1));
    if (dicTemp == NULL) {
        printf("The creation of the dictionary has failed!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    dictionaries = dicTemp;
    dubCharTemp = (char**)calloc(1, sizeof(char*));
    if (dubCharTemp == NULL) {
        printf("The creation of the dictionary has failed!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    dictionaries[*numOfDictionaries].languages = dubCharTemp;
    charTemp = (char*)calloc(1, sizeof(char));
    if (charTemp == NULL) {
        printf("The creation of the dictionary has failed!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    temp = charTemp;
    scanf("%c", &enter);
    scanf("%c", &letter);
    while (letter != '\n') {
        if (letter != ',') {
            charTemp = (char*)realloc(temp, sizeof(char) * (i + 2));
            if (charTemp == NULL) {
                printf("The creation of the dictionary has failed!\n");
                tabOfContText(numOfDictionaries, dictionaries);
            }
            temp = charTemp;
            if (temp != NULL) {
                temp[i] = letter;
                temp[i + 1] = '\0';
            }
            i++;
            scanf("%c", &letter);
        }
        if (letter == ',' && temp != '\0') {
            charTemp = (char*)calloc(i + 1, sizeof(char));
            if (charTemp == NULL) {
                printf("The creation of the dictionary has failed!\n");
                tabOfContText(numOfDictionaries, dictionaries);
            }
            dictionaries[*numOfDictionaries].languages[j] = charTemp;
            strcpy(dictionaries[*numOfDictionaries].languages[j], temp);
            free(temp);
            charTemp = (char*)calloc(1, sizeof(char));
            if (charTemp == NULL) {
                printf("The creation of the dictionary has failed!\n");
                tabOfContText(numOfDictionaries, dictionaries);
            }
            temp = charTemp;
            i = 0;
            j++;
            scanf("%c", &letter);
            dubCharTemp = (char**)realloc(dictionaries[*numOfDictionaries].languages, sizeof(char*) * (j + 2));
            if (dubCharTemp == NULL) {
                printf("The creation of the dictionary has failed!\n");
                tabOfContText(numOfDictionaries, dictionaries);
            }
            dictionaries[*numOfDictionaries].languages = dubCharTemp;
        }
    }
    charTemp = (char*)calloc(i + 1, sizeof(char));
    if (charTemp == NULL) {
        printf("The creation of the dictionary has failed!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    dictionaries[*numOfDictionaries].languages[j] = charTemp;
    strcpy(dictionaries[*numOfDictionaries].languages[j], temp);
    free(temp);
    j++;
    dictionaries[*numOfDictionaries].numOfLanguages = j;
    dictionaries[*numOfDictionaries].languages[j] = NULL;
    wordTemp = (Word*)calloc(1, sizeof(Word));
    if (wordTemp == NULL) {
        printf("The creation of the dictionary has failed!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    dictionaries[*numOfDictionaries].wordList = wordTemp;
    dictionaries[*numOfDictionaries].wordList->next = NULL;
    dubCharTemp = (char**)calloc(i + 1, sizeof(char*));
    if (dubCharTemp == NULL) {
        printf("The creation of the dictionary has failed!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    dictionaries[*numOfDictionaries].wordList->translantions = dubCharTemp;
    printf("The dictionary has been created successfully!\n");
    *numOfDictionaries += 1;
    tabOfContText(numOfDictionaries, dictionaries);
}

/************************************************************************
* Function Name: addWord
* Input: int *numOfDictionaries (the address to the numbers of dictionaries
         that exists until now)
         Dictionary *dictionaries
* Output: none
* Function Operation: the function add word to the dictinary that the
                      user choose
************************************************************************/
void addWord(int *numOfDictionaries, Dictionary *dictionaries) {
    int i, j, dictionaryNum;
    char letter, enter;
    char* charTemp;
    char* temp;
    char** dubCharTemp;
    Word* tempWord;
    Word* newWord;
    printf("Choose a dictionary:\n");
    for (i = 0; i < *numOfDictionaries; i++) {
        for (j = 0; j < dictionaries[i].numOfLanguages; j++) {
            if (j == 0) {
                printf("%d. ", i + 1);
            }
            printf("%s", dictionaries[i].languages[j]);
            if (j < dictionaries[i].numOfLanguages - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
    scanf("%d", &dictionaryNum);
    while (dictionaryNum > *numOfDictionaries) {
        printf("This option is not available right now, try again:\n");
        scanf("%d", &dictionaryNum);
    }
    dictionaryNum -= 1;
    printf("Enter a word in ");
    for (j = 0; j < dictionaries[dictionaryNum].numOfLanguages; j++) {
        printf("%s", dictionaries[dictionaryNum].languages[j]);
        if (j < dictionaries[dictionaryNum].numOfLanguages - 1) {
            printf(",");
        }
    }
    printf(":\n");
    tempWord = (Word*)calloc(1, sizeof(Word));
    if (tempWord == NULL) {
        printf("The addition of the word has failed!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    newWord = tempWord;
    dubCharTemp = (char**)calloc(1, sizeof(char*));
    if (dubCharTemp == NULL) {
        printf("The addition of the word has failed!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    newWord->translantions = dubCharTemp;
    charTemp = (char*)calloc(1, sizeof(char));
    if (charTemp == NULL) {
        printf("The addition of the word has failed!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    temp = charTemp;
    scanf("%c", &enter);
    scanf("%c", &letter);
    j = 0;
    i = 0;
    while (letter != '\n') {
        if (letter != ',') {
            charTemp = (char*)realloc(temp, sizeof(char) * (i + 2));
            if (charTemp == NULL) {
                printf("The addition of the word has failed!\n");
                tabOfContText(numOfDictionaries, dictionaries);
            }
            temp = charTemp;
            if (temp != NULL) {
                temp[i] = letter;
                temp[i + 1] = '\0';
            }
            i++;
            scanf("%c", &letter);
        }
        if (letter == ',' && temp != '\0' && newWord->translantions != NULL) {
            charTemp = (char*)calloc(i + 2, sizeof(char));
            if (charTemp == NULL) {
                printf("The addition of the word has failed!\n");
                tabOfContText(numOfDictionaries, dictionaries);
            }
            newWord->translantions[j] = charTemp;
            strcpy(newWord->translantions[j], temp);
            free(temp);
            newWord->next = NULL;
            charTemp = (char*)calloc(1, sizeof(char));
            if (charTemp == NULL) {
                printf("The addition of the word has failed!\n");
                tabOfContText(numOfDictionaries, dictionaries);
            }
            temp = charTemp;
            i = 0;
            j++;
            scanf("%c", &letter);
            dubCharTemp = (char**)realloc(newWord->translantions, sizeof(char*) * (j + 2));
            if (dubCharTemp == NULL) {
                printf("The addition of the word has failed!\n");
                tabOfContText(numOfDictionaries, dictionaries);
            }
            newWord->translantions = dubCharTemp;
            newWord->translantions[j] = NULL;
        }
    }
    if (newWord->translantions != NULL) {
        charTemp = (char*)calloc(i + 2, sizeof(char));
        if (charTemp == NULL) {
            printf("The addition of the word has failed!\n");
            tabOfContText(numOfDictionaries, dictionaries);
        }
        newWord->translantions[j] = charTemp;
        strcpy(newWord->translantions[j], temp);
        free(temp);
        j++;
        newWord->translantions[j] = NULL;
        if (dictionaries[dictionaryNum].wordList->next == NULL) {
            dictionaries[dictionaryNum].wordList->next = newWord;
        }
        else {
            newWord->next = dictionaries[dictionaryNum].wordList->next;
            dictionaries[dictionaryNum].wordList->next = newWord;
        }
    }
    printf("The word has been added successfully!\n");
    tabOfContText(numOfDictionaries, dictionaries);
}

/************************************************************************
* Function Name: deleteWord
* Input: int *numOfDictionaries (the address to the numbers of dictionaries
         that exists until now)
         Dictionary *dictionaries
* Output: none
* Function Operation: the function delete a word (and its translations)
                      that the user choose in a dictinary that he choose
************************************************************************/
void deleteWord(int *numOfDictionaries, Dictionary *dictionaries) {
    int j, i, dictionaryNum;
    char enter, letter;
    char* charTemp;
    char* temp;
    Word *rightWord;
    Word *newAddress;
    Word* tempAddress;
    printf("Choose a dictionary:\n");
    for (i = 0; i < *numOfDictionaries; i++) {
        for (j = 0; j < dictionaries[i].numOfLanguages; j++) {
            if (j == 0) {
                printf("%d. ", i + 1);
            }
            printf("%s", dictionaries[i].languages[j]);
            if (j < dictionaries[i].numOfLanguages - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
    scanf("%d", &dictionaryNum);
    while (dictionaryNum > *numOfDictionaries) {
        printf("This option is not available right now, try again:\n");
        scanf("%d", &dictionaryNum);
    }
    dictionaryNum -= 1;
    printf("Enter a word in %s:\n", dictionaries[dictionaryNum].languages[0]);
    charTemp = (char*)calloc(1, sizeof(char));
    if (charTemp == NULL) {
        printf("The deletion of the word has failed!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    temp = charTemp;
    scanf("%c", &enter);
    scanf("%c", &letter);
    i = 0;
    j = 0;
    while (letter != '\n') {
        charTemp = (char*)realloc(temp, sizeof(char) * (i + 2));
        if (charTemp == NULL) {
            printf("The deletion of the word has failed!\n");
            tabOfContText(numOfDictionaries, dictionaries);
        }
        temp = charTemp;
        if (temp != NULL) {
            temp[i] = letter;
            temp[i + 1] = '\0';
        }
        i++;
        scanf("%c", &letter);
    }
    printf("Are you sure? (y/n)\n");
    scanf("%c", &letter);
    if (letter == 'y') {
        rightWord = whereInDic(temp, (Word*)dictionaries[dictionaryNum].wordList->next);
        if (rightWord == NULL) {
            printf("The deletion of the word has failed!\n");
        }
        else {
            tempAddress = rightWord;
            newAddress = addressBefore(dictionaries[dictionaryNum].wordList, rightWord);
            newAddress->next = rightWord->next;
            i = dictionaries[dictionaryNum].numOfLanguages;
            for (i; i >= 0 ;i--) {
                free(tempAddress->translantions[i]);
            }
            free(tempAddress->translantions);
            free(tempAddress);
            printf("The word has been deleted successfully!\n");
        }
    }
    else {
        printf("The deletion of the word has been canceled.\n");
    }
    free(temp);
    tabOfContText(numOfDictionaries, dictionaries);
}

/************************************************************************
* Function Name: addressBefore
* Input: Word *wordList (the first word in the struck) Word *rightWord
*        (the word the function searchs)
* Output: wordList (the address that points to rightWord)
* Function Operation: the function finds the the address that points to
                      rightWord in the dictinary
************************************************************************/
Word *addressBefore(Word *wordList, Word *rightWord) {
    if ((Word*)wordList->next == rightWord) {
        return wordList;
    }
    else {
        addressBefore((Word*)wordList->next, rightWord);
    }
}

/************************************************************************
* Function Name: findWord
* Input: int *numOfDictionaries (the address to the numbers of dictionaries
         that exists until now)
         Dictionary *dictionaries
* Output: none
* Function Operation: the function search for word in the dictinary
                      if it finds it it prints its translation on
                      the Languages in the dictinary
************************************************************************/
void findWord(int *numOfDictionaries, Dictionary *dictionaries) {
    int j, i, dictionaryNum;
    char enter, letter;
    char *charTemp;
    char *temp;
    Word *rightWord;
    printf("Choose a dictionary:\n");
    for (i = 0; i < *numOfDictionaries; i++) {
        for (j = 0; j < dictionaries[i].numOfLanguages; j++) {
            if (j == 0) {
                printf("%d. ", i + 1);
            }
            printf("%s", dictionaries[i].languages[j]);
            if (j < dictionaries[i].numOfLanguages - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
    scanf("%d", &dictionaryNum);
    while (dictionaryNum > *numOfDictionaries) {
        printf("This option is not available right now, try again:\n");
        scanf("%d", &dictionaryNum);
    }
    dictionaryNum -= 1;
    printf("Enter a word in %s:\n", dictionaries[dictionaryNum].languages[0]);
    charTemp = (char*)calloc(1, sizeof(char));
    if (charTemp == NULL) {
        printf("The search has failed successfully!\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
    temp = charTemp;
    scanf("%c", &enter);
    scanf("%c", &letter);
    i = 0;
    j = 0;
    while (letter != '\n') {
        charTemp = (char*)realloc(temp, sizeof(char) * (i + 2));
        if (charTemp) {
            temp = charTemp;
        }
        else {
            printf("The search has failed successfully!\n");
            tabOfContText(numOfDictionaries, dictionaries);
        }
        if (temp != NULL) {
            temp[i] = letter;
            temp[i + 1] = '\0';
        }
        i++;
        scanf("%c", &letter);
    }
    rightWord = whereInDic(temp, (Word*)dictionaries[dictionaryNum].wordList->next);
    if (rightWord != NULL) {
        printf("The translations are:\n");
        for (j = 1; j+1 < dictionaries[dictionaryNum].numOfLanguages; j++) {
            printf("%s: %s, ", dictionaries[dictionaryNum].languages[j], rightWord->translantions[j]);
        }
        printf("%s: %s", dictionaries[dictionaryNum].languages[j], rightWord->translantions[j]);
        printf("\n");
    }
    else {
        printf("There are no translations for \"%s\" in this dictionary.\n", temp);
    }
    free(temp);
    tabOfContText(numOfDictionaries, dictionaries);
}

/************************************************************************
* Function Name: whereInDic
* Input: char *temp (pointer to a string), Word *wordList (pointer to
         Word struck in the dictionary)
* Output: NULL (if temp is not on the dictionary), rightword or wordList
          (the address the the searched word in the dictionary)
* Function Operation: the function search if the word is in the
                      dictionary. if it finds it - it returns the address
                      if now, it sends the next address to this function
                      if the next address is 'NULL' it returns 'NULL'
************************************************************************/
Word *whereInDic(char *temp, Word *wordList) {
    Word *rightWord;
    rightWord = (Word*)calloc(1, sizeof(Word));
    if (wordList == NULL) {
        free(rightWord);
        return NULL;
    }
    if (isSame(temp, wordList->translantions[0]) == 1 && wordList->next == NULL) {
        free(rightWord);
        return NULL;
    }
    if (rightWord == NULL) {
        free(rightWord);
        return NULL;
    }
    if (isSame(temp, wordList->translantions[0]) == 0) {
        free(rightWord);
        return wordList;
    }
    if (isSame(temp, wordList->translantions[0]) == 1 && wordList->next != NULL) {
        free(rightWord);
        rightWord = whereInDic(temp, (Word*)wordList->next);
        return rightWord;
    }
}

/************************************************************************
* Function Name: isSame
* Input: char word1[] (a string), char word2[] (another string)
* Output: 0 or 1
* Function Operation: if the words in the strings, before '/0' are the
                      the same, the function return 1, else - the
                      function return 0
************************************************************************/
int isSame(char word1[], char word2[]) {
    int i = 0;
    while (word1[i] || word2[i]) {
        if (word1[i] != '\0' && word2[i] == '\0') {
            return 1;
        }
        if (word1[i] == '\0' && word2[i] != '\0') {
            return 1;
        }
        if (word1[i] != word2[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}

/************************************************************************
* Function Name: deleteDictionary
* Input: int *numOfDictionaries (the address to the numbers of dictionaries
         that exists until now)
         Dictionary *dictionaries
* Output: none
* Function Operation: the function delete a choosen dictinary and all of
                      his contents
************************************************************************/
void deleteDictionary(int *numOfDictionaries, Dictionary *dictionaries) {
    int j, i, dictionaryNum;
    char enter, c;
    char* charTemp;
    Word *rightWord;
    Word *wordTemp;
    Dictionary *tempDic;
    printf("Choose a dictionary:\n");
    for (i = 0; i < *numOfDictionaries; i++) {
        for (j = 0; j < dictionaries[i].numOfLanguages; j++) {
            if (j == 0) {
                printf("%d. ", i + 1);
            }
            printf("%s", dictionaries[i].languages[j]);
            if (j < dictionaries[i].numOfLanguages - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
    scanf("%d", &dictionaryNum);
    while (dictionaryNum > *numOfDictionaries) {
        printf("This option is not available right now, try again:\n");
        scanf("%d", &dictionaryNum);
    }
    dictionaryNum -= 1;
    printf("Are you sure? (y/n)\n");
    scanf("%c", &enter);
    scanf("%c", &c);
    if (c == 'y') {
        j = dictionaries[dictionaryNum].numOfLanguages;
        for (j; j >= 0; j--) {
            free(dictionaries[dictionaryNum].languages[j]);
        }
        free(dictionaries[dictionaryNum].languages);
        while (dictionaries[dictionaryNum].wordList != NULL) {
            wordTemp = dictionaries[dictionaryNum].wordList;
            dictionaries[dictionaryNum].wordList = (Word*)dictionaries[dictionaryNum].wordList->next;
            j = dictionaries[dictionaryNum].numOfLanguages;
            for (j; j >= 0; j--) {
                free(wordTemp->translantions[j]);
            }
            free(wordTemp->translantions);
            free(wordTemp);
        }
        free(dictionaries[dictionaryNum].wordList);
        for (i = dictionaryNum; i < *numOfDictionaries - 1; i++) {
            dictionaries[i].numOfLanguages = dictionaries[i + 1].numOfLanguages;
            dictionaries[i].languages = dictionaries[i + 1].languages;
            dictionaries[i].wordList = dictionaries[i + 1].wordList;
        }
        *numOfDictionaries -= 1;
        tempDic = (Dictionary*)realloc(dictionaries, sizeof(Dictionary) * (*numOfDictionaries + 1));
        if (tempDic) {
            dictionaries = tempDic;
            printf("The dictionary has been deleted successfully!\n");
            tabOfContText(numOfDictionaries, dictionaries);
        }
        else {
            printf("The deletion of the dictionary has failed!\n");
            tabOfContText(numOfDictionaries, dictionaries);
        }
    }
    else {
        printf("The deletion of the dictionary has been canceled.\n");
        tabOfContText(numOfDictionaries, dictionaries);
    }
}

/************************************************************************
* Function Name: freeAll
* Input: int *numOfDictionaries (the address to the numbers of dictionaries
         that exists until now)
         Dictionary *dictionaries
* Output: none
* Function Operation: the function free all the space that used in the
                      program
************************************************************************/
void freeAll(int *numOfDictionaries, Dictionary *dictionaries) {
    int i = *numOfDictionaries - 1;
    int j, k;
    Word* wordTemp;
    for (i; i >= 0; i--) {
        j = dictionaries[i].numOfLanguages;
        for (j; j >= 0; j--) {
            free(dictionaries[i].languages[j]);
        }
        free(dictionaries[i].languages);
        while (dictionaries[i].wordList != NULL) {
            wordTemp = dictionaries[i].wordList;
            dictionaries[i].wordList = (Word*)dictionaries[i].wordList->next;
            k = dictionaries[i].numOfLanguages;
            for (k; k >= 0; k--) {
                free(wordTemp->translantions[k]);
            }
            free(wordTemp->translantions);
            free(wordTemp);
        }
        free(dictionaries[i].wordList);
    }
    free(dictionaries);
}