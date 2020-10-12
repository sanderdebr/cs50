from cs50 import get_string

# Ask user for input string
userInput = get_string("Text: ")

# Loop over input
letters = 0
words = 0
sentences = 0
i = 0
n = len(userInput)

while i < n:
    # Check for letters
    if ((userInput[i] >= 'a' and userInput[i] <= 'z') or (userInput[i] >= 'A' and userInput[i] <= 'Z')):
        letters += 1
    # Check for words
    if (userInput[i] == ' '):
        words += 1
    # Check for sentences
    if (userInput[i] == '!' or userInput[i] == '?' or userInput[i] == '.'):
        sentences += 1
    i += 1

# Fix words
words += 1

#  Average number of letters per 100 words
L = (100 / words) * letters
# Average number of sentences per 100 words
S = (100 / words) * sentences

# Return Coleman-Liau index formula
formula = 0.0588 * L - 0.296 * S - 15.8

# Check max grade
if formula < 16 and formula >= 1:
    print(f"Grade {round(formula)}")
elif (formula < 1):
    print("Before Grade 1\n")
else:
    print("Grade 16+\n")