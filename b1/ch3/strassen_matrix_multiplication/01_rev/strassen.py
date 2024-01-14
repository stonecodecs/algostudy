import numpy as np

def splitMatrix(X):
    row, col= X.shape # rows, cols
    Q1 = X[0:row//2, 0:col//2] # quadrant1 
    Q2 = X[0:row//2, col//2:col] # quadrant1 
    Q3 = X[row//2:row, 0:col//2] # quadrant1 
    Q4 = X[row//2:row, col//2:col] # quadrant1 

    return Q1, Q2, Q3, Q4

# for now, assume N is power of 2
def strassen(x: np.ndarray, y: np.ndarray) -> np.ndarray:
    if x.size == 1 and y.size == 1: return x*y
    if x.shape != y.shape:
        raise ValueError("input matrices X and Y must have the same shape.")
    
    # divide
    A, B, C, D = splitMatrix(x)
    E, F, G, H = splitMatrix(y)

    # conquer
    P1 = strassen(A,F-H)
    P2 = strassen(A+B,H)
    P3 = strassen(C+D,E)
    P4 = strassen(D,G-E)
    P5 = strassen(A+D,E+H)
    P6 = strassen(B-D,G+H)
    P7 = strassen(A-C,E+F)

    # combine
    result = np.vstack((np.hstack((P5 + P4 - P2 + P6, P1 + P2)),np.hstack((P3 + P4, P1 + P5 - P3 - P7))))
    return result

X_rand = np.random.randint(low=1, high=10, size=(16,16))
Y_rand = np.random.randint(low=1, high=10, size=(16,16))

X = np.array([
    [2, 4, 5, 8],
    [10, 7, 8, 9],
    [1, 7, 8, 2],
    [9, 9, 8, 6]
])

Y = np.array([
    [2, 4, 5, 8],
    [10, 7, 8, 9],
    [1, 7, 8, 2],
    [9, 9, 8, 6]
])

XY = strassen(X, Y)

print(XY)
print(X@Y == XY)

XY_rand = strassen(X_rand, Y_rand)
print (X_rand@Y_rand == XY_rand)