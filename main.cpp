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


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Load Data once
    // Use the FULL path from your E: drive based on your screenshot
    vector<Course> allCourses = importCSV("E:/DSA Project2/cmake-build-debug/Data/gen_ed_courses_500k.csv");

    QWidget window;
    window.setWindowTitle("Sunshine Scholar");
    window.setMinimumSize(1000, 800);

    window.setStyleSheet(
    // Global text and background
    "* {"
    "   color: #2c3e50;"
    "   font-family: 'Segoe UI', sans-serif;"
    "}"
    "QWidget {"
    "   background-color: #fdfdfd;"
    "}"

    // Header
    "QLabel#Title {"
    "   color: #2980b9;"
    "   font-size: 32pt;"
    "   font-weight: 900;"
    "   margin-bottom: 10px;"
    "}"

    // Inputs and Dropdowns
    "QComboBox, QLineEdit, QTextEdit {"
    "   border: 2px solid #bdc3c7;"
    "   border-radius: 8px;"
    "   padding: 8px 15px;"
    "   background-color: #ffffff;"
    "   selection-background-color: #3498db;"
    "}"
    "QComboBox:hover, QLineEdit:hover {"
    "   border: 2px solid #3498db;"
    "}"
    "QComboBox::drop-down {"
    "   border: 0px;" // Removes default arrow box
    "}"

    // The Action Button
    "QPushButton {"
    "   background-color: #3498db;"
    "   color: white;"
    "   font-weight: bold;"
    "   border-radius: 8px;"
    "   padding: 12px;"
    "   min-width: 200px;"
    "}"
    "QPushButton:hover {"
    "   background-color: #2980b9;"
    "}"
    "QPushButton:pressed {"
    "   background-color: #1f6391;"
    "}"

    // Results Area
    "QTextEdit {"
    "   background-color: #f9f9f9;"
    "   font-family: 'Consolas', 'Monaco', monospace;" // Monospace for better list alignment
    "   font-size: 11pt;"
    "   line-height: 1.5;"
    "}"

    // Runtime Label
    "QLabel#RuntimeLabel {"
    "   font-size: 10pt;"
    "   color: #7f8c8d;"
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
    factorCombo->addItems({"Sort by: Overall Rating", "Sort by: Avg GPA", "Sort by: Workload", "Sort by: Course Rating"});

    // New Algorithm Dropdown
    QComboBox *algoCombo = new QComboBox();
    algoCombo->addItems({"Select Algorithm", "Quick Sort", "Merge Sort"});

    QPushButton *btn = new QPushButton("Find Top 10 Recommendations");
    btn->setFixedWidth(400);

    // Results and Runtime area
    QTextEdit *resArea = new QTextEdit();
    resArea->setPlaceholderText("Results will appear here...");
    resArea->setReadOnly(true);

    QLabel *runLabel = new QLabel("Execution Time: -- ms");
    runLabel->setObjectName("RuntimeLabel");


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
    layout->addWidget(runLabel);

    QObject::connect(btn, &QPushButton::clicked, [&]() {
        auto start = high_resolution_clock::now();

        string selectedCat = catCombo->currentText().toStdString();
        string selectedFactor = factorCombo->currentText().toStdString();

        if (catCombo->currentIndex() == 0) {
            resArea->setText("Please select a category first.");
            return;
        }

        vector<Course> filtered;
        for (const auto& c : allCourses) {
            if (c.category == selectedCat) filtered.push_back(c);
        }

        // Sort
        sort(filtered.begin(), filtered.end(), [&](const Course& a, const Course& b) {
            if (selectedFactor == "Sort by: Avg GPA") return a.avg_gpa > b.avg_gpa;
            if (selectedFactor == "Sort by: Workload") return a.workload_hours < b.workload_hours;
            if (selectedFactor == "Sort by: Course Rating") return a.course_rating > b.course_rating;
            return a.overall_rating > b.overall_rating;
        });

        // Display Top 10
        QString displayBuffer = "";
        int limit = min((int)filtered.size(), 10);

        for (int i = 0; i < limit; ++i) {
            displayBuffer += QString("%1. [%2] %3 - %4 (Score: %5)\n")
                .arg(i + 1)
                .arg(QString::fromStdString(filtered[i].course_code))
                .arg(QString::fromStdString(filtered[i].course_name))
                .arg(QString::fromStdString(filtered[i].university))
                .arg(filtered[i].overall_rating);
        }

        resArea->setText(displayBuffer);

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        runLabel->setText(QString::number(duration.count()) + " ms");
    });

    window.show();
    return app.exec();
}