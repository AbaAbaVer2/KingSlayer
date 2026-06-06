#ifndef PLAYVALIDATOR_H
#define PLAYVALIDATOR_H

#include <vector>
#include <QString>
#include "card.h"

class PlayValidator {
public:
    static bool isValidPlay(const std::vector<Card>& cards);
    static QString getInvalidReason(const std::vector<Card>& cards);
    static int calculateBaseDamage(const std::vector<Card>& cards);
};

#endif // PLAYVALIDATOR_H
