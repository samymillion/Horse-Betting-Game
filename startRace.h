#ifndef STARTRACE_H
#define STARTRACE_H

#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>

class startRace : public QWidget {
    Q_OBJECT

public:
    startRace(QWidget *parent = nullptr);

signals:
    void raceFinished(int winningHorseIndex);

private slots:
    void advanceHorses();

private:
    QGridLayout *raceTrackLayout;
    QPushButton *startRaceButton;
    QVector<QVector<QPushButton*>> trackButtons;
    const int numRows = 5;
    const int numCols = 25;
    QTimer *timer;
    int horsesFinished = 0;
    int results[5];

    void setupUI();
    void showHorseRoster();
    QHBoxLayout* createButtonBar();
    QPushButton* createButton(const QString &text, int width, int height, const QString &style);
    void createRaceTrack(QVBoxLayout *mainLayout);
    void setupStartingLineButton(QPushButton *button, int row);
    bool placeHorse(int horseRow);
};

#endif // STARTRACE_H
