#ifndef DOCUMENTANDFREQUENCY_H
#define DOCUMENTANDFREQUENCY_H

class DocumentAndFrequency
{
private:
    int documentNumber;
    int frequency;

public:
    DocumentAndFrequency(int docNumb, int freq);

    void increaseFreq();
    int getFreq();
    int getDocNumb();
};

#endif // DOCUMENTANDFREQUENCY_H
