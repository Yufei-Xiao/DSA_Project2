#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Main Window Setup
    QWidget window;
    window.setWindowTitle("Sunshine Scholar");
    window.setMinimumSize(1000, 800);
    window.setStyleSheet("background-color: #f0f0f0; font-family: 'Segoe UI', sans-serif;");

    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->setContentsMargins(50, 40, 50, 40);
    layout->setSpacing(20);
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    // Global Stylesheet for the "Hand-Drawn" look
    // 1. Force a global black color and valid font size
    QString widgetStyle =
        "* {"
        "   color: #000000;"          // Deep black for all text
        "   font-size: 14pt;"         // Use 'pt' to avoid scaling errors
        "   selection-background-color: #d0d0d0;"
        "}"
        "QLabel#Title {"
        "   font-size: 28pt;"
        "   font-weight: 800;"        // Extra bold for the "Sunshine Scholar" header
        "}"
        "QLabel#Subtitle {"
        "   font-size: 12pt;"
        "   color: #1a1a1a;"          // Slightly softer black for readability
        "}"
        "QComboBox, QPushButton, QLineEdit {"
        "   border: 2px solid black;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "   background: white;"
        "   min-height: 30px;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #e0e0e0;" // Visual feedback for the click
        "}"
        "QLineEdit {"
        "   border-width: 2px;"       // Matches the "drawn" box thickness
        "}";

    app.setStyleSheet(widgetStyle);

    // UI Elements
    QLabel *title = new QLabel("Sunshine Scholar");
    title->setObjectName("Title");
    title->setAlignment(Qt::AlignCenter);

    QLabel *subtitle = new QLabel("Find the most suitable general education course for\nyou across 500 universities in the US");
    subtitle->setObjectName("Subtitle");
    subtitle->setAlignment(Qt::AlignCenter);

    QComboBox *catCombo = new QComboBox();
    catCombo->addItem("Choose a Gen Ed category");

    QComboBox *factorCombo = new QComboBox();
    factorCombo->addItem("Choose a factor for sorting");

    QComboBox *methodCombo = new QComboBox();
    methodCombo->addItem("Choose your sorting method");

    QPushButton *btn = new QPushButton("View top 10 recommendations");
    btn->setFixedWidth(300);

    // Results area
    QHBoxLayout *resLayout = new QHBoxLayout();
    QLabel *resLabel = new QLabel("Results");
    QLineEdit *resEdit = new QLineEdit();
    resLayout->addWidget(resLabel);
    resLayout->addWidget(resEdit);

    // Runtime area
    QHBoxLayout *runLayout = new QHBoxLayout();
    QLabel *runLabel = new QLabel("Runtime");
    QLineEdit *runEdit = new QLineEdit();
    runEdit->setFixedWidth(150);
    runLayout->addWidget(runLabel);
    runLayout->addWidget(runEdit);
    runLayout->addStretch();

    // Adding to main layout
    layout->addWidget(title);
    layout->addWidget(subtitle);
    layout->addSpacing(20);
    layout->addWidget(catCombo);
    layout->addWidget(factorCombo);
    layout->addWidget(methodCombo);
    layout->addSpacing(10);
    layout->addWidget(btn, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addLayout(resLayout);
    layout->addLayout(runLayout);

    window.show();
    return app.exec();
}

