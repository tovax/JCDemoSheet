#ifndef SHEET_H
#define SHEET_H

#include <stdint.h>
#include <QString>

class SheetGroup
{
public:
    static const QString Text;
};

class SheetColumn
{
public:
    enum T : uint8_t {
        A1 = 0,
        A2,
        A3,
        A4,
        A5,
        A6,
        A7,
        A8,
        A9,
        A10,
        A11,
        A12,
        A13,
        A14,
        A15,
        A16,
        Min = A1,
        Max = A16,
        Count
    };

    static const QString Text[Count];
};

#endif // SHEET_H
