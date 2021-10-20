from cs50 import get_string

# Main function


def main():
    text = get_string("Text: ")

    # L is the average number of letters per 100 words in the text.
    L = float(countLetters(text)) / countWords(text) * 100

    # S is the average number of sentences per 100 words in the text.
    S = float(countSentences(text)) / countWords(text) * 100

    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")

    elif index >= 16:
        print("Grade 16+")

    else:
        print("Grade ", index)


def countLetters(text):
    letters = 0
    for i in range(len(text)):
        # Alphabet occurs, increment letters
        if text[i].isalpha():
            letters += 1
    return letters


def countWords(text):
    words = 0
    spaceFlag = False
    for i in range(len(text)):
        # Space occurs reset space_flag
        if text[i].isspace():
            spaceFlag = False
        # If character is first letter of word, increment words
        if text[i].isalpha() and spaceFlag == False:
            words += 1
            spaceFlag = True
    return words


def countSentences(text):
    sentences = 0
    for i in range(len(text)):
        # Sentence ended increment sentences
        if text[i] in {
            '.',
            '!',
            '?'
        }:
            sentences += 1
    return sentences


# Calling main
if __name__ == "__main__":
    main()