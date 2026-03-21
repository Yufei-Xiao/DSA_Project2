#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QDebug>
#include <QDialog>
#include <QSpinBox>
#include <QMessageBox>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include "Course.h"
using namespace std;
using namespace std::chrono;

vector<Course> importCSV(string filename) {

    vector<Course> courses;
    courses.reserve(500000);
    ifstream file(filename);

    if (!file.is_open()) {
        qDebug() << "Error: Could not find CSV file!";
        return courses;
    }

    string line, temp;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        Course c;

        getline(ss, c.course_code, ',');
        getline(ss, c.course_name, ',');
        getline(ss, c.university, ',');
        getline(ss, c.category, ',');

        getline(ss, temp, ','); c.avg_gpa = stof(temp);
        getline(ss, temp, ','); c.workload_hours = stof(temp);
        getline(ss, temp, ','); c.course_rating = stof(temp);
        getline(ss, temp, ','); c.professor_rating = stof(temp);
        getline(ss, temp, ','); c.overall_rating = stof(temp);

        courses.push_back(c);
    }
    return courses;
}
void merge(vector<Course>& courses, int left,int middle, int right,string factor) {
    int size1=middle+1-left;
    int size2=right-middle;
    Course* X=new Course[size1];
    Course* Y=new Course[size2];
    for (int i=0;i<size1;i++) {
        X[i]=courses[left+i];
    }
    for (int j=0;j<size2;j++) {
        Y[j]=courses[middle+1+j];
    }
    int k=left;
    int i=0;
    int j=0;
    if (factor=="GPA"){
        while (i<size1 && j<size2) {
            if (X[i].avg_gpa>=Y[j].avg_gpa) {
                courses[k]=X[i];
                i++;
            }else if (X[i].avg_gpa<Y[j].avg_gpa) {
                courses[k]=Y[j];
                j++;
            }
            k++;
        }
    }else if (factor=="Workload") {
        while (i<size1 && j<size2) {
            if (X[i].workload_hours<=Y[j].workload_hours) {
                courses[k]=X[i];
                i++;
            }else if (X[i].workload_hours>Y[j] .workload_hours) {
                courses[k]=Y[j];
                j++;
            }
            k++;
        }
    }else if (factor=="Rating") {
        while (i<size1 && j<size2) {
            if (X[i].overall_rating>=Y[j].overall_rating) {
                courses[k]=X[i];
                i++;
            }else if (X[i].overall_rating<Y[j].overall_rating) {
                courses[k]=Y[j];
                j++;
            }
            k++;
        }
    }else if (factor=="Personal Preference") {
        while (i<size1 && j<size2) {
            if (X[i].personal_rating>=Y[j].personal_rating) {
                courses[k]=X[i];
                i++;
            }else if (X[i].personal_rating<Y[j].personal_rating) {
                courses[k]=Y[j];
                j++;
            }
            k++;
        }
    }
    while (i<size1) {
        courses[k]=X[i];
        k++;
        i++;
    }
    while (j<size2) {
        courses[k]=Y[j];
        k++;
        j++;
    }
    delete[] X;
    delete[] Y;

}
void merge_sort(vector<Course>& courses,int left,int right,string factor) {
    if (left<right) {
        int middle = left+(right-left)/2;
        merge_sort(courses, left, middle,factor);
        merge_sort(courses, middle+1, right,factor);
        merge(courses,left,middle,right,factor);
    }
}
int partition(vector<Course>& courses,int low,int high,string factor) {
    int up=low;
    int down=high;
    Course pivot=courses[low];
    if (factor=="GPA") {
        while (up<down) {
            for (int i=up;i<high;i++) {
                if (courses[up].avg_gpa<pivot.avg_gpa) {
                    break;
                }
                up++;
            }
            for (int i=down;i>low;i--) {
                if (courses[down].avg_gpa>pivot.avg_gpa) {
                    break;
                }
                down--;
            }
            if (up<down) {
                Course temp=courses[up];
                courses[up]=courses[down];
                courses[down]=temp;
            }
        }
    }else if (factor=="Workload") {
        while (up<down) {
            for (int i=up;i<high;i++) {
                if (courses[up].workload_hours>pivot.workload_hours) {
                    break;
                }
                up++;
            }
            for (int i=down;i>low;i--) {
                if (courses[down].workload_hours<pivot.workload_hours) {
                    break;
                }
                down--;
            }
            if (up<down) {
                Course temp=courses[up];
                courses[up]=courses[down];
                courses[down]=temp;
            }
        }
    }else if (factor=="Rating") {
        while (up<down) {
            for (int i=up;i<high;i++) {
                if (courses[up].overall_rating<pivot.overall_rating) {
                    break;
                }
                up++;
            }
            for (int i=down;i>low;i--) {
                if (courses[down].overall_rating>pivot.overall_rating) {
                    break;
                }
                down--;
            }
            if (up<down) {
                Course temp=courses[up];
                courses[up]=courses[down];
                courses[down]=temp;
            }
        }
    }else if (factor=="Personal Preference") {
        while (up<down) {
            for (int i=up;i<high;i++) {
                if (courses[up].personal_rating<pivot.personal_rating) {
                    break;
                }
                up++;
            }
            for (int i=down;i>low;i--) {
                if (courses[down].personal_rating>pivot.personal_rating) {
                    break;
                }
                down--;
            }
            if (up<down) {
                Course temp=courses[up];
                courses[up]=courses[down];
                courses[down]=temp;
            }
        }
    }
    Course temp=courses[down];
    courses[down]=courses[low];
    courses[low]=temp;
    return down;
}
void quick_sort(vector<Course>& courses,int low,int high,string factor) {
    if (low<high) {
        int pivot=partition(courses,low,high,factor);
        quick_sort(courses,low,pivot-1,factor);
        quick_sort(courses,pivot+1,high,factor);
    }
}
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    vector<Course> allCourses = importCSV("E:/DSA Project2/cmake-build-debug/Data/gen_ed_courses_500k.csv");

    QWidget window;
    window.setWindowTitle("Sunshine Scholar");
    window.setMinimumSize(1500, 1200);

    window.setStyleSheet(
    "* {"
    "   color: #2c3e50;"
    "   font-family: 'Segoe UI', system-ui, -apple-system, sans-serif;"
    "}"
    "QWidget {"
    "   background-color: #ffffff;"
    "}"


    "QLabel#Title {"
    "   color: #2980b9;"
    "   font-size: 42pt;"
    "   font-weight: 900;"
    "   letter-spacing: -1px;"
    "   margin-top: 20px;"
    "   margin-bottom: 20px;"
    "}"


    "QLabel {"
    "   font-size: 14pt;"
    "   font-weight: 700;"
    "   color: #34495e;"
    "}"


    "QComboBox, QLineEdit, QTextEdit {"
    "   border: 2px solid #bdc3c7;"
    "   border-radius: 10px;"
    "   padding: 12px 20px;"
    "   background-color: #ffffff;"
    "   font-size: 13pt;"
    "   selection-background-color: #3498db;"
    "}"
    "QComboBox:hover, QLineEdit:hover {"
    "   border: 2px solid #3498db;"
    "}"


    "QPushButton {"
    "   background-color: #3498db;"
    "   color: white;"
    "   font-size: 16pt;"
    "   font-weight: 800;"
    "   border-radius: 12px;"
    "   padding: 18px;"
    "   min-width: 300px;"
    "}"
    "QPushButton:hover {"
    "   background-color: #2980b9;"
    "}"


    "QTextEdit#ResultsArea {"
    "   background-color: #f9fbfd;"
    "   border: 2px solid #dcdde1;"
    "   font-family: 'Consolas', 'Monaco', monospace;"
    "   font-size: 14pt;"
    "   line-height: 1.8;"
    "   color: #2f3640;"
    "}"


    "QLabel#RuntimeLabel {"
    "   font-size: 12pt;"
    "   color: #7f8c8d;"
    "   font-weight: 400;"
    "   font-style: italic;"
    "}"
);

    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->setContentsMargins(50, 40, 50, 40);
    layout->setSpacing(15);

    QLabel *title = new QLabel("Sunshine Scholar");
    title->setObjectName("Title");
    title->setAlignment(Qt::AlignCenter);

    QComboBox *catCombo = new QComboBox();
    catCombo->addItems({"Choose Category", "Math", "Humanities", "Social Sciences", "Physical Science", "Biological Sciences"});

    QComboBox *factorCombo = new QComboBox();
    factorCombo->addItems({"Select factor", "Sort by: Average GPA","Sort by: Workload", "Sort by: Overall Rating", "Sort by: Personal Preference"});


    QComboBox *algoCombo = new QComboBox();
    algoCombo->addItems({"Select Algorithm", "Quick Sort", "Merge Sort"});

    QPushButton *btn = new QPushButton("Find Top 10 Recommendations");
    btn->setFixedWidth(400);


    QTextEdit *resArea = new QTextEdit();
    resArea->setPlaceholderText("Results will appear here...");
    resArea->setReadOnly(true);

    QLabel *runLabel = new QLabel("Execution Time: -- ms");
    runLabel->setObjectName("RuntimeLabel");
    QLabel *sizeLabel = new QLabel("");
    sizeLabel->setObjectName("SizeLabel");


    layout->addWidget(title);
    layout->addWidget(new QLabel("Step 1: Select Category"));
    layout->addWidget(catCombo);
    layout->addWidget(new QLabel("Step 2: Select Sorting Factor"));
    layout->addWidget(factorCombo);
    layout->addWidget(new QLabel("Step 3: Select Sorting Algorithm"));
    layout->addWidget(algoCombo); // Dropdown added here
    layout->addSpacing(10);
    layout->addWidget(btn, 0, Qt::AlignCenter);
    layout->addSpacing(10);
    layout->addWidget(new QLabel("Top 10 Results:"));
    layout->addWidget(resArea);
    layout->addWidget(new QLabel("Runtime:"));
    layout->addWidget(runLabel);
    layout->addWidget(new QLabel("Data Size:"));
    layout->addWidget(sizeLabel);


    float gpaWeight=0;
    float ratingWeight=0;
    float workloadWeight=0;
    QObject::connect(factorCombo, &QComboBox::currentTextChanged, [&](const QString &text){
        while(text == "Sort by: Personal Preference") {

            QDialog dialog;
            dialog.setWindowTitle("Set Ranking Weights");
            dialog.setMinimumWidth(400);
            dialog.setStyleSheet(
                "QDialog { background-color: #ffffff; border: 3px solid #3498db; border-radius: 15px; }"

                "QLabel { "
                "   font-size: 16pt; font-weight: 800; color: #2c3e50; margin-top: 10px; "
                "}"

                "QSpinBox { "
                "   background-color: #f8fafc; "
                "   color: #1e293b; "
                "   border: 2px solid #bdc3c7; "
                "   border-radius: 10px; "
                "   padding: 12px; "
                "   font-size: 20pt; "
                "   font-weight: bold; "
                "   qproperty-alignment: 'AlignCenter'; "
                "}"
                "QSpinBox:focus { border: 2px solid #3498db; background-color: #ffffff; }"


                "QSpinBox::up-button, QSpinBox::down-button { "
                "   width: 0px; "
                "   height: 0px; "
                "   border: none; "
                "}"

                "QPushButton { "
                "   background-color: #27ae60; color: #ffffff; font-size: 16pt; "
                "   font-weight: 900; border-radius: 10px; padding: 20px; margin-top: 20px; "
                "}"
                "QPushButton:hover { background-color: #2ecc71; }"
            );

            QVBoxLayout layout(&dialog);

            QLabel gpaLabel("GPA Weight (%)");
            QLabel ratingLabel("Professor Rating Weight (%)");
            QLabel workloadLabel("Workload Weight (%)");

            QSpinBox gpaBox;
            QSpinBox ratingBox;
            QSpinBox workloadBox;

            gpaBox.setRange(0,100);
            ratingBox.setRange(0,100);
            workloadBox.setRange(0,100);

            gpaBox.setValue(40);
            ratingBox.setValue(40);
            workloadBox.setValue(20);

            QPushButton confirm("Confirm");

            layout.addWidget(&gpaLabel);
            layout.addWidget(&gpaBox);
            layout.addWidget(&ratingLabel);
            layout.addWidget(&ratingBox);
            layout.addWidget(&workloadLabel);
            layout.addWidget(&workloadBox);
            layout.addWidget(&confirm);

            QObject::connect(&confirm, &QPushButton::clicked, &dialog, &QDialog::accept);

            if(dialog.exec() == QDialog::Accepted){

                int g = gpaBox.value();
                int r = ratingBox.value();
                int w = workloadBox.value();

                if(g + r + w != 100){
                    QMessageBox::warning(&window, "Invalid Input", "Weights must sum to 100%");
                    continue;
                }else {
                    gpaWeight = g / 100.0;
                    ratingWeight = r / 100.0;
                    workloadWeight = w / 100.0;
                    break;
                }


            }
        }

    });
    QObject::connect(btn, &QPushButton::clicked, [&]() {

        string selectedCat = catCombo->currentText().toStdString();
        string selectedFactor = factorCombo->currentText().toStdString();
        string selectedAlgorithm = algoCombo->currentText().toStdString();

        if (catCombo->currentIndex() == 0) {
            resArea->setText("Please select a category first.");
            return;
        }
        if (factorCombo->currentIndex() == 0) {
            resArea->setText("Please select a factor first.");
            return;
        }
        if (algoCombo->currentIndex() == 0) {
            resArea->setText("Please select an algorithm first.");
            return;
        }

        vector<Course> filtered;
        for (auto& c : allCourses) {
            c.personal_rating=c.avg_gpa*gpaWeight/4.0+c.professor_rating*ratingWeight/5.0-c.workload_hours*workloadWeight/15.0;
            if (c.category == selectedCat) filtered.push_back(c);
        }
        auto start = high_resolution_clock::now();
        // Sort
        if (selectedFactor=="Sort by: Average GPA") {
            if (selectedAlgorithm == "Merge Sort") {
                merge_sort(filtered,0,filtered.size()-1,"GPA");
            }else if (selectedAlgorithm == "Quick Sort") {
                quick_sort(filtered,0,filtered.size()-1,"GPA");
            }
        }else if (selectedFactor=="Sort by: Workload") {
            if (selectedAlgorithm == "Merge Sort") {
                merge_sort(filtered,0,filtered.size()-1,"Workload");
            }else if (selectedAlgorithm == "Quick Sort") {
                quick_sort(filtered,0,filtered.size()-1,"Workload");
            }
        }else if (selectedFactor=="Sort by: Overall Rating") {
            if (selectedAlgorithm == "Merge Sort") {
                merge_sort(filtered,0,filtered.size()-1,"Rating");
            }else if (selectedAlgorithm == "Quick Sort") {
                quick_sort(filtered,0,filtered.size()-1,"Rating");
            }
        }else if (selectedFactor=="Sort by: Personal Preference") {
            if (selectedAlgorithm == "Merge Sort") {
                merge_sort(filtered,0,filtered.size()-1,"Personal Preference");
            }else if (selectedAlgorithm == "Quick Sort") {
                quick_sort(filtered,0,filtered.size()-1,"Personal Preference");
            }
        }
        auto end = high_resolution_clock::now();
        // Display Top 10
        QString displayBuffer = "";
        int limit = min((int)filtered.size(), 10);

        for (int i = 0; i < limit; ++i) {
            displayBuffer += QString("%1. %2  %3 - %4  Average GPA:%5  Workload:%6  Professor Rating:%7  (Overall Rating: %8)\n")
                .arg(i + 1)
                .arg(QString::fromStdString(filtered[i].course_code))
                .arg(QString::fromStdString(filtered[i].course_name))
                .arg(QString::fromStdString(filtered[i].university))
                .arg(filtered[i].avg_gpa)
                .arg(filtered[i].workload_hours)
                .arg(filtered[i].professor_rating)
                .arg(filtered[i].overall_rating);
        }

        resArea->setText(displayBuffer);


        auto duration = duration_cast<milliseconds>(end - start);
        runLabel->setText(QString::number(duration.count()) + " ms");
        sizeLabel->setText(QString::number(filtered.size()));
    });
    window.showMaximized();
    window.show();
    return app.exec();
}