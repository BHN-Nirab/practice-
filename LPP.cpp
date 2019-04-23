#include <iostream>
#include<string.h>
#include <sstream>
#include <math.h>

using namespace std;

string removeUnusualChar(string objectiveFunction) {
    string tmp = "";

    for (int i = 0; i < objectiveFunction.length() - 1; i++) {
        if ((objectiveFunction[i] == 'x' || objectiveFunction[i] == 'X') &&
            (objectiveFunction[i + 1] >= '0' && objectiveFunction[i + 1] <= '9'))
            objectiveFunction[i + 1] = ' ';
    }

    for (int i = 0; i < objectiveFunction.length(); i++)
        if (objectiveFunction[i] != ' ')
            tmp = tmp + objectiveFunction[i];

    return tmp;
}

int countVar(string str) {
    int counter = 0;

    for (int i = 0; i < str.length(); i++)
        if (str[i] == 'x' || str[i] == 'X')
            counter++;
    return counter;
}

void updateCoefficientOfObjectiveFunction(string objectiveFunction, double equation[], int length) {
    for (int i = 0; i < length; i++)
        equation[i] = 0.0;

    int counter = 0;
    string tmp = "";

    for (int i = 0; i < objectiveFunction.length(); i++) {
        if ((objectiveFunction[i] >= '0' && objectiveFunction[i] <= '9') || objectiveFunction[i] == '-' ||
            objectiveFunction[i] == '+')
            tmp = tmp + objectiveFunction[i];
        else if (objectiveFunction[i] == 'x' || objectiveFunction[i] == 'X') {
            std::istringstream iss(tmp);
            iss >> equation[counter];
            counter++;
            tmp = "";
        }
    }

}

void updateCoefficientOfConstrains(string constrain, double equation[], int length) {
    for (int i = 0; i < length; i++)
        equation[i] = 0;

    int counter = 0;
    string tmp = "";

    for (int i = 0; i < constrain.length() + 1; i++) {
        if (i == constrain.length()) {
            std::istringstream iss(tmp);
            iss >> equation[counter];
            counter++;
            tmp = "";
            break;
        } else if ((constrain[i] >= '0' && constrain[i] <= '9') || constrain[i] == '-' || constrain[i] == '+')
            tmp = tmp + constrain[i];

        else if (constrain[i] == 'x' || constrain[i] == 'X') {
            std::istringstream iss(tmp);
            iss >> equation[counter];
            counter++;
            tmp = "";
        }
    }

    for (int i = 0; i < length; i++) {
        if (equation[i] == 0) {
            double tmp = equation[i - 1];
            equation[i - 1] = equation[length - 1];
            equation[length - 1] = tmp;

            break;
        }
    }

}

void makeObjectiveFuntiontoMax(double function[], int length) {
    for (int i = 0; i < length; i++)
        function[i] = function[i] * (-1);
}

void makeStandardizeFormOfConstrain(string constrain, double coefficient[], int length, int numberOfConstrain,
                                    int constrainNumber) {


    if (coefficient[length - 1] < 0) {
        for (int i = 0; i < length; i++)
            coefficient[i] = coefficient[i] * (-1);

        int indexOfLessGrteq = constrain.find("<=");

        if (indexOfLessGrteq != -1)
            constrain[indexOfLessGrteq] = '>';
        else {
            indexOfLessGrteq = constrain.find(">=");
            constrain[indexOfLessGrteq] = '<';
        }

    }

    int lessEqual = constrain.find("<=");

    if (lessEqual != -1)
        coefficient[(length - 2) - (numberOfConstrain - 1) + constrainNumber] = 1;
    else
        coefficient[(length - 2) - (numberOfConstrain - 1) + constrainNumber] = -1;
}

int search(double ara[], double key, int length) {
    for (int i = 0; i < length; i++) {
        if (ara[i] == key)
            return i;
    }
}

int getMaximum(double array[], int startingIndex, int endingIndex) {
    int maxValue = INT_MIN;
    int maxIndex;

    for (int i = startingIndex; i < endingIndex; i++) {
        if (array[i] > maxValue)
            maxValue = array[i], maxIndex = i;
    }

    return maxIndex;
}

int getMinimumForMinimization(double array[], int startingIndex, int endingIndex)
{
    int minValue = INT_MAX;
    int minIndex;

    for (int i = startingIndex; i < endingIndex; i++) {
        if (array[i] < minValue)
            minValue = array[i], minIndex = i;
    }

    return minIndex;
}

bool isOptimal(double array[], int startingIndex, int endingIndex) {
    for (int i = startingIndex; i < endingIndex; i++)
        if (array[i] > 0)
            return false;

    return true;
}

bool isOptimalForMinimization(double array[], int startingIndex, int endingIndex) {
    for (int i = startingIndex; i < endingIndex; i++)
        if (array[i] < 0)
            return false;

    return true;
}

string addCoefficient(string str) {

    for (int i = 1; i < str.length(); i++) {
        if ((str[i] == 'x' || str[i] == 'X') && str[i - 1] == '0' && i == 1)
            str[i - 1] = '1';

        else if ((str[i] == 'x' || str[i] == 'X') && str[i - 1] == '0' && !(str[i - 2] >= '0' && str[i - 2] <= '9'))
            str[i - 1] = '1';
    }

    return str;
}

int main() {

    string objectiveFunction;
    int numberOfConstrain;

    cout << "---Enter objective function---" << endl;
    getline(cin, objectiveFunction);
    objectiveFunction = addCoefficient(objectiveFunction);
    objectiveFunction = removeUnusualChar(objectiveFunction);

    cout << "---Enter number of constrain---" << endl;
    string tmp;
    getline(cin, tmp);
    std::istringstream iss(tmp);
    iss >> numberOfConstrain;

    string constrain[numberOfConstrain];

    cout << "---Enter constrains---" << endl;

    for (int i = 0; i < numberOfConstrain; i++) {
        getline(cin, constrain[i]);
        constrain[i] = addCoefficient(constrain[i]);
        constrain[i] = removeUnusualChar(constrain[i]);
    }

    int numberOfVar = countVar(objectiveFunction);

    int lengthOfcoefficientOfObjectiveFunction = numberOfConstrain + numberOfVar;
    double coefficientOfObjectiveFunction[lengthOfcoefficientOfObjectiveFunction];
    double coefficientOfConstrains[numberOfConstrain][lengthOfcoefficientOfObjectiveFunction + 1];

    updateCoefficientOfObjectiveFunction(objectiveFunction, coefficientOfObjectiveFunction,
                                         lengthOfcoefficientOfObjectiveFunction);

    for (int i = 0; i < numberOfConstrain; i++)
        updateCoefficientOfConstrains(constrain[i], coefficientOfConstrains[i],
                                      lengthOfcoefficientOfObjectiveFunction + 1);

    cout << "---1.Minimization / 2.Maximization (1/2)---" << endl;
    string ch;
    getline(cin, ch);

    if (ch == "1") {
        //makeObjectiveFuntiontoMax(coefficientOfObjectiveFunction, lengthOfcoefficientOfObjectiveFunction);

        for (int i = 0; i < numberOfConstrain; i++)
            makeStandardizeFormOfConstrain(constrain[i], coefficientOfConstrains[i],
                                           lengthOfcoefficientOfObjectiveFunction + 1, numberOfConstrain, i);

        int m = numberOfConstrain + 3;
        int n = lengthOfcoefficientOfObjectiveFunction + 3;
        double table[m][n];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                table[i][j] = INT_MAX;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j > 0 && j < (n - 2))
                    table[i][j] = coefficientOfObjectiveFunction[j - 1];

                if (j == 0 && i > 0 && i < m - 2)
                    table[i][j] = 0;

                if (i > 0 && j > 0 && i < m - 2 && j < n - 1)
                    table[i][j] = coefficientOfConstrains[i - 1][j - 1];

                if (i == (m - 2) && j > 0 && j < (n - 2))
                    table[i][j] = 0;
                if (i == (m - 1) && j > 0 && j < (n - 2))
                    table[i][j] = table[0][j] - table[i - 1][j];
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                cout << table[i][j] << "\t";

            cout << endl;
        }
        cout << endl;

        do {
            int enteringColumn = getMinimumForMinimization(table[m - 1], 1, n - 2);

            //find ratio
            for (int i = 1; i < m - 2; i++) {
                if (table[i][enteringColumn] > 0)
                    table[i][n - 1] = table[i][n - 2] / table[i][enteringColumn];
                else
                    table[i][n - 1] = INT_MAX;
            }

            int leavingRow;

            int minValue = INT_MAX;
            int minIndex;

            for (int i = 1; i < m - 2; i++) {
                if (table[i][n - 1] < minValue)
                    minValue = table[i][n - 1], minIndex = i;
            }

            leavingRow = minIndex;

            table[leavingRow][0] = table[0][enteringColumn];

            for (int i = 1; i < m - 2; i++) {
                for (int j = 1; j < n - 1; j++) {
                    if (i != leavingRow && j != enteringColumn) {
                        double oldValue = table[i][j];
                        table[i][j] = oldValue - ((table[leavingRow][j] * table[i][enteringColumn]) /
                                                  table[leavingRow][enteringColumn]);
                    }
                }

                if (i != leavingRow)
                    table[i][enteringColumn] = 0;
            }

            double keyValue = table[leavingRow][enteringColumn];
            for (int i = 1; i < n - 1; i++)
                table[leavingRow][i] = table[leavingRow][i] / keyValue;

            for (int j = 1; j < n - 2; j++) {
                double sum = 0;
                for (int i = 1; i < m - 2; i++) {
                    sum = sum + table[i][0] * table[i][j];
                }

                table[m - 2][j] = sum;
            }

            for (int i = 1; i < n - 2; i++)
                table[m - 1][i] = table[0][i] - table[m - 2][i];


            cout << "keyValue: " << keyValue << endl;

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++)
                    cout << table[i][j] << "\t";

                cout << endl;
            }
            cout << endl;

        } while (!isOptimalForMinimization(table[m - 1], 1, n - 2));

        double solution = 0;

        for (int i = 1; i < m - 2; i++)
            solution = solution + table[i][0] * table[i][n - 2];

        cout << "Solution is: " << solution << endl;

        for (int i = 1; i < m - 2; i++) {
            if (table[i][0] != 0) {
                int index = search(coefficientOfObjectiveFunction, table[i][0], lengthOfcoefficientOfObjectiveFunction);
                if (coefficientOfConstrains[index] != 0)
                    cout << "x" << index + 1 << " : " << table[i][n - 2] << endl;
            }
        }
    }

    else if(ch=="2")
    {
        for (int i = 0; i < numberOfConstrain; i++)
            makeStandardizeFormOfConstrain(constrain[i], coefficientOfConstrains[i],
                                           lengthOfcoefficientOfObjectiveFunction + 1, numberOfConstrain, i);

        int m = numberOfConstrain + 3;
        int n = lengthOfcoefficientOfObjectiveFunction + 3;
        double table[m][n];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                table[i][j] = INT_MAX;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j > 0 && j < (n - 2))
                    table[i][j] = coefficientOfObjectiveFunction[j - 1];

                if (j == 0 && i > 0 && i < m - 2)
                    table[i][j] = 0;

                if (i > 0 && j > 0 && i < m - 2 && j < n - 1)
                    table[i][j] = coefficientOfConstrains[i - 1][j - 1];

                if (i == (m - 2) && j > 0 && j < (n - 2))
                    table[i][j] = 0;
                if (i == (m - 1) && j > 0 && j < (n - 2))
                    table[i][j] = table[0][j] - table[i - 1][j];
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                cout << table[i][j] << "\t";

            cout << endl;
        }
        cout << endl;

        do {
            int enteringColumn = getMaximum(table[m - 1], 1, n - 2);

            //find ratio
            for (int i = 1; i < m - 2; i++) {
                if (table[i][enteringColumn] > 0)
                    table[i][n - 1] = table[i][n - 2] / table[i][enteringColumn];
                else
                    table[i][n - 1] = INT_MAX;
            }

            int leavingRow;

            int minValue = INT_MAX;
            int minIndex;

            for (int i = 1; i < m - 2; i++) {
                if (table[i][n - 1] < minValue)
                    minValue = table[i][n - 1], minIndex = i;
            }

            leavingRow = minIndex;

            table[leavingRow][0] = table[0][enteringColumn];

            for (int i = 1; i < m - 2; i++) {
                for (int j = 1; j < n - 1; j++) {
                    if (i != leavingRow && j != enteringColumn) {
                        double oldValue = table[i][j];
                        table[i][j] = oldValue - ((table[leavingRow][j] * table[i][enteringColumn]) /
                                                  table[leavingRow][enteringColumn]);
                    }
                }

                if (i != leavingRow)
                    table[i][enteringColumn] = 0;
            }

            double keyValue = table[leavingRow][enteringColumn];
            for (int i = 1; i < n - 1; i++)
                table[leavingRow][i] = table[leavingRow][i] / keyValue;

            for (int j = 1; j < n - 2; j++) {
                double sum = 0;
                for (int i = 1; i < m - 2; i++) {
                    sum = sum + table[i][0] * table[i][j];
                }

                table[m - 2][j] = sum;
            }

            for (int i = 1; i < n - 2; i++)
                table[m - 1][i] = table[0][i] - table[m - 2][i];


            cout << "keyValue: " << keyValue << endl;

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++)
                    cout << table[i][j] << "\t";

                cout << endl;
            }
            cout << endl;

        } while (!isOptimal(table[m - 1], 1, n - 2));

        double solution = 0;

        for (int i = 1; i < m - 2; i++)
            solution = solution + table[i][0] * table[i][n - 2];

        cout << "Solution is: " << solution << endl;

        for (int i = 1; i < m - 2; i++) {
            if (table[i][0] > 0) {
                int index = search(coefficientOfObjectiveFunction, table[i][0], lengthOfcoefficientOfObjectiveFunction);
                if (coefficientOfConstrains[index] != 0)
                    cout << "x" << index + 1 << " : " << table[i][n - 2] << endl;
            }
        }




    }

    return 0;
}
/*12x1 + 16x2
4
10x1 + 20x2 <=120
8x1 + 8x2 <= 80
1x1 >= 0
0x1 + 1x2 >= 0*/
/*
-2x1 + 3x2 - 4x3
2
3x1 <= 20
-5x1 + 2x2 >= -10*/
/*
1x1 + 2x2
2
3x1 - 2x2 <= 20
-3x1 + 5x2 + 15x3>= 30*/

/*
-2x1 + 3x2 - 4x3
3
3x1 <= 20
-5x1 + 2x2 >= -10
-3x1 + 5x2 + 15x3>= 30
2
 */
/*
12x1+16x2
2
10x1 + 20x2 >=120
8x1 + 8x2 <=80
1
 */

/*
1x1 + 2x2
2
1x1 + 1x2 <=12
1x1 + 2x2 <=22
2*/
/*

12x1 + 3x2 + 1x3
3
10x1 + 2x2 + 1x3 <= 100
7x1 + 3x2 + 2x3 <= 77
2x1 + 4x2 + 1x3 <=80
2

*/

/*
300x1 + 36x2 + 90x3
2
60x1 + 12x2 + 10x3 <= 0.12
60x1 + 6x2 + 30x3 <= 0.15
2*/
/*
5x1 + 5x2
3
1x1 + 1x2 >= 5
1x1 + 1x2 <= 9
1x1 + 2x2 <= 10
2
 */
/*
8x1 + 9x2
3
2x1 + 3x2 <=50
2x1 + 6x2 <= 80
3x1 + 3x2 <= 70

1x1 + 2x2 + 4x3
3
3x1 + 1x2 + 5x3 <= 10
1x1 + 4x2 + 1x3 <= 8
2x1 + 1x2 + 2x3 <=7
2
*/

/*
1x1 + 2x2 + 4x3
3
3x1 + 1x2 + 5x3 <= 10
1x1 + 4x2 + 1x3 <= 8
2x1 + 0x2 + 2x3 <= 7
2
 */
/*
1x1 - 3x2 + 3x3
3
3x1 - 1x2 + 2x3 <= 7
2x1 + 4x2 >= -12
-4x1 + 3x2 + 8x3 <= 10
1*/
