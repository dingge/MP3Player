#include <QApplication>
#include <QAudioFormat>
#include <QAudioOutput>
#include "customwindow.h"
#include "mpg123.h"
#include "audioengine.h"

#define INBUFF  16384
#define OUTBUFF 32768

void loadMp3File(QString);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));
    QPalette p;
    p = qApp->palette();
    p.setColor(QPalette::Highlight, QColor(39,146,217,120));
    p.setColor(QPalette::HighlightedText, QColor(0,0,0));
    qApp->setPalette(p);
    AudioEngine engine(0);
	engine.show();

    return app.exec();
}
