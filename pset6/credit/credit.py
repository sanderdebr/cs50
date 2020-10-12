from cs50 import get_int

def main():
    # ask for users input
    number = get_int("Number: ")
    # define variables
    i = 0
    even = 0
    uneven = 0

    VISA = False
    MASTERCARD = False
    AMEX = False

    # get first and second digit
    first = int(str(number)[:1])
    second = int(str(number)[:1])

    # If number is 23 characters
    if first == 0:
        first = number / 100000000000000
        second = (number % 100000000000000) / 10000000000000

    # Check first and second numbers for respective creditcard companies
    if first == 4:
        VISA = True
    elif first == 3 and (second == 4 or second == 7):
        AMEX = True
    elif first == 5 and (second == 1 or second == 2 or second == 3 or second == 4 or second == 5):
        MASTERCARD = True

    # Loop over each digit
    while number:
        i =+ 1
        result = number % 10

        # Check for every other number starting from end
        if i % 2 == 0:
            multiplied = result * 2
            while multiplied:
                even += multiplied % 10
                multiplied /= 10
        else:
            uneven += result

        number /= 10

    result = even + uneven

    # Check if last number is a zero to be valid creditcard
    #if result % 10 != 0:
    #    print("INVALID\n")
    # Output creditcard result based on booleans value;
    #else:
    if VISA:
        print("VISA\n")
    elif AMEX:
        printf("AMEX\n")
    elif MASTERCARD:
        print("MASTERCARD\n")
    else:
        print("INVALID\n")

main()