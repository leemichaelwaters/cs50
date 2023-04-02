from cs50 import get_string


def main():
    text = get_text()
    letter_count = count_letters(text)
    word_count = count_words(text)
    sentence_count = count_sentences(text)
    grade = get_grade(letter_count, word_count, sentence_count)
    print_grade(grade)


def get_text():
    return get_string("Text: ")


def count_letters(text):
    count = 0
    for c in text:
        if c.islower() or c.isupper():
            count += 1
    return count


def count_words(text):
    count = 0
    for c in text:
        if c == ' ':
            count += 1
    return count + 1  # add one for last word


def count_sentences(text):
    count = 0
    for c in text:
        if (c == '.' or c == '!' or c == '?'):
            count += 1
    return count


def get_grade(letters, words, sentences):
    letters_per_100 = letters / words * 100
    sentences_per_100 = sentences / words * 100
    index = round(0.0588 * letters_per_100 - 0.296 * sentences_per_100 - 15.8)
    return index


def print_grade(grade):
    if (grade < 1):
        print("Before Grade 1")
    elif (grade > 16):
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()