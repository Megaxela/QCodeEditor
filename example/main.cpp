
// Qt
#include <QApplication>
#include <QMainWindow>
#include <QDebug>

// QCodeEditor
#include <QCodeEditor>
#include <QCXXHighlighter>
#include <QSyntaxStyle>
#include <QGLSLCompleter>

const char* codeSample = R"(
/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QCoreApplication>
#include <QTextStream>

#include "game.h"
//! [0]
int main(int argc, char *argv[])
{
)" "\t" R"(QCoreApplication app(argc, argv);
    QStringList args = QCoreApplication::arguments();
    bool newGame = true;
    if (args.length() > 1)
        newGame = (args[1].toLower() != QStringLiteral("load"));
    bool json = true;
    if (args.length() > 2)
        json = (args[2].toLower() != QStringLiteral("binary"));

    Game game;
    if (newGame)
        game.newGame();
    else if (!game.loadGame(json ? Game::Json : Game::Binary))
            return 1;
    // Game is played; changes are made...
//! [0]
//! [1]
    QTextStream(stdout) << "Game ended in the following state:\n";
    game.print();
    if (!game.saveGame(json ? Game::Json : Game::Binary))
        return 1;

    return 0;
}
//! [1]

)";

const char* darkulaStyle = R"(<?xml version="1.0" encoding="UTF-8"?>
<style-scheme version="1.0" name="Dracula">
  <style name="Text" foreground="#f8f8f2" background="#282a36"/>
  <style name="Link" foreground="#8be9fd" underlineStyle="SingleUnderline"/>
  <style name="Selection" background="#44475a"/>
  <style name="LineNumber" foreground="#6272a4"/>
  <style name="SearchResult" foreground="#d57544" bold="true"/>
  <style name="SearchScope" foreground="#000000" background="#f8f8f2"/>
  <style name="Parentheses" foreground="#f8f8f2" bold="true"/>
  <style name="ParenthesesMismatch" foreground="#f8f8f2"/>
  <style name="AutoComplete" foreground="#f8f8f2"/>
  <style name="CurrentLine" foreground="#000000" background="#383b4c"/>
  <style name="CurrentLineNumber" foreground="#f8f8f2"/>
  <style name="Occurrences" foreground="#000000" background="#f8f8f2"/>
  <style name="Occurrences.Unused" foreground="#f8f8f2"/>
  <style name="Occurrences.Rename" foreground="#000000" background="#f8f8f2"/>
  <style name="Number" foreground="#bd93f9"/>
  <style name="String" foreground="#f1fa8c"/>
  <style name="Type" foreground="#7ce4fb"/>
  <style name="Local" foreground="#ffffff"/>
  <style name="Global" foreground="#ffb86c"/>
  <style name="Field" foreground="#ffffff"/>
  <style name="Static" foreground="#ffb86c"/>
  <style name="VirtualMethod" foreground="#50fa7b" italic="true"/>
  <style name="Function" foreground="#50fa7b"/>
  <style name="Keyword" foreground="#ff79c6" bold="true"/>
  <style name="PrimitiveType" foreground="#7ce4fb" italic="true"/>
  <style name="Operator" foreground="#ffffff"/>
  <style name="Overloaded Operator"/>
  <style name="Preprocessor" foreground="#ff79c6"/>
  <style name="Label" foreground="#ffb86c"/>
  <style name="Comment" foreground="#6272a4" bold="true"/>
  <style name="Doxygen.Comment" foreground="#6272a4"/>
  <style name="Doxygen.Tag" foreground="#6272a4" bold="true"/>
  <style name="VisualWhitespace" foreground="#6272a4"/>
  <style name="QmlLocalId" foreground="#50fa7b" italic="true"/>
  <style name="QmlExternalId" foreground="#ffb86c" italic="true"/>
  <style name="QmlTypeId" foreground="#8be9fd"/>
  <style name="QmlRootObjectProperty" foreground="#50fa7b" italic="true"/>
  <style name="QmlScopeObjectProperty" foreground="#50fa7b" italic="true"/>
  <style name="QmlExternalObjectProperty" foreground="#ffb86c" italic="true"/>
  <style name="JsScopeVar" foreground="#bd93f9" italic="true"/>
  <style name="JsImportVar" foreground="#8be9fd" italic="true"/>
  <style name="JsGlobalVar" foreground="#8be9fd" italic="true"/>
  <style name="QmlStateName" foreground="#50fa7b" italic="true"/>
  <style name="Binding" foreground="#ff79c6"/>
  <style name="DisabledCode" foreground="#6272a4"/>
  <style name="AddedLine" foreground="#50fa7b"/>
  <style name="RemovedLine" foreground="#ff5555"/>
  <style name="DiffFile" foreground="#8be9fd"/>
  <style name="DiffLocation" foreground="#ffb86c"/>
  <style name="DiffFileLine" foreground="#282a36" background="#f1fa8c"/>
  <style name="DiffContextLine" foreground="#282a36" background="#8be9fd"/>
  <style name="DiffSourceLine" background="#ff5555"/>
  <style name="DiffSourceChar" background="#cc2222"/>
  <style name="DiffDestLine" foreground="#282a36" background="#50fa7b"/>
  <style name="DiffDestChar" foreground="#282a36" background="#1dc748"/>
  <style name="LogChangeLine" foreground="#ff5555"/>
  <style name="Warning" underlineColor="#ffb86c" underlineStyle="SingleUnderline"/>
  <style name="WarningContext" underlineColor="#ffb86c" underlineStyle="DotLine"/>
  <style name="Error" underlineColor="#ff5555" underlineStyle="SingleUnderline"/>
  <style name="ErrorContext" underlineColor="#ff5555" underlineStyle="DotLine"/>
  <style name="Declaration" bold="true"/>
  <style name="FunctionDefinition"/>
  <style name="OutputArgument" italic="true"/>
</style-scheme>)";



int main(int argc, char** argv)
{
    // Creating application
    QApplication a(argc, argv);

    // Creating main window
    QMainWindow w;

    // Creating new style object (must be deleted before return)
    auto style = new QSyntaxStyle();

    // Loading style from XML string
    if (!style->load(darkulaStyle))
    {
        qDebug() << "Can't parse style.";
        return 1;
    }

    // Creating editor widget
    auto editor = new QCodeEditor(&w);

    // Setting up
    editor->setSyntaxStyle(style);
    editor->setHighlighter(new QCXXHighlighter);
    editor->setCompleter(new QGLSLCompleter(editor));
    editor->setWordWrapMode(QTextOption::NoWrap);
    editor->setPlainText(codeSample);

    w.setCentralWidget(editor);
    w.show();

    // Running application
    auto result = QApplication::exec();

    delete style;

    return result;
}