#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QFileInfo>
#include <QImage>
#include <QDir>
#include <QDebug>

namespace {
constexpr uint16_t color565(uint8_t red, uint8_t green, uint8_t blue) noexcept
{
    return __builtin_bswap16(((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3));
}
uint16_t color565(const QColor &color) noexcept
{
    return color565(color.red(), color.green(), color.blue());
}
} // namespace

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("iconconvert");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Converts icons to .h/.cpp sources");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("icon", QCoreApplication::translate("main", "Icon file."));
    parser.addPositionalArgument("destination", QCoreApplication::translate("main", "Destination directory."));
    parser.addPositionalArgument("header-templ", QCoreApplication::translate("main", "Header template"));
    parser.addPositionalArgument("footer-templ", QCoreApplication::translate("main", "Footer template"));

    parser.process(app);

    const QStringList args = parser.positionalArguments();
    if (args.size() < 1)
    {
        qCritical("icon missing!");
        parser.showHelp();
        return -1;
    }

    if (args.size() < 2)
    {
        qCritical("destination missing!");
        parser.showHelp();
        return -2;
    }

    if (args.size() < 3)
    {
        qCritical("header-templ missing!");
        parser.showHelp();
        return -3;
    }

    if (args.size() < 4)
    {
        qCritical("footer-templ missing!");
        parser.showHelp();
        return -4;
    }

    QFileInfo fileInfo{args.at(0)};
    if (!fileInfo.exists())
    {
        qCritical("icon not found!");
        return -5;
    }

    QImage image;
    if (!image.load(args.at(0)) || image.size().isEmpty())
    {
        qCritical("could not load icon!");
        return -6;
    }

    QString bytes;
    {
        std::size_t i{};

        for (int y = 0; y < image.height(); y++)
            for (int x = 0; x < image.width(); x++)
            {
                if (i == 0)
                {
                    bytes += "    ";
                }
                else
                    bytes += ", ";

                bytes += QStringLiteral("0x%0").arg(color565(image.pixel(x, y)), 4, 16, QLatin1Char('0'));

                if (++i == 16)
                {
                    i = 0;
                    bytes += ",\n";
                }
            }
    }

    QDir dir{args.at(1)};
    if (!dir.exists())
    {
        if (!dir.mkpath(dir.absolutePath()))
        {
            qCritical("could not create target directory");
            return -7;
        }
    }

    {
        QString templ;

        {
            QFile file{args.at(2)};
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qCritical("could not open header template (for reading) %s", qPrintable(file.errorString()));
                return -8;
            }

            templ = file.readAll();
        }

        {
            QFile file{dir.absoluteFilePath(QStringLiteral("%0.h").arg(fileInfo.baseName()))};
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
            {
                qCritical("could not open .h file for writing %s", qPrintable(file.errorString()));
                return -9;
            }

            const auto content = templ
                                     .replace("${name}", fileInfo.baseName())
                                     .replace("${width}", QString::number(image.width()))
                                     .replace("${height}", QString::number(image.height()))
                                     .toUtf8();
            const std::size_t contentSize = content.size();
            if (const std::size_t written = file.write(content); written != contentSize)
            {
                qCritical("error while writing %zd != %zd %s", written, contentSize, qPrintable(file.errorString()));
                return -10;
            }
        }
    }

    {
        QString templ;

        {
            QFile file{args.at(3)};
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qCritical("could not open source template (for reading) %s", qPrintable(file.errorString()));
                return -8;
            }

            templ = file.readAll();
        }

        {
            QFile file{dir.absoluteFilePath(QStringLiteral("%0.cpp").arg(fileInfo.baseName()))};
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
            {
                qCritical("could not open .cpp file for writing %s", qPrintable(file.errorString()));
                return -8;
            }

            const auto content = templ
                                     .replace("${name}", fileInfo.baseName())
                                     .replace("${width}", QString::number(image.width()))
                                     .replace("${height}", QString::number(image.height()))
                                     .replace("${bytes}", bytes)
                                     .toUtf8();
            const std::size_t contentSize = content.size();
            if (const std::size_t written = file.write(content); written != contentSize)
            {
                qCritical("error while writing %zd != %zd %s", written, contentSize, qPrintable(file.errorString()));
                return -10;
            }
        }
    }

    qDebug() << fileInfo.baseName() << image.width() << image.height();

    return 0;
}
