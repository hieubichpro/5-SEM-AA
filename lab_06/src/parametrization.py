from in_out import read_file_matrix
from algo import bruteForce, antAlgo


def parametrization(latex = False):

    alpha_arr = [num / 10 for num in range(1, 10)]
    k_eva_arr = [num / 10 for num in range(1, 9)]
    days_arr  = [50, 100, 200]

    size = 10

    matrix1 = read_file_matrix("./data/param_1.csv")
    matrix2 = read_file_matrix("./data/param_2.csv")

    optimal1 = bruteForce(matrix1, size)
    optimal2 = bruteForce(matrix2, size)

    file1 = open("parametrization_1.txt", "w")
    file2 = open("parametrization_2.txt", "w")

    count = 0
    count_all = len(alpha_arr) * len(k_eva_arr)

    print()

    for alpha in alpha_arr:
        beta = 1 - alpha

        for k_eva in k_eva_arr:
            count += 1

            for days in days_arr:
                res1 = antAlgo(matrix1, size, alpha, beta, k_eva, days)
                res2 = antAlgo(matrix2, size, alpha, beta, k_eva, days)

                if latex:
                    sep = "&"
                    end = "\\\\"
                else:
                    sep = "|" 
                    end = ""

                str1 = "%4.1f %s %4.1f %s %4.1f %s %4d %s %5d %s %5d %s\n" \
                    % (alpha, sep, beta, sep, k_eva, sep, days, sep, optimal1[0], sep, res1[0] - optimal1[0], end)

                str2 = "%4.1f %s %4.1f %s %4.1f %s %4d %s %5d %s %5d %s\n" \
                    % (alpha, sep, beta, sep, k_eva, sep, days, sep, optimal2[0], sep, res2[0] - optimal2[0], end)

                file1.write(str1)
                file2.write(str2)

            if latex:
                file1.write("\\hline\n")
                file2.write("\\hline\n")

            print("Выполнено: %3d%s" %((count / count_all) * 100, "%"))
            
    file1.close()
    file2.close()
