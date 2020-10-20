import sys
import csv
from cs50 import SQL

# Get access to db
db = SQL("sqlite:///students.db")

# 1. Check command line arguments
# csv.reader

if len(sys.argv) != 2:
    print("Give one argument")
else:
    # 2. Open CSV file given by command line argument
    file_name = sys.argv[1]
    with open(file_name) as file:
        reader = csv.DictReader(file)

        # 3. For each row, parse name
        # Split method, None if no middle name found
        for row in reader:
            name = row["name"].split()
            first = name[0]
            if len(name) == 3:
                middle = name[1]
                last = name[2]
            else:
                middle = None
                last = name[1]

            house = row["house"]
            birth = row["birth"]

            # 4. Insert each student into the students table of students.db
            # db.execute to INSERT a row into table

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth);