#include <QCoreApplication>
#include <QString>
#include <QBuffer>
#include <QDataStream>
#include <QDebug>

/**
 * We create a buffer in the memory, then we create a stream which can write into it.
 * Finally we crete another stream for the same buffer which can read from it.
 */
int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    // The buffer stores the data
    QByteArray buffer;
    // The stream which will write (there is no WriteOnly like flag).
    // The stream is able to track where it points and where can it write to.
    // However, it does not have storage, that is why we gave the buffer to the constructor
    QDataStream stream(&buffer, QIODevice::ReadWrite);

    QString text1("ABCD");
    QString text2("EFG");

    // Writing into the stream. A QString can be written into a stream
    //  and can be read out too.
    stream << text1;
    stream << text2;

    // The stream which will read from the stream.
    // The two stream can access the buffer simultaneously without any conflicts
    QDataStream readStream(&buffer, QIODevice::ReadOnly);
    QString readText1;
    QString readText2;

    // It is important, that both QStrings know their own length,
    // therefore it is not required to search their boundaries.
    // This makes the serialization of complex data structures compfortable,
    // since only the data should be read out one after other

    readStream >> readText1;
    readStream >> readText2;

    // Checking the reads
    qDebug() << "Text1: " << readText1;
    qDebug() << "Text2: " << readText2;

    // And checking the raw content of the buffer
    qDebug() << "A buffer: " << buffer.toHex();

    /* A the output:
     * Text1:  "ABCD"
     * Text2:  "EFG"
     * A buffer:  "00000008004100420043004400000006004500460047"
     *
     * The QString first stores its length in bytes, in 32 bit
     * (00000008) than the characters with UTF-16 encoding:
     * A (0041), B (0042), C (0043), D (0044). Then comes the
     * second QString
     */
}
