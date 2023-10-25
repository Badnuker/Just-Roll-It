#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTextStream>
#include <algorithm>
#include <chrono>
#include <random>

class JustRollIt : public QMainWindow
{
    Q_OBJECT

public:
    JustRollIt(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        setWindowTitle("抽奖工具");

        QVBoxLayout *layout = new QVBoxLayout;

        inputFileButton = new QPushButton("选择参与者名单文件");
        connect(inputFileButton, &QPushButton::clicked, this, &JustRollIt::loadParticipantsFromFile);
        layout->addWidget(inputFileButton);

        numParticipantsLabel = new QLabel("参与者人数：");
        layout->addWidget(numParticipantsLabel);

        numWinnersLabel = new QLabel("中奖者人数：");
        numWinnersInput = new QLineEdit;
        winnersLayout = new QHBoxLayout;
        winnersLayout->addWidget(numWinnersLabel);
        winnersLayout->addWidget(numWinnersInput);
        layout->addLayout(winnersLayout);

        startButton = new QPushButton("开始抽奖");
        connect(startButton, &QPushButton::clicked, this, &JustRollIt::startLottery);
        layout->addWidget(startButton);

        winnersLabel = new QLabel("中奖者名单：");
        layout->addWidget(winnersLabel);

        winnersTextEdit = new QTextEdit;
        winnersTextEdit->setReadOnly(true);
        layout->addWidget(winnersTextEdit);

        QWidget *centralWidget = new QWidget;
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);
    }

private slots:
    void loadParticipantsFromFile()
    {
        QString fileName = QFileDialog::getOpenFileName(this, "选择参与者名单文件");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                int numParticipants = 0;
                while (!in.atEnd()) {
                    in.readLine();
                    numParticipants++;
                }
                file.close();
                numParticipantsLabel->setText("参与者人数：" + QString::number(numParticipants));
                participants.clear();

                file.open(QIODevice::ReadOnly | QIODevice::Text);
                while (!in.atEnd()) {
                    participants.append(in.readLine());
                }
                file.close();
            } else {
                QMessageBox::critical(this, "错误", "无法打开文件。");
            }
        }
    }

    void startLottery()
    {
        int numWinners = numWinnersInput->text().toInt();
        if (numWinners <= 0 || numWinners > participants.size()) {
            QMessageBox::warning(this,
                                 "警告",
                                 "无效的中奖者人数。请确保中奖者人数大于0且不超过参与者人数。");
            return;
        }

        winnersTextEdit->clear();

        QList<QString> remainingParticipants = participants;

        std::shuffle(remainingParticipants.begin(),
                     remainingParticipants.end(),
                     std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count()));

        for (int i = 0; i < numWinners; ++i) {
            if (remainingParticipants.isEmpty()) {
                QMessageBox::warning(this, "警告", "所有参与者已中奖。");
                break;
            }
            QString winner = remainingParticipants.takeFirst();
            winnersTextEdit->append(QString::number(i + 1) + ". " + winner);
        }
    }

private:
    QPushButton *inputFileButton;
    QLabel *numParticipantsLabel;
    QLabel *numWinnersLabel;
    QLineEdit *numWinnersInput;
    QPushButton *startButton;
    QLabel *winnersLabel;
    QTextEdit *winnersTextEdit;
    QHBoxLayout *winnersLayout;
    QStringList participants;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    JustRollIt justRollIt;
    justRollIt.show();
    return app.exec();
}

#include "main.moc"
