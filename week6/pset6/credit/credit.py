from cs50 import get_string


def main():
    ccNumber = get_string('Number: ')
    tmpNumber = int(ccNumber)
    # get the number of digits from the user's input 
    noDigits = len(ccNumber)
    
    if noDigits == 15:  # if its an American Expres...
        ccHeader = int(tmpNumber / 1e13)
        if ccHeader == 34 or ccHeader == 37:  # 34 and 37 corresponds to AMEX
            # Validation trough Luhn's algorithm
            validCard = luhnValidation(tmpNumber, noDigits)
            if validCard == True:
                print("AMEX")
            else:
                # if the Luhn's algorithm returns false that means that the number is invalid
                print("INVALID")
        else:
            # AMEX is the only card with 15 numbers, but if the IDs are not equal to 34 or 37, that means that the number is invalid
            print("INVALID")
    elif noDigits == 16:  # ...or if its a mastercard or visa
        ccHeader = int(tmpNumber / 1e15)
        if ccHeader == 4:
            # Validation trough Luhn's algorithm
            validCard = luhnValidation(tmpNumber, noDigits)
            if validCard == True:
                print("VISA")
            else:  # if the Luhn's algorithm returns false that means that the number is invalid
                print("INVALID")
        else:
            ccHeader = int(tmpNumber / 1e14)
            if ccHeader == 51 or ccHeader == 52 or ccHeader == 53 or ccHeader == 54 or ccHeader == 55:
                # Validation trough Luhn's algorithm
                validCard = luhnValidation(tmpNumber, noDigits)
                if validCard == True:
                    print("MASTERCARD")
                else:
                    print("INVALID")
            else:
                # MASTERCARD and VISA use 16 numbers in their cards, but if the IDs are not equal to 51-55 or 4, that means that the number is invalid
                print("INVALID")
    elif noDigits == 13:  # ...or if its a visa 
        ccHeader = int(tmpNumber / 1e12)
        if ccHeader == 4:  # This is VISA's Id number
            # Validation trough Luhn's algorithm
            validCard = luhnValidation(tmpNumber, noDigits)
            if validCard == True:
                print("VISA")
            else:
                # if the Luhn's algorithm returns false that means that the number is invalid
                print("INVALID")
        else:
            # VISA is the only card with 13 numbers, but if the IDs are not equal to 4, that means that the number is invalid
            print("INVALID")
    else:
        # ...or invalid
        print("INVALID")


def luhnValidation(ccNumber, noDigits):
    digits = []
    everyotheracc = 0
    boRet = False

    for i in range(0, noDigits, 1):
        digits.append(int(ccNumber % 10)) 
        ccNumber = int(ccNumber / 10)
    for i in range(1, noDigits, 2):
        ccNumber = digits[i] * 2
        everyotheracc = everyotheracc + int(ccNumber / 10) + int(ccNumber % 10)
    for i in range(0, noDigits, 2):
        everyotheracc = everyotheracc + digits[i]
    if int(everyotheracc % 10) == 0:
        boRet = True
    return boRet


if __name__ == "__main__":
    main()

