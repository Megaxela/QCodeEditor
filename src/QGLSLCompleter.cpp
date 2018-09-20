// QCodeEditor
#include <QGLSLCompleter>

// Qt
#include <QStringListModel>
#include <QtWidgets/QCompleter>

QGLSLCompleter::QGLSLCompleter(QObject *parent) :
    QCompleter(parent)
{
    // Setting up GLSL types
    QStringList list;

    list << "radians"          << "degrees"       << "sin"
         << "cos"              << "tan"           << "asin"
         << "acos"             << "atan"          << "pow"
         << "exp"              << "log"           << "exp2"
         << "log2"             << "sqrt"          << "inversesqrt"
         << "abs"              << "sign"          << "floor"
         << "ceil"             << "fract"         << "mod"
         << "min"              << "max"           << "clamp"
         << "mix"              << "step"          << "smoothstep"
         << "length"           << "distance"      << "dot"
         << "cross"            << "normalize"     << "faceforward"
         << "reflect"          << "refract"       << "matrixCompMult"
         << "lessThan"         << "lessThanEqual" << "greaterThan"
         << "greaterThanEqual" << "equal"         << "notEqual"
         << "any"              << "all"           << "not"
         << "texture2D"        << "textureCube";

    setModel(new QStringListModel(list, this));
    setCompletionColumn(0);
    setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    setCaseSensitivity(Qt::CaseSensitive);
    setWrapAround(true);
}
