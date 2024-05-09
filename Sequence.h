#ifndef SEQUENCE_H
#define SEQUENCE_H

template <typename T> class Sequence {
public:
    virtual ~Sequence () {}
    virtual T GetFirst () const = 0;
    virtual T GetLast () const = 0;
    virtual T Get (int index) = 0;
    virtual int GetLength () = 0;

    virtual Sequence<T> *GetSubSequence (int startIndex, int endIndex) = 0;
    virtual Sequence<T> *Append (const T &item) = 0;
    virtual Sequence<T> *Prepend (const T &item) = 0;
    virtual Sequence<T> *InsertAt (const T &item, int index) = 0;
    virtual Sequence<T> *Concat (Sequence<T> &list) = 0;
};

#endif //SEQUENCE_H
