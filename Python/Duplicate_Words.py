'''
PROGRAM TO IDENTIFY DUPLICATE WORDS FROM A GIVEN STRING
'''


# initializing string 
string = input("Enter the string: ")
cnt=0; i,j,k=0,0,0

for x in string:
        if x==' ':
            cnt+=1
            
flag=0
res = string.split()

print("The following words are duplicate:-\n")
while i<=cnt:
    word_cnt=0
    j=0; k=0; flag=0
    while k<i:
        if res[i]==res[k]:
            flag=1; break
        k+=1
    if flag!=1:    
        while j<=cnt:
            if res[i]==res[j]:
                word_cnt+=1
            j+=1
    if word_cnt>1:
        print(res[i])
    i+=1
