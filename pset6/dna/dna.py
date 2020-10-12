import csv
import re
from sys import argv, exit

# 1. Open CSV file and DNA sequence, read contents into memory
def main():
    # Check if arguments are okay
    arguments = check_arguments()
    # Open CSV file and retrieve its data
    db = open_file(arguments[1])
    # Open sequence file and retrieve its data
    sq = open_file(arguments[2])
    # Check DNA for first STR
    STRs = []

    for k in range(len(db[0])):
        if k > 0:
            STRs.append(checkDNA(db[0][k], sq[0][0]))

    # Compare with people
    result = []

    for i in range(len(db)):
        if i > 0:
            result.append(compareData(STRs, db[i]))

    # No match found
    if all(x is None for x in result):
        print("No match")
    # Print out the only match found
    else:
        for item in result:
            if (item):
                print(item)

# Check if all arguments are given
def check_arguments():
    if len(argv) != 3:
        print("missing command-line argument")
        exit(1)
    return argv

# Open CSV files and load into memory
def open_file(file):
    with open(file) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        data = []
        for row in csv_reader:
            data.append(row)
        return data

# 2. For each STR, compute longest run of consecutive repeats in the DNA sequence
def checkDNA(STR, sq):
    STRlength = len(STR)
    counter = 0
    maxCount = []

    # check each letter till STR match
    for i in range(len(sq)):
        batch = sq[i:i + STRlength]
        if (STR == batch):
            # match found, check consecutives
            j = 0
            while j < 10000:
                # Get the next batch
                needle = i + ( STRlength *  j)
                nextBatch = sq[needle:needle + STRlength]
                # If match, add counter
                if (STR == nextBatch):
                    counter += 1
                else:
                    break
                j += 1
            # After looping, add num to maxCount array
            maxCount.append(counter)
            counter = 0
    # Return the highest num in maxCount array
    return max(maxCount)

#def checkDNA(STR, sq):
#    groups = re.findall(STR, sq)
#    return len(groups)

# 3. Compare STR counts against each row in CSV file
# For each row in the data, check if each STR count matches. If so, print out the person's name
def compareData(STRs, person):
    matches = 0
    needs = len(STRs)
    for i in range(len(person)):
        if i > 0:
            if int(person[i]) == STRs[i - 1]:
                matches += 1

    if matches == needs:
        return person[0]

# Startup program
main()