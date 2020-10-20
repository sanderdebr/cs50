import sys
import csv
from cs50 import SQL

# Get access to db
db = SQL("sqlite:///students.db")

# 1. Check command line arguments
if len(sys.argv) != 2:
    print("Give one argument")
else:

    # 2. Query database for all students in house
    # db.execute to SELECT rows - will return a list of dicts (rows)
    # Check for NULL values for middle names
    house = sys.argv[1]
    result = db.execute("SELECT * FROM students WHERE HOUSE = ? ORDER BY last, first", house);
    for row in result:
        first = row["first"]
        middle = row["middle"]
        last = row["last"]
        birth = row["birth"]

        if middle == None:
            print(first,last,", born",birth)
        else:
            print(first,middle,last,", born",birth)

# 3. Print out each student't full name and birt year
# Should be sorted alphabetically by last name, then first name