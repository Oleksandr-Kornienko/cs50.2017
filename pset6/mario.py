import cs50

while True:
    number = int(input("Введіть ціле число від 0 до 23:\n"))
    if number>=0 and number<=23:
        break;
i=1
empty=1
for i in range(number):
    for empty in range(number-i-1):
        print(" ", end='')
    for symbol in range(i+2):
        print("#", end='')
    print("")

    

