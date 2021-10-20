import sys
import csv

# Main function


def main():

    # Check arguments
    if len(sys.argv) != 3:
        print("Incomplete arguments!")

    # Extract the STR names(key for our dictionary) from persons record file
    with open(sys.argv[1], 'r') as peopledata:
        csvdictreader = csv.DictReader(peopledata)
        header = csvdictreader.fieldnames
        header.pop(0)

    # Dictionary for storing highest repeatative STR count
    strcount = {i: 0 for i in header}

    # Reset header (list) to count integer
    for i in range(len(header)):
        header[i] = 0

    # Load DNA sequence file
    with open(sys.argv[2], 'r') as sequencefile:

        # Read sequence file and store it into sequence string
        sequence = sequencefile.read()

        # Lets keep track of how many str type we calculated
        index = 0
        for str in strcount:
            # Give i the position of the first STR of current STR type
            i = sequence.find(str)
            header[index] += 1
            while i >= 0 and i < len(sequence):
                # Next STR is of same type found
                if sequence.find(str, i + len(str), i + 2 * len(str)) != -1:
                    header[index] += 1
                # Next STR is not of same type
                else:
                    if strcount[str] < header[index]:
                        strcount[str] = header[index]
                    header[index] = 0

                # Update i until we found all str of current type
                i = sequence.find(str, i + len(str))
                if header[index] == 0:
                    header[index] += 1
            index += 1

    # Load all person data into DictReader object
    with open(sys.argv[1], 'r') as peopledata:
        people = csv.DictReader(peopledata)

        # Flag for DNA match or not
        personfound = False

        # Count how many STR matches for each person
        strmatch = 0

        # Lets check which person matches DNA STR same as sequence
        for person in people:
            # Check for all STR type
            for strtype in strcount:
                if int(person[strtype]) == strcount[strtype]:
                    # Total STR matches
                    strmatch += 1

            # Does all STR type matches
            if strmatch == len(strcount):
                personfound = True
                print(person['name'])
                break

            # Reset strmatch count for other person
            strmatch = 0

        # Look like no person matches with this sequence
        if personfound == False:
            print('No match')


# Calling main
if __name__ == "__main__":
    main()