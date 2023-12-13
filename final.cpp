#include <iostream>
#include <vector>
#include <cmath>
#include <numeric> 
#include <algorithm> 

using namespace std;

float calculateCredit(float marks) {
    if (marks >= 90) {
        return 6.0;
    } else if (marks >= 80) {
        return 5.0;
    } else if (marks >= 70) {
        return 4.0;
    } else if (marks >= 50) {
        return 3.0;
    } else if (marks >= 40) {
        return 2.0;
    } else if (marks >= 30) {
        return 1.0;
    } else {
        return 0.0;
    }
}

float calculateAverageCredit(int totalCredits) {
    return static_cast<float>(totalCredits) / 6.0;
}

float calculateSGPA(const vector<float>& subjectMarks, const vector<float>& subjectCredits) {
    float sgpa = 0.0;
    float totalMarks = accumulate(subjectMarks.begin(), subjectMarks.end(), 0.0);
    float totalCredits = accumulate(subjectCredits.begin(), subjectCredits.end(), 0.0);

    if (totalCredits > 0) {
        sgpa = (totalMarks / (subjectMarks.size() * 100.0)) * 10.0; // SGPA is out of 10
        sgpa = max(0.0f, min(sgpa, 10.0f));
    } else {
        sgpa = 0.0;
    }

    return sgpa;
}

float calculateCGPA(const vector<float>& sgpaList, const vector<float>& totalCreditsList) {
    float totalCredits = accumulate(totalCreditsList.begin(), totalCreditsList.end(), 0.0);
    float weightedSum = inner_product(sgpaList.begin(), sgpaList.end(), totalCreditsList.begin(), 0.0);

    float cgpa = (weightedSum / totalCredits);
    cgpa = max(0.0f, min(cgpa, 10.0f));
    return cgpa;
}

int main() {
    int totalSemesters = 2;
    vector<float> sgpaList;
    vector<float> totalCreditsList;

    for (int semester = 1; semester <= totalSemesters; ++semester) {
        int totalCredits;
        int obtainedCredits = 0;
        cout << "Enter total credits for Semester " << semester << ": ";
        cin >> totalCredits;
        int sub = totalCredits/6;

        float avgCredit = calculateAverageCredit(totalCredits);

        vector<float> subjectMarks(6, 0.0);
        vector<float> subjectCredits(6, 0.0);

        cout << "Enter marks (out of 100) for each subject:\n";

        for (int i = 0; i < 6; ++i) {
            do {
                cout << "Enter marks for Subject " << i + 1 << ": ";
                cin >> subjectMarks[i];
                if (subjectMarks[i] > 100 || subjectMarks[i] < 0) {
                    cout << "Error!!! Enter between (0-100)" << endl;
                }
            } while (subjectMarks[i] > 100 || subjectMarks[i] < 0);

            // Assign credits based on performance using the average credit value
            subjectCredits[i] = calculateCredit(subjectMarks[i]) * avgCredit / 6.0;
            obtainedCredits = subjectCredits[i] + obtainedCredits;
        }

        float sgpa = calculateSGPA(subjectMarks, subjectCredits);
        float semesterTotalMarks = accumulate(subjectMarks.begin(), subjectMarks.end(), 0.0);

        cout << "\n***************Result Semester " << semester << "****************" << endl;
        cout << "\n";
        for (int i = 0; i < 6; ++i) {
            cout << "Subject " << i + 1 << ": Marks = " << subjectMarks[i] <<"   | Credits = "<<sub<< "   | Credits = " << subjectCredits[i] << endl;
        }
        cout << "Total Credits in Semester " << semester << ": " << obtainedCredits << endl;
        cout << "Total Marks in Semester " << semester << ": " << semesterTotalMarks << endl;
        cout << "SGPA for Semester " << semester << ": " << sgpa << endl;
        cout << "__________________________________________\n" << endl;

        sgpaList.push_back(sgpa);
        totalCreditsList.push_back(static_cast<float>(totalCredits));
    }

    float cgpa = calculateCGPA(sgpaList, totalCreditsList);
    cout << "*******Final Result***********\n" << endl;
    cout << "CGPA is: " << cgpa << "\n\n" << endl;

    return 0;
}
