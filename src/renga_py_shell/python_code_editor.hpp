#ifndef PYTHON_CODE_EDITOR_HPP
#define PYTHON_CODE_EDITOR_HPP

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;


class python_code_editor: public QPlainTextEdit
{
     Q_OBJECT
public:
    explicit python_code_editor(QWidget *parent = 0);
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
public:
    LineNumberArea(python_code_editor *editor) : QWidget(editor) {
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
    python_code_editor *codeEditor;
};
#endif // PYTHON_CODE_EDITOR_HPP
