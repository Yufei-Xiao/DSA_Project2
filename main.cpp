#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Gen Ed Course Finder");
    window.resize(420,250);

    QLabel title("Gen Ed Course Finder");
    title.setAlignment(Qt::AlignCenter);

    QPushButton button("Get Easiest Gen Ed Course");

    QLabel resultLabel("Result will appear here");
    resultLabel.setAlignment(Qt::AlignCenter);
    resultLabel.setWordWrap(true);

    QVBoxLayout layout;
    layout.setSpacing(20);
    layout.setContentsMargins(40,30,40,30);

    layout.addWidget(&title);
    layout.addWidget(&button);
    layout.addWidget(&resultLabel);

    window.setLayout(&layout);

    QObject::connect(&button, &QPushButton::clicked, [&]() {
        resultLabel.setText("University of Florida — Intro to Film Studies");
    });

    window.setStyleSheet(R"(

        QWidget {
            background-color: #f5f7fb;
        }

        QLabel {
            font-size: 16px;
            color: #333333;
        }

        QPushButton {
            background-color: #3b82f6;
            color: white;
            border-radius: 6px;
            padding: 6px 12px;
            font-size: 14px;
        }

        QPushButton:hover {
            background-color: #2563eb;
        }

    )");

    title.setStyleSheet("font-size:20px; font-weight:bold;");
    resultLabel.setStyleSheet(
        "background:white; padding:10px; border:1px solid #ddd; border-radius:6px;"
    );

    window.show();

    return app.exec();
}

