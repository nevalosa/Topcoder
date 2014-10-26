'''
Created on 2014-2-14

@author: hexiang
'''
import time
def orders_of_cards(N):
    start= time.clock()
    ret = [0] * N
    for i in range(N):
        a = 1 if i < N - 1 else 0 # 1%(N-i)
        for j in range(N + 1 - i, N + 1):
            a = (a + 2) if (a + 2) < j else (a + 2 - j)  # (a+2)%j
        ret[a] = i + 1
    end = time.clock()
    print end-start
    print ret

  
def orders_of_cards2(N):
    li = [0] * N
    for i in range(N):
        li[i] = recur(N,i)+1
    print li

def recur(n, k):
    "assert 0=<k<n and n>=1"
    if k == 1 or n == 1:
        return 0
    elif k == 0:
        return recur(n - 1, n - 2) + 1
    else:
        return recur(n - 1, k - 2) + 1
    

orders_of_cards2(9)
orders_of_cards(5)
