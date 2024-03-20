def createMatrix(n, m):
    L = [[0] * m for _ in range(n)]
    for i in range(n):
        L[i][0] = i
    for j in range(m):
        L[0][j] = j
    return L

def printMatrix(L, A, B):
    print("\n   ∅  " + "  ".join([letter for letter in B]))
    for i in range(len(A) + 1):
        print(A[i - 1] if (i != 0) else "∅", end = "")
        for j in range(len(B) + 1):
            print("  " + str(L[i][j]), end = "")
        print("")

## нерекурсивный Левенштейн
def levenshteinDistance(A, B, output = True):
    n = len(A)
    m = len(B)
    L = createMatrix(n + 1, m + 1)

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            cost = 0 if A[i - 1] == B[j - 1] else 1
            L[i][j] = min(L[i - 1][j] + 1, L[i][j - 1] + 1, L[i - 1][j - 1] + cost)

    if (output):
        print("\nМатрица, с помощью которой происходило вычисление расстояния Левенштейна:")
        printMatrix(L, A, B)

    return L[n][m]

## нерекурсивный Дамерау-Левенштейн
def damerauLevenshteinDistance(A, B, output = True):
    n = len(A)
    m = len(B)
    L = createMatrix(n + 1, m + 1)

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if A[i - 1] == B[j - 1]:
                L[i][j] = L[i - 1][j - 1]
            else:
                L[i][j] = min(L[i - 1][j], L[i][j - 1], L[i - 1][j - 1]) + 1
            
            if (i > 1 and j > 1 and A[i - 1] == B[j - 2] and A[i - 2] == B[j - 1]):
                L[i][j] = min(L[i][j], L[i - 2][j - 2] + 1)

    if (output):
        print("\nМатрица, с помощью которой происходило вычисление " +
            "расстояния Дамерау-Левенштейна:")
        printMatrix(L, A, B)

    return L[n][m]

# рекурсивный Дамерау-Левенштейн
def damerauLevenshteinDistanceRecursive(A, B, output = True):
    n = len(A)
    m = len(B)

    if ((n == 0) or (m == 0)):
        return abs(n - m)

    D = min(
        damerauLevenshteinDistanceRecursive(A[:-1], B) + 1,
        damerauLevenshteinDistanceRecursive(A, B[:-1]) + 1,
        damerauLevenshteinDistanceRecursive(A[:-1], B[:-1]) + (A[-1] != B[-1])
        )
    
    if (n > 1 and m > 1 and A[-1] == B[-2] and A[-2] == B[-1]):
        D = min(D, damerauLevenshteinDistanceRecursive(A[:-2], B[:-2]) + 1)

    return D

def recursiveWithCache(A, B, n, m, L):
    if (L[n][m] != -1):
        return L[n][m]
    
    if n == 0 or m == 0:
        L[n][m] = abs(n - m)
        return L[n][m]

    L[n][m] = min(recursiveWithCache(A, B, n - 1, m, L) + 1,
                  recursiveWithCache(A, B, n, m - 1, L) + 1,
                  recursiveWithCache(A, B, n - 1, m - 1, L) + (A[n - 1] != B[m - 1]))
    if (n > 1 and m > 1 and
        A[n - 1] == B[m - 2] and
        A[n - 2] == B[m - 1]):

        L[n][m] = min(L[n][m], recursiveWithCache(A, B, n - 2, m - 2, L) + 1)

    return L[n][m]

# рекурсивный Дамерау-Левенштейн с кэшем
def damerauLevenshteinDistanceRecurciveCache(A, B, output = True):
    n = len(A)
    m = len(B)
    L = createMatrix(n + 1, m + 1)

    for i in range(n + 1):
        for j in range(m + 1):
            L[i][j] = -1

    recursiveWithCache(A, B, n, m, L)

    if (output):
        print("\nМатрица для кеша рекурсивного нахождения расстояния Дамерау-Левенштейна:")
        printMatrix(L, A, B)

    return L[n][m]
