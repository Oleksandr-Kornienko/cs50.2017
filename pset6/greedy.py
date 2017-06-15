import cs50

change =  float(input('Введіть число: '))
change = change * 100;
coins = 0
while True:
    if change>=25:
        change = change - 25;
        coins = coins + 1;
    else:
        break;
        
while True:
    if change>=10:
        change = change - 10;
        coins = coins + 1;
    else:
        break;
        
while True:
    if change>=5:
        change = change - 5;
        coins = coins + 1;
    else:
        break;
        
while True:
    if change>=1:
        change = change - 1;
        coins = coins + 1;
    else:
        break;
        
print(coins)