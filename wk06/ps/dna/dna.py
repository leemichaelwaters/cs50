import csv
import sys


def main():

    # Check for command-line usage
    # argv[1] name of CSV file containg STR counts for a list of individuals
    # argv[2] name of text file containing the DNA sequence to identify
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Extract person database
    with open(sys.argv[1], "r") as file:
        person_database = []
        dict_reader = csv.DictReader(file)
        for row in dict_reader:
            person_database.append(row)

        # Change str counts to int
        for person in person_database:
            for key in person:
                # Can't conver name key to int
                try:
                    person[key] = int(person[key])
                except:
                    pass

    # Extract sequence
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        header = True
        strs = []
        for row in reader:
            if header:
                strs = row[1:]  # remove "name"
                break

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    for str in strs:
        str_counts.update({str: longest_match(sequence, str)})

    # Check database for matching profiles
    true_count = 0  # str matches per person
    found = 0       # flag for whether match found
    # loop over person
    for person in person_database:
        # loop over str, count
        for k, v in str_counts.items():
            if (k, v) in person.items():
                true_count += 1
            else:
                break
        # check if everything matches
        if true_count == len(str_counts):
            found = person['name']
            break
        # if not, reset counter and check next person
        else:
            true_count = 0

    if found:
        print(found)
    else:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()