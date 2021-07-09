from cs50 import get_string


def main():
    # get a text from the user
    text = get_string("Text: ")
    # count the number of sentences by dividing it with ".", "!" and "?"
    sentences = text.count('.') + text.count('!') + text.count('?')
    # holds the number of letters in the text, explicitely ignoring spaces, apostrophes
    letters = len(text) - text.count(' ') - text.count("'") - sentences - text.count(',')
    # to count words, we count the groups of letters divided by a space " "
    words = text.count(' ') + 1
    # calculate the readability grade
    L = (letters * 100) / words
    S = (sentences * 100) / words
    index = 0.0588 * L - 0.296 * S - 15.8
    # round the grade to the nearest integer value
    modulo = index - int(index)
    if modulo < 0.5:
        grade = int(index)
    else:
        grade = int(index) + 1
    # print the results
    if grade >= 16:
        print('Grade 16+')   
    elif grade < 1:
        print('Before Grade 1')
    else:
        print('Grade ', int(grade)) 


if __name__ == "__main__":
    main()

