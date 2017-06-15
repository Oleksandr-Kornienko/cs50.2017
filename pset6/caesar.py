import cs50
import sys

key = int(sys.argv[1])

plaintext =  str(input('plaintext: '))

print("ciphertext: ", end ='')

for i in plaintext:
    number = ord(i)
    if (number>=65 and number<=90)or(number>=97 and number<=122):
        lower = 0
        if i.islower():
           number = number - 32
           lower = 1
        changedNumber = (number + key)%26
        if changedNumber >= 13:
            changedNumber = changedNumber + 52
        else : changedNumber = changedNumber + 78
        if lower==1:
            print(chr(changedNumber+32), end ='')
        else : print(chr(changedNumber), end ='')
    else: print(i,end='')
print()
