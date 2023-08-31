#ifndef PYTHON_CODE_EDITOR_HPP
#define PYTHON_CODE_EDITOR_HPP

#include <QPlainTextEdit>
#include <QObject>
#include <QtWidgets>
#include <QWidget>
#include <QSize>
#include <QPaintEvent>
#include <QResizeEvent>

class PythonCodeEditor: public QPlainTextEdit
{
     Q_OBJECT

public:
    explicit PythonCodeEditor(QWidget *parent = nullptr);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};


class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    LineNumberArea(PythonCodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    PythonCodeEditor *codeEditor;
};
#endif // PYTHON_CODE_EDITOR_HPP
