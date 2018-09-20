#include <internal/QSyntaxStyle.hpp>

// Qt
#include <QDebug>
#include <QXmlStreamReader>

QSyntaxStyle::QSyntaxStyle(QObject* parent) :
    QObject(parent),
    m_name(),
    m_data(),
    m_loaded(false)
{

}

bool QSyntaxStyle::load(QString fl)
{
    QXmlStreamReader reader(fl);

    while (!reader.atEnd() && !reader.hasError())
    {
        auto token = reader.readNext();

        if(token == QXmlStreamReader::StartElement)
        {
            if (reader.name() == "style-scheme")
            {
                if (reader.attributes().hasAttribute("name"))
                {
                    m_name = reader.attributes().value("name").toString();
                }
            }
            else if (reader.name() == "style")
            {
                auto attributes = reader.attributes();

                auto name = attributes.value("name");

                QTextCharFormat format;

                if (attributes.hasAttribute("background"))
                {
                    format.setBackground(QColor(attributes.value("background")));
                }

                if (attributes.hasAttribute("foreground"))
                {
                    format.setForeground(QColor(attributes.value("foreground")));
                }

                if (attributes.hasAttribute("bold") &&
                    attributes.value("bold") == "true")
                {
                    format.setFontWeight(QFont::Weight::Bold);
                }

                if (attributes.hasAttribute("italic") &&
                    attributes.value("italic") == "true")
                {
                    format.setFontItalic(true);
                }

                if (attributes.hasAttribute("underlineStyle"))
                {
                    auto underline = attributes.value("underlineStyle");

                    auto s = QTextCharFormat::UnderlineStyle::NoUnderline;

                    if (underline == "SingleUnderline")
                    {
                        s = QTextCharFormat::UnderlineStyle::SingleUnderline;
                    }
                    else if (underline == "DashUnderline")
                    {
                        s = QTextCharFormat::UnderlineStyle::DashUnderline;
                    }
                    else if (underline == "DotLine")
                    {
                        s = QTextCharFormat::UnderlineStyle::DotLine;
                    }
                    else if (underline == "DashDotLine")
                    {
                        s = QTextCharFormat::DashDotLine;
                    }
                    else if (underline == "DashDotDotLine")
                    {
                        s = QTextCharFormat::DashDotDotLine;
                    }
                    else if (underline == "WaveUnderline")
                    {
                        s = QTextCharFormat::WaveUnderline;
                    }
                    else if (underline == "SpellCheckUnderline")
                    {
                        s = QTextCharFormat::SpellCheckUnderline;
                    }
                    else
                    {
                        qDebug() << "Unknown underline value " << underline;
                    }

                    format.setUnderlineStyle(s);
                }

                m_data[name.toString()] = format;
            }
        }
    }

    m_loaded = !reader.hasError();

    return m_loaded;
}

QString QSyntaxStyle::name() const
{
    return m_name;
}

QTextCharFormat QSyntaxStyle::getFormat(QString name) const
{
    auto result = m_data.find(name);

    if (result == m_data.end())
    {
        return QTextCharFormat();
    }

    return result.value();
}

bool QSyntaxStyle::isLoaded() const
{
    return m_loaded;
}

QSyntaxStyle* QSyntaxStyle::defaultStyle()
{
    static QSyntaxStyle style;

    if (!style.isLoaded())
    {
        style.load(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<style-scheme version=\"1.0\" name=\"Default\">\n"
            "  <style name=\"Text\" foreground=\"#000000\" background=\"#ffffff\"/>\n"
            "  <style name=\"Link\" foreground=\"#0000ff\"/>\n"
            "  <style name=\"Selection\" foreground=\"#eff0f1\" background=\"#3daee9\"/>\n"
            "  <style name=\"LineNumber\" foreground=\"#000000\" background=\"#31363b\"/>\n"
            "  <style name=\"SearchResult\" background=\"#ffef0b\"/>\n"
            "  <style name=\"SearchScope\" background=\"#2d5c76\"/>\n"
            "  <style name=\"Parentheses\" foreground=\"#ff0000\" background=\"#b4eeb4\"/>\n"
            "  <style name=\"ParenthesesMismatch\" background=\"#ff00ff\"/>\n"
            "  <style name=\"AutoComplete\" foreground=\"#000080\" background=\"#c0c0ff\"/>\n"
            "  <style name=\"CurrentLine\" background=\"#eeeeee\"/>\n"
            "  <style name=\"CurrentLineNumber\" foreground=\"#808080\" bold=\"true\"/>\n"
            "  <style name=\"Occurrences\" background=\"#b4b4b4\"/>\n"
            "  <style name=\"Occurrences.Unused\" underlineColor=\"#808000\" underlineStyle=\"SingleUnderline\"/>\n"
            "  <style name=\"Occurrences.Rename\" background=\"#ff6464\"/>\n"
            "  <style name=\"Number\" foreground=\"#000080\"/>\n"
            "  <style name=\"String\" foreground=\"#008000\"/>\n"
            "  <style name=\"Type\" foreground=\"#800080\"/>\n"
            "  <style name=\"Local\" foreground=\"#092e64\"/>\n"
            "  <style name=\"Global\" foreground=\"#ce5c00\"/>\n"
            "  <style name=\"Field\" foreground=\"#800000\"/>\n"
            "  <style name=\"Static\" foreground=\"#800080\"/>\n"
            "  <style name=\"VirtualMethod\" foreground=\"#00677c\" background=\"#ffffff\" italic=\"true\"/>\n"
            "  <style name=\"Function\" foreground=\"#00677c\" background=\"#ffffff\"/>\n"
            "  <style name=\"Keyword\" foreground=\"#808000\"/>\n"
            "  <style name=\"PrimitiveType\" foreground=\"#808000\"/>\n"
            "  <style name=\"Operator\"/>\n"
            "  <style name=\"Overloaded Operator\"/>\n"
            "  <style name=\"Preprocessor\" foreground=\"#000080\"/>\n"
            "  <style name=\"Label\" foreground=\"#800000\"/>\n"
            "  <style name=\"Comment\" foreground=\"#008000\"/>\n"
            "  <style name=\"Doxygen.Comment\" foreground=\"#000080\"/>\n"
            "  <style name=\"Doxygen.Tag\" foreground=\"#0000ff\"/>\n"
            "  <style name=\"VisualWhitespace\" foreground=\"#c0c0c0\"/>\n"
            "  <style name=\"QmlLocalId\" foreground=\"#000000\" background=\"#ffffff\" italic=\"true\"/>\n"
            "  <style name=\"QmlExternalId\" foreground=\"#000080\" background=\"#ffffff\" italic=\"true\"/>\n"
            "  <style name=\"QmlTypeId\" foreground=\"#800080\"/>\n"
            "  <style name=\"QmlRootObjectProperty\" foreground=\"#000000\" background=\"#ffffff\" italic=\"true\"/>\n"
            "  <style name=\"QmlScopeObjectProperty\" foreground=\"#000000\" background=\"#ffffff\" italic=\"true\"/>\n"
            "  <style name=\"QmlExternalObjectProperty\" foreground=\"#000080\" background=\"#ffffff\" italic=\"true\"/>\n"
            "  <style name=\"JsScopeVar\" foreground=\"#2985c7\" background=\"#ffffff\" italic=\"true\"/>\n"
            "  <style name=\"JsImportVar\" foreground=\"#0055af\" background=\"#ffffff\" italic=\"true\"/>\n"
            "  <style name=\"JsGlobalVar\" foreground=\"#0055af\" background=\"#ffffff\" italic=\"true\"/>\n"
            "  <style name=\"QmlStateName\" foreground=\"#000000\" background=\"#ffffff\" italic=\"true\"/>\n"
            "  <style name=\"Binding\" foreground=\"#800000\"/>\n"
            "  <style name=\"DisabledCode\" background=\"#efefef\"/>\n"
            "  <style name=\"AddedLine\" foreground=\"#00aa00\"/>\n"
            "  <style name=\"RemovedLine\" foreground=\"#ff0000\"/>\n"
            "  <style name=\"DiffFile\" foreground=\"#000080\"/>\n"
            "  <style name=\"DiffLocation\" foreground=\"#0000ff\"/>\n"
            "  <style name=\"DiffFileLine\" background=\"#ffff00\"/>\n"
            "  <style name=\"DiffContextLine\" background=\"#afd7e7\"/>\n"
            "  <style name=\"DiffSourceLine\" background=\"#ffdfdf\"/>\n"
            "  <style name=\"DiffSourceChar\" background=\"#ffafaf\"/>\n"
            "  <style name=\"DiffDestLine\" background=\"#dfffdf\"/>\n"
            "  <style name=\"DiffDestChar\" background=\"#afffaf\"/>\n"
            "  <style name=\"LogChangeLine\" foreground=\"#c00000\"/>\n"
            "  <style name=\"Warning\" underlineColor=\"#ffbe00\" underlineStyle=\"SingleUnderline\"/>\n"
            "  <style name=\"WarningContext\" underlineColor=\"#ffbe00\" underlineStyle=\"DotLine\"/>\n"
            "  <style name=\"Error\" underlineColor=\"#ff0000\" underlineStyle=\"SingleUnderline\"/>\n"
            "  <style name=\"ErrorContext\" underlineColor=\"#ff0000\" underlineStyle=\"DotLine\"/>\n"
            "  <style name=\"Declaration\" bold=\"true\"/>\n"
            "  <style name=\"FunctionDefinition\"/>\n"
            "  <style name=\"OutputArgument\" italic=\"true\"/>\n"
            "</style-scheme>"
        );
    }

    return &style;
}
