#ifndef DOCUMENTANDFREQUENCY_H
#define DOCUMENTANDFREQUENCY_H

//Class that represents the page a word was found on
//and how many times it occured.
class DocumentAndFrequency
{
private:
    int documentNumber; // The index position of the seekp position contained in the vector in documentindex class
    int frequency;
    int finalFrequency;

public:
    DocumentAndFrequency(int docNumb, int freq);
    DocumentAndFrequency();

    void increaseFreq();
    void setFreq(int numb);
    void addToFreq(int numb);
    int getFreq();
    int getFinalFreq();

    void setDocNumb(int numb);
    int getDocNumb();

    void resetFreq();

    static bool notCompare(DocumentAndFrequency *obj1, DocumentAndFrequency *obj2);
    static bool andCompare(DocumentAndFrequency *obj1, DocumentAndFrequency *obj2);
    static bool descendingByFreq(DocumentAndFrequency *obj1, DocumentAndFrequency *obj2);
    static bool ascendingByDocID(DocumentAndFrequency *obj1, DocumentAndFrequency *obj2);
};

#endif // DOCUMENTANDFREQUENCY_H
