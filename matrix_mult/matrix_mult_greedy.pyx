#for use sys.maxint
import sys
import numpy as np  # Importa la biblioteca numpy



def matrix_mult_chain_order(p):
    cdef int i, j, k
    n=len(p)-1
   
    # Create a matrix to store the results of subproblems
    m = [[0 for x in range(n)] for x in range(n)]
    s = [[0 for x in range(n-1)] for x in range(n-1)]

    # Cost is zero when multiplying one matrix.
    for i in range(n):
        m[i][i] = 0

    #iterates in the possible sizes of our parenthesis (contains 2 matrices, 3, ..., n)
    for L in range(2, n+1):
        #and we move the parentheses in steps of size L
        for i in range(n-L+1):
            j = i+L-1  
            m[i][j] = 2**31 - 1 #a very large number
            for k in range(i, j):
                # q = cost/scalar multiplications
                #print(p[i-1])
                #print(p[k])
                #print(p[j])
                q = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1]
                if q < m[i][j]:
                    m[i][j] = q
                    s[i][j-1] = k

    return m,s


def get_optimal(i, j, s):
    if i == j:
        print(f'A{i}', end='')
    else:
        print("(", end="")
        get_optimal(i, s[i][j-1], s)
        get_optimal(s[i][j-1] + 1, j, s)
        print(")", end="")



