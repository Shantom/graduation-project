S = []
movieIDs = []
userIDs = []

with open('output.csv') as file:
    data = file.readlines()
    movies=data[0].split(',')
    print(len(movies))
